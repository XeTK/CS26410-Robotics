/* 
 * File:   mapc.h
 * Author: xetk
 *
 * Created on April 13, 2013, 7:41 AM
 */

#ifndef MAPC_H
#define	MAPC_H
class mapc
{
public:
    mapc(int x,int y);
    mapc();
    bool getTop();
    bool getBottom();
    bool getLeft();
    bool getRight();
    int getX();
    int getY();
private:
    int x, y;
    bool top,bottom,left,right;
    void check();
};


#endif	/* MAPC_H */

