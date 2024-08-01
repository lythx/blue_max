#ifndef BLUE_MAX_VECTOR_H
#define BLUE_MAX_VECTOR_H

typedef struct {
    double x;
    double y;
    double z;
} vector;

vector vector_create(double x, double y, double z);

vector vector_sum(const vector* v1, const vector* v2);

vector vector_multiply(const vector* v, double scalar);

double vector_norm(const vector* v);

vector vector_normalize(const vector* v);

double vector_dot_product(const vector* v1, const vector* v2);

vector vector_cross_product(const vector* v1, const vector* v2);

void vector_print(const vector* v);

#endif //BLUE_MAX_VECTOR_H
