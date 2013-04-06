#include <iostream>
#include <libplayerc++/playerc++.h>
#include "Mapt.h"
/*This class creates a ocupancy grid for a robots travel from, sensor readings, X & Y cordinates and robots current Yaw/Angle*/

/*Keep a static grid of location on the grid*/
static int grid[32][32];
/*Method to convert are values into a grid to be displayed*/
void Mapt::sens(double sp[],int x, int y, double yaw)
{
	/*Convert are yaw into the difference between sensors so that robotic is 'always facing the same direction'*/
	int dif = (int)((int)(yaw * 100) / 22.5);
	/*if value is less than 0 flip it to positive*/
	if (dif < 0)
		dif = dif * -1;
	/*tempory array to hold are ajusted sensor index's*/
	double jigged[16];
	int i,k;
	/*convert are in sensor readings to are jigged always faceing the same direction ones*/
	for (i = 0;i < 16; i++)
	{
		int j = i + dif;
		if (j > 15)
			j = j - 15;
		jigged[i] = sp[j];
	}
	//fix stages odd negative cordinates
	x += 16;
	y += 16;
	/*Display are X & Y to the screen so we can see what is happerning*/
	printf("X:%i,Y:%i\n",x,y);
	grid[x][y] = -1;
	/**For the next section we inrement the cells round the robot to see what is ocupised and what is not*/
	/*Sensors at the top of the robot*/
	if ((y - 1) >= 0)
	{
		if ((x - 1) >= 0)
			if (grid[x -1][y -1] != -1)
				grid[x - 1][y - 1] += (range(jigged[1]) + range(jigged[2]));
		if (grid[x][y-1] != -1)
			grid[x][y -1] += (range(jigged[3]) + range(jigged[4]));
		if ((x + 1) < 16)
			if (grid[x + 1][y - 1] != -1)
				grid[x + 1][y - 1] += (range(jigged[6]) + range(jigged[7]));
	}	
	/*Sensors either side of the robot*/
	if ((x - 1) >=0)
		if (grid[x -1][y] != -1)
			grid[x -1][y] += (range(jigged[0]) + range(jigged[15]));
	if ((x + 1) < 16)
		if (grid[x + 1][y] != -1)
			grid[x +1][y] += (range(jigged[7]) + range(jigged[8]));
	/*Sensors at the bottom of the robot*/
	if ((y + 1) < 16)
	{
		if ((x -1) >= 0)
			if (grid[x -1][y + 1] != -1)
				grid[x - 1][y + 1] += (range(jigged[14]) + range(jigged[13]));
		if (grid[x][y + 1] != -1)
			grid[x][y + 1] += (range(jigged[12]) + range(jigged[11]));
		if((x +1) < 16)
			if (grid[x + 1][y + 1] != -1)
			grid[x + 1][y + 1] += (range(jigged[10]) + range(jigged[9]));     
	}
	/*lastly we print out the grid*/
	for (i = 0; i < 32;i++)
	{
		for (k = 0;k <32;k++)
		{
			if (grid[i][k] == 0)
				printf("\e[34m-");
			else if (grid[i][k] >= 1)				
				printf("\e[35m=");
			else
				printf("\e[33m*");
		}
		printf("\n");
	}
	printf("\n");
}
/*Range converts are double into a int of a specific value so we can gage how close we are to something*/		
int Mapt::range(double in)
{
	int ret =0;
	if (in > 2.5)
		ret = 0;
	else
		ret = 1;
	return ret;
}
