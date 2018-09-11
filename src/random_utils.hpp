#include <cstdlib>

#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;

inline void random_seed(int seed) {
    srand(seed);
}

inline int random_int(int min, int max) { /* inclusive */
    int range = max-min+1;
    return min + (rand() % range);
}

inline double random_fraction() {
    return (double) rand() / RAND_MAX;
}

#endif /* UTILS_HPP */
