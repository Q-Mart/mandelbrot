#include "ThreadPool.hpp"

// taken from http://progsch.net/wordpress/?p=81

ThreadPool::ThreadPool(size_t threads)
{
  stop = false;
  for (size_t i=0; i<threads; i++)
  {
    workers.push_back(std::thread(Worker(*this)));
  }
}

ThreadPool::~ThreadPool()
{
  stop = true;
  cv.notify_all();

  for(size_t i=0; i<workers.size(); i++)
  {
    workers[i].join();
  }
}

template <class F>
void ThreadPool::enque(F f)
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    tasks.push_back(std::function<void()>(f));
  }
  cv.notify_one();
}

void Worker::operator()()
{
  std::function<void()> task;
  while (true)
  {
    {
      std::unique_lock<std::mutex> lock(pool.queue_mutex);

      while (!pool.stop and pool.tasks.empty())
      {
        pool.cv.wait(lock);
      }

      if (pool.stop)
      {
        return;
      }

      task = pool.tasks.front();
      pool.tasks.pop_front();
    }

    //going out of scope releases the lock
    
    task();
  }
}

int main()
{
  ThreadPool tp(10);

  for (int i=0; i<10; i++)
  {
    tp.enque([i]{ std::cout << "hello from " << i << std::endl; });
  }
}
