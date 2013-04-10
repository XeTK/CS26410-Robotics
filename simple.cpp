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

                    /*if (sp[3] < 1)
                    {
                        simple::turnangle(45);
                    }
                    else if (sp[4] < 1)
                    {
                        simple::turnangle(-45);
                    }
                    else if (sp[1] < 0.5)
                    {
                        simple::turnangle(20);
                    }
                    else if (sp[6] < 0.5)
                    {
                        simple::turnangle(-20);
                    }
                    else
                    {
                        speed = 0.1;
                                 //simple::align();
                    }*/
                    simple::align();
                   
                    pp.SetSpeed(speed, turnrate);
                }
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
        double turnrate;
        int curd = (rtod(pp.GetYaw()) + 180);
        if (dd > curd)
            turnrate = dtor(1);
        else
            turnrate = dtor(-1);
        
        pp.SetSpeed(0,turnrate);
        
        if (curd == dd)
            break;
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
            simple::turnangle(5);
        }
        else if (sp[0] < sp[15])
        {
            simple::turnangle(-5);
        }
        pp.SetSpeed(speed,turnrate);
    }
    
}
void simple::move(int distance)
{
    
    for (;;)
    {
        
    }
}