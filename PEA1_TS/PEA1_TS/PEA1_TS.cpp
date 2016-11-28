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
	//city.bruteForce();
	//city.printBestPermutation();
	city.duplicate();

	city.printMatrix();
	city.printMatrix2();
	float r=0;

	
	
	cout << endl << r << endl;

	city.TraverseTree(city.cityMatrix, &city.path, r);

	//city.deleteRowAndColumn(1, 1, city.cityMatrix);



	return 0;
}

