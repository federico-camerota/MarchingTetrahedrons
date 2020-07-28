#include <stddef.h>
#include "geometry.h"

#define SQUARE(x) x*x
#define DOT(x, y) x[0] * y[0] + x[1] * y[1] + x[2] * y[2]
#define AVGPT(p, p0, p1) p[0] = (p0[0] + p1[0]) / 2; p[1] = (p0[1] + p1[1]) / 2; p[2] = (p0[2] + p1[2]) / 2
#define PTCPY(t, p) t[0] = p[0]; t[1] = p[1]; t[2] = p[2]

size_t collapse_edges(struct surface *surf, double **normals, double D2, double V, double H, size_t *vert_map, int *v_to_remove, int *f_to_remove, size_t n_vertices, size_t n_faces);
size_t retrive_id(size_t start, size_t *map);
int is_degenerate(size_t v_id0, size_t v_id1, size_t v_id2);
void dk_volume_reduction(struct surface *surf, double ***normals, double D2, double V, double H);

void dk_volume_reduction(struct surface *surf, double ***normals, double D2, double V, double H){

    size_t n_vertices = surf->size_vertices / 3;
    size_t n_faces = surf->size_faces / 3;

    size_t vertices_map[2*n_vertices];
    int vertices_to_remove[2*n_vertices];
    int faces_to_remove[n_faces];

    size_t i;
    for (i = 0; i < 2*n_vertices; i++)
        vertices_map[i] = i;
        vertices_to_remove[i] = 0;
    for (i = 0; i < n_faces; i++)
        faces_to_remove[i] = 0;

    surf->size_vertices *= 2;
    surf->vertices = (double *) realloc(surf->vertices, surf->size_vertices * sizeof(double));

    normals = (double **) realloc(normals, 2 * n_vertices * sizeof(double *));

    n_vertices = collapse_edges(surf, normals, D2, V, H, &(vertices_map[0]), &(vertices_to_remove[0]), &(faces_to_remove[0]), n_vertices, n_faces);
    
    //REMOVE VERTICES AND FACES TO BE REMOVED
    size_t new_idx[n_vertices];
    size_t current_pos = 0;
    size_t n_vertices_removed = 0;
    for (i = 0; i < n_vertices; i++){
        if (vertices_to_remove[i]){
            n_vertices_removed++;
        }
        else{
            double *t, *p;
            t = &(surf->vertices[current_pos]);
            p = &(surf->vertices[i * 3]);
            PTCPY(t, p);
            current_pos += 3;
            size_t new_id = i - n_vertices_removed;
            new_idx[i] = new_id;
            double *n1, *n2;
            n1 = (*normals)[new_id];
            n2 = (*normals)[i];
            PTCPY(n1, n2);
        }
    }

    size_t n_faces_removed = 0;
    current_pos = 0;
    for (i = 0; i < n_faces; i++){
        if (faces_to_remove[i]){
            n_faces_removed++;
        }
        else{
            size_t v_id0, v_id1, v_id2;
            v_id0 = retrive_id(surf->faces[i * 3    ], &(vertices_map[0]));
            v_id1 = retrive_id(surf->faces[i * 3 + 1], &(vertices_map[0]));
            v_id2 = retrive_id(surf->faces[i * 3 + 2], &(vertices_map[0]));
            
            if (is_degenerate(v_id0, v_id1, v_id2)){
                n_faces_removed++;
                continue;
            }

            surf->faces[current_pos] = new_idx[v_id0];
            surf->faces[current_pos + 1] = new_idx[v_id1];
            surf->faces[current_pos + 2] = new_idx[v_id2];

            current_pos += 3;
        }
    }
    
    //RESIZE VERTICES ARRAY (remember difference between size_vertices (3 * n_vertices) and n_vertices)
    size_t remained_vertices = n_vertices - n_vertices_removed;
    surf->size_vertices = 3 * remained_vertices;
    surf->size_faces = 3 * (n_faces - n_faces_removed);

    surf->vertices = (double *) realloc(surf->vertices, surf->size_vertices * sizeof(double));
    surf->faces = (int *) realloc(surf->faces, surf->size_faces * sizeof(int));

    for (i = remained_vertices; i < n_vertices; i++)
        free((*normals)[i]);
    *normals = realloc(*normals, remained_vertices * sizeof(double *));

}


