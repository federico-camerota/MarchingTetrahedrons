#include <tetrahedral_utils.h>


int same_cube_decomposition(struct T6Cube *expected, struct T6Cube *result){

    //tetrahedron 0
    if (!same_tetrahedron(&(expected->t0), &(result->t0)))
        return 0;
                      
    //tetrahedron 1
    if (!same_tetrahedron(&(expected->t1), &(result->t1)))
        return 0;
                      
    //tetrahedron 2
    if (!same_tetrahedron(&(expected->t2), &(result->t2)))
        return 0;
                      
    //tetrahedron 3
    if (!same_tetrahedron(&(expected->t3), &(result->t3)))
        return 0;
                      
    //tetrahedron 4
    if (!same_tetrahedron(&(expected->t4), &(result->t4)))
        return 0;
                      
    //tetrahedron 5
    if (!same_tetrahedron(&(expected->t5), &(result->t5)))
        return 0;

    return 1;
}


int same_tetrahedron(struct Tetrahedron *expected, struct Tetrahedron *result){
    if (expected->v0.x != result->v0.x)
        return 0;
    if (expected->v0.y != result->v0.y)
        return 0;
    if (expected->v0.z != result->v0.z)
        return 0;
    if (expected->v1.x != result->v1.x)
        return 0;
    if (expected->v1.y != result->v1.y)
        return 0;
    if (expected->v1.z != result->v1.z)
        return 0;
    if (expected->v2.x != result->v2.x)
        return 0;
    if (expected->v2.y != result->v2.y)
        return 0;
    if (expected->v2.z != result->v2.z)
        return 0;
    if (expected->v3.x != result->v3.x)
        return 0;
    if (expected->v3.y != result->v3.y)
        return 0;
    if (expected->v3.z != result->v3.z)
        return 0;

    return 1;
}
