#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tetrahedral_utils.h>
#include <tetrahedral_decomposition.h>

int main(){

    size_t max_id;
    double ***data;
    struct T5Cube *old_decomp;
    struct T5Cube_v2 *new_decomp;

    max_id = 200;

    data = (double ***) calloc(max_id + 1, sizeof(double*));

    size_t i, j, k;
    for (i = 0; i <= max_id; i++){
        data[i] = (double **) calloc(max_id + 1, sizeof(double *));
        for (j = 0; j <= max_id; j++){
            data[i][j] = (double *) calloc(max_id + 1, sizeof(double));
            for (k = 0; k <= max_id; k++)
                data[i][j][k] = i + j + k;
        }
    }

    old_decomp = (struct T5Cube *) calloc(max_id * max_id * max_id, sizeof(struct T5Cube));
    new_decomp = (struct T5Cube_v2 *) calloc(max_id * max_id * max_id, sizeof(struct T5Cube_v2));

    size_t idx;
    clock_t start_t, end_t;
    start_t = clock();
    for (i = 0; i < max_id; i++){
        for (j = 0; j < max_id; j++){
            for (k = 0; k < max_id; k++){
                idx = i + j * max_id + k * max_id * max_id;
                cube5_decomposition(&(old_decomp[idx]), 0, 0, 0, 1, i, j, k, data);
            }
        }
    }
    end_t = clock();
    printf("Old time: %f\n", (double) (end_t - start_t) / CLOCKS_PER_SEC);

    start_t = clock();
    for (i = 0; i < max_id; i++){
        for (j = 0; j < max_id; j++){
            for (k = 0; k < max_id; k++){
                idx = i + j * max_id + k * max_id * max_id;
                cube5_decomposition_v2(&(new_decomp[idx]), 0, 0, 0, 1, i, j, k, data);
            }
        }
    }
    end_t = clock();
    printf("New time: %f\n", (double) (end_t - start_t) / CLOCKS_PER_SEC);

    free(old_decomp);
    free(new_decomp);

    for (i = 0; i <= max_id; i++){
        for (j = 0; j <= max_id; j++){
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);
}