size_t collapse_edges(struct surface *surf, double **normals, double D2, double V, double H, size_t *vert_map, int *v_to_remove, int *f_to_remove, size_t n_vertices, size_t n_faces){

    size_t last_vertex = n_vertices;


    size_t i, face_idx;
    for (i = 0; i < n_faces; i++){

        face_idx = i * 3;
        size_t v_id0, v_id1, v_id2;
        v_id0 = retrive_id(surf->faces[face_idx    ], vert_map);
        v_id1 = retrive_id(surf->faces[face_idx + 1], vert_map);
        v_id2 = retrive_id(surf->faces[face_idx + 2], vert_map);

        if (is_degenerate(v_id0, v_id1, v_id2)){
            f_to_remove[i] = 1;
            continue;
        }
            

        double *v0, *v1, *v2;
        v0 = &(surf->vertices[v_id0 * 3]);
        v1 = &(surf->vertices[v_id1 * 3]);
        v2 = &(surf->vertices[v_id2 * 3]);

        double d01, d12, d20;
        double v01, v12, v20;

        d01 = SQUARE((v0[0] - v1[0])) + SQUARE((v0[1] - v1[1])) + SQUARE((v0[2] - v1[2]));
        v01 = DOT(normals[v_id0], normals[v_id1]);

        //if (d01 < D2 && v01 > V && (1 - v01) * d01 < 32 * H){
        if (d01 < D2){
            vert_map[v_id0] = last_vertex;
            vert_map[v_id1] = last_vertex;
            v_to_remove[v_id0] = 1;
            v_to_remove[v_id1] = 1;
            f_to_remove[i] = 1;

            double *v_avg = &(surf->vertices[last_vertex * 3]);
            AVGPT(v_avg, v0, v1);        
            
            normals[last_vertex] = (double *) calloc(3, sizeof(double));
            AVGPT(normals[last_vertex], normals[v_id0], normals[v_id1]);

            last_vertex += 1;
            continue;
        }

        d12 = SQUARE((v1[0] - v2[0])) + SQUARE((v1[1] - v2[1])) + SQUARE((v1[2] - v2[2]));
        v12 = DOT(normals[v_id1], normals[v_id2]);

        //if (d12 < D2 && v12 > V && (1 - v12) * d12 < 32 * H){
        if (d12 < D2){
            vert_map[v_id1] = last_vertex;
            vert_map[v_id2] = last_vertex;
            v_to_remove[v_id1] = 1;
            v_to_remove[v_id2] = 1;
            f_to_remove[i] = 1;

            double *v_avg = &(surf->vertices[last_vertex * 3]);
            AVGPT(v_avg, v1, v2);        
            
            normals[last_vertex] = (double *) calloc(3, sizeof(double));
            AVGPT(normals[last_vertex], normals[v_id1], normals[v_id2]);

            last_vertex += 1;
            continue;
        }

        d20 = SQUARE((v0[0] - v2[0])) + SQUARE((v0[1] - v2[1])) + SQUARE((v0[2] - v2[2]));
        v20 = DOT(normals[v_id0], normals[v_id2]);

        //if (d20 < D2 && v20 > V && (1 - v20) * d20 < 32 * H){
        if (d20 < D2){
            vert_map[v_id0] = last_vertex;
            vert_map[v_id2] = last_vertex;
            v_to_remove[v_id0] = 1;
            v_to_remove[v_id2] = 1;
            f_to_remove[i] = 1;

            double *v_avg = &(surf->vertices[last_vertex * 3]);
            AVGPT(v_avg, v0, v2);        
            
            normals[last_vertex] = (double *) calloc(3, sizeof(double));
            AVGPT(normals[last_vertex], normals[v_id0], normals[v_id2]);

            last_vertex += 1;
        }
    }
    
    return last_vertex;
}

size_t retrive_id(size_t start, size_t *map){
    size_t current = start;
    while(map[current] != current)
        current = map[current];

    return current;
}

int is_degenerate(size_t v_id0, size_t v_id1, size_t v_id2){

    return v_id0 == v_id1 || v_id1 == v_id2 || v_id2 == v_id0;
}
