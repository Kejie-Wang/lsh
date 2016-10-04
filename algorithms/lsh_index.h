/* lsh_index.h
*  @Date 2016/9/9
*  @Author: Wang Kejie<wang_kejie@foxmail.com>
*
*/

#ifndef LSH_LSH_INDEX
#define LSH_LSH_INDEX

#include <vector>
#include <string>
#include "lsh_index_params.h"
#include "../util/lsh_table.h"
#include "../util/matrix.h"

namespace lsh
{

template<typename T>
class LshIndex
{

public:

	typedef T ElementType;
  
public:

	/**Constructor using with the params with default value
	 * @param params The params of the index
	*/
	LshIndex(const LshIndexParams params = LshIndexParams())
	{
		table_number_ = params.get_table_number();
		key_size_ = params.get_key_size();
		multi_probe_level_  =params.get_multi_probe_level();

		hash_coefficient_.reserve(key_size_);
		hash_coefficient_ = lsh::genUniformRandIntVec(0, 1<<29, key_size_);
	}

	/**Constructor using the input dataset and params
	 * @param input_data The input dataset
	 * @param params The params of the index
	 */
	LshIndex(const lsh::Matrix<ElementType>& input_data, const LshIndexParams params = LshIndexParams())
	{
		table_number_ = params.get_table_number();
		key_size_ = params.get_key_size();
		multi_probe_level_  =params.get_multi_probe_level();

		hash_coefficient_ = lsh::genUniformRandIntVec(0, 1<<29, key_size_);

		setDataset(input_data);
	}

	~LshIndex()
	{
	}

	void buildIndex()
	{
        tables_.resize(table_number_);
        // Add the features to each table
        for (unsigned int i = 0; i < table_number_; ++i) 
        {
        	tables_[i] = lsh::LshTable<ElementType>(veclen_, key_size_, hash_coefficient_);

            for(int j=0;j<points_.size();++j)
            	tables_[i].add(j, points_[j]);	
        }
	}


private:

	/**set the dataset for this index
	 * @param dataset The set dataset
	*/
	void setDataset(const Matrix<ElementType>& dataset)
	{
		size_ = dataset.rows;
		veclen_ = dataset.cols;

		for(int i=0;i<size_;++i)
			points_[i] = dataset[i];
	}

private:

	/*Points Data*/
	std::vector<ElementType*> points_;

	/*Number of points in the dataset*/
	unsigned int size_;

	/*Length of points in the dataset*/
	unsigned int veclen_;

	/*Hashing tables*/
	std::vector<lsh::LshTable<ElementType> > tables_;

	/*Table number*/
	unsigned int table_number_;

	/*Key size*/
	unsigned int key_size_;

	/*Multi-probe level*/
	unsigned int multi_probe_level_;

	/*The general hash function coefficients*/
	std::vector<int> hash_coefficient_;

};



}

#endif /*LSH_LSH_INDEX*/