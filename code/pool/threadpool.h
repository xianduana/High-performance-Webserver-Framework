/*
 * @Author       : xianduana
 * @Date         : 2024-02
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount = 8): pool_(std::make_shared<Pool>()) {
            assert(threadCount > 0);
            //创建threadCount个子线程
            for(size_t i = 0; i < threadCount; i++) {
                std::thread([pool = pool_] {
                    std::unique_lock<std::mutex> locker(pool->mtx);
                    while(true) {
                        //判断任务队列不为空
                        if(!pool->tasks.empty()) {
                            //从任务队列里取第一个任务
                            auto task = std::move(pool->tasks.front());
                            pool->tasks.pop();
                            //加锁，解锁
                            locker.unlock();
                            //任务执行的代码
                            task();
                            locker.lock();
                        } 
                        //判断池子是否关闭
                        else if(pool->isClosed) break;
                        else pool->cond.wait(locker);//阻塞
                    }
                }).detach();//线程分离
            }
    }

    ThreadPool() = default;

    ThreadPool(ThreadPool&&) = default;
    
    ~ThreadPool() {
        if(static_cast<bool>(pool_)) {
            {
                std::lock_guard<std::mutex> locker(pool_->mtx);
                pool_->isClosed = true;
            }
            pool_->cond.notify_all();
        }
    }

    template<class F>
    void AddTask(F&& task) {//从池子里添加一个任务
        {
            std::lock_guard<std::mutex> locker(pool_->mtx);
            pool_->tasks.emplace(std::forward<F>(task));
        }
        pool_->cond.notify_one();//唤醒一个线程
    }

private:
//定义了一个池子里面的信息，结构体
    struct Pool {
        std::mutex mtx;//互斥锁
        std::condition_variable cond;//条件变量
        bool isClosed;//是否关闭
        std::queue<std::function<void()>> tasks;//队列，保存任务
    };
    std::shared_ptr<Pool> pool_;//线程池
};


#endif //THREADPOOL_H