#pragma once

#include <chrono>
#include <atomic>
#include <iostream>
#include <shared_mutex>
#include <queue>
#include <condition_variable>

class SharedMutex {
public:
    using Clock = std::chrono::steady_clock;

    SharedMutex() = default;
    SharedMutex(const SharedMutex& origin);

    SharedMutex& operator=(const SharedMutex& smx);

    std::string waitAndRead() const;
    bool read(std::string& data) const;
    void write(const std::string& data);
    int size() const;
    void timePrint() const;
    
private:
    long long _waitTime = 10;
    mutable std::shared_mutex _mutex;
    std::queue<std::string> _data;
    mutable std::atomic<long long> _writeTimeSum;
    mutable std::atomic<long long> _readTimeSum;
};

class NormalMutex {
public:
    using Clock = std::chrono::steady_clock;

    NormalMutex() = default;
    NormalMutex(const NormalMutex& origin);

    NormalMutex& operator=(const NormalMutex& smx);

    std::string waitAndRead();
    void write(const std::string& data);
    int size() const;
    void timePrint();

private:
    std::condition_variable _cv;
    mutable std::mutex _mutex;
    std::queue<std::string> _data;
    mutable std::atomic<long long> _writeTimeSum;
    mutable std::atomic<long long> _readTimeSum;
};