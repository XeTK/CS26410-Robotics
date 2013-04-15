#include <iostream>
#include <stdio.h>
#include <libplayerc++/playerc++.h>
#include "rsens.h"
#include "Mapt.h"
#include "mapc.h"
#include "simple.h"


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
void Mapt::sens(PlayerCc::RangerProxy &sp,int x, int y, int yaw)
{
    double *dp;
    Mapt::jiggedsens(dp,sp,yaw);
	printf("X:%i,Y:%i\n",x,y);
	grid[x][y].read = -1;
        grid[x][y].type = "";

	range(x, y -1, x -1, y -1, (dp[3] + dp[4]) /2,av(vtop),"top");
        vtop.push_back((dp[3] + dp[4]) /2);
       

	range(x -1,y, x-2,y,((dp[0] + dp[15]) /2),av(vleft),"left");
        vleft.push_back((dp[0] + dp[15]) /2);
        
	range(x +1,y, x+2,y,((dp[7] + dp[8]) /2),av(vright),"right");
        vright.push_back((dp[7] + dp[8]) /2);


	range(x, y + 1, x + 1, y + 1, (dp[12] + dp[11]) /2,av(vbottom),"bottom");
        vbottom.push_back((dp[12] + dp[11]) /2);

        vector<mapc> p = find_bp();
	for (int i = 0; i < 32;i++)
	{
		for (int k = 0;k <32;k++)
		{
                    bool a = false;
                    for (int j = 0; j < p.size();j++)
                    {
                        if (p[j].getX() == i && p[j].getY() ==k)
                        {
                            a = true;
                            if (grid[i][k].read == -1)
                                cout << "\e[31m*";
                            else
                                cout << "\e[31m" << (int)grid[i][k].read;
                            break;
                        }
                    }
                    if (!a)
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
                                        //cout << "\e[36m^";
                                     cout << "\e[36m" << (int)grid[i][k].read ;
                                 }
                                 else
                                 {
                                        cout << "\e[34m-";
                                 }
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
    sens = (int)(sens * 100);
    cout << sens << endl;
        if (ox >= 0 && ox < 32)
        {
                if (oy >= 0 && oy < 32)
                {
                        if(grid[ox][oy].read != -1)
                        {
                                if (sens >= 50 )//&& sens < (int)(gv(type) + 1))
                                {
                                        grid[ox][oy].read = sens /100;
                                        grid[ox][oy].type = type;
                                }
                                /*else
                                {
                                        grid[ox][oy].read = 0;
                                        grid[ox][oy].type = type;
                                }*/
                        }
                }
        }
	
        if (sx >= 0 && sx < 32)
        {
                if (sy >= 0 && sy < 32)
                {
                        if(grid[sx][sy].read != -1)
                        {
                                if (sens >= (int)(gv(type) * 100)&& sens > 425)
                                {
					grid[sx][sy].read = sens /100;
                                        grid[sx][sy].type = type;
                                }
                                /*else
                                {
                                        grid[sx][sy].read = 0;
                                        grid[sx][sy].type = type;
                                }*/
                        }
                }
        }
}
double Mapt::av(std::vector<double> in)
{
    double ret = 0;
    for (int i =0; i < in.size();i++)
        ret += (in[i] - ((in[i] / 100)));
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
    int dirx = -1, diry = -1;
    
    if (sx < dx)
        dirx = 1;
    else
        dirx = -1;
    
    if (sy < dy)
        diry = 1;
    else
        diry = -1;

    for (;;)
    {
        mapc c(sx,sy);

        cout << "Sens " << c.getTop() << c.getBottom() << c.getRight() << c.getLeft() << endl;
        cout << "dir " << dirx << " " << diry << endl;
        
        int degree = -1;
        
        if (dirx == 1)
        {
            if (diry == 1)
            {
                if (c.getLeft() == true)
                {
                    degree = 0;
                    sx -= 1;
                }
                else if (c.getTop() == true)
                {
                    degree = 90;
                    sy += 1;
                }
            }
            else if (diry == -1)
            {
                if (c.getLeft() == true)
                {
                    degree = 0;
                    sx -= 1;
                }
                else if (c.getBottom() == true)
                {
                    degree = 270;
                    sy -= 1;
                }
            }
        }
        else if (dirx == -1)
        {
            if (diry == 1)
            {
                if (c.getRight() == true)
                {
                    degree = 180;
                    sx += 1;
                }
                else if (c.getTop() == true)
                {
                    degree = 90;
                    sy += 1;
                }
            }
            else if (diry == -1)
            {
                if (c.getRight() == true)
                {
                    degree = 180;
                    sx += 1;
                }
                else if (c.getBottom() == true)
                {
                    degree = 270;
                    sy -= 1;
                }
            }
        }
        
        if (degree == -1)
        {
            if (c.getRight() == true)
            {
                degree = 180;
                sx += 1;
            }
            else if (c.getLeft() == true)
            {
                degree = 0;
                sx -= 1;
            }
            else if (c.getTop() == true)
            {
                degree = 90;
                sy += 1;
            }
            else if (c.getBottom() == true)
            {
                degree = 270;
                sy -= 1;
            }
            else
                break;  
        }
            
        
        cout << degree << endl;
        list.push_back(degree);
        cout << list.size() << endl;
        cout << list[list.size() -1] << endl;
        cout << "XY " << sx << " " << sy << endl;

        if (!c.getBottom() && !c.getTop() && !c.getLeft() && !c.getRight())
            break;

        if (sx == dx && sy == dy)
            break;
    }
    for (int i = 0; i < list.size();i++)
    {
        cout << list[i] << endl;
    }
    return list;
}
vector<mapc> Mapt::find_bp()
{
    int lco = 9999;
    vector<mapc> vco;
    for (int i = 0; i < 32;i++)
    {
        for (int j = 0; j < 32; j++)
        {
            //cout << i << " " << j << endl;
            mapc l(i,j);
            //cout << l.nabours() << endl;
            if (l.nabours() < lco&&l.nabours() > 1)
            {
                vco.clear();
                lco = l.nabours();
                vco.push_back(l);
            }
            else if (l.nabours() == lco)
            {
                vco.push_back(l);
            }
        }
    }
    for (int i =0; i < vco.size();i++)
    {
        cout << vco[i].getX() << " " << vco[i].getY() << endl;
    }
    return vco;
}
