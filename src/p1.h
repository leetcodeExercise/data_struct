#pragma once
#include <stdint.h>

namespace p1{
int sumI(int A[], int n);
int sum(int A[], int n);
int sum(int A[], int lo, int hi);

void shuffle(int A[], int n);
void shuffle(int A[], int lo, int hi);

void reverse1(int* A, int lo, int hi);
void reverse(int* A, int n);

void bubblesort(int A[], int n);
void bubblessort1A(int A[], int n);
void bubblesort1B(int A[], int n);
void bubblesort2(int A[], int n);

int64_t powerBF(int64_t a, int n);
int64_t power(int64_t a, int n);
int64_t power2BF_1(int n);
int64_t power2BF(int n);
int64_t power2_1(int n);
int64_t power2(int n);

int64_t sqr(int64_t a);

int64_t fib1(int n);
int64_t fib(int n);
int64_t fib(int n, int64_t& prev);

class Fib {
public:
	Fib(int n);

	int get() const { return g; }
	int next();
	int prev();
private:
	int f;
	int g;
};

void print(int A[], int lo, int hi);
int TEST_P1();
}
