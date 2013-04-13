#include <iostream>
#include "Mapt.h"
#include "simple.h"
#include "mapc.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

 static PlayerClient    robot("localhost");
 static Position2dProxy pp(&robot,0);
 static RangerProxy     sp(&robot,0);
int main(int argc, char *argv[])
{
        
	pp.SetMotorEnable(true);
        robot.Read();
        
        Mapt::start();
        
        int prex, prey, dir;
        
        
        simple::move(1);
        simple::align();
       
        
        /*simple::turnangle(90);
        simple::move(22);
        simple::turnangle(-90);
        simple::move(1);
        simple::turnangle(-90);
        simple::move(22);
        simple::turnangle(90);
        simple::move(10);
        simple::turnangle(-90);
        simple::move(1);
        simple::turnangle(-90);
        simple::move(20);
        simple::turnangle(-90);
        simple::move(20);*/

	for(;;)
	{
		robot.Read();
                if (sp.GetRangeCount() != 0)
                {
                    int x = ((pp.GetXPos() * 100) / 60), y = ((pp.GetYPos() * 100) / 60);

                    if (x != prex||y != prey)
                    {
                        prex = x;
                        prey = y;
                        Mapt::sens(sp,x,y);
                        mapc m(x,y);
                    }
                    simple::nav();
                            
                }
	}
        
}
void simple::nav()
{
    cout << "nav" << endl;
    if (sp[3] < 0.5||sp[4] < 0.5)
    {
        if ((int)sp[7] == (int)sp[0])
        {
            turnangle(90);
        }
        else
        {
            if (sp[7] < sp[0])
            {
                turnangle(90);
            }
            else
            {
                turnangle(-90);
            }
            align();
        }
        if (sp[3] > 0.75||sp[4] > 0.75)
        {
                move(1);
        }
    }
               
    
    if (sp[0] > 4 && sp[15] > 4)
    {
        if ((int)sp[7] != (int)sp[0])
        {
            move(1);
            turnangle(90);
            move(2);
            align();
        }
    }
    pp.SetSpeed(0.5,0);
}
void simple::gotocord(int x, int y)
{
    int dir = 1;
    for (;;)
    {
        robot.Read();
        
        int ix = (((pp.GetXPos() * 100) / 60) + 16), iy = (((pp.GetYPos() * 100) / 60) + 16);
        
        if (ix == x || iy == y)
        {
            if (dir == 1)
                dir = -1;
            else
                dir = 1;
        }
        if (dir == 1)
        {
            
        }
        else if (dir == -1)
        {
            
        }
        
    }
    cout << "Got there" << endl;
}
void simple::turnangle(int angle)
{
    cout << "turn angle" << endl;
    int pred = (rtod(pp.GetYaw()) + 180);
    int dd = pred + angle;
    
    if (dd > 359)
        dd = dd - 360;
    
    if (dd < 0)
        dd = dd + 360;
    
    for (;;)
    {
        robot.Read();
        double turnrate = 0;
        int curd = (rtod(pp.GetYaw()) + 180);
        if (curd == dd)
            break;
        
        if (dd > curd)
            if ((dd - curd) > 10)
                turnrate = dtor(10);
            else
                turnrate = dtor(1);
        else
            if ((curd - dd) > 10)
                turnrate = dtor(-10);
            else
                turnrate = dtor(-1);
        
        pp.SetSpeed(0,turnrate);     
    }       
}

void simple::turntoangle(int angle)
{
    cout << "turn to angle" << endl;
    int pred = (rtod(pp.GetYaw()) + 180);
    int dd = angle;
    
    if (dd > 359)
        dd = dd - 360;
    if (dd < 0)
        dd = dd + 360;
    
    for (;;)
    {
        robot.Read();
        double turnrate = 0;
        int curd = (rtod(pp.GetYaw()) + 180);
        
        if (curd == dd)
            break;
        
        if (dd > curd)
            if ((dd - curd) > 10)
                turnrate = dtor(10);
            else
                turnrate = dtor(1);
        else
            if ((curd - dd) > 10)
                turnrate = dtor(-10);
            else
                turnrate = dtor(-1);
        
        pp.SetSpeed(0,turnrate);     
    }  
}

void simple::align()
{
    cout << "Align" << endl;
    robot.Read();
    if (sp.GetRangeCount() != 0)
    {
        int dir = 0;
        
        if (sp[7] > sp[0])
        {
            turnangle(90);
            dir = 1;
        }
        else
        {
            turnangle(-90);
            dir = -1;
        }
            
        for (;;)
        {
            robot.Read();
            
            if (sp[3] < 0.45&&sp[4] <0.45)
            {
                pp.SetSpeed(-0.1,0);
            }
            else if (sp[3] > 0.55&&sp[4] > 0.55)
            {
                pp.SetSpeed(0.1,0);
            }
            else
            {
                if (dir == -1)
                {
                    turnangle(90);
                }
                else if (dir == 1)
                {
                    turnangle(-90);
                }
                break;
            }
        }
    }
    pp.SetSpeed(0,0);
}
void simple::move(int distance)
{
    cout << "move" << endl;
    int angle = rtod(pp.GetYaw()) + 180;
    
    if ((angle % 90) != 0)
        turntoangle((int)(angle / 90) * 90);
    
    int dir = angle / 90;

    cout << "Dir " << dir << endl;
    
    int prex = ((pp.GetXPos() * 100) / 60), prey = ((pp.GetYPos() * 100) / 60);
        
    for (;;)
    {
        robot.Read(); 
        
        if (((sp[4] + sp[3])/2) < 0.4)
            break;
        
        int x = ((pp.GetXPos() * 100) / 60), y = ((pp.GetYPos() * 100) / 60);
        
        if (dir == 2 || dir == 4)
        {
            if (prex + distance == x)
            {
                break;
            }
        }
        else if (dir == 4)
        {
            if (prex - distance == x)
            {
                break;
            }
        }
        else if (dir == 1)
        {
            if (prey - distance == y)
            {
                break;
            }
        }
        else if (dir == 3)
        {
            if (prey + distance == y)
            {
                break;
            }
        }
        pp.SetSpeed(0.5, 0);
    }
    pp.SetSpeed(0,0);
}