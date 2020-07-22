#ifndef T_DEC

#define T_DEC
#include <stdlib.h>
#include "tetrahedral_utils.h"

void cube_decomposition(struct T6Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values);

void cube5_decomposition(struct T5Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values);
void cube5_even_decomposition(struct T5Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values);
void cube5_odd_decomposition(struct T5Cube* c_decom, double o_x, double o_y, double o_z, double l, size_t i, size_t j, size_t k, double ***values);
#endif
