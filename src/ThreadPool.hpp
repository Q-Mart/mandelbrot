#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <memory>
#include <thread>
#include <future>
#include <stdexcept>
#include "Common.hpp"

// taken from github.com/progschj/ThreadPool

class ThreadPool
{
  public:
    ThreadPool(size_t);
    template<class F, class... Args>
      auto enque(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();

  private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    //sync variables
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads)
{
  stop = false;

  for (size_t i=0; i<threads; i++)
  {
    workers.emplace_back(
        [this]
        {
          while (true)
          {
            std::function<void()> task;

            //go into a scope so that when we leave, we release the mutex lock
            {
              std::unique_lock<std::mutex> lock(this->queue_mutex);

              auto shouldRunTask = [this]{ return this->stop || !this->tasks.empty();};

              this->cv.wait(lock, shouldRunTask);

              if (this->stop && this->tasks.empty())
              {
                return;
              }
              task = std::move(this->tasks.front());
              this->tasks.pop();
            }

            task();
          }
        }
    );
  }
}

template<class F, class... Args>
auto ThreadPool::enque(F&&f , Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
{
  using return_type = typename std::result_of<F(Args...)>::type;

  auto task = std::make_shared<std::packaged_task<return_type()>>(
    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
  );

  std::future<return_type> res = task->get_future();

  {
    std::unique_lock<std::mutex> lock(queue_mutex);

    if (stop)
      throw std::runtime_error("enqueue on stopped ThreadPool");

    tasks.emplace([task](){ (*task)(); });
  }
  cv.notify_one();
  return res;
}

inline ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }

  cv.notify_all();
  for (std::thread &worker: workers)
    worker.join();
}

#endif
