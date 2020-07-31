#include <stddef.h>
int determinant_test(const double* alpha, const double* beta, const double* gamma, const double* delta);
void solve_vertex_permutations(int p, int* alpha, int* beta, int* gamma, int* delta);
size_t* extract_faces( double* vertices, size_t* vertices_ids, size_t* tetrahedron, size_t* faces, double isovalue, double r);


size_t edge_decomposition(double isovalue, size_t r, size_t *faces , size_t faces_pos, double *edge_intercep, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values);
size_t edge_even_decomposition(double isovalue, size_t r, size_t *faces , size_t faces_pos, double *vertices, size_t *vertices_ids);
size_t edge_odd_decomposition(double isovalue, size_t r, size_t *faces , size_t faces_pos, double *vertices, size_t *vertices_ids);

void extract_cube_vertices(double *vertices, size_t *vertices_ids, size_t r, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values);
void intersect_edges(double isovalue, size_t r, double *edge_intercep, double *vertices, size_t *vertices_ids);

void intersect_edge(double isovalue, double *edge_intercept, const double *v0, const double *v1, size_t r);
size_t get_edge_id(size_t v0_id, size_t v1_id, size_t r);
