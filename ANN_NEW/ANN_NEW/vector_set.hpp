#pragma once
#include"matrix.hpp"

// set memory of  clusters&clu_members
template<typename T>
T** setCluster(const int num, const int dim) 
{
	T **clu = new T *[num];
	for (int i = 0; i < num; i++) {
		clu[i] = new T[dim];
	}
	return clu;
}

// distance between  vector_x, cluster_y
template<typename T>
T distance_calculation(T** clu, ss::Matrix<T>&matrix,const int x,const int y)
{
	T distance = 0.0;
	for (int i = 0; i<matrix.getDim(); i++) {
		distance = distance + pow((matrix[x][i] - clu[y][i]), 2.0);
	}
	return sqrt(distance);
}

// which cluster vector_x belong to
template<typename T>
void cluster_divide(const int x, const int num_clu, int** clu_mem, T** clu, ss::Matrix<T>&matrix)
{
	float dis = FLT_MAX;
	int cluster_y = 0;
	for (int i = 0; i<num_clu; i++) {
		if (dis>distance_calculation<T>(clu, matrix, x, i)) {
			cluster_y = i;
			dis = distance_calculation<T>(clu, matrix, x, i);
		}
	}
	clu_mem[cluster_y][0]++;
	clu_mem[cluster_y][clu_mem[cluster_y][0]] = x;
}

// calculate cores of cluster_y
template<typename T>
void core_calculation(int y, const int num_cluster, T** clu, int** clu_mem, ss::Matrix<T> &matrix)
{
	for (int i = 0; i<num_cluster; i++) {
		for (int j = 1; j <= clu_mem[y][0]; j++) {
			clu[y][i] = clu[y][i] + (matrix[clu_mem[y][j]][i]/clu_mem[y][0] * 1.0);
		}
	}
}