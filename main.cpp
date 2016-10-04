#include "algorithms/lsh_index.h"
#include <cstdlib>
#include "siftsmall/vecs_read.h"

int main()
{
	int nn=3;

	int base_dim, query_dim;
	int base_vecs_num, query_vecs_num;

	//read the dataset and query vectors
	float* base_data;
	float* query_data;
	vecs_read<float>("siftsmall/siftsmall_base.fvecs", base_data, base_dim, base_vecs_num);
	vecs_read<float>("siftsmall/siftsmall_query.fvecs", query_data, query_dim, query_vecs_num);

	if(base_dim != query_dim)
	{
		fprintf(stderr, "Input error : The dimension of the base vector and the query vector is not same\n");
		exit(0);
	}

	lsh::Matrix<float> dataset(base_data, base_vecs_num, base_dim);
	lsh::Matrix<float> query(query_data, query_vecs_num, query_dim);

	lsh::Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
	lsh::Matrix<float> dists(new float[query.rows*nn], query.rows, nn);

	//test
	vecs_print<float>("dataset.out", dataset.ptr(), dataset.cols, dataset.rows);

	// construct an randomized kd-tree index using 4 kd-trees
	lsh::LshIndex<float> index(dataset);
	index.buildIndex();
	// do a knn search, using 128 checks
	/*index.knnSearch(query, indices, dists, nn, lsh::SearchParams(128));

	//read the groundtruth  data
	int* groundtruth_data;
	int groundtruth_dim, groundtruth_vecs_num;
	vecs_read<int>("siftsmall/siftsmall_groundtruth.ivecs", groundtruth_data, groundtruth_dim, groundtruth_vecs_num);

	vecs_print<int>("indices.print", indices.ptr(), indices.cols, indices.rows);*/

	//free the memory
	delete[] dataset.ptr();
	delete[] query.ptr();
	delete[] indices.ptr();
	delete[] dists.ptr();
}
