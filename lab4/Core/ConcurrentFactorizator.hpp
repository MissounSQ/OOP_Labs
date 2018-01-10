
#ifndef LAB4_CONCURENTFACTORIZATOR_HPP
#define LAB4_CONCURENTFACTORIZATOR_HPP

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Factorizator.hpp"
#include "Input.hpp"
#include "Threadpool.hpp"
#include "Output.hpp"
#include "ConcurrentQueue.hpp"
#include "../Algorithm/Pollard_Rho_Brent.hpp"
#include <vector>


template<class T>
class ConcurrentFactorizator {
public:
    ConcurrentFactorizator(std::istream &inputStream, std::ofstream &outputStream, size_t poolSize)
            : input(inputStream), output(outputStream), threadPool(poolSize + 2), reader(inputStream),
              writer(outputStream), pause(false), disabled(false) {};

    ~ConcurrentFactorizator() = default;

    void run() {
        std::future<void> producer = threadPool.addTaskToPool([this]() { reader.readStream(queue); });
        std::future<void> pauser = threadPool.addTaskToPool([this]() {
            std::string comm;
            while (!queue.isEmpty() || !reader.done) {
                if (comm == "pause" && !disabled)
                    pauseSystem();
                if (comm == "resume" && !disabled)
                    resumeSystem();
                if (comm == "exit") {
                    exitSystem();
                    break;
                }
            }
            std::cout << "Pauser is finishing" << std::endl;
        });
        bool a = queue.isEmpty();
        while(true) {
            std::future<void> factors;

            if(!queue.isEmpty()) {
                std::unique_lock<std::mutex> locker(mutex_);
                pauseCondition.wait(locker, [this](){return !pause;});

                factors = threadPool.addTaskToPool([this](){
                    T val = queue.pop();
                    std::vector<T> vec = Factorizator::factorize<Pollard_Brent>(val);
                    writer.writeStream(vec);
                });
                factors.get();
            }
            if(queue.isEmpty() && reader.done) {
                std::cout << "Queue now is empty, finishing..."   << std::endl;
                break;
            }
            if(disabled) {
                std::cout << "Queue now is empty, finishing..." << std::endl;
                break;
            }
        }

    }
    void pauseSystem()
    {
        {
            std::unique_lock<std::mutex> locker (mutex_);
            std::cout << "Pausing..." << std::endl;
            pause = true;
        }
        pauseCondition.notify_all();
    }
    void resumeSystem()
    {
        {
            std::unique_lock<std::mutex> locker(mutex_);
            std::cout << "Resuming..." << std::endl;
            pause = false;
        }
        pauseCondition.notify_all();
    }
    void exitSystem()
    {
        std::unique_lock<std::mutex> locker(mutex_);
        std::cout << "Exiting..." << std::endl;
        disabled = true;
        pause = false;
        reader.done = true;
    }

private:
    std::condition_variable pauseCondition;
    std::istream &input;
    std::ofstream &output;
    ConcurrentQueue<T> queue;
    ThreadPool threadPool;
    std::mutex mutex_;
    Input reader;
    Output writer;
    bool pause;
    bool disabled;

};

#endif //LAB4_CONCURENTFACTORIZATOR_HPP
