#ifndef BLUE_MAX_VECTOR_H
#define BLUE_MAX_VECTOR_H

typedef struct {
    double x;
    double y;
    double z;
} Vector;

Vector vector_create(double x, double y, double z);

Vector vector_sum(const Vector* v1, const Vector* v2);

Vector vector_multiply(const Vector* v, double scalar);

double vector_norm(const Vector* v);

Vector vector_normalize(const Vector* v);

double vector_dot_product(const Vector* v1, const Vector* v2);

Vector vector_cross_product(const Vector* v1, const Vector* v2);

void vector_print(const Vector* v);

#endif //BLUE_MAX_VECTOR_H
