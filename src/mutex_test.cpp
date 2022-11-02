#include "mutex_test.h"

void SharedMutex::timePrint() const
{
    std::cout << "shared Mutex write time " << _writeTimeSum << " read time" << _readTimeSum 
    << " size " << size() <<std::endl;
}

SharedMutex::SharedMutex(const SharedMutex& origin)
{
    std::unique_lock<std::shared_mutex> lock(_mutex);
    _data = origin._data;
}

SharedMutex& SharedMutex::operator=(const SharedMutex& smx) 
{ 
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _data = smx._data;
    }
    return (*this);
}

std::string SharedMutex::waitAndRead() const
{
    auto start = Clock::now();
    auto waitTime = start + std::chrono::seconds(_waitTime);
    std::string data;
    while (Clock::now() < waitTime)
        if (read(data))
            break;
    
    auto end = Clock::now();
    auto duration = end - start;
    _readTimeSum += duration.count();
    return data;
}

bool SharedMutex::read(std::string& data) const
{
    std::shared_lock<std::shared_mutex> lock(_mutex);
    if (!_data.empty()) {
        data = _data.back();
        return true;
    } else 
        return false;       
}

void SharedMutex::write(const std::string& data)
{
    auto start = Clock::now();
    {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _data.push(data);
    }
    auto end = Clock::now();
    auto duration = end - start;
    _writeTimeSum += duration.count();
}

int SharedMutex::size() const
{
    std::shared_lock<std::shared_mutex> lock(_mutex);
    return _data.size();
}

void NormalMutex::timePrint()
{
    std::cout << "normal Mutex write time " << _writeTimeSum << " read time" << _readTimeSum 
    << " size " << size() <<std::endl;
}

int NormalMutex::size() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _data.size();
}

void NormalMutex::write(const std::string& data)
{
    auto start = Clock::now();
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _data.push(data);
    }
    _cv.notify_all();
    auto end = Clock::now();
    auto duration = end - start;
    _writeTimeSum += duration.count();
}

std::string NormalMutex::waitAndRead()
{
    auto start = Clock::now();
    std::string data;
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [this] { return !_data.empty(); });
        data = _data.back();
    }
    auto end = Clock::now();
    auto duration = end - start;
        _readTimeSum += duration.count();
    return data;
}

NormalMutex& NormalMutex::operator=(const NormalMutex& smx) 
{ 
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _data = smx._data;
    }
    return (*this);
}

NormalMutex::NormalMutex(const NormalMutex& origin)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _data = origin._data;
}
