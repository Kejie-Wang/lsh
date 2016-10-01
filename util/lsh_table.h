/* lsh_table.h
*  @Date 2016/9/30
*  @Author: Wang Kejie<wang_kejie@foxmail.com>
*
*/

#ifndef _LSH_LSH_TABLE
#define _LSH_LSH_TABLE

#include <vector>
#include <map>
#include <cmath>
#include "random.h"

namespace lsh
{

//2^32 - 5
#define PRIME_DEFAULT 4294967291U

/*The feature index which unique determines a feature, start from zero*/
typedef unsigned int FeatureIndex;

/*The key used to find the bucket in the lsh table*/
typedef unsigned int BucketKey;

/*A bucket in the lsh table*/
typedef std::vector<FeatureIndex> Bucket;

<typename T>
class LshTable
{
	typedef T ElementType;
	typedef unsigned int uint32_t;
	typedef long long uint64_t;

public:
	LshTable()
	{
	}

	LshTable(unsigned int feature_size, unsigned int key_size)
	{
		feature_size_ = feature_size;
		key_size_ = key_size_;
		computeOptParams();
	}

	/**@breif Add a value into the lsh table b
	 * @param value The value added into the table
	 * @param feature The feature 
	 */
	void add(unsigned int value, const ElementType* feature)
	{
		BucketKey key = getKey(feature);
		bucket_space_.push_back(key);
	}

private:
	void computeOptParams()
	{	
		w = 
	}

	/**
	*  Get the hashing key uusing hashing function family: H(v) = (a*v + b) / w
	*  @param feature The computed feature
	*
	*  a: each entry of it chosen independently from a p-stable distribution
	*  b: a real number chosen uniformly from the range [0, w]
	*/
	unsigned int getKey(const ElementType* feature) const
	{
		std::vector<double> a = lsh::getGaussianRandVec(feature_size_);
		double b = lsh::genUniformRandom(0, w);

		double key=0;
		for(int i=0;i<feature_size_;++i)
			key += a[i]*feature[i];
		key = (unsigned int)floor((key+b) / w);

		return key;
	}



private:

	/**
	*  Bucket space, a map for the bucket key to bucket
	*/
	std::map<BucketKey, Bucket> bucket_space_;

	
	/**
	*  The mask used to get the hashing key for basic lsh lsh
	*  The first value of the mask is the id
	*  The second value of the mask is the offset
	*  In the binary descriptor, it selects the id*C+ offset bit (C is the max number)
	*/
	std::pair<unsigned int, ElementType> mask_;	//<id, offset>

	/*Max element in the feature*/
	ElementType max_element_;

	unsigned int key_size_;

	unsigned int feature_size_;

	double w;

	/*two random vector
	 *r1: use to hash the concatenate the L hash function
	 */
	std::vector<unsigned int> r1, r2;
}


}


#endif //_LSH_LSH_TABLE