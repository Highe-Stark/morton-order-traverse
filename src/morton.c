#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This program traverse a matrix in morton order
 */

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
		printf ("*************************************\nRead matrix[%d][%d] from %s complete.\n*************************************\n", rowNumber, colNumber, matrixFile);

		traverse(matrix, rowNumber, colNumber);
		return 0;
}

/*
 * traverse - traverse the matrix[rowNum][colNum] in morton order
 */
int traverse(const int **matrix, const int rowNum, const int colNum)
{
		int chunkRow = rowNum;
		int chunkCol = colNum;
		int m11 = 0, m22 = 0, m44 = 0, m88 = 0, m1616 = 0;
		int i = 0, j = 0;
		while (1) {
				if (i < rowNum && j < colNum)
						printf("[%3d][%3d]: %8d -> ", i, j, matrix[i][j]);
				else if (i >= rowNum && j >= colNum) break;
				m11 = (m11 + 1) % 4;
				if (m11 == 0) {
						m22 = (m22 + 1) % 4;
						if (m22 == 0) {
								m44 = (m44 + 1) % 4;
								if (m44 == 0) {
										m88 = (m88 + 1) % 4;
										if (m88 == 0) {
												m1616 = (m1616 + 1) % 4;
												if (m1616 == 0) {
														printf ("\n*************\nm1616 = 0\n*************\n");
														i -= 31;
														j += 1;
												}
												else if (m1616 == 1 || m1616 == 3) {
														i -= 15;
														j += 1;
												}
												else {
														i += 1;
														j -= 31;
												}
										}
										else if (m88 == 1 || m88 == 3) {
												i -= 7;
												j += 1;
										}
										else {
												i += 1;
												j -= 15;
										}
								}
								else if (m44 == 1 || m44 == 3) {
										i -= 3;
										j += 1;
								}
								else {
										i += 1;
										j -= 7;
								}
						}
						else if (m22 == 1 || m22 == 3) {
								i-= 1;
								j += 1;
						}
						else {
								i += 1;
								j -= 3;
						}
				}
				else if (m11 == 1 || m11 == 3) {
						j += 1;
				}
				else {
						i += 1;
						j -= 1;
				}
		}
		printf ("\n****************\nTraverse complete\n****************\n");
		return 1;
}
