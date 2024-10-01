#include "utils.h"
#include "sys/time.h"

long long time_ms(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (long long) tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

double rand_0_1(void) {
  return (double) rand() / RAND_MAX;
}

double rand_min_max(double min, double max) {
  return min + ((double) rand() / RAND_MAX) * (max - min);
}

double min_d(double a, double b) {
  return a < b ? a : b;
}

double max_d(double a, double b) {
  return a > b ? a : b;
}

double min_i(int a, int b) {
  return a < b ? a : b;
}

double max_i(int a, int b) {
  return a > b ? a : b;
}

int binary_search(const void* val, const void* array, size_t count, size_t size,
                  int (*comparator)(const void*, const void*)) {
  const char* arr = (const char*) array;
  size_t left = 0, mid, right = count;
  while (left < right) {
    mid = left + (right - left) / 2;
    if (comparator(val, &arr[mid * size]) == 1) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}
