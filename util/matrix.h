#ifndef LSH_MATRIX_H_
#define LSH_MATRIX_H_

namespace lsh
{
typedef unsigned int size_t;

template<typename T>
class Matrix
{
public:
	//default constructor
	Matrix()
	{
	}

	//constructor
	Matrix(T* data_, size_t rows_, size_t cols, size_t stride=0) :
		data(data_), rows(rows_), cols(cols_), stride(stride_)
	{
		if(stride==0) stride = sizeof(T)*cols;
	}

	//overload the operator [] to return a pointer
	inline T* operator[](size_t index) const
	{
		return reinterpret_cast<T*>(data+index*stride);
	}

	//return the data pointer
	T* ptr() const
	{
		return reinterpret_cast<T*>(data);
	}

public:
	size_t rows;
	size_t cols;
	size_t stride;

private:
	T* data;
}

}

#endif	/*LSH_MATRIX_H_*/
