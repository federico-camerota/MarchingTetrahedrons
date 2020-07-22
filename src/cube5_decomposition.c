#include <stdlib.h>

#include <tetrahedral_decomposition.h>
#include <tetrahedral_utils.h>

void cube5_decomposition(struct T5Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values){

    int parity = (i + j + k) % 2;

    if (parity){

        cube5_odd_decomposition(c_decom, o_x, o_y, o_z, l, i, j, k, values);
    }
    else{
        cube5_even_decomposition(c_decom, o_x, o_y, o_z, l, i, j, k, values);
    }
}


void cube5_even_decomposition(struct T5Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values){
    size_t i1, j1, k1;
    i1 = i + 1;
    j1 = j + 1;
    k1 = k + 1;

    double x0, y0, z0;
    x0 = o_x + i * l;
    y0 = o_y + j * l;
    z0 = o_z + k * l;

    double x1, y1, z1;
    x1 = x0 + l;
    y1 = y0 + l;
    z1 = z0 + l;

    //tetrahedron 0
    c_decom->t0.v0.x = x0;
    c_decom->t0.v0.y = y0;
    c_decom->t0.v0.z = z0;
    c_decom->t0.v0.prty = values[i][j][k];

    c_decom->t0.v1.x = x1;
    c_decom->t0.v1.y = y0;
    c_decom->t0.v1.z = z0;
    c_decom->t0.v1.prty = values[i1][j][k];

    c_decom->t0.v2.x = x0;
    c_decom->t0.v2.y = y1;
    c_decom->t0.v2.z = z0;
    c_decom->t0.v2.prty = values[i][j1][k];

    c_decom->t0.v3.x = x0;
    c_decom->t0.v3.y = y0;
    c_decom->t0.v3.z = z1;
    c_decom->t0.v3.prty = values[i][j][k1];
                      
    //tetrahedron 1
    c_decom->t1.v0.x = x1;
    c_decom->t1.v0.y = y1;
    c_decom->t1.v0.z = z0;
    c_decom->t1.v0.prty = values[i1][j1][k];

    c_decom->t1.v1.x = x0;
    c_decom->t1.v1.y = y1;
    c_decom->t1.v1.z = z0;
    c_decom->t1.v1.prty = values[i][j1][k];

    c_decom->t1.v2.x = x1;
    c_decom->t1.v2.y = y0;
    c_decom->t1.v2.z = z0;
    c_decom->t1.v2.prty = values[i1][j][k];

    c_decom->t1.v3.x = x1;
    c_decom->t1.v3.y = y1;
    c_decom->t1.v3.z = z1;
    c_decom->t1.v3.prty = values[i1][j1][k1];
                      
    //tetrahedron 2
    c_decom->t2.v0.x = x1;
    c_decom->t2.v0.y = y0;
    c_decom->t2.v0.z = z1;
    c_decom->t2.v0.prty = values[i1][j][k1];

    c_decom->t2.v1.x = x0;
    c_decom->t2.v1.y = y0;
    c_decom->t2.v1.z = z1;
    c_decom->t2.v1.prty = values[i][j][k1];

    c_decom->t2.v2.x = x1;
    c_decom->t2.v2.y = y1;
    c_decom->t2.v2.z = z0;
    c_decom->t2.v2.prty = values[i1][j1][k];

    c_decom->t2.v3.x = x1;
    c_decom->t2.v3.y = y0;
    c_decom->t2.v3.z = z0;
    c_decom->t2.v3.prty = values[i1][j][k];
                      
    //tetrahedron 3
    c_decom->t3.v0.x = x0;
    c_decom->t3.v0.y = y1;
    c_decom->t3.v0.z = z1;
    c_decom->t3.v0.prty = values[i][j1][k1];

    c_decom->t3.v1.x = x1;
    c_decom->t3.v1.y = y1;
    c_decom->t3.v1.z = z1;
    c_decom->t3.v1.prty = values[i1][j1][k1];

    c_decom->t3.v2.x = x0;
    c_decom->t3.v2.y = y0;
    c_decom->t3.v2.z = z1;
    c_decom->t3.v2.prty = values[i][j][k1];

    c_decom->t3.v3.x = x0;
    c_decom->t3.v3.y = y1;
    c_decom->t3.v3.z = z0;
    c_decom->t3.v3.prty = values[i][j1][k];
                      
    //tetrahedron 4
    c_decom->t4.v0.x = x1;
    c_decom->t4.v0.y = y0;
    c_decom->t4.v0.z = z0;
    c_decom->t4.v0.prty = values[i1][j][k];

    c_decom->t4.v1.x = x0;
    c_decom->t4.v1.y = y1;
    c_decom->t4.v1.z = z0;
    c_decom->t4.v1.prty = values[i][j1][k];

    c_decom->t4.v2.x = x0;
    c_decom->t4.v2.y = y0;
    c_decom->t4.v2.z = z1;
    c_decom->t4.v2.prty = values[i][j][k1];

    c_decom->t4.v3.x = x1;
    c_decom->t4.v3.y = y1;
    c_decom->t4.v3.z = z1;
    c_decom->t4.v3.prty = values[i1][j1][k1];
}

