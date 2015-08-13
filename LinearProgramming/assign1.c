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

/* Convert given matrix to row echelon form.
 */
void row_echelon(float A[M][N + 1])
{
	int i, j, k;
	
	/* Move diagonally making them 1 */
	for (i = 0, j = 0; i < M && j < N; i++, j++) {

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
		if ( k == M ) {
			/* do not move to next row */
			i--;
			continue;
		}

		/* Make the j th element of the ith row 1 */
		scale(A, i, 1/A[i][j]);
		/* X * (1/X) might be computed as 1 +/- error. Correct it */
		A[i][j] = 1;

		/* Make entire jth colomn zero except the ith row */
		for (k = 0; k < M; k++) {
			if (k == i)
				continue;
			linear(A, k, i, 1, -1 * A[k][j]);
		}
	}
}

/* Checks  wheather a solution exist for the system in
 * row echelon form. If there is a row with all zeros in
 * A and corresponding entry in B is non zero, then the 
 * system has no solution.
 * Returns 1 if a solution exist. Otherwise 0.
 * Input A should be in row echelon form
 */
int checkif_sol_exist(float A[M][N + 1])
{
	int i, j;

	for (i = 0; i < M; i++) {
		for (j = 0; j < N && IS_ZERO(A[i][j]); j++);

		/* If above loop reach j = N, it means all elements in
		 * the row except the last element is zero. Now check
		 * if last element is zero. If it is not zero, the
		 * system is inconsistent
		 */
		if (j == N && !IS_ZERO(A[i][N]))
			return 0;
	}

	/* The is no row which has all elements zero except the last
	 * element. So the system is consistent
	 */
	return 1;
}

/* Find a equation with a single variable in the row echelon form
 * (All other variables have zero coefficient)
 * Returns the index of the first such equation.
 * Returns M if no such equation is found
 * Input A is assumed to be in row echelon form.
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
 * Input A should be in row echelon form.
 */
void assign_and_solve(float A[M][N + 1], float rand)
{
	int flag[N] = {0}; /* Is the variable solved or not */
	int i, j, k;
	float X[N];

	j = 0;

	/* In each iteration of this while loop, exactly one variable will
	 * get a value assigned. But it need not be the jth variable.
	 */
	while (j < N) {
		/* Find a row with a single variable
		 */
		i = find_single_row(A);

		if (i != M) {
			/* If an equation in a single variable exist, the return
			 * value of find_single_row i != M. The ith row will
			 * contain only a single variable and its coeficient is one,
			 * since our matrix is in row echelon form.
			 */
			/* Now find the variable with non zero coeficient in the ith row.
			 */
			for (k = 0; k < N && IS_ZERO(A[i][k]); k++);

			if (A[i][k] != 1) {
				/* Something has gone bad. The coeficient of this
				 * should be 1, beacuse the matrix is in row echelon
				 * form. The first non zero entry in each row must
				 * be 1.
				 */
				printf("You should not be here!!!\n");
				return;
			}

			/* The ith equation has only kth varialble in it and its
			 * coeficient is one. Also since the matrix is in row echelon
			 * form this variable will not be part of any other equation.
			 * The ith equation is Xk = A[i][N]. So we can
			 * substitute kth variable with A[i][N]
			 */
			X[k] = A[i][N];
		} else {
			/* find_single_row returns M if all equations have more than
			 * one variable. So we take the LAST unsolved variable and
			 * assign value "rand" to it. The variable is taken from last
			 * so that even after substituting the variable, the row echelon
			 * form is maintained.
			 */
			for (k = N - 1; k >= 0 && flag[k] == 1; k--);
			X[k] = rand;
		}
		flag[k] = 1; /* Mark variable as solved */

		/* Substiute the variable with value in the system */
		substitute_variable(A, k, X[k]);
		j++;
	}
	
	/* Print the solution */
	for (k = 0; k < N; k++)
		printf("X%d = %.2f\n", k, X[k]);
}

int main()
{
	int i, j;
	float A[M][N + 1];

	/* Read the M * N matrix A */
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			scanf ("%f", &A[i][j]);

	/* Read the M * 1 matrix B and augment it to A*/
	for (i = 0; i < M; i++)
		scanf ("%f", &A[i][N]);

	/* Convert A to row echelon form */
	row_echelon(A);
	
	printf("Row echelon Form :\n");
	print_matrix(A);

	/* Check whether system is consistent */
	if (checkif_sol_exist(A) == 0) {
		printf ("\nEquation is in consistent\n");
		return 0;
	}

	printf("\nOne solution is :\n");
	/* Solve and priint the solutions. Each free variable is
	 * substituted as 1. This could be anyother number instead of 1.
	 */
	assign_and_solve(A, 1);

	/* Verification print. If every is correct this should print all
	 * zeros. All variables have been assigned values and substituted.
	 * printf("\nVerification :\n");
	 * print_matrix(A);
	 */
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
