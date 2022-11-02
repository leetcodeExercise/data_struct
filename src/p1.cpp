#include <iostream>
#include <cstdlib>
#include "p1.h"
#include "algorithm"

namespace p1 {
int sumI(int A[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += A[i];
	return sum;
}

int sum(int A[], int n)
{
	if (1 > n)
		return 0;
	else
		return sum(A, n - 1) + A[n - 1];
}

int sum(int A[], int lo, int hi)
{
	if (hi - lo < 2)
		return A[lo];
	int mi = (lo + hi) >> 1;
	return sum(A, lo, mi) + sum(A, mi, hi);
}

void shuffle(int A[], int n)
{
	for (; 1 < n; --n)
		std::swap(A[rand() % n], A[n - 1]);
}

void shuffle(int A[], int lo, int hi)
{
	shuffle(A + lo, hi - lo);
}

void reverse1(int* A, int lo, int hi)
{
	while (lo < hi)
		std::swap(A[lo++], A[hi--]);
}

void reverse(int* A, int n)
{
	reverse1(A, 0, n - 1);
}

void bubblesort(int A[], int n)
{
	int cmp = 0;
	int swp = 0;

	while (n--)
	{
		for (int i = 0; i < n; i++)
		{
			if (A[i] > A[i + 1])
			{
				std::swap(A[i], A[i + 1]);
				swp++;
			}
			cmp++;
		}
	}
	std::cout << "cmp " << cmp << " swp " << swp << std::endl;
}

void bubblessort1A(int A[], int n)
{
	int cmp = 0;
	int swp = 0;
	bool sorted = false;
	while ( !sorted )
	{
		sorted = true;
		for (int i = 1; i < n; i++)
		{
			if (A[i - 1] > A[i]) {
				std::swap(A[i - 1], A[i]);
				sorted = false;
				swp++;
			}
			cmp++;
		}
		n--;
	}
	std::cout << "cmp " << cmp << " swp " << swp << std::endl;
}

void bubblesort1B(int A[], int n)
{
	int cmp = 0;
	int swp = 0;
	for (bool sorted = false; sorted != true; n--)
	{
		sorted = true;
		for (int i = 1; i < n; i++)
		{
			if (A[i - 1] > A[i])
			{
				std::swap(A[i - 1], A[i]);
				sorted = false;
				swp++;
			}
			cmp++;
		}
	}
	std::cout << "cmp " << cmp << " swp " << swp << std::endl;
}

void bubblesort2(int A[], int n)
{
	int cmp = 0;
	int swp = 0;
	for (int m; 1 < n; n = m)
	{
		for (int i = m = 1; i < n; i++)
		{
			if (A[i - 1] > A[i])
			{
				std::swap(A[i - 1], A[i]);
				m = i;
				swp++;
			}
			cmp++;
		}
	}
	std::cout << "cmp " << cmp << " swp " << swp << std::endl;
}
int64_t sqr(int64_t a) { return a * a; }

int64_t fib(int n) { return (2 > n) ? (__int64)n : fib(n - 1) + fib(n - 2); }

int64_t powerBF(int64_t a, int n)
{
	int64_t pow = 1;
	while (0 < n)
	{
		pow *= a;
		n--;
	}
	return pow;
}

int64_t power(int64_t a, int n)
{
	int64_t pow = 1;
	int64_t p = a;
	while (0 < n)
	{
		if (n & 1)
			pow *= p;
		n >>= 1;
		p *= p;
	}
	return pow;
}

int64_t power2BF_1(int n)
{
	int64_t pow = 1;
	while (0 < n--)
		pow <<= 1;
	return pow;
}

int64_t power2BF(int n)
{
	return (1 > n) ? 1 : power2BF(n - 1) << 1;
}

int64_t power2_1(int n)
{
	int64_t pow = 1;
	int64_t p = 2;
	while (0 < n)
	{
		if (n & 1)
			pow *= p;
		n >>= 1;
		p *= p;
	}
	return pow;
}

int64_t power2(int n)
{
	if (0 == n)
		return 1;
	return (n & 1) ? sqr(power2(n >> 1)) << 1 : sqr(power2(n >> 1));
}

int64_t fib1(int n)
{
	int64_t f = 1;
	int64_t g = 0;
	while (0 < n--)
	{
		g += f;
		f = g - f;
	}
	return g;
}

int64_t fib(int n, int64_t& prev)
{
	if (0 == n)
	{
		prev = 1;
		return 0;
	}
	else {
		int64_t prevPrev;
		prev = fib(n - 1, prevPrev);
		return prevPrev + prev;
	}
}

Fib::Fib(int n) 
{
    f = 1;
    g = 0;
    while (g < n)
        next();
}

int Fib::next()
{
    g += f;
    f = g - f;
    return g;
}

int Fib::prev()
{
    f = g - f;
    g -= f;
    return g;
}

void print(int A[], int lo, int hi)
{
	std::cout << "A:";
	for (int i = lo; i < hi; i++)
		std::cout << ", " << A[i];
	std::cout << std::endl;
}

int TEST_P1()
{
	std::cout << "Hello CMake." << std::endl;
	int A[] = {5, 2, 7, 4, 6, 3, 1};
	int n = 7;
	print(A, 0, n);

	std::cout << "sumI: " << p1::sumI(A, n) << std::endl;
	std::cout << "sumI: " << sum(A, n) << std::endl;
	std::cout << "sumI: " << sum(A, 0, n) << std::endl;

	shuffle(A, 0, n);
	print(A, 0, n);

	reverse(A, n);
	print(A, 0, n);

	bubblesort1B(A, n);
	print(A, 0, n);

	shuffle(A, 0, n);
	print(A, 0, n);
	bubblesort2(A, n);
	print(A, 0, n);

	int64_t a = 4;
	int r = 3;
	std::cout << "power2BF_1 " << power2BF_1(r) << " power2_1 " << power2_1(r) << std::endl;
	std::cout << "power2BF " << power2BF(r) << " power2 " << power2(r) << std::endl;
	std::cout << "powerBF " << powerBF(a, r) << " power " << power(a, r) << std::endl;

	Fib f(0);
	for (int i = 0; i < n; i++, f.next())
		std::cout << "FibClass " << i << " " << f.get() << std::endl;
	std::cout << "prev" << std::endl;
	for (int i = 0; i <= n; i++, f.prev())
		std::cout << "FibClass " << n - i << " " << f.get() << std::endl;

	for (int i = 0; i < n; i++)
		std::cout << "fib1 " << i << " " << fib1(i) << std::endl;
	for (int i = 0; i < n; i++)
	{
		int64_t f;
		std::cout << "fib " << i << " " << fib(i, f) << std::endl;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << "fib " << i << " " << fib(i) << std::endl;
	}
	return 0;
}
}
