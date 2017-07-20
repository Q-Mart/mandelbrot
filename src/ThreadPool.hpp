#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>
#include "Common.hpp"

// taken from http://progsch.net/wordpress/?p=81

class ThreadPool
{
  friend class Worker;
  std::vector< std::thread > workers;
  std::deque< std::function<void()> > tasks;

  //sync variables
  std::mutex queue_mutex;
  std::condition_variable cv;
  bool stop;

  public:
    ThreadPool(size_t);
    template<class F>
      void enque(F f);
    ~ThreadPool();
};

class Worker
{
  ThreadPool& pool;

  public:
    Worker(ThreadPool& pool);
    void operator()();
};
