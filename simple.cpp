#include <iostream>
#include "Mapt.h"
#include "simple.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

 static PlayerClient    robot("localhost");
 static Position2dProxy pp(&robot,0);
 static RangerProxy     sp(&robot,0);
int main(int argc, char *argv[])
{
        
	pp.SetMotorEnable(true);
        
        int prex, prey, dir;
        
        robot.Read();
        simple::move(10);

	for(;;)
	{
		robot.Read();
                if (sp.GetRangeCount() != 0)
                {
                    double turnrate, speed;

                    int x = ((pp.GetXPos() * 100) / 60), y = ((pp.GetYPos() * 100) / 60);

                    if (x != prex||y != prey)
                    {
                        prex = x;
                        prey = y;
                        Mapt::sens(sp,x,y,rtod(pp.GetYaw()));

                    }

                }
                pp.SetSpeed(0,dtor(0));
                break;
	}
        
}
void simple::turnangle(int angle)
{
    int pred = (rtod(pp.GetYaw()) + 180);
    int dd = pred + angle;
    
    if (dd > 360)
        dd = dd - 360;
    
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
    int pred = (rtod(pp.GetYaw()) + 180);
    int dd = angle;
    
    if (dd > 360)
        dd = dd - 360;
    
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
    if (sp[0] < sp[7])
        simple::turnangle(180);
    
    double turnrate, speed;
    
    for (;;)
    {
        if (sp[0] > sp[15])
        {
            turnrate = dtor(1);
        }
        else if (sp[0] < sp[15])
        {
            turnrate = dtor(-1);
        }
        if (sp[0] == sp[15])
            break;
        pp.SetSpeed(speed,turnrate);
    }
    
}
void simple::move(int distance)
{
    int angle = rtod(pp.GetYaw()) + 180;
    
    cout << (angle / 90) << endl;
    
    if ((angle % 90) != 0)
        turntoangle((int)(angle / 90) * 90);
    int dir = angle / 90;
    
    int x = ((pp.GetXPos() * 100) / 60), y = ((pp.GetYPos() * 100) / 60);
    
    int prex = x, prey = y;
        
    for (;;)
    {
        if (dir == 2 || dir == 4)
            if (prex + distance == x)
                break;
        else if (dir == 1 || dir == 3)
            if (prey + distance == y)
                break;
        pp.SetSpeed(0.1,dtor(0));
    }
}