/* vecs_read.cpp
*  
* Date: 2016/9/7
* Autor: Wang Kejie<wang_kejie@foxmail.com>
*/
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

//A test function to print the fvecs to check the correctness of the fvecs_read function
template<typename T>
void vecs_print(T* vecs, int dim, int vecs_num)
{
	ofstream out("vecs.out");

	if(!out.is_open())
	{
		fprintf(stderr,"I/O error : Open file vecs.out error\n");
		exit(0);
	}
	for(int i=0;i<vecs_num;++i)
	{
		for(int j=0;j<dim;++j)
		{
			out << int(vecs[i*dim+j]) << " ";
		}
		out << endl;
	}

	out.close();
}

template<typename T>
T* vecs_read(const string filename)
{
	FILE* fp = fopen(filename.c_str(), "r");

	if(fp == NULL)
	{
		fprintf(stderr, "I/O error : Unable to open the file %s\n", filename.c_str());
		exit(0);
	}

	//read the vector dimension and vecotr size
	int dim;	
	fread(&dim, sizeof(T), 1, fp);
	int vecs_sizeof = 1*4 + sizeof(T)*dim;

	//Get the number of vector
	fseek(fp, 0, SEEK_END);
	int vecs_num = ftell(fp) / vecs_sizeof;

	T* vecs = new T[dim*vecs_num];

	printf("dim=%d, num=%d\n",dim, vecs_num);
	fseek(fp, 0, SEEK_SET);
	for(int i=0;i<vecs_num;++i)
	{
		int buff[128];
		int dim_;
		fread(&dim_, sizeof(T), 1, fp);
		if(dim_ != dim)
		{
			fprintf(stderr, "File error : The dimension of the vector is not same\n");
			exit(0);
		}
		fread(vecs+i*dim, sizeof(T), dim, fp);
		//vecs_print<T>(vecs+i*dim, dim, 1);
	}

	fclose(fp);

	vecs_print<T>(vecs, dim, vecs_num);

	return vecs;
}

int main()
{
	// int* a = new int[8];
	// for(int i=0;i<8;++i)
	// 	a[i] = 2*i;
	// for(int i=0;i<8;++i)
	// 	printf("%d ", a[i]);
	vecs_read<float>("siftsmall_base.fvecs");
}