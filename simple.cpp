/*
 * Copyright (c) 2005, Brad Kratochvil, Toby Collett, Brian Gerkey, Andrew Howard, ...
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *           this list of conditions and the following disclaimer.
 *               * Redistributions in binary form must reproduce the above copyright notice,
 *                     this list of conditions and the following disclaimer in the documentation
 *                           and/or other materials provided with the distribution.
 *                               * Neither the name of the Player Project nor the names of its contributors
 *                                     may be used to endorse or promote products derived from this software
 *                                           without specific prior written permission.
 *
 *                                           THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *                                           ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *                                           WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *                                           DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *                                           ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *                                           (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *                                           LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *                                           ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *                                           (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *                                           SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *                                           */

#include <iostream>
#include "Mapt.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
/* 
 * Keep some static variables of current turn direction and 
 * the previous X & Y cordernates so we can check when we move 
 * between cells
*/ 
static int prex, prey, dir;
int main(int argc, char *argv[])
{
	/*Declare all the robot's default sensors*/
	PlayerClient    robot("localhost");
	RangerProxy      sp(&robot,0);
	Position2dProxy pp(&robot,0);
	/*Enable Motors*/
	pp.SetMotorEnable(true);
	
	for(;;)
	{
		robot.Read();
		/*temp store for are double values from the sensors*/
		double temp[16];
		int i;
		Mapt m;
		/*Convert are sensor readings to double values*/ 
		for (i =1;i < 16;i++)
			temp[i] = (double)sp[i];

		double turnrate, speed;
		
		speed = 0;

		int x = ((pp.GetXPos() * 100) / 60), y = ((pp.GetYPos() * 100) / 60);
			
                if (x != prex||y != prey)
                {
                    prex = x;
                    prey = y;
                    m.sens(temp,x,y,pp.GetYaw());
                }
                if (sp[2] < 0.5|| sp[5] < 0.5||sp[3] < 0.75||sp[4] < 0.75||sp[1] < 0.6||sp[6] < 0.6||sp[0] < 0.3||sp[7] < 0.3) 
                {
                    if ((sp[1] + sp[3]) - (sp[4] + sp[6]) < 1 && (sp[1] + sp[3]) - (sp[4] + sp[6]) > -1)
                        dir = +1;
                    else
                        dir = 1;
                    turnrate = dtor(5 * dir);
                    if ((sp[3] + sp[4]) < (sp[12] + sp[13]))
                            turnrate += dtor(5 * dir);
                }
                else
                {

                    
                    turnrate = dtor(0);
                    speed = 0.1;
                }

		pp.SetSpeed(speed, turnrate);

	}
}
