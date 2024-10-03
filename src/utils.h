#ifndef BLUE_MAX_UTILS_H
#define BLUE_MAX_UTILS_H

#include "stdlib.h"

long long time_ms(void);

double rand_0_1(void);

double rand_min_max(double min, double max);

double min_d(double a, double b);

double max_d(double a, double b);

double min_i(int a, int b);

double max_i(int a, int b);

size_t binary_search(const void* val, const void* array, size_t count, size_t size,
                  int (*comparator)(const void*, const void*));

#endif //BLUE_MAX_UTILS_H
