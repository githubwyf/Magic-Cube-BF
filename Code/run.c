#include "includes.h"
//#include "MCBF.h"
//#include "BF.h"
//#include "File_Reader.h"
#include "Helper_Func.h"
//#include "Element.h"

string out_data_name = "OutSetData.txt";
string in_data_name = "SortUniqueData.txt";
Element elements[MAX_ELE_NUM];
string out_data[MAX_OUT_DATA_NUM];

int main()
{
	int set_num;
	int ele_num = read_in(elements,in_data_name,set_num);
	
	MCBF mc_bf;
	Bloom_Filter bf(set_num);

	do_insert(elements, mc_bf, "mc_bf", ele_num);
	do_insert(elements, bf, "bf", ele_num);

	do_inset_query(elements, mc_bf, "mc_bf", ele_num);
	do_inset_query(elements, bf, "bf", ele_num);
	
	int out_num = read_out(out_data,out_data_name);
	do_outset_query(out_data, mc_bf, "mc_bf", out_num);
	do_outset_query(out_data, bf, "bf", out_num);

	return 0;
}

