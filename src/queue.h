#include "list.h"

template<typename T>
class Queue : public List<T> {
public:
    void enqueue(const T& e) { insertAsLast(e); }
    T dequeue() { return remove(first()); }
    T& front() { return first()->data; }
};

struct Customer {
    int window;
    unsigned int time;
};

class Simulation {
public:
    void simulate(int nWin, int servTime);
    int bestWindow(Queue<Customer> windows[], int nWin);
};