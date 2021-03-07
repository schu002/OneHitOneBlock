#ifndef common_h
#define common_h 1

#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
typedef unsigned int	uint;

#pragma warning(disable:4996)

#define	M_MAX(a,b)		((a)<(b)?(b):(a))
#define	M_MIN(a,b)		((a)>(b)?(b):(a))
#define	M_ABS(a)		((a)<0?-(a):a)

typedef vector<int>		IntVector;

#endif
