#include "mapc.h"
#include "Mapt.h"
#include "rsens.h"
#define UNKNOWN 0
#define FREE -1
mapc::mapc(int x, int y)
{
    this->x = x + 16;
    this->y = y + 16;
    check();
}

void mapc::check()
{
    rsens **map;
    Mapt::getGrid(&map);
    cout << map << endl;
    if (map)
        if (map[x][y].read != 0)
            cout << "Cell Is Checked " << endl;
        else
            cout << "Cell is not checked" << endl;
    else
        cout << "Pointer is null" << endl;
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
