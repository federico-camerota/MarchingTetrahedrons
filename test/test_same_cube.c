#include <tetrahedral_utils.h>
#include <stdio.h>

int test_same_tetrahedron();

int main(){

    printf("Testing same_tetrahedron function: ");
    if (test_same_tetrahedron())
        printf("PASSED!\n");
    else
        printf("FAILED!\n");

    return 0;
}

        
        


int test_same_tetrahedron(){

    struct Tetrahedron t1, t2;
    t1.v0.x = t2.v0.x = 1;
    t1.v0.y = t2.v0.y = 1;
    t1.v0.z = t2.v0.z = 1;
    t1.v1.x = t2.v1.x = 1;
    t1.v1.y = t2.v1.y = 1;
    t1.v1.z = t2.v1.z = 1;
    t1.v2.x = t2.v2.x = 1;
    t1.v2.y = t2.v2.y = 1;
    t1.v2.z = t2.v2.z = 1;
    t1.v3.x = t2.v3.x = 1;
    t1.v3.y = t2.v3.y = 1;
    t1.v3.z = t2.v3.z = 1;

    int result =  same_tetrahedron(&t1, &t2);
    int expected = 1;

    return result == expected;
}
