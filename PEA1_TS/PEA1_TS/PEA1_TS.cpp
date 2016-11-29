// PEA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "City.h"


int main()
{
	Generator g(6, 0, 5, 0, 10);
	City city("plik.txt");
	//city.print();
	city.bruteForce();
	city.printBestPermutation();
	city.duplicate();

	city.printMatrix();
	city.printMatrix2();
	float r=0;

	
	city.TraverseTree(city.cityMatrix, &city.path, r);

	//city.deleteRowAndColumn(1, 1, city.cityMatrix);



	return 0;
}

