/* lsh_index.h
*  @Date 2016/9/9
*  @Author: Wang Kejie<wang_kejie@foxmail.com>
*
*/

#ifndef LSH_LSH_INDEX
#define LSH_LSH_INDEX

namespace lsh
{

struct LshIndexParams
{

}

template<typename Distance>
class LshIndex
{
public:
  typedef typename Distance::ElementType ElementType;
  typedef typename Distance::ResultType DistanceType;

public:
  LshIndex()
  {
  }
}



}

#endif /*LSH_LSH_INDEX*/
