#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::high_resolution_clock::time_point;

std::chrono::microseconds duration(const TimePoint& t1, const TimePoint& t2);

void writeData(std::vector<int64_t>& dataBase, int64_t data);
int64_t findMax(const std::vector<int64_t>& dataBase);

class SharedMutex {
public:
    int64_t read() const;
    void write(int64_t data);
    
private:
    mutable std::shared_mutex _mutex;
    mutable std::condition_variable_any _cv;
    std::vector<int64_t> _dataBase;
};

class NormalMutex {
public:
    int64_t read() const;
    void write(int64_t data);

private:
    mutable std::mutex _mutex;
    mutable std::condition_variable _cv;
    std::vector<int64_t> _dataBase;
};

enum class Operation { Read, Write };

template<typename MutexT>
class MutexBenchmark {
public:
    MutexBenchmark(size_t loopCount, size_t readerCount, size_t writerCount) : 
        _loopCount(loopCount), _readerCount(readerCount), _writerCount(writerCount) {}

    void printTimeCost() 
    {
        std::cout << "Mutex type:" << typeid(MutexT).name() << " Loop count: " << _loopCount
        << " readerCount " << _readerCount << " writerCount " << _writerCount
        << " Reading time cost(us): " << _readerTimeCostUs.load() << " Writing time cost(us): " 
        << _writerTimeCostUs.load() << std::endl;
    }

    void run(Operation op) 
    {
        const auto startTime = Clock::now();

        for (size_t i = 0; i < _loopCount; ++i) {
            if (op == Operation::Read) {
                _mutex.read();
            } else {
                _mutex.write(i);
            }
        }

        const auto timeCostUs = duration(startTime, Clock::now()).count();
        if (op == Operation::Read) {
            _readerTimeCostUs += timeCostUs;
        }  else {
            _writerTimeCostUs += timeCostUs;
        }
    }

private:
    const size_t _loopCount;
    const size_t _readerCount;
    const size_t _writerCount;
    MutexT _mutex;
    std::atomic_int64_t _readerTimeCostUs{};
    std::atomic_int64_t _writerTimeCostUs{};
};

template<typename MutexT>
void benchmark(size_t loopCount, size_t readerCount, size_t writerCount)
{
    MutexBenchmark<MutexT> bm(loopCount, readerCount, writerCount);
    {
        std::vector<std::jthread> readers;
        readers.reserve(readerCount);
        std::vector<std::jthread> writers;
        writers.reserve(writerCount);

        for (size_t i = 0; i < readerCount; i++) {
            readers.emplace_back([&] { bm.run(Operation::Read); });
        }
        for (size_t i = 0; i < writerCount; i++) {
            writers.emplace_back([&] { bm.run(Operation::Write); });
        }
    }
    bm.printTimeCost();
}
