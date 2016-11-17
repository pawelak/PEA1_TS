// PEA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "City.h"


int main()
{
	//Generator g(9, -10, 10, -10, 10);
	City city("plik.txt");
	//city.print();
	city.duplicate();

	city.printMatrix();
	vector <float> to;
	to = city.FindSmallestV();
	//city.bruteForce();
	//city.printBestPermutation();


	return 0;
}

