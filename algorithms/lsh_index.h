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
#include "../util/universal_hash.h"

namespace lsh
{

static 

static 

<typename T>
class LshIndex
{
public:
	typedef T ElementType;
  

public:

	/**
	   Constructor using with the params with default value
	*/
	LshIndex(const LshIndexParams params = LshIndexParams())
	{
		table_number_ = params.get_table_number();
		key_size_ = params.get_key_size();
		multi_probe_level_  =params.get_multi_probe_level_();

		universah_hash_ = UniversalHash(key_size_);
	}

}


private:

	/*Points Data*/
	std::vector<ElementType*> points_;

	/*Hashing tables*/
	std::std::vector<lsh::LshTable<ElementType> > tables_;

	/*table number*/
	unsigned int table_number_;

	/*key size*/
	unsigned int key_size_;

	/*multi-probe level*/
	unsigned int multi_probe_level_;

	/*universal hash function*/
	static UniversalHash universah_hash_;
}

#endif /*LSH_LSH_INDEX*/
