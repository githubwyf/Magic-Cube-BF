#include "includes.h"
//#include "Element.h"

char* itoa(int num, char*str, int radix)
{
	char index[] = "0123456789ABCDEF";
	unsigned unum;
	int i = 0, j, k;
	
	if (radix == 10 && num<0)
	{
		unum = (unsigned)-num;
		str[i++] = '-';
	}
	else unum = (unsigned)num;
	do {
		str[i++] = index[unum % (unsigned)radix];
		unum /= radix;
	} while (unum);
	str[i] = '\0';
	if (str[0] == '-')k = 1;
	else k = 0;
	char temp;
	for (j = k;j <= (i - 1) / 2;j++)
	{
		temp = str[j];
		str[j] = str[i - 1 + k - j];
		str[i - 1 + k - j] = temp;
	}
	return str;
}

bool exist(string test_str, string* str_arr, int cnt)
{
	return binary_search(str_arr, str_arr + cnt, test_str);
}

void generate_out_data(string* str_arr, Element* ele_arr, int ele_num)
{
	FILE* outdata = fopen("OutSetData.txt", "w");
	string* tmp = new string[ele_num + 50];
	for (int i = 0; i < ele_num;i++)
		tmp[i] = ele_arr[i].mac_add;

	srand(0);
	for (int j = 0;j < OUT_DATA_NUM;j++)
	{
		if (j % 5461 == 0)
			srand(j);
		char buf[10];
		string mac_add = "";
		for (int i = 1; i <= 14;i++)
		{
			if (i % 5 == 0)
				mac_add.append(".");
			else
				mac_add.append(itoa(rand() % 10, buf, 10));
		}
		if (!exist(mac_add, tmp, ele_num)) // successfully generated
		{
			str_arr[j] = mac_add;
			fprintf(outdata, "%s\n", mac_add.c_str());
		}
		else // failure
			j--;
	}

	delete[]tmp;
}
