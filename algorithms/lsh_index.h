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

namespace lsh
{

// class LshIndexParams
// {
// 	/*lsh table params*/
// 	unsigned int table_number;

// 	*
// 	// *  lsh function params
// 	*  using hashing function family: H(v) = (a*v + b) / w
// 	*  Concatenation of k LSH functions: g(v) = (h1(v), h2(v), ..., hk(v)) where hi belong to H
	
// 	unsigned int key;

// 	/**
// 	*  lsh query params
// 	*  multi_probe_level The multi-probe level
// 	*/
// 	unsigned int multi_probe_level;

// 	LshIndexParams(unsigned int table_number, )
// }

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

}

#endif /*LSH_LSH_INDEX*/
