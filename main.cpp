#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include "polygon.h"
#include "polygon.cpp"

using namespace std;


int main(int argc, char** argv) {
	//Declaration des variables
	double x, y;
	Polygon bubulle;
	bubulle.create(); //constructeur
	bubulle.load();

    
    bubulle.afficher();
    cout<<"Entrez coordonnees point a tester : "<<endl;
    cin>>x;
    cin>>y;
    cout<<"Le point de coordonnees "<<x<<" ; "<<y<<" est situe "<<(bubulle.inside(x,y)?"a l'interieur":"en dehors")<<" du polygone."<<endl;
    

	return 0;
}