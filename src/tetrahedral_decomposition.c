#include <stdlib.h>

#include <tetrahedral_decomposition.h>
#include <tetrahedral_utils.h>

struct T6Cube* decompose_domain(double o_x, double o_y, double o_z, double l, double domain_l){

    size_t max_idx = (size_t) domain_l / l;
    struct T6Cube* decomposition = (struct T6Cube*) calloc(max_idx * max_idx * max_idx, sizeof(struct T6Cube));
    int i, j, k;
    for (i = 0; i < max_idx; i++)
        for (j = 0; j < max_idx; j++)
            for (k = 0; k < max_idx; k++){
                int idx = i + j * max_idx + k * (max_idx * max_idx);
                cube_decomposition(&(decomposition[idx]), o_x, o_y, o_z, l, i, j, k);
            }

    return decomposition;
}

void cube_decomposition(struct T6Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k){

    double x0, y0, z0;
    x0 = o_x + i * l;
    y0 = o_y + j * l;
    z0 = o_z + k * l;


    //tetrahedron 0
    c_decom->t0.v0.x = x0;
    c_decom->t0.v0.y = y0;
    c_decom->t0.v0.z = z0;
    c_decom->t0.v1.x = x0 + l;
    c_decom->t0.v1.y = y0;
    c_decom->t0.v1.z = z0;
    c_decom->t0.v2.x = x0;
    c_decom->t0.v2.y = y0 + l;
    c_decom->t0.v2.z = z0;
    c_decom->t0.v3.x = x0 + l;
    c_decom->t0.v3.y = y0;
    c_decom->t0.v3.z = z0 + l;
                      
    //tetrahedron 1
    c_decom->t1.v0.x = x0 + l;
    c_decom->t1.v0.y = y0;
    c_decom->t1.v0.z = z0;
    c_decom->t1.v1.x = x0 + l;
    c_decom->t1.v1.y = y0 + l;
    c_decom->t1.v1.z = z0;
    c_decom->t1.v2.x = x0;
    c_decom->t1.v2.y = y0 + l;
    c_decom->t1.v2.z = z0;
    c_decom->t1.v3.x = x0 + l;
    c_decom->t1.v3.y = y0;
    c_decom->t1.v3.z = z0 + l;
                      
    //tetrahedron 2
    c_decom->t2.v0.x = x0;
    c_decom->t2.v0.y = y0;
    c_decom->t2.v0.z = z0;
    c_decom->t2.v1.x = x0;
    c_decom->t2.v1.y = y0 + l;
    c_decom->t2.v1.z = z0;
    c_decom->t2.v2.x = x0;
    c_decom->t2.v2.y = y0;
    c_decom->t2.v2.z = z0 + l;
    c_decom->t2.v3.x = x0 + l;
    c_decom->t2.v3.y = y0;
    c_decom->t2.v3.z = z0 + l;
                      
    //tetrahedron 3
    c_decom->t3.v0.x = x0 + l;
    c_decom->t3.v0.y = y0 + l;
    c_decom->t3.v0.z = z0;
    c_decom->t3.v1.x = x0;
    c_decom->t3.v1.y = y0 + l;
    c_decom->t3.v1.z = z0;
    c_decom->t3.v2.x = x0 + l;
    c_decom->t3.v2.y = y0;
    c_decom->t3.v2.z = z0 + l;
    c_decom->t3.v3.x = x0 + l;
    c_decom->t3.v3.y = y0 + l;
    c_decom->t3.v3.z = z0 + l;
                      
    //tetrahedron 4
    c_decom->t4.v0.x = x0;
    c_decom->t4.v0.y = y0 + l;
    c_decom->t4.v0.z = z0;
    c_decom->t4.v1.x = x0 + l;
    c_decom->t4.v1.y = y0;
    c_decom->t4.v1.z = z0 + l;
    c_decom->t4.v2.x = x0 + l;
    c_decom->t4.v2.y = y0 + l;
    c_decom->t4.v2.z = z0 + l;
    c_decom->t4.v3.x = x0;
    c_decom->t4.v3.y = y0 + l;
    c_decom->t4.v3.z = z0 + l;
                      
    //tetrahedron 5
    c_decom->t5.v0.x = x0;
    c_decom->t5.v0.y = y0 + l;
    c_decom->t5.v0.z = z0;
    c_decom->t5.v1.x = x0;
    c_decom->t5.v1.y = y0;
    c_decom->t5.v1.z = z0 + l;
    c_decom->t5.v2.x = x0 + l;
    c_decom->t5.v2.y = y0;
    c_decom->t5.v2.z = z0 + l;
    c_decom->t5.v3.x = x0;
    c_decom->t5.v3.y = y0 + l;
    c_decom->t5.v3.z = z0 + l;

}
