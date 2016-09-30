/* lsh_index.h
*  @Date 2016/9/9
*  @Author: Wang Kejie<wang_kejie@foxmail.com>
*
*/

#ifndef LSH_LSH_INDEX
#define LSH_LSH_INDEX

#include <vector>

namespace lsh
{

struct LshIndexParams
{

}

<typename T>
class LshIndex
{
public:
	typedef T ElementType;
  

public:

	/**
	  *Default constructor
	*/
	LshIndex()
	{
	}

	LshIndex()
}


private:

	/*
	* Points Data
	*/
	std::vector<ElementType*> points_;


}

#endif /*LSH_LSH_INDEX*/
