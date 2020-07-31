#include <stdlib.h>

#include <tetrahedral_decomposition.h>
#include <tetrahedral_utils.h>
#include "edge_decomposition.h"


size_t edge_decomposition(double isovalue, size_t r, size_t *faces , size_t faces_pos, double *edge_intercep, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values){
    int parity = (i + j + k) % 2;

    double vertices[8 * 4];
    size_t vertices_ids[8];

    extract_cube_vertices(&(vertices[0]), &(vertices_ids[0]), r, o_x, o_y, o_z, l, i, j, k, values);
    intersect_edges(isovalue, r, edge_intercep, &(vertices[0]), &(vertices_ids[0]));

    if (parity){
        return edge_odd_decomposition(isovalue, r, faces , faces_pos, vertices, vertices_ids);
    }
    else{
        return edge_even_decomposition(isovalue, r, faces , faces_pos, vertices, vertices_ids);
    }
}

size_t edge_even_decomposition(double isovalue, size_t r, size_t *faces , size_t faces_pos, double *vertices, size_t *vertices_ids){


    size_t tetrahedron[4];
    //EXTRACT FACES FOR EACH TETRAHEDRON
    //tetrahedron 0
    tetrahedron[0] = 7;
    tetrahedron[1] = 6;
    tetrahedron[2] = 4;
    tetrahedron[3] = 3;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);
                      
    //tetrahedron 1
    tetrahedron[0] = 5;
    tetrahedron[1] = 4;
    tetrahedron[2] = 6;
    tetrahedron[3] = 1;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);
                      
    //tetrahedron 2
    tetrahedron[0] = 2;
    tetrahedron[1] = 3;
    tetrahedron[2] = 1;
    tetrahedron[3] = 6;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);
                      
    //tetrahedron 3
    tetrahedron[0] = 0;
    tetrahedron[1] = 1;
    tetrahedron[2] = 3;
    tetrahedron[3] = 4;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);
                      
    //tetrahedron 4
    tetrahedron[0] = 6;
    tetrahedron[1] = 4;
    tetrahedron[2] = 3;
    tetrahedron[3] = 1;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);

    return faces_pos;
}

size_t edge_odd_decomposition(double isovalue, size_t r, size_t *faces , size_t faces_pos, double *vertices, size_t *vertices_ids){

    size_t tetrahedron[4];
    //EXTRACT FACES FOR EACH TETRAHEDRON
    //tetrahedron 0
    tetrahedron[0] = 6;
    tetrahedron[1] = 7;
    tetrahedron[2] = 5;
    tetrahedron[3] = 2;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);
                      
    //tetrahedron 1
    tetrahedron[0] = 4;
    tetrahedron[1] = 5;
    tetrahedron[2] = 7;
    tetrahedron[3] = 0;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);

    //tetrahedron 2
    tetrahedron[0] = 3;
    tetrahedron[1] = 2;
    tetrahedron[2] = 0;
    tetrahedron[3] = 7;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);
                      
    //tetrahedron 3
    tetrahedron[0] = 1;
    tetrahedron[1] = 0;
    tetrahedron[2] = 2;
    tetrahedron[3] = 5;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);
                      
    //tetrahedron 4
    tetrahedron[0] = 7;
    tetrahedron[1] = 5;
    tetrahedron[2] = 2;
    tetrahedron[3] = 0;
    faces_pos += extract_faces(vertices, vertices_ids, &(tetrahedron[0]), faces, isovalue, r);

    return faces_pos;
}

