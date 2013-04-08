#include <iostream>
#include <stdio.h>
#include <libplayerc++/playerc++.h>
#include "Mapt.h"

class rsens {
public:
    double read;
    std::string type;

};
/*This class creates a ocupancy grid for a robots travel from, sensor readings, X & Y cordinates and robots current Yaw/Angle*/
using namespace std;
/*Keep a static grid of location on the grid*/
static rsens grid[32][32];
static vector<double> vtop, vbottom, vleft, vright;
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
	grid[x][y].read = -1;
        grid[x][y].type = "";
	/**For the next section we inrement the cells round the robot to see what is ocupised and what is not*/
	/*		grid[x - 1][y - 1] += (range(jigged[1]) + range(jigged[2]));
			grid[x][y -1] += (range(jigged[3]) + range(jigged[4]));
			grid[x + 1][y - 1] += (range(jigged[6]) + range(jigged[7]));
			grid[x -1][y] += (range(jigged[0]) + range(jigged[15]));
			grid[x +1][y] += (range(jigged[7]) + range(jigged[8]));
			grid[x - 1][y + 1] += (range(jigged[14]) + range(jigged[13]));
			grid[x][y + 1] += (range(jigged[12]) + range(jigged[11]));
			grid[x + 1][y + 1] += (range(jigged[10]) + range(jigged[9])); 
	*/
	//range(x - 1, y - 1, x - 2, y - 1, (jigged[1]+jigged[2]));
	range(x, y -1, x -1, y -1, (jigged[3] + jigged[4]),av(vtop),"top");
        vtop.push_back(jigged[3] + jigged[4]);
        
	//range(x + 1, y - 1, x + 2, y -1,(jigged[6] + jigged[7]));

	range(x -1,y, x-2,y,(jigged[0] + jigged[15]),av(vleft),"left");
        vleft.push_back(jigged[0] + jigged[15]);
	range(x +1,y, x+2,y,(jigged[7] + jigged[8]),av(vright),"right");
        vright.push_back(jigged[7] + jigged[8]);

	//range(x - 1, y + 1, x - 2, y + 1,(jigged[14] + jigged[13]));
	range(x, y + 1, x + 1, y + 1, (jigged[12] + jigged[11]),av(vbottom),"bottom");
        vbottom.push_back(jigged[12] + jigged[11]);
	//range(x + 1, y +1, x + 2, y + 1, (jigged[10] + jigged[9]));

	for (i = 0; i < 32;i++)
	{
		for (k = 0;k <32;k++)
		{
			if (grid[i][k].read == 0)
                        {
				cout << "\e[34m-";
                        }
			else if (grid[i][k].read == -1)
                        {
				cout << "\e[33m*";
                        }
                        else 
                        {
                                 if (grid[i][k].read > gv(grid[i][k].type))
                                 {
                                        cout << "\e[36m^";
                                 }
                                 else
                                 {
                                        cout << "\e[34m-";
                                 }
                        }
		}
		cout << endl;
	}
	cout << endl;
}
/*Range converts are double into a int of a specific value so we can gage how close we are to something*/		
void Mapt::range(int ox, int oy, int sx, int sy, double sens, double range, string type)
{
   // cout << sens << endl;
        if (ox >= 0 && ox < 32)
        {
                if (oy >= 0 && oy < 32)
                {
                        if(grid[ox][oy].read != -1)
                        {
                                if (sens > range)
                                {
                                        grid[ox][oy].read = sens;
                                        grid[ox][oy].type = type;
                                }
                                else
                                {
                                        grid[ox][oy].read = 0;
                                        grid[ox][oy].type = type;
                                }
                        }
                }
        }
	
        if (sx >= 0 && sx < 32)
        {
                if (sy >= 0 && sy < 32)
                {
                        if(grid[sx][sy].read != -1)
                        {
                                if (sens > range)
                                {
					grid[sx][sy].read = sens;
                                        grid[sx][sy].type = type;
                                }
                                else
                                {
                                        grid[sx][sy].read = 0;
                                        grid[sx][sy].type = type;
                                }
                        }
                }
        }
}
double Mapt::av(vector<double> in)
{
    double ret = 0;
    for (int i =0; i < in.size();i++)
        ret += in[i] + ((in[i] / 100) * 25);
    ret = ret / in.size();
    //cout << "< " << ret << endl;
    return ret;
}
double Mapt::gv(string type)
{
    if (type == "right")
        return av(vright);
    else if (type == "left")
        return av(vleft);
    else if (type == "top")
        return av(vtop);
    else if (type == "bottom")
        return av(vleft);
    else
        return 0;
}
