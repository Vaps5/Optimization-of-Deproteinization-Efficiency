/*
Solving Least Squares problem for finding ai, 0 <= i <= 6
f(x1,x2,x3) = a0 + a1x1 + a2x2 + a3x3 + a4 * x1 * x2 + a5 * x1 *x3 + a6 * x2 * x3

Method used: Gaussian Elimination Method
By Vaps
*/


#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 10; // N is the number of bibliographies studied
const int M = 7; // Number of unknowns

/* 
A set of 10 data points was stablished from the data set obtained by the literature review. 
[Molarity, Efficiency, Temperature, Time]

Each row of the matrix represent the information of each bibliography studied
*/

double Data[N][4] = {
    {2.00, 99.9,   90, 2.5},
    {2.56, 43.23,  80, 0.75},
    {1.25, 86.00,  95, 3},
    {0.50, 97.88,  85, 3},
    {3.00, 87.03, 100, 2},
    {1.25, 96.00,  90, 4},
    {1.00, 98.20,  90, 1},
    {1.40, 98.92,  90, 1},
    {1.25, 91.53,  95, 3},
    {1.00, 98.30,  80, 1}
};

/* 
We stablished a system of linear of equations for the Least Squares problem:
A^T * A * x = A^T * b

The matrix A  where each row corresponds to a 
data point and columns represent the basis functions (constant term, linear, and interaction terms)

The vector b us the second column of Data matrix, ie, the efficiency results.

It was used the Gaussian Elimination algorithm for solving the system, with partial pivoting.

*/

void gauss(double A[M][M], double b[M], double x[M]) {
    for (int i = 0; i < M; ++i) {
        // It finds maxRow with the largest absolute value in column i from row i to down.
        int maxRow = i;
        for (int k = i + 1; k < M; ++k){
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        }
        for (int k = 0; k < M; ++k) {
            double aux = A[i][k];
            A[i][k] =  A[maxRow][k];
            A[maxRow][k] = aux;
        double auxx = b[i];
        b[i] = b[maxRow];
        b[maxRow] = auxx;
        }

        // Gaussian Elimination 
        for (int k = i + 1; k < M; ++k) {
            double f = A[k][i] / A[i][i];
            for (int j = i; j < M; ++j)
                A[k][j] -= f * A[i][j];
            b[k] -= f * b[i];
        }
    }

    // Back Substitution
    for (int i = M - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < M; ++j)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
}

int main() {

    double A[N][M], b[N];
    
    /*
    Function f(x1,x2,x3) = a0 + a1x1 + a2x2 + a3x3 + a4 * x1 * x2 + a5 * x1 *x3 + a6 * x2 * x3
    */

    for (int i = 0; i < N; ++i) {
        double x1 = Data[i][0];
        double y  = min(Data[i][1], 100.0);
        double x2 = Data[i][2];
        double x3 = Data[i][3];

        A[i][0] = 1;
        A[i][1] = x1;
        A[i][2] = x2;
        A[i][3] = x3;
        A[i][4] = x1 * x2;
        A[i][5] = x1 * x3;
        A[i][6] = x2 * x3;

        b[i] = y;
    }

    // System A^T * A * x = A^T * b
    double AtA[M][M] = {0};
    double Atb[M] = {0};

    //  A^T * A
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < N; ++k)
                AtA[i][j] += A[k][i] * A[k][j];

        // A^T * b
        for (int k = 0; k < N; ++k)
            Atb[i] += A[k][i] * b[k];
    }

    double alpha[M]; 
    gauss(AtA, Atb, alpha);

    cout << "Coefficients are:\n";
    for (int i = 0; i < M; ++i)
        cout << "a" << i << " = " << alpha[i] << "\n";

    return 0;
}
