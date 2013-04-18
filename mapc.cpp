#include "mapc.h"
#include "Mapt.h"
#include "rsens.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define UNKNOWN 0
#define FREE -1
using namespace std;
//set up the cordernates for the location of a cell refrence within the map.
mapc::mapc(int x, int y)
{
    this->x = x;
    this->y = y;
    check();
}
//check the cells around the current cell to see what paths are free and what ways the robot can travel.
void mapc::check()
{
    rsens **map;
    Mapt::getGrid(&map);

    if (map)
    {
        int ix = x, iy = (y + 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read > Mapt::gv(map[ix][iy].type)|| map[ix][iy].read == -1)
                top = true;
            else
                top = false;
        else 
            top = false;
        
        iy = (y - 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read > Mapt::gv(map[ix][iy].type)|| map[ix][iy].read == -1)
                bottom = true;
            else
                bottom = false;
        else
            bottom = false;
        
        iy = y;
        ix = (x - 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read > Mapt::gv(map[ix][iy].type)|| map[ix][iy].read == -1)
                left = true;
            else
                left = false;
        else
            left = false;
        
        ix = (x + 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read > Mapt::gv(map[ix][iy].type)|| map[ix][iy].read == -1)
                right = true;
            else
                right = false;
        else
            right = false;    
    }        
}
//caluclate the number of free cells around the robot so that we can see if the spot is a good place for the robot to hide or not
int mapc::nabours()
{
    rsens **map;
    Mapt::getGrid(&map);
    int ar = 0;
    if (valid(x,y))
    {
        if (map[x][y].read > Mapt::gv(map[x][y].type)||map[x][y].read == -1)
        {
            //ar++;
            if (top == true)
                ar++;
            if (bottom == true)
                ar++;
            if (left == true)
                ar++;
            if (right == true)
                ar++;
            return ar;
        }
    }
    return -1;
}
//Getter and setters for the class
int mapc::getX()
{
    return x;
}
int mapc::getY()
{
    return y;
}
bool mapc::getTop()
{
    return top;
}
bool mapc::getBottom()
{
    return bottom;
}
bool mapc::getLeft()
{
    return left;
}
bool mapc::getRight()
{
    return right;
}
//return a boolean of if the location on the grid is a valid location.
bool mapc::valid(int ix,int iy)
{
    if (ix >= 0 && ix < 32)
        if (iy >= 0 && iy < 32)
            return true;
    return false;
}
