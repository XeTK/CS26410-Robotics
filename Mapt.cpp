#include <iostream>
#include <libplayerc++/playerc++.h>
#include "Mapt.h"

//using namespace std;  

void Mapt::sens(double sp[])
{
	printf("[%i][%i][%i][%i][%i][%i]\n",range(sp[1]),range(sp[2]),range(sp[3]),range(sp[4]),range(sp[5]),range(sp[6]));
	printf("[%i]            [%i]\n",range(sp[0]),range(sp[7]));
	printf("[%i]            [%i]\n",range(sp[15]),range(sp[8]));
	printf("[%i][%i][%i][%i][%i][%i]\n",range(sp[14]),range(sp[13]),range(sp[12]),range(sp[11]),range(sp[10]),range(sp[9]));
}		
int Mapt::range(double in)
{
	int ret =0;
	if (in > 1.5)
		ret = 3;
	else if (in > 0.5)
		ret = 2;
	else
		ret = 1;
	return ret;
}
