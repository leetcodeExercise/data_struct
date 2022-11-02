#include <cstdlib>
#include "stack.h"
#include "laby.h"

bool Laby::labyrinth(Cell laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t) {
    if ((s->status != Status::Available) || (t->status != Status::Available))
        return false;
    StackVector<Cell*> path;
    s->incoming = ESWN::Unknown;
    s->status = Status::Route;
    path.push(s);
    do {
        Cell* c = path.top();
        if (c == t) return true;
        while ((c->outgoing = nextESWN(c->outgoing)) < ESWN::NoWay)
            if (neighbor(c)->status == Status::Available) 
                break;
        if (c->outgoing >= ESWN::NoWay) {
            c->status = Status::BackTracked;
            c = path.pop();
        } else {
            path.push(c = advance(c));
            c->outgoing = ESWN::Unknown;
            c->status = Status::Route;
        } 
    } while (!path.empty());
    
    return false;
}

Cell* Laby::neighbor(Cell* cell) {
    switch (cell->outgoing) {
        case ESWN::East: return cell + LABY_MAX;
        case ESWN::South: return cell + 1;
        case ESWN::West: return cell - LABY_MAX;
        case ESWN::North: return cell - 1;
        default: std::exit(-1);
    }
}

Cell* Laby::advance(Cell* cell) {
    Cell* next;
    switch(cell->outgoing) {
        case ESWN::East: {
            next = cell + LABY_MAX;
            next->incoming = ESWN::West;
        }
        case ESWN::South: {
            next = cell + 1;
            next->incoming = ESWN::North;
        }
        case ESWN::West: {
            next = cell - LABY_MAX;
            next->incoming = ESWN::East;
        }
        case ESWN::North: {
            next = cell - 1;
            next->incoming = ESWN::South;
        }
        default: std::exit(-1);
    }
    return next;
}
