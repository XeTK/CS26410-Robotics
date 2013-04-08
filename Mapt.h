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
		void sens(double sp[],int x, int y, double yaw);
		/*Range converts are large double value into a simple int so we have some ranges to work with*/
		void range(int ox, int oy, int sx, int sy, double sens, double range, string type);
                double av(vector<double> in);
                double gv(string type);

};
