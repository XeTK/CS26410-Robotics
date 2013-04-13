#include <iostream>
#include <stdio.h>
#include <libplayerc++/playerc++.h>
#include "rsens.h"
#include "Mapt.h"
#include "mapc.h"


/*This class creates a ocupancy grid for a robots travel from, sensor readings, X & Y cordinates and robots current Yaw/Angle*/
using namespace PlayerCc;
/*Keep a static grid of location on the grid*/
static rsens **grid;
static vector<double> vtop, vbottom, vleft, vright;
/*Method to convert are values into a grid to be displayed*/

void Mapt::start()
{
    grid = new rsens *[32];
    for (int i = 0; i < 32; i++)
        grid[i] = new rsens[32];
}
void Mapt::sens(PlayerCc::RangerProxy &sp,int x, int y)
{

	x += 16;
	y += 16;

	printf("X:%i,Y:%i\n",x,y);
	grid[x][y].read = -1;
        grid[x][y].type = "";

	range(x, y -1, x -1, y -1, (sp[3] + sp[4]),av(vtop),"top");
        vtop.push_back(sp[3] + sp[4]);
       

	range(x -1,y, x-2,y,(sp[0] + sp[15]),av(vleft),"left");
        vleft.push_back(sp[0] + sp[15]);
        
	/*range(x +1,y, x+2,y,(sp[7] + sp[8]),av(vright),"right");
        vright.push_back(sp[7] + sp[8]);


	range(x, y + 1, x + 1, y + 1, (sp[12] + sp[11]),av(vbottom),"bottom");
        vbottom.push_back(sp[12] + sp[11]);*/


	for (int i = 0; i < 32;i++)
	{
		for (int k = 0;k <32;k++)
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
                            cout << sens << endl;
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
double Mapt::av(std::vector<double> in)
{
    double ret = 0;
    for (int i =0; i < in.size();i++)
        ret += (in[i] - ((in[i] / 100) * 25));
    ret = ret / in.size();

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
void Mapt::jiggedsens(double *&array, PlayerCc::RangerProxy &sp, int yaw)
{
    if (sp.GetRangeCount() != 0)
    {

	int dif = (int)((int)(yaw + 180) / 22.5);

	if (dif < 0)
		dif = dif * -1;
        
	double* jigged = new double[16];

	for (int i = 0;i < 16; i++)
	{
		int j = i + dif;
		if (j > 15)
			j = j - 15;
                
		jigged[i] = (double)sp[j];
	}
        array = jigged;
     }
    
}
void Mapt::getGrid(rsens ***array)
{
    *array = grid;
}
vector<int> Mapt::search(int sx, int sy, int dx, int dy)
{
    vector<int> list;
    int dirx = 0, diry = 0;
    
    if (sx < dx)
        dirx = 1;
    else
        dirx = -1;
    
    if (sy < dy)
        diry = 1;
    else
        diry = -1;
        
    mapc c(sx,sy);
    
    if (dirx == 1)
    {
        if (diry == 1)
        {
            if (c.getRight() == true)
            {
                list.push_back(180);
            }
            else if (c.getTop() == true)
            {
                list.push_back(90);
            }
        }
        else if (diry == -1)
        {
            if (c.getRight() == true)
            {
                list.push_back(180);
            }
            else if (c.getBottom() == true)
            {
                list.push_back(270);
            }
        }
    }
    else if (dirx == -1)
    {
        if (diry == 1)
        {
            if (c.getLeft() == true)
            {
                list.push_back(0);
            }
            else if (c.getTop() == true)
            {
                list.push_back(90);
            }
        }
        else if (diry == -1)
        {
            if (c.getLeft() == true)
            {
                list.push_back(0);
            }
            else if (c.getBottom() == true)
            {
                list.push_back(270);
            }
        }
    }
        
}