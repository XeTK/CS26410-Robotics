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
#include <libplayerc++/playerc++.h>
static int dir = 1, preX = 0, preY =0;
	int
main(int argc, char *argv[])
{
	using namespace PlayerCc;

	PlayerClient    robot("localhost");
	RangerProxy      sp(&robot,0);
	Position2dProxy pp(&robot,0);

	pp.SetMotorEnable(true);
	
	for(;;)
	{
		double turnrate, speed;
//		dd	turnrate = dtor(90);
//                pp.SetSpeed(1, dtor(0));
		//  read from the proxies
		robot.Read();

		//         print out sonars for fun
//		std::cout << sp << std::endl;

		//             do simple collision avoidance
		speed = 0;
		//double close = 0.75, far = 1.5; //Robot
		double close = 0.5, far = 1; //Sim
		int x = ((pp.GetXPos() * 100) / 60), y = ((pp.GetYPos() * 100) / 60);
                if (x != preX||y != preY)
		{
			std::cout << x << " " << y  << std::endl;
			preX = x;
			preY = y;
		}

		if (sp[3] < far||sp[4] < far|| sp[1] < close|| sp[6] < close || sp[0] < close || sp[7] < close)
		{
			
			int blah = (sp[1] - sp[6]);
			//std::cout << (blah) << std::endl ;
                        if (blah < 1)
			{
                               dir = -1;
			}
                        else if (blah > 1)
                        {
			      dir = +1;
			}

/*			if ((((int)(sp[0] * 10)) == ((int)(sp[15] * 10))))
				dir = 0;*/

			if(sp[3] < close || sp[4] < close)
			{
				turnrate = dtor((34.25)) * dir;
			}
			else 
			{
				turnrate = dtor((11.75)) * dir;
				speed = 0.01;
			}
		}
		else
		{
			//speed = 2; //Robot
			speed = 0.1; //sim
			turnrate = dtor(0);
		}
		
		pp.SetSpeed(speed, turnrate);

	}
}


