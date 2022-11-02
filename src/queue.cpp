#include <cstdlib>
#include "list.h"
#include "queue.h"

struct Customer {
    int window;
    unsigned int time;
};

class Simulation {
public:
    void simulate(int nWin, int servTime);
    int bestWindow(Queue<Customer> windows[], int nWin);
};
void Simulation::simulate(int nWin, int servTime) {
    Queue<Customer>* windows = new Queue<Customer>[nWin];
    for (int now = 0; now < servTime; now++) {
        if (std::rand() % (1 + nWin)) {
            Customer c;
            c.time = 1 + std::rand() % 98;
            c.window = bestWindow(windows, nWin);
            windows[c.window].enqueue(c);
        }
        for (int i = 0; i < windows->size(); i++) {
            if (!windows[i].empty())
                if (--windows[i].front().time <= 0)
                    windows[i].dequeue();
        }
    }

    delete[] windows;
}
int Simulation::bestWindow(Queue<Customer> windows[], int nWin) {
    int minSize = windows[0].size();
    int optiWin = 0;
    for (int i = 1; i < nWin; i++) {
        if (minSize > windows[i].size()) {
            minSize = windows[i].size();
            optiWin = i;
        }
    }

    return optiWin;
}