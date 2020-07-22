#ifndef T_UTILS

#define T_UTILS
struct TPoint{
    double x, y, z;
    double prty;
};

struct Tetrahedron{
    struct TPoint v0, v1, v2, v3;
};

struct T6Cube{

    struct Tetrahedron t0, t1, t2, t3, t4, t5;
};

struct T5Cube{

    struct Tetrahedron t0, t1, t2, t3, t4;
};

int same_cube_decomposition(struct T6Cube *c1, struct T6Cube *c2);
int same_cube5_decomposition(struct T5Cube *c1, struct T5Cube *c2);
int same_tetrahedron(struct Tetrahedron *expected, struct Tetrahedron *result);

#endif
