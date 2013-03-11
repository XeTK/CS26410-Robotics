#include <iostream>
#include <libplayerc++/playerc++.h>
/*This is the header file for the Mapt.cpp file*/
class Mapt
{
	/*Make are methods public to the world*/
	public:
		/*Sens is the main logic of the class to carry out are mapping function*/
		void sens(double sp[],int x, int y, double yaw);
		/*Range converts are large double value into a simple int so we have some ranges to work with*/
		int range(double in);
};
