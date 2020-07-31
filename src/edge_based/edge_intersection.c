#include <stddef.h>
void intersect_edge(double isovalue, double *edge_intercept, const double *v0, const double *v1, size_t r)
{
    double a = v0[3];
    double b = v1[3];

    /* 
        This assertion should never happen if the parent function is working, it is here for
        debugging and should be removed in release builds.
    */
    assert(a != b && "intersect_vertices called for vertices of equal intensity!");

    double interp = (isovalue - a) / (b - a);
    edge_intercept[0] = v0[0] * (1 - interp) + v1[0] * interp;
    edge_intercept[1] = v0[1] * (1 - interp) + v1[1] * interp;
    edge_intercept[2] = v0[2] * (1 - interp) + v1[2] * interp;
}
