#include "src/mutex_test.h"

int main()
{ 
    // write read cost test
    std::vector<int64_t> dataBase;
    auto t1 = Clock::now();
    writeData(dataBase, 1);
    auto t2 = Clock::now();
    auto m1 = findMax(dataBase);
    auto t3 = Clock::now();
    writeData(dataBase, 2);
    auto t4 = Clock::now();
    auto m2 = findMax(dataBase);
    auto t5 = Clock::now();
    std::cout << "writeCost_1st " << duration(t1, t2) << " readCost_1st " << duration(t2, t3) 
              << " writeCost_2nd " << duration(t3, t4) << " readCost_2nd " << duration(t4, t5)
              << std::endl;

    // mutex cost test
    constexpr size_t loopCount = 1000;
    constexpr size_t readerCount = 40;
    constexpr size_t writerCount = 1;
    benchmark<SharedMutex>(loopCount, readerCount, writerCount);
    benchmark<NormalMutex>(loopCount, readerCount, writerCount);

    std::cout << m1 << " " << m2 << std::endl; // prevent optimization
    return 0;
}
