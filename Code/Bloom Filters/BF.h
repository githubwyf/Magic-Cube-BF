#include "includes.h"
#include "BOBhash.h"
#include "File_Reader.h"

class Bloom_Filter
{
private:
	BOBHash bobhash[MAX_HASH_NUM];
	int set_num;
	char bloomfilter[64][16 * MEM_SIZE];
	int bucket_num;

public:
	Bloom_Filter(int _)
	{
		set_num = _;
		bucket_num = ((MEM_SIZE * 1024 * 8) / set_num);
		memset(bloomfilter, 0, sizeof(bloomfilter));
		for (int i = 0;i < HASH_TIME;i++)
			bobhash[i] = BOBHash(1000 + i);
	}

	void Insert(const char* str, int index)
	{
		for (int i = 0;i < HASH_TIME;i++)
		{
			int bit = (bobhash[i].run(str, strlen(str))) % (bucket_num);
			bloomfilter[index][bit >> 3] |= (1 << (bit & 7));
		}
	}

	int Query(const char* str)
	{
		int bit[HASH_TIME];
		for (int i = 0;i < HASH_TIME;i++)
			bit[i] = bobhash[i].run(str, strlen(str)) % bucket_num;

		int ret = 0, cnt = 0;
		for (int i = 0;i < set_num;i++)
		{
			bool test = 1;
			for (int j = 0;j < HASH_TIME;j++)
			{
				int num = bit[j] >> 3;
				int offset = bit[j] & 7;
				test &= (!!(bloomfilter[i][num] & (1 << offset)));
			}
			if (test)
				cnt++, ret = i;
		}
		if (cnt == 0)
			return -2;
		if (cnt > 1)
			return -1;
		return ret;

	}

	~Bloom_Filter()
	{

	}
};
