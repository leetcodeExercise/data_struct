#pragma once

struct Queen {
	int x;
	int y;
	Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {}
	bool operator== (const Queen& q) const {
		return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || ( x - y == q.x - q.y);  
	}
	bool operator!= (const Queen& q) const { return !(*this == q); }
};

enum class RunMode { Continuous, Step };

class QueenGame {
public:
    RunMode runMode;
    int nSolu;
    int nCheck;

    void placeQueen(int);
    // void displayRow(Queen& q, int);
    // void displayProgress(StackVector<Queen>& S, int);
};