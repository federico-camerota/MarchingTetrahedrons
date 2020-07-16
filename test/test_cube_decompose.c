#include <stdio.h>
#include <tetrahedral_decomposition.h>
#include <tetrahedral_utils.h>


int test_cube_decomposition();

int main(){

    printf("Testing cube decomposition: ");
    if (test_cube_decomposition())
        printf("PASSED!\n");
    else
        printf("FAILED\n");

    return 0;
}

int test_cube_decomposition(){
    double origin_x, origin_y, origin_z, l;
    origin_x = origin_y = origin_z = 0;
    l = 1.5;

    int i, j, k;
    i = 2;
    j = 5;
    k = 3;

    double p0x, p0y, p0z, p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z, p4x, p4y, p4z, p5x, p5y, p5z, p6x, p6y, p6z, p7x, p7y, p7z;

    p0x = origin_x + i * l;
    p0y = origin_y + j * l;
    p0z = origin_z + k * l;
    p1x = p0x + l;
    p1y = p0y;
    p1z = p0z;
    p2x = p0x + l;
    p2y = p0y + l;
    p2z = p0z;
    p3x = p0x;
    p3y = p0y + l;
    p3z = p0z;
    p4x = p0x;
    p4y = p0y;
    p4z = p0z + l;
    p5x = p1x;
    p5y = p1y;
    p5z = p1z + l;
    p6x = p2x;
    p6y = p2y;
    p6z = p2z + l;
    p7x = p3x;
    p7y = p3y;
    p7z = p3z + l;

    struct T6Cube expected, *result;
    //tetrahedron 0
    expected.t0.v0.x = p0x;
    expected.t0.v0.y = p0y;
    expected.t0.v0.z = p0z;
    expected.t0.v1.x = p1x;
    expected.t0.v1.y = p1y;
    expected.t0.v1.z = p0z;
    expected.t0.v2.x = p3x;
    expected.t0.v2.y = p3y;
    expected.t0.v2.z = p0z;
    expected.t0.v3.x = p5x;
    expected.t0.v3.y = p5y;
    expected.t0.v3.z = p0z + l;

    //tetrahedron 1
    expected.t1.v0.x = p1x;
    expected.t1.v0.y = p1y;
    expected.t1.v0.z = p0z;
    expected.t1.v1.x = p2x;
    expected.t1.v1.y = p2y;
    expected.t1.v1.z = p0z;
    expected.t1.v2.x = p3x;
    expected.t1.v2.y = p3y;
    expected.t1.v2.z = p0z;
    expected.t1.v3.x = p5x;
    expected.t1.v3.y = p5y;
    expected.t1.v3.z = p0z + l;

    //tetrahedron 2
    expected.t2.v0.x = p0x;
    expected.t2.v0.y = p0y;
    expected.t2.v0.z = p0z;
    expected.t2.v1.x = p3x;
    expected.t2.v1.y = p3y;
    expected.t2.v1.z = p0z;
    expected.t2.v2.x = p4x;
    expected.t2.v2.y = p4y;
    expected.t2.v2.z = p0z + l;
    expected.t2.v3.x = p5x;
    expected.t2.v3.y = p5y;
    expected.t2.v3.z = p0z + l;

    //tetrahedron 3
    expected.t3.v0.x = p2x;
    expected.t3.v0.y = p2y;
    expected.t3.v0.z = p0z;
    expected.t3.v1.x = p3x;
    expected.t3.v1.y = p3y;
    expected.t3.v1.z = p0z;
    expected.t3.v2.x = p5x;
    expected.t3.v2.y = p5y;
    expected.t3.v2.z = p0z + l;
    expected.t3.v3.x = p6x;
    expected.t3.v3.y = p6y;
    expected.t3.v3.z = p0z + l;

    //tetrahedron 4
    expected.t4.v0.x = p3x;
    expected.t4.v0.y = p3y;
    expected.t4.v0.z = p0z;
    expected.t4.v1.x = p5x;
    expected.t4.v1.y = p5y;
    expected.t4.v1.z = p0z + l;
    expected.t4.v2.x = p6x;
    expected.t4.v2.y = p6y;
    expected.t4.v2.z = p0z + l;
    expected.t4.v3.x = p7x;
    expected.t4.v3.y = p7y;
    expected.t4.v3.z = p0z + l;

    //tetrahedron 5
    expected.t5.v0.x = p3x;
    expected.t5.v0.y = p3y;
    expected.t5.v0.z = p0z;
    expected.t5.v1.x = p4x;
    expected.t5.v1.y = p4y;
    expected.t5.v1.z = p0z + l;
    expected.t5.v2.x = p5x;
    expected.t5.v2.y = p5y;
    expected.t5.v2.z = p0z + l;
    expected.t5.v3.x = p7x;
    expected.t5.v3.y = p7y;
    expected.t5.v3.z = p0z + l;

    result = cube_decomposition(origin_x, origin_y, origin_z, l, i, j, k);

    int passed = same_cube_decomposition(&expected, result);

    free(result);

    return passed;
}