void extract_cube_vertices(double *vertices, size_t *vertices_ids, size_t r, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values){

    size_t idx = i + j * r + k * r * r;
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

    // BUILD VERTICES ARRAY
    vertices[0] = x0;
    vertices[1] = y0;
    vertices[2] = z0;
    vertices[3] = values[i][j][k];
    vertices_ids[0] = idx;

    vertices[1 * 4 + 0] = x1;
    vertices[1 * 4 + 1] = y0;
    vertices[1 * 4 + 2] = z0;
    vertices[1 * 4 + 3] = values[i1][j][k];
    vertices_ids[1] = idx + 1;

    vertices[2 * 4 + 0] = x1;
    vertices[2 * 4 + 1] = y1;
    vertices[2 * 4 + 2] = z0;
    vertices[2 * 4 + 3] = values[i1][j1][k];
    vertices_ids[2] = idx + r + 1;

    vertices[3 * 4 + 0] = x0;
    vertices[3 * 4 + 1] = y1;
    vertices[3 * 4 + 2] = z0;
    vertices[3 * 4 + 3] = values[i][j1][k];
    vertices_ids[3] = idx + r;

    vertices[4 * 4 + 0] = x0;
    vertices[4 * 4 + 1] = y0;
    vertices[4 * 4 + 2] = z1;
    vertices[4 * 4 + 3] = values[i][j][k1];
    vertices_ids[4] = idx + r*r;

    vertices[5 * 4 + 0] = x1;
    vertices[5 * 4 + 1] = y0;
    vertices[5 * 4 + 2] = z1;
    vertices[5 * 4 + 3] = values[i][j][k1];
    vertices_ids[5] = idx + r*r + 1;

    vertices[6 * 4 + 0] = x1;
    vertices[6 * 4 + 1] = y1;
    vertices[6 * 4 + 2] = z1;
    vertices[6 * 4 + 3] = values[i][j][k1];
    vertices_ids[6] = idx + r*r + r + 1;

    vertices[7 * 4 + 0] = x0;
    vertices[7 * 4 + 1] = y1;
    vertices[7 * 4 + 2] = z1;
    vertices[7 * 4 + 3] = values[i][j][k1];
    vertices_ids[7] = idx + r*r + r;
}

void intersect_edges(double isovalue, size_t r, double *edge_intercep, double *vertices, size_t *vertices_ids){
    size_t edge_id;
    edge_id = get_edge_id(vertices_ids[0], vertices_ids[1], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[0]), &(vertices[4*1]), r);

    edge_id = get_edge_id(vertices_ids[0], vertices_ids[2], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[0]), &(vertices[4*2]), r);

    edge_id = get_edge_id(vertices_ids[0], vertices_ids[3], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[0]), &(vertices[4*3]), r);

    edge_id = get_edge_id(vertices_ids[0], vertices_ids[4], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[0]), &(vertices[4*4]), r);

    edge_id = get_edge_id(vertices_ids[0], vertices_ids[5], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[0]), &(vertices[4*5]), r);

    edge_id = get_edge_id(vertices_ids[0], vertices_ids[7], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[0]), &(vertices[4*7]), r);

    edge_id = get_edge_id(vertices_ids[2], vertices_ids[5], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[4*2]), &(vertices[4*5]), r);

    edge_id = get_edge_id(vertices_ids[1], vertices_ids[4], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[4*1]), &(vertices[4*4]), r);

    edge_id = get_edge_id(vertices_ids[1], vertices_ids[3], r);
    intersect_edge(isovalue, &(edge_intercep[edge_id]), &(vertices[4*1]), &(vertices[4*3]), r);
}

size_t get_edge_id(size_t v0_id, size_t v1_id, size_t r)
{
    size_t min_id  = (v0_id < v1_id) ? v0_id : v1_id;
    size_t edge_id = ((v0_id < v1_id) ? v1_id : v0_id) - min_id;

    size_t x1dr = (edge_id + 1) / r;
    size_t x1mr = (edge_id + 1) % r;
    size_t xdr2 = edge_id / (r * r); 
    size_t g1, g2; 
    g1 = (x1dr == 1); 
    g2 = (x1dr == r); 
    edge_id = x1mr + 3*g1 + 6*g2 + (1-g1)*(1-g2)*(2*xdr2 - 1);

    return min_id * 9 + edge_id;
 }



