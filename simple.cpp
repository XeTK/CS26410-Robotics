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
static int dir = 1, preX = 0, preY =0;
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

		//double close = 0.75, far = 1.5; //Robot
		double close = 0.5, far = 1; //Sim
		/*convert the x and y cordernats to cell refrences, first by converting from CM to Meters then deviding by 60*/
		int x = ((pp.GetXPos() * 100) / 60), y = ((pp.GetYPos() * 100) / 60);
		/*check if the new position is different from the last*/
                if (x != preX||y != preY)
		{	
			/*set the last x and y to the cur so we can check again next time round*/
			preX = x;
			preY = y;
			/*Deploy the mapping class giving it the current sensor readings, cell refrence, and robots current yaw*/
			m.sens(temp,x,y,pp.GetYaw());
		}
		/*Robot Motor logic, check if we are crashing into anything using the threshold*/
		if (sp[3] < far||sp[4] < far|| sp[1] < close|| sp[6] < close || sp[0] < close || sp[7] < close)
		{
			/*get the differences between each corner to find out which direction has the most free space*/
			int dif = (sp[1] - sp[6]);
			/*set the direction of traval to the side where there is the most free space*/
                        if (dif < 1)
			{
                               dir = -1;
			}
                        else if (dif > 1)
                        {
			      dir = +1;
			}

			/*if there is something close to the front then we turn more abruply, with no speed*/
			if(sp[3] < close || sp[4] < close)
			{
				turnrate = dtor((34.25)) * dir;
			}
			else /*else we turn alot less and set the speed low*/ 
			{
				turnrate = dtor((11.75)) * dir;
				speed = 0.1;
			}
		}
		else /* if there is nothing around the robot then we set the speed higher 
		      * and set the turnrate to nothing so it travels in a sttraight light*/
		{
			//speed = 2; //Robot
			speed = 0.2; //sim
			turnrate = dtor(0);
		}
		/*set the motors to the speed & turn that we want*/
		pp.SetSpeed(speed, turnrate);

	}
}
