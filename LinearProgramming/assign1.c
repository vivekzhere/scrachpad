/* Linear Programming Course Assignment 1
 * m = 6, n = 10
 * Given an m x n matrix A and vector B of dimension m. Find X s.t AX=B.
 * 
 * Input
 * m rows, each row containing n elements. These are the elements of matrix A
 * m row each containing 1 element. This is the matrix B.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 6
#define N 10
#define IS_ZERO(x) ((x) <= 0.00001 && (x) >= -0.00001)

/* Print the matrix A
 */
void print_matrix(float A[M][N + 1])
{
	int i, j;

	for (i = 0 ; i < M; i++) {
		for (j = 0; j < N; j++)
			printf ( "%.2f\t", A[i][j]);
		printf("\t%.2f\n", A[i][j]);
	}
}

/* Exchange the xth and yth rows of the Matrix A
 */
void exchange(float A[M][N + 1], int x, int y)
{
	int j;
	float temp;

	for (j = 0; j <= N; j++) {
		temp = A[x][j];
		A[x][j] = A[y][j];
		A[y][j] = temp;
	}
}

/* Multiply the xth row with constant c
 */
void scale(float A[M][N + 1], int x, float c)
{
	int j;

	for (j = 0; j <= N; j++) {
		A[x][j] = A[x][j] * c;
	}
}

/* xth row = a times xth row + b times yth row
 */
void linear(float A[M][N + 1], int x, int y, float a, float b)
{
	int j;

	for (j = 0; j <= N; j++) {
		A[x][j] = (A[x][j] * a) + (A[y][j] * b);
		if (IS_ZERO(A[x][j]))
			A[x][j] = 0;
	}
}

/* Convert given matrix to row echelon form
 */
void row_echelon(float A[M][N + 1])
{
	int i, j, k;
	
	for (i = 0, j = 0; i < M && j <= N; j++) {

		/* Find a non zero entry in the jth column from ith row to end
		 * Mostly the A[i][j] will be non zero. If so the loop
		 * is skipped*/
		for (k = i; k < M && IS_ZERO(A[k][j]); k++);

		/* If the A[i][j] is zero and there is another row with jth
		 * element non zero swap the rows
		 */
		if ( k != i && k < M)
			exchange(A, i, k);
		
		/* If all entries in the jth cloumn is zero skip to next colomn
		 * without incrementing row index
		 */
		if ( k == M )
			continue;

		/* Make the j th element of the ith row 1 */
		scale(A, i, 1/A[i][j]);

		/* Make entire jth colomn zero except the ith row */
		for (k = 0; k < M; k++) {
			if (k == i)
				continue;
			linear(A, k, i, 1, -1 * A[k][j]);
		}

		/* move to next row */
		i++;
	}
}

/* Checks  wheather a solution exist for the system in
 * row echelon form. If there is a row with all zeros in
 * A and corresponding entry in B is non zero, then the 
 * system has no solution.
 * Returns 1 if a solution exist. Otherwise 0.
 */
int checkif_sol_exist(float A[M][N + 1])
{
	int i, j;

	for (i = 0; i < M; i++) {
		for (j = 0; j < N && IS_ZERO(A[i][j]); j++);
		if (j == N && !IS_ZERO(A[i][j]))
			return 0;
	}
	return 1;
}

/* Find a equation with a single variable in the row echelon form
 * (All other variables have zero coefficient
 * Returns the index of the first such equation.
 * Returns M if no such equation is found
 */
int find_single_row(float A[M][N + 1])
{
	int i, j, count;

	for (i = 0; i < M; i++) {
		count = 0;
		for (j = 0; j < N; j++)
			if (A[i][j] != 0)
				count++;
		if (count == 1)
			break;
	}
	return i;
}

/* Substitute variable var with value val in
 * the system of equations
 */
void substitute_variable(float A[M][N + 1], int var, float val)
{
	int i;
	
	for (i = 0; i < M; i++) {
		if (A[i][var] != 0) { 
			A[i][N] -= (A[i][var] * val);
			A[i][var] = 0;
		}
	}
}

/* Find a soloution for the system of equations.
 * Loop untill each variable has a value assigned.
 * First check is there is any equation with a single variable.
 * If such an equation is found the, corresponding variable
 * is substituted by the RHS of equation.
 * If no such equation is found, substitute the value
 * rand for one unsolved variable
 */
void assign_and_solve(float A[M][N + 1], float rand)
{
	float X[N];
	int flag[N] = {0};
	int i, j, k;

	j = 0;
	while (j < N) {
		i = find_single_row(A);
		if (i != M) {
			for (k = 0; k < N && IS_ZERO(A[i][k]); k++);
			printf("X%d = %.2f\n", k, A[i][N]);
			substitute_variable(A, k, A[i][N]);
			i = find_single_row(A);
		} else {
			for (k = N - 1; k >= 0 && flag[k] == 1; k--);
			if (k >= 0) {
				printf("X%d = %.2f\n", k, rand);
				substitute_variable(A, k, rand);
				i = find_single_row(A);
			}
		}
		flag[k] = 1;
		j++;
	}
}

int main()
{
	int i, j;
	float A[M][N + 1];

	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			scanf ("%f", &A[i][j]);

	for (i = 0; i < M; i++)
		scanf ("%f", &A[i][N]);

	row_echelon(A);
	if (checkif_sol_exist(A) == 0) {
		printf ("Equation is in consistent\n");
		return 0;
	}

	printf("One solution is :\n");
	assign_and_solve(A, 1);
	print_matrix(A);
	return 0;
}
/* Sample Input
3 2 4 7 6 5 4 3 2 1
2 4 7 6 5 4 3 2 1 3
4 7 6 5 4 3 2 1 3 2
7 6 5 4 3 2 1 3 2 4
6 5 4 3 2 1 3 2 4 7
5 4 3 2 1 3 2 4 7 6
4
7
6
5
4
3
*/
