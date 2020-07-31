#include <stddef.h>
#include <stdlib.h>
#include "edge_decomposition.h"
#include "isosurface.h"

struct surface edge_isosurface(double isovalue, double o_x, double o_y, double o_z, double l, size_t max_idx, double ***values){

    size_t r = max_idx + 1;
    size_t n_vert = r * r * r;
    size_t v_end = n_vert * 9 * 3;
    double *edge_intercep = (double *) calloc(v_end, sizeof(double));

    size_t n_tetrahedra = max_idx * max_idx * max_idx * 5;
    size_t *faces = (size_t *) calloc(n_tetrahedra * 2 * 3, sizeof(size_t));
    size_t f_end = 0;

    int i, j, k;
    for (i = 0; i < max_idx; i++)
        for (j = 0; j < max_idx; j++)
            for (k = 0; k < max_idx; k++){
                f_end = edge_decomposition(isovalue, r, faces , f_end, edge_intercep, o_x, o_y, o_z, l, i, j, k, values);
            }

    faces = realloc(faces, f_end);

    return (struct surface) {
         f_end,
         v_end,
         faces,
         edge_intercep
     };
}
