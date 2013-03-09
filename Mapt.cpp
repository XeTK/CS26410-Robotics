#include <iostream>
#include <libplayerc++/playerc++.h>
#include "Mapt.h"

//using namespace std;  
static int grid[32][32];
void Mapt::sens(double sp[],int x, int y, double yaw)
{
	int dif = (int)((int)(yaw * 100) / 22.5);
	if (dif < 0)
		dif = dif * -1;
	double jigged[16];
	int i,k;
	for (i = 0;i < 16; i++)
	{
		int j = i + dif;
		if (j > 15)
			j = j - 15;
		jigged[i] = sp[j];
	}
	x += 16;
	y += 16;
	printf("X:%i,Y:%i\n",x,y);

	if ((y - 1) >= 0)
	{
		if ((x - 1) >= 0)
			grid[x - 1][y - 1] += (range(jigged[1]) + range(jigged[2]));
		grid[x][y -1] += (range(jigged[3]) + range(jigged[4]));
		if ((x + 1) < 16)
			grid[x + 1][y - 1] += (range(jigged[6]) + range(jigged[7]));
	}	
	if ((x - 1) >=0)
		grid[x -1][y] += (range(jigged[0]) + range(jigged[15]));
	if ((x + 1) < 16)
		grid[x +1][y] += (range(jigged[7]) + range(jigged[8]));
	if ((y + 1) < 16)
	{
		if ((x -1) >= 0)
			grid[x - 1][y + 1] += (range(jigged[14]) + range(jigged[13]));
		grid[x][y + 1] += (range(jigged[12]) + range(jigged[11]));
		if((x +1) < 16)
			grid[x + 1][y + 1] += (range(jigged[10]) + range(jigged[9]));     
	}
	for (i = 0; i < 32;i++)
	{
		for (k = 0;k <32;k++)
		{
			if (grid[i][k] == 0)
				printf("*");
			else if (grid[i][k] >= 1)				
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}		
int Mapt::range(double in)
{
	int ret =0;
	if (in > 1.5)
		ret = 0;
	else
		ret = 1;
	return ret;
}
