#include <stdio.h>

int main()
{
    int m, n, p;

    // Read dimensions of matrix A
    scanf("%d %d", &m, &n);

    int A[m][n];

    // Read matrix A
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    // Read dimensions of matrix B
    int rowsB, colsB;
    scanf("%d %d", &rowsB, &colsB);

    // Check whether multiplication is possible
    if (n != rowsB)
    {
        printf("Invalid input\n");
        return 0;
    }

    int B[rowsB][colsB];
    int C[m][colsB];

    // Read matrix B only if multiplication is possible
    for (int i = 0; i < rowsB; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    // Initialize and calculate product
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Print result
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
