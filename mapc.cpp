#include "mapc.h"
#include "Mapt.h"
#include "rsens.h"
#define UNKNOWN 0
#define FREE -1
mapc::mapc(int x, int y)
{
    this->x = x;
    this->y = y;
    check();
}

void mapc::check()
{
    rsens **map;
    Mapt::getGrid(&map);

    if (map)
    {
        int ix = x, iy = (y + 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read == 0)
                top = false;
            else
                top = true;
        else 
            top = false;
        
        iy = (y - 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read == 0)
                bottom = false;
            else
                bottom = true;
        else
            bottom = false;
        
        iy = y;
        ix = (x - 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read == 0)
                left = false;
            else
                left = true;
        else
            left = false;
        
        ix = (x + 1);
        
        if (valid(ix,iy))
            if (map[ix][iy].read == 0)
                right = false;
            else
                right = true;
        else
            right = false;    
    }        
}

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
bool mapc::valid(int ix,int iy)
{
    if (ix >= 0 && ix < 32)
        if (iy >= 0 && iy < 32)
            return true;
    return false;
}