void cube5_odd_decomposition(struct T5Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values){

    size_t i1, j1, k1;
    i1 = i + 1;
    j1 = j + 1;
    k1 = k + 1;

    double x0, y0, z0;
    x0 = o_x + i * l;
    y0 = o_y + j * l;
    z0 = o_z + k * l;

    double x1, y1, z1;
    x1 = x0 + l;
    y1 = y0 + l;
    z1 = z0 + l;

    //tetrahedron 0
    c_decom->t0.v0.x = x1;
    c_decom->t0.v0.y = y0;
    c_decom->t0.v0.z = z0;
    c_decom->t0.v0.prty = values[i1][j][k];

    c_decom->t0.v1.x = x0;
    c_decom->t0.v1.y = y0;
    c_decom->t0.v1.z = z0;
    c_decom->t0.v1.prty = values[i][j][k];

    c_decom->t0.v2.x = x1;
    c_decom->t0.v2.y = y1;
    c_decom->t0.v2.z = z0;
    c_decom->t0.v2.prty = values[i1][j1][k];

    c_decom->t0.v3.x = x1;
    c_decom->t0.v3.y = y0;
    c_decom->t0.v3.z = z1;
    c_decom->t0.v3.prty = values[i1][j][k1];
                      
    //tetrahedron 1
    c_decom->t1.v0.x = x0;
    c_decom->t1.v0.y = y1;
    c_decom->t1.v0.z = z0;
    c_decom->t1.v0.prty = values[i][j1][k];

    c_decom->t1.v1.x = x1;
    c_decom->t1.v1.y = y1;
    c_decom->t1.v1.z = z0;
    c_decom->t1.v1.prty = values[i1][j1][k];

    c_decom->t1.v2.x = x0;
    c_decom->t1.v2.y = y0;
    c_decom->t1.v2.z = z0;
    c_decom->t1.v2.prty = values[i][j][k];

    c_decom->t1.v3.x = x0;
    c_decom->t1.v3.y = y1;
    c_decom->t1.v3.z = z1;
    c_decom->t1.v3.prty = values[i][j1][k1];
                      
    //tetrahedron 2
    c_decom->t2.v0.x = x0;
    c_decom->t2.v0.y = y0;
    c_decom->t2.v0.z = z1;
    c_decom->t2.v0.prty = values[i][j][k1];

    c_decom->t2.v1.x = x1;
    c_decom->t2.v1.y = y0;
    c_decom->t2.v1.z = z1;
    c_decom->t2.v1.prty = values[i1][j][k1];

    c_decom->t2.v2.x = x0;
    c_decom->t2.v2.y = y1;
    c_decom->t2.v2.z = z1;
    c_decom->t2.v2.prty = values[i][j1][k1];

    c_decom->t2.v3.x = x0;
    c_decom->t2.v3.y = y0;
    c_decom->t2.v3.z = z0;
    c_decom->t2.v3.prty = values[i][j][k];
                      
    //tetrahedron 3
    c_decom->t3.v0.x = x1;
    c_decom->t3.v0.y = y1;
    c_decom->t3.v0.z = z1;
    c_decom->t3.v0.prty = values[i1][j1][k1];

    c_decom->t3.v1.x = x0;
    c_decom->t3.v1.y = y1;
    c_decom->t3.v1.z = z1;
    c_decom->t3.v1.prty = values[i][j1][k1];

    c_decom->t3.v2.x = x1;
    c_decom->t3.v2.y = y0;
    c_decom->t3.v2.z = z1;
    c_decom->t3.v2.prty = values[i1][j][k1];

    c_decom->t3.v3.x = x1;
    c_decom->t3.v3.y = y1;
    c_decom->t3.v3.z = z0;
    c_decom->t3.v3.prty = values[i1][j1][k];
                      
    //tetrahedron 4
    c_decom->t4.v0.x = x0;
    c_decom->t4.v0.y = y0;
    c_decom->t4.v0.z = z0;
    c_decom->t4.v0.prty = values[i][j][k];

    c_decom->t4.v1.x = x1;
    c_decom->t4.v1.y = y1;
    c_decom->t4.v1.z = z0;
    c_decom->t4.v1.prty = values[i1][j1][k];

    c_decom->t4.v2.x = x1;
    c_decom->t4.v2.y = y0;
    c_decom->t4.v2.z = z1;
    c_decom->t4.v2.prty = values[i1][j][k1];

    c_decom->t4.v3.x = x0;
    c_decom->t4.v3.y = y1;
    c_decom->t4.v3.z = z1;
    c_decom->t4.v3.prty = values[i][j1][k1];
}
