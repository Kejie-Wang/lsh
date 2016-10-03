/**lsh_table.h
 * @brief This is an universal hash function class which can hash a unsigned int vector into a unsigned int number
 		  The hashing value is no more than the prime 2^32-5
 * @Date 2016/10/2
 * @Author: Wang Kejie<wang_kejie@foxmail.com>
 *
 */
#ifndef _LSH_UNIVERSAL_HASH_
#define _LSH_UNIVERSAL_HASH_

#include <vector>
#include <assert>

namespace lsh
{

// 2^32 - 5
#define PRIME_DEFAULT 4294967291U

// 2^32-1
#define TWO_TO_32_MINUS_1 4294967295U

typedef unsigned long long uint64_t;
class UniversalHash
{

public:

	/*default constructor*/
	UniversalHash()
	{
	}


	/**Constructor using a integer number
	 * @param size: The length of the hashing number
	 */
	UniversalHash(int size)
	{
		r = lsh::genUniformRandom(0, 1<<29);
	}

	unsigned int hash(const std::vector<unsigned int>& vec)
	{
		unsigned int h = 0;
		for(int i=0;i<r.size();++i)
		{
			h = h + (uint64_t)(r[i]) * (uint64_t)(vec[i]);
			h = (h & TWO_TO_32_MINUS_1) + 5 * (h >> 32);
			if(h > PRIME_DEFAULT)
				h -= PRIME_DEFAULT;
			assert(h < PRIME_DEFAULT);
		}

		return h;
	}


private:
	/*use to hash the concatenate the L hash function*/
	std::vector<double> r;

	unsigned int prime;
}


static unsigned int 
}

#endif