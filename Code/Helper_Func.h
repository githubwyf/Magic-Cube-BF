#include "includes.h"
//#include "Timer.h"
#include "Element.h"
#include "MCBF.h"
#include "BF.h"
#include "File_Reader.h"


template<class T>
void do_insert(Element* elements, T& bf, char* name, int ele_num)
{
	double insert_time[20] = { 0 };
	clock_t t1,t2;
	//timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
	for (int j = 0;j < TEST_TIME;j++)
	{
		t1 = clock();
		for (int i = 0;i < ele_num;i++)
		{
			if (i % BREAK_NUM == 0 && i != 0)
			{
				t2 = clock();
				insert_time[i / BREAK_NUM] += t2 - t1;
			}
			bf.Insert(elements[i].mac_add.c_str(), elements[i].index);
		}
	}
	for (int i = 1;i <= ele_num / BREAK_NUM;i++)
		insert_time[i] /= TEST_TIME;
	FILE* throughput = fopen(name, "a");
	for (int i = 1;i <= ele_num / BREAK_NUM;i++)
		fprintf(throughput, "%f\n", i * 1000 * BREAK_NUM / insert_time[i]);
	printf("insert over\n");
}

template <class T>
void do_inset_query(Element* elements, T& bf, char* name, int ele_num)
{
	double query_time[20] = { 0 };
	ull cor_num = 0;
	clock_t t1,t2;
	for (int kount = 0; kount < TEST_TIME; kount++)
	{
		t1 = clock();
		for (int i = 0;i < ele_num;i++)
		{
			if (i % BREAK_NUM == 0 && i != 0)
			{
				t2 = clock();
				query_time[i / BREAK_NUM] += t2 - t1;
			}
			int query_result = bf.Query(elements[i].mac_add.c_str());
			if (query_result == elements[i].index)
				cor_num++;
		}
	}
	cor_num /= TEST_TIME;
	for (int i = 1;i <= ele_num / BREAK_NUM;i++)
		query_time[i] /= TEST_TIME;

	FILE* throughput = fopen(name, "a");
	for (int i = 1;i <= ele_num / BREAK_NUM;i++)
		fprintf(throughput, "%f\n", i * 1000 * BREAK_NUM / query_time[i]);
	FILE* error_rate = fopen(name, "a");

	double er = 1 - (double)cor_num / (double)ele_num;
	printf("%s\t%f\n", name, er);
	fprintf(error_rate, "%f\n", er);
}

int read_in(Element* elements, string in_data_name, int& set_num)
{
	int cnt = 0;
	char buf_mac[30];
	int buf_index = 0, setn = 0;
	File_Reader file_reader(in_data_name);
	while (file_reader.getdata(buf_mac, buf_index))
	{
		if (buf_index > setn)
			setn = buf_index;
		elements[cnt].mac_add = buf_mac;
		elements[cnt].index = buf_index;
		cnt++;
	}
	set_num = setn + 1;
	printf("%d\n", cnt);
	return cnt;
}

template <class T>
void do_outset_query(string* out_data, T& bf, char* name, int out_num)
{
	ull cor_num_out = 0;
	double cor_rate_out = 0;
	for (int kount = 0; kount < TEST_TIME; kount++)
	{
		for (int i = 0;i < out_num; i++)
		{
			int query_result = bf.Query(out_data[i].c_str());
			if (query_result == -2)
				cor_num_out++;
		}
	}
	cor_num_out /= TEST_TIME;
	cor_rate_out = (double)(cor_num_out) / (double)out_num;
	FILE* error_rate = fopen(name, "a");
	double er = 1 - cor_rate_out;
	printf("%s\t%f\n", name,er);
	fprintf(error_rate, "%f\n", er);
}

 int read_out(string* out_data, string out_data_name)
{
	File_Reader file_reader_out(out_data_name);
	int cnt_out = 0, filter = 0;
	char buf_mac_out[50];
	while (file_reader_out.getdata(buf_mac_out, filter))
	{
		out_data[cnt_out++] = buf_mac_out;
	}
	return cnt_out;
}


