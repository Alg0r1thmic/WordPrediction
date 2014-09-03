#include <cstdio>
#include <ctime>
#include <cstdlib>

#include "myers.h"
using namespace std;

int main() {	
	int alphabetLength = 9;
	int queryLength = 5;
	int targetLength = 9;
	char query[5] = {0,1,2,3,4};
	char target[9] = {8,5,0,1,3,4,6,7,5};
	int score, pos;
	myersCalcEditDistance(query, queryLength, target, targetLength, alphabetLength, -1, MYERS_MODE_NW, &score, &pos);
	printf("%d %d\n", score, pos);
}

