#ifndef BLUE_MAX_VECTOR_H
#define BLUE_MAX_VECTOR_H

typedef struct {
    double x;
    double y;
    double z;
} Vector;

Vector vector_create(double x, double y, double z);

Vector vector_copy(const Vector* v);

void vector_negate(Vector* v);

void vector_sum(Vector* v1, const Vector* v2);

void vector_subtract(Vector* v1, const Vector* v2);

void vector_multiply(Vector* v, double scalar);

double vector_norm(const Vector* v);

void vector_normalize(Vector* v);

double vector_dot(const Vector* v1, const Vector* v2);

void vector_cross(Vector* v1, const Vector* v2);

void vector_rotate(Vector* v);

void vector_rotate_about_origin(Vector* to_rotate, const Vector* origin);

double vector_point_distance(const Vector* v1, const Vector* v2);

void vector_print(const Vector* v);

#endif //BLUE_MAX_VECTOR_H
