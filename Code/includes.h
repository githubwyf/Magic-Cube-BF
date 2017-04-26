#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

typedef unsigned int uint;
typedef unsigned long int u4;
typedef unsigned long long ull;

// for BOB hash
#define MAX_PRIME 1229
#define MAX_BIG_PRIME 50
#define HASH_TIME 4

// for Magic Cube Sketch
#define	MEM_SIZE  64// KB
#define RAW_NUM  ((MEM_SIZE * 1024) / 8)
#define MAX_HASH_NUM 50

// for Experiment Data
#define MAX_SET_NUM 64
#define MAX_ELE_NUM 100000
#define SET_NUM 4
#define TEST_TIME 50
#define MAX_OUT_DATA_NUM 1000010
#define OUT_DATA_NUM 1000000
#define BREAK_NUM 3000
