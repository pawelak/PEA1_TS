// PEA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "City.h"
#include "Clock.h"


int main()
{
	//Generator g(6, 0, 5, 0, 10);
	City city("att48.txt");
	//city.print();
	//city.bruteForce();
	//city.printBestPermutation();
	city.duplicate();

	//city.printMatrix();
	//city.printMatrix2();
	float r=0;
	
	
	Clock timer;
	timer.startTimer();
	city.TraverseTree(city.cityMatrix, &city.path, r);
	timer.endTimer();
	cout <<"TIME:   " <<  timer.ReturnTime() << endl;

	//city.deleteRowAndColumn(1, 1, city.cityMatrix);



	return 0;
}

