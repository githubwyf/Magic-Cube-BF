

#include "includes.h"
#include "File_Reader.h"
#include "Element.h"
#include "Out_data.h"

Element elements[MAX_ELE_NUM];
string ports[MAX_ELE_NUM];
string out_data[10000000];

int rmdup_index(Element* ele_arr, string* port_arr, int cnt)
{
	map<string, int> mymap;
	sort(ele_arr, ele_arr + cnt);
	int ele_num = unique(ele_arr, ele_arr + cnt) - ele_arr;
	cout << ele_num << endl;
	sort(port_arr, port_arr + cnt);
	int port_num = unique(port_arr, port_arr + cnt) - port_arr;
	cout << "一共有" << port_num << "个组" << endl;
	int index = 0;
	for (int i = 0; i < port_num;i++)
		mymap[port_arr[i]] = index++;
	for (int i = 0;i < ele_num;i++)
		ele_arr[i].index = mymap[ele_arr[i].port];
	return ele_num;
}


int main()
{
	ull cnt = 0;
	string file_name = "test_data.txt";
	string ports[MAX_ELE_NUM];
	char buf_mac[50], buf_port[50];
	int ret = 0;
	File_Reader file_reader(file_name);
	while (ret = file_reader.getString(buf_mac, buf_port))
	{
		if (ret > 1) 
			continue;
		elements[cnt].mac_add = buf_mac;
		elements[cnt].port = buf_port;
		ports[cnt] = buf_port;
		cnt++;
	}
	int ele_num = rmdup_index(elements, ports, cnt);

	FILE* data = fopen("SortUniqueData.txt", "w");
	for (int i = 0;i < ele_num;i++)
		fprintf(data, "%s\t %d\n", elements[i].mac_add.c_str(), elements[i].index);

	generate_out_data(out_data, elements, ele_num);

}

