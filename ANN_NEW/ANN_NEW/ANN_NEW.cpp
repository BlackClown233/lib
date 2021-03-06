#include"vector_set.hpp"
#include<iostream>
#include<string>
#include<time.h>
#include<stdio.h>

#define num_cluster 100
#define computing_cycle 1000

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "NO FILE NAME INPUT" << std::endl;
		return 1;
	}
	// read data file
	const std::string str = argv[1];
	ss::Matrix<float> matrix(str);
	
	// get matrix size
	const int dimension = matrix.getDim();
	const int size = matrix.getSize();

	// set memory of  clusters&clu_members
	float **clu = setCluster<float>(num_cluster, dimension);

	int **clu_mem = new int *[num_cluster];
	for (int i = 0; i < num_cluster; i++) {
		clu_mem[i] = new int[size];
	}

	// random clusters
	int random;
	srand((unsigned)time(NULL));
	for (int i = 0; i<num_cluster; i++) {
		random = rand() % size;
		for (int j = 0; j<dimension; j++) {
			clu[i][j]=matrix[random][j];
		}
	}

	// calculate clusters
	for (int i = 0; i<=computing_cycle; i++) {
		// update members of clusters
		for (int j = 0; j < num_cluster; j++) {
			for (int k = 0; k < size; k++)
				clu_mem[j][k] = 0;
		}
		for (int j = 0; j<size; j++) {
			cluster_divide<float>(j, num_cluster, clu_mem, clu, matrix);
		}

		// update cores of clusters
		for (int j = 0; j < num_cluster; j++) {
			for (int k = 0; k < dimension; k++)
				clu[j][k] = 0.0;
		}
		for (int j = 0; j<num_cluster; j++) {
			core_calculation<float>(j, num_cluster, clu, clu_mem, matrix);
		}

		printf("%d\n", i);
	}

	//(ok) output result
	FILE *fp;
	fopen_s(&fp,"result.txt", "wt+");
	if (fp == NULL) {
		puts("Can not make the file.");
		exit(1);
	}
	for (int i = 0; i<num_cluster; i++) {
		fprintf(fp, "%d %d\n", i, clu_mem[i][0]);
		for (int j = 0; j<clu_mem[i][0]; j++) {
			fprintf(fp, "%d\n", clu_mem[i][j + 1]);
		}
	}
	fclose(fp);

	// free the memory
	for (int i = 0; i < num_cluster; i++) {
		delete[] clu[i];
	}
	delete[] clu;

	system("pause");
    return 0;
}