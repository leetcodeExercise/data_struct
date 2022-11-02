#include <iostream>
#include <string>
#include "src/p1.h"
#include "src/mutex_test.h"

int main()
{
    SharedMutex sMutex;
    NormalMutex nMutex;

    std::vector<std::thread> writers;
    std::vector<std::thread> readers;
    int writeThreadNum = 50;
    int readThreadNum = 200;
    std::string s = "sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    for (int i = 0; i < writeThreadNum; i++) {
        std::thread writer(&SharedMutex::write, &sMutex, s + std::to_string(i));
        writers.push_back(std::move(writer));
    }
    for (int i = 0; i < readThreadNum; i++) {
        std::thread reader(&SharedMutex::waitAndRead, &sMutex);
        readers.push_back(std::move(reader));
    }

    for (int i = 0; i < writeThreadNum; i++) {
        std::thread writer(&NormalMutex::write, &nMutex, s + std::to_string(i));
        writers.push_back(std::move(writer));
    }
    for (int i = 0; i < readThreadNum; i++) {
        std::thread reader(&NormalMutex::waitAndRead, &nMutex);
        readers.push_back(std::move(reader));
    }

    for (auto& thread : writers)
        if (thread.joinable())
            thread.join();
    for (auto& thread : readers)
        if (thread.joinable())
            thread.join();
    nMutex.timePrint();
    sMutex.timePrint();
    // return p1::TEST_P1();
}