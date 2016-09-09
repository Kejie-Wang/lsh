/* vecs_read.h
*
*/
#include <string>
#include <fstream>

template<typename T>
void vecs_read(const std::string filename, T* vecs, int* dim_ptr, int* vecs_num_ptr)
{
	FILE* fp = fopen(filename.c_str(), "r");

	if(fp == NULL)
	{
		fprintf(stderr, "I/O error : Unable to open the file %s\n", filename.c_str());
		exit(0);
	}

	//read the vector dimension and vecotr size
	fread(dim_ptr, sizeof(T), 1, fp);
	int vecs_sizeof = 1*4 + sizeof(T)*(*dim_ptr);

	//Get the number of vector
	fseek(fp, 0, SEEK_END);
	*vecs_num_ptr = ftell(fp) / vecs_sizeof;

	//allocate memory for the vectors
  const int dim = *dim_ptr, vecs_num = *vecs_num_ptr;
  vecs = new T[dim*vecs_num];

	//printf("dim=%d, num=%d\n",dim, vecs_num);

	fseek(fp, 0, SEEK_SET);
	for(int i=0;i<vecs_num;++i)
	{
		int dim_;
		fread(&dim_, sizeof(T), 1, fp);
		if(dim_ != dim)
		{
			fprintf(stderr, "File error : The dimension of the vector is not same\n");
			exit(0);
		}
		fread(vecs+i*dim, sizeof(T), dim, fp);
	}

	fclose(fp);
}

//A test function to print the fvecs to check the correctness of the fvecs_read function
template<typename T>
void vecs_print(T* vecs, int dim, int vecs_num)
{
	std::ofstream out("vecs.out");

	if(!out.is_open())
	{
		fprintf(stderr,"I/O error : Open file vecs.out error\n");
		exit(0);
	}
	for(int i=0;i<vecs_num;++i)
	{
		for(int j=0;j<dim;++j)
		{
			T data;
			data = vecs[i*dim+j];
			out << int(data) << " ";
		}
		out << std::endl;
	}

	out.close();
}
