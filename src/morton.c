#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This program traverse a matrix in morton order
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define GET4(n, a) (((n) >> (2 * (a))) & 0x3)
#define EXP2(a) (1 << (a))
#define roundSquare(len, a) (((square) / (a) >= 1) && ((square) % (a)))

int traverse(const int **matrix, const int rowNum, const int colNum);

/*
 * main - parse command arguments
 * -h - print USAGE
 * -f <matrix file> - path of matrix file
 * get matrix size and content from given file
 * traverse the matrix
 */
int main(int argc, char *argv[])
{
	FILE *fp;
	int helpFlag = 0;
	const char *matrixFile;
	int opt;
	while ((opt = getopt(argc, argv, "hf:")) != -1) {
		if (opt == 'h') {
			printf("Usage: ./morton_traverse [-h] -f <matrix_file>\n");
			return 0;
		}
		else if (opt == 'f') {
			matrixFile = optarg;
		}
	}

	if ((fp = fopen(matrixFile, "r")) == NULL) {
		fprintf (stderr, "%s is not a valid file or directory!\n", matrixFile);
		return -1;
	}
	int rowNumber = 0;
	int colNumber = 0;
	fscanf(fp, "%d %d", &rowNumber, &colNumber);
	if ( rowNumber <= 0 && colNumber <= 0 ) {
		fprintf (stderr, "[%d][%d] is not a valid matrix size!\n", rowNumber, colNumber);
		return -1;
	}
	int **matrix = (int **)malloc(sizeof(int *) * rowNumber);
	for (int i = 0; i != rowNumber; ++i) {
		matrix[i] = (int *)malloc(sizeof(int) * colNumber);
		for (int j = 0; j != colNumber; j++) {
			fscanf(fp, "%d", &(matrix[i][j]));
		}
	}
	printf ("*************************************\n"
	"Read matrix[%d][%d] from %s complete.\n"
	"*************************************\n", rowNumber, colNumber, matrixFile);

	traverse(matrix, rowNumber, colNumber);
	for (int i = 0; i != rowNumber; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}

/*
 * traverse - traverse the matrix[rowNum][colNum] in morton order
 */
int traverse(const int **matrix, const int rowNum, const int colNum)
{
	int square = MAX(rowNum, colNum);
	if (roundSquare(square, 64)) square = 128;
	else if (roundSquare(square, 32)) square = 64;
	else if (roundSquare(square, 16)) square = 32;
	else if (roundSquare(square, 8)) square = 16;
	else if (roundSquare(square, 4)) square = 8;
	else if (roundSquare(square, 1)) square = 4;
	else if (square == 1) {
		printf ("[%3d][%3d]: %8d\n", 0, 0, matrix[0][0]);
		printf ("\n****************\nTraverse complete\n****************\n");
		return 0;	
	}
	else {
		printf ("input matrix size is %3d x %3x.\n", rowNum, colNum);
		return 0;
	}
	printf ("Input matrix size: %3d x %3d\nSquare edge length: %3d\n", rowNum, colNum, square);
	int type = 1;
	if (rowNum <= square / 2) type = 2;
	int steps = 0;
	int i = 0, j = 0;
	int printTimes = 0;
	while (i < square / type && j < square) {
		steps++;
		if (i < rowNum && j < colNum) {
			printTimes++;
			printf("[%3d][%3d] -> ", i, j);
			if (printTimes % 4 == 0) printf("\n");
		}
		else if (i >= rowNum && j >= colNum) break;
		
		/* Next part is calculating the next cell's cordinate */
		int times = 0;
		while ((1 << times) <= square) {
			if ( GET4(steps, times) == 0) {
				times++;
				continue;
			}
			else if (GET4(steps, times) == 1 || GET4(steps, times) == 3) {
				i -= (EXP2(times) - 1);
				j += 1;
			}
			else {
				i += 1;
				j -= (2 * EXP2(times)) - 1;
			}
			break;
		}
		/* Cordinate calculation completed */
	}
	printf ("\n****************\nTraverse complete\n****************\n");
	return 1;
}
