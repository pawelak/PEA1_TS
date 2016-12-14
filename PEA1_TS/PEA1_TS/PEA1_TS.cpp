// PEA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "City.h"
#include "Clock.h"


int main()
{
	Clock timer;

	Generator g(7, 0, 100, 0, 100);
	City city("plik.txt");



	//city.print();
	city.bruteForce();




	city.printBestPermutation();
	city.duplicate();

	city.printMatrix();
	//cout << "tutaj druga" << endl;
	//city.printMatrix2();
	//float r=0;
	
	
	

	//city.TraverseTree(city.cityMatrix, &city.path, r);

	//city.deleteRowAndColumn(1, 1, city.cityMatrix);
	//cout << city.getMinSol() << endl;

	//city.printMatrix2();

	//city.FloydWarshallAlgorithms();
	city.dynamic();
	return 0;
}

