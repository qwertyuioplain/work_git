#include <iostream>
#include "tdp.h"

using namespace std;

int	main(void)
{
	const int test_dentition[] = {47,46,45,44,43,42,31,31,32,37};
	int	length = 10;
	int	*renum;
	TDP	dp;

	dp.set_verbose();
	renum = dp.renumbering(LOWER_DENTITION, test_dentition, length);
	cout << "END" << endl;
	for(int i = 0; i < length; i++)
		cout << renum[i] << endl;
}
