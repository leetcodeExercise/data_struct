using Rank = int;

template<typename T> static bool It (T* a, T* b) {return It(*a, *b);}
template<typename T> static bool It (T& a, T& b) {return a < b;}
template<typename T> static bool eq (T* a, T* b) {return eq(*a, *b);}
template<typename T> static bool eq (T& a, T& b) {return a == b;}
