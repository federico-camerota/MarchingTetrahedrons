#include "isosurface.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*
    Performs the determinant test as descibed by Doi & Koide in "An efficient method of triangulating
    equi-valued surfaces by using tetrahedral cells."

    Returns 1 if the determinant test fails and a cycle needs to occur, 0 if not.
*/
int determinant_test(const double* alpha, const double* beta, const double* gamma, const double* delta)
{
    double a = beta[0] - alpha[0];
    double b = beta[1] - alpha[1];
    double c = beta[2] - alpha[2];

    double d = gamma[0] - beta[0];
    double e = gamma[1] - beta[1];
    double f = gamma[2] - beta[2];

    double g = delta[0] - gamma[0];
    double h = delta[1] - gamma[1];
    double i = delta[2] - gamma[2];

    return (a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h) <= 0;
}


/*
    Solves vertex permutations for tetrahedrons with exactly two enclosed vertices.

    Implements a function such that:

        f( 3) = (2, 3, 0, 1)
        f( 5) = (1, 3, 0, 2)
        f( 6) = (1, 2, 0, 3)
        f( 9) = (0, 3, 1, 2)
        f(10) = (0, 2, 1, 3)
        f(12) = (0, 1, 2, 3)
*/
void solve_vertex_permutations(int p, int* alpha, int* beta, int* gamma, int* delta)
{
    *alpha = (p / 6) - (p == 9);
    *beta  = 1 + (p >  3) + (p > 6);
    *gamma = 1 + (p < 12) + (p < 9);
    *delta = 6 - (gamma[0] + beta[0] + alpha[0]);
} 



/*
    Extracts the faces from a tetrahedral decomposition.
*/
size_t* extract_faces(
    double* vertices,
    size_t* vertices_ids,
    size_t* tetrahedron,
    size_t* faces,
    double isovalue,
    double r)
{

    /* the four vertcies of the current tetrahedron */
    double* t[4] = {
        &vertices[ tetrahedron[0] * 5],
        &vertices[ tetrahedron[1] * 5],
        &vertices[ tetrahedron[2] * 5],
        &vertices[ tetrahedron[3] * 5]
    };

    /* parity of each vertex */
    int p0 = t[0][3] > isovalue;
    int p1 = t[1][3] > isovalue;
    int p2 = t[2][3] > isovalue;
    int p3 = t[3][3] > isovalue;

    int n_enclosed = p0 + p1 + p2 + p3;

    switch(n_enclosed)
    {   
        /*
            Case for a single enclosed vertex, resulting in a single triangle surface in this
            tetrahedron.
        */
        case(1) :
        {          
            /* vertex number of the enclosed vertex */
            int enclosed_vertex = p1 + 2*p2 + 3*p3;

            double* delta = t[enclosed_vertex];

            double* alpha = t[0 + (enclosed_vertex <= 0)];
            double* beta  = t[1 + (enclosed_vertex <= 1)];
            double* gamma = t[2 + (enclosed_vertex <= 2)];

            int swap = determinant_test(alpha, beta, gamma, delta);

            faces[0]      = get_edge_id(delta[4], alpha[4], r);
            faces[1+swap] = get_edge_id(delta[4], beta[4] , r);
            faces[2-swap] = get_edge_id(delta[4], gamma[4], r);

            return faces + 3;
        }

        /*
            Case two enclosed vertices, resulting in two triangle surfaces inside the
            tetrahedron.
        */
        case(2) :
        {
            int p = p0 + p1*2 + p2*4 + p3*8; // permutation value

            int a, b, g, d;
            solve_vertex_permutations(p, &a, &b, &g, &d);

            double* alpha = t[a];
            double* beta  = t[b];
            double* gamma = t[g];
            double* delta = t[d];

            int swap = determinant_test(alpha, beta, gamma, delta);

            faces[0]      = get_edge_id(alpha[4], gamma[4], r);
            faces[1+swap] = get_edge_id(gamma[4], beta[4] , r);
            faces[2-swap] = get_edge_id(beta[4] , delta[4], r);

            faces[3]      = get_edge_id(alpha[4], gamma[4], r);
            faces[4+swap] = get_edge_id(beta[4] , delta[4], r);
            faces[5-swap] = get_edge_id(alpha[4], delta[4], r);

            return faces + 6;
        }

        /* 
            Case for when all but one vertices are enclosed. Inversion of the case(1)
        */
        case(3) :
        {   
            /* vertex number of the enclosed vertex */
            int enclosed_vertex = 6 - (p1 + 2*p2 + 3*p3);

            double* delta = t[enclosed_vertex];

            double* alpha = t[0 + (enclosed_vertex <= 0)];
            double* beta  = t[1 + (enclosed_vertex <= 1)];
            double* gamma = t[2 + (enclosed_vertex <= 2)];

            int swap = determinant_test(alpha, beta, gamma, delta);

            faces[0]      = get_edge_id(alpha[4], beta[4] , r);
            faces[1+swap] = get_edge_id(alpha[4], gamma[4], r);
            faces[2-swap] = get_edge_id(alpha[4], delta[4], r);

            return faces + 3;
        }

        default : {}
    }
}
