/* lsh_table.h
*  @Date 2016/10/1
*  @Author: Wang Kejie<wang_kejie@foxmail.com>
*
*/
#ifndef _LSH_LSH_INDEX_PARAMS
#define _LSH_LSH_INDEX_PARAMS

namespace lsh
{

st LshIndexParams
{
private:
	unsigned int table_number;
	unsigned int multi_probe_level;

	//lsh function params
	unsigned int key_size;


public:
	LshIndexParams(unsigned table_number = 12, unsigned int key_size = 20, unsigned int multi_probe_level = 2)
	{
		this->table_number = table_number;
		this->key_size = key_size;
		this->multi_probe_level = multi_probe_level;
	}

	unsigned int get_table_number()
	{
		return table_number;
	}

	unsigned int get_key_size()
	{
		return key_size;
	}

	unsigned int get_multi_probe_level()
	{
		return multi_probe_level;
	}
}

}

#endif //_LSH_LSH_INDEX_PARAMSs