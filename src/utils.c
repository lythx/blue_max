#include "utils.h"
#include "sys/time.h"
#include "stdlib.h"

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