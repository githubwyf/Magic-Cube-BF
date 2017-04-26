#include "includes.h"

struct Element
{
	string mac_add;
	string port;
	int index;
	bool operator == (const Element& e2)
	{
		return mac_add == e2.mac_add;
	}
};

bool operator < (const Element& e1, const Element& e2)
{
	if (e1.mac_add < e2.mac_add || (e1.mac_add == e2.mac_add && e1.port < e2.port))
		return 1;
	return 0;
}
