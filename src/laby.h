#pragma once

#define LABY_MAX 24

enum class Status { Available, Route, BackTracked, Wall };

enum class ESWN { 
    Unknown = 0, 
    East = 1, 
    South = 2, 
    West = 3, 
    North = 4, 
    NoWay = 5 
};

struct Cell {
    int x, y;
    Status status;
    ESWN incoming, outgoing;
};

class Laby {
public:
    Cell laby[LABY_MAX][LABY_MAX];

    bool labyrinth(Cell laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t);
    ESWN nextESWN(ESWN eswn) { return ESWN(int(eswn) + 1); }
    Cell* neighbor(Cell* cell);
    Cell* advance(Cell* cell);
};