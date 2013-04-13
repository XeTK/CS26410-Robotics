#include <iostream>
#include <libplayerc++/playerc++.h>
#include <vector>
#include "rsens.h"
/*This is the header file for the Mapt.cpp file*/
using namespace std;
class Mapt
{
	/*Make are methods public to the world*/
	public:
                static void start();
		/*Sens is the main logic of the class to carry out are mapping function*/
		static void sens(PlayerCc::RangerProxy &sp,int x, int y);
		/*Range converts are large double value into a simple int so we have some ranges to work with*/
		static void range(int ox, int oy, int sx, int sy, double sens, double range, string type);
                static double av(vector<double> in);
                static double gv(string type);
                static void jiggedsens(double *&array, PlayerCc::RangerProxy &sp, int yaw);
                static vector<int> search(int sx, int sy, int dx, int dy);
                static void getGrid(rsens ***array);
};
