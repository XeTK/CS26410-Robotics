#include <iostream>
#include <libplayerc++/playerc++.h>
#include <vector>
/*This is the header file for the Mapt.cpp file*/
using namespace std;
class Mapt
{
	/*Make are methods public to the world*/
	public:
		/*Sens is the main logic of the class to carry out are mapping function*/
		static void sens(PlayerCc::RangerProxy &sp,int x, int y, double yaw);
		/*Range converts are large double value into a simple int so we have some ranges to work with*/
		static void range(int ox, int oy, int sx, int sy, double sens, double range, string type);
                static double av(vector<double> in);
                static double gv(string type);

};
