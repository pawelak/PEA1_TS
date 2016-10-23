#include "stdafx.h"
#include "City.h"


City::City()
{
}


City::~City()
{
}

City::City(string filename)			// czyta z pliku
{
	verticlesTab(filename);
	generateMatrix();
}

void City::verticlesTab(string filename)
{
	vector <int> tmp;

	tmp.clear();

	fstream file(filename, ios::in);
	int help;
	if (file.is_open())
	{
		file >> numberOfCities;
		if (file.fail())
			cout << "blad wczytywania pliku" << endl;

		for (int i = 0; i < numberOfCities; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				file >> help;
				tmp.push_back(help);
			}
			cityTab.push_back(tmp);
			tmp.clear();
		}
		file.close();
	}
	else
		cout << "blad wczytywania" << endl;
}

void City::generateMatrix()
{
	vector <float> tmp;
	for (int j = 0; j < numberOfCities; j++)			//paskudne sprawdziæ!!!
	{
		tmp.push_back(0);
	}
	for (int i = 0; i < numberOfCities; i++)
	{
		cityMatrix.push_back(tmp);
	}
	float help;
	for (int i = 0; i < numberOfCities - 1; i++)
	{
		for (int j = i + 1; j < numberOfCities; j++)
		{
			help = sqrt(pow((abs(cityTab[i][0] - cityTab[j][0])), 2) + pow(abs(cityTab[i][1] - cityTab[j][1]), 2));

			cityMatrix[i][j] = help;
			cityMatrix[j][i] = help;
		}
	}

	//i tu pobieranie i liczenie odleg³oœci i wpisywanie w poprawne miejsce w macierzy 
}

void City::printMatrix()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			cout << setw(6) << setprecision(3) << cityMatrix[i][j];
		}
		cout << endl;
	}
}


void City::bruteForce()
{
	vector <int> forPermutation;

	for (int i = 0; i < numberOfCities; i++)
	{
		forPermutation.push_back(i);
	}

	bestWay = forPermutation;
	float currentCost = 0;

	for (int i = 0; i < factorial(numberOfCities); i++)
	{
		for (int j = 0; j < numberOfCities - 1; j++)
		{
			//		cout << forPermutation[j];
			currentCost += cityMatrix[forPermutation[j]][forPermutation[j + 1]];
		}
		//	cout << forPermutation[3] << "    " << currentCost;
		//	cout << endl;
		if (currentCost < bestCost)
		{
			bestCost = currentCost;
			bestWay.assign(forPermutation.begin(), forPermutation.end());
		}
		currentCost = 0;
		next_permutation(forPermutation.begin(), forPermutation.end());
	}



}

unsigned long City::factorial(unsigned long f)
{
	if (f == 0)
		return 1;
	return(f * factorial(f - 1));
}

void City::printBestPermutation()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		cout << bestWay[i] << " ";
	}
	cout << "koszt: " << setprecision(6) << bestCost << endl;
}


