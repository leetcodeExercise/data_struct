#pragma once

using LABY_MAX = 24;
enum class Status { Available, Route, BackTracked, Wall };
enum class ESWN { Unknown, East, South, West, North, NoWay };


struct Cell {
    int x, y;
    Status status;
    ESWN incoming, outgoing;
};

class Laby {
public:
cell laby[LABY_MAX][LABY_MAX];

bool labyrinth(Cell laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t);
ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }
Cell* neighbor(Cell* cell);
Cell* advance(Cell* cell);
};