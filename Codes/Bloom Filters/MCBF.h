#pragma once

#include "stdafx.h"
#include "BOBhash.h"
#include "Helper_Func.h"
#include "File_Reader.h"


class MCBF
{
private:
	BOBHash bobhash[MAX_HASH_NUM];
	ull A[RAW_NUM];
public:
	MCBF()
	{
		memset(A, 0, sizeof(A));
		for (int i = 0;i < HASH_TIME ;i++)
		{
			bobhash[i] = BOBHash(i + 1000);
		}
	}

	MCBF(int )
	{
		memset(A, 0, sizeof(A));
		for (int i = 0;i < HASH_TIME;i++)
		{
			bobhash[i] = BOBHash(i + 1000);
		}
	}

	void Insert(const char* str, int index)
	{
		for (int i = 0;i < HASH_TIME;i++)
		{
			ull tmp = bobhash[i].run(str, strlen(str));
			int bucket = (tmp % (RAW_NUM - 1)); // 为了获得更好的效果
			int offset = (tmp + index) & (ull)63;
			A[bucket] |= ((ull)1 << offset);
		}
	}

	void Insert2(const char* str, int index)
	{
		int offset = ((bobhash[0].run(str, strlen(str)) + index) & (ull)63);
		for (int i = 0;i < HASH_TIME;i++)
		{
			int bucket = (bobhash[i].run(str, strlen(str))) % (RAW_NUM - 1); // 为了获得更好的效果
			A[bucket] |= ((ull)1 << offset);
		}
	}

	int Query(const char* str)
	{
		int bucket, offset;
		ull ans = ~(ull)0;
		for (int i = 0;i < HASH_TIME;i++)
		{
			ull tmp = bobhash[i].run(str, strlen(str));
			bucket = tmp % (RAW_NUM - 1);
			offset = (tmp & (ull)63);
			ans &= ((A[bucket] >> offset) | (A[bucket] << (64 - offset)));
		}
		int ret = 0, cnt = 0;
		for (int i = 0;i < 64;i++)
		{
			if (ans & ((ull)1 << i))
				cnt++, ret = i;
		}
		if (cnt == 0) // 要查元素不在集合内
			return -2;
		if (cnt > 1) // 查询出错，该元素位于多个集合
			return -1;
		return ret; // 正确查询
	}

	int Query2(const char* str)
	{
		int bucket, offset;
		offset = (bobhash[0].run(str, strlen(str)) & (ull)63);
		ull ans = ~(ull)0;
		for (int i = 0;i < HASH_TIME;i++)
		{
			bucket = bobhash[i].run(str, strlen(str)) % (RAW_NUM - 1);
			ans &= ((A[bucket] >> offset) | (A[bucket] << (64 - offset)));
		}
		int ret = 0, cnt = 0;
		for (int i = 0;i < 64;i++)
		{
			if (ans & ((ull)1 << i))
				cnt++, ret = i;
		}
		if (cnt == 0) // 要查元素不在集合内
			return -2;
		if (cnt > 1) // 查询出错，该元素位于多个集合
			return -1;
		return ret; // 正确查询
	}

	~MCBF()
	{

	}
};
