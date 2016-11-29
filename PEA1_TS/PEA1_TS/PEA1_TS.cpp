// PEA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "City.h"
#include "Clock.h"


int main()
{
	Clock timer;

	Generator g(6, 0, 100, 0, 100);
	City city("plik.txt");

	timer.startTimer();

	//city.print();
	city.bruteForce();

	timer.endTimer();
	cout << "TIME:   " << timer.ReturnTime() << endl;


	//city.printBestPermutation();
	city.duplicate();

	//city.printMatrix();
	//city.printMatrix2();
	float r=0;
	
	
	
	timer.startTimer();
	city.TraverseTree(city.cityMatrix, &city.path, r);
	timer.endTimer();
	cout <<"TIME:   " <<  timer.ReturnTime() << endl;

	//city.deleteRowAndColumn(1, 1, city.cityMatrix);
	cout << city.getMinSol() << endl;


	return 0;
}

