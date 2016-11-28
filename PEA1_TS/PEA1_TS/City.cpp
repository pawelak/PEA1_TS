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
	inv = 666.0;
	verticlesTab(filename);
	generateMatrix();
	LB = 0;
	minSolution = 10000000;
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
			if (help == 0)
			{
				help = rand() % 10;
			}

			cityMatrix[i][j] = help;
			cityMatrix[j][i] = help;
		}
		cityMatrix[i][i] = inv;


	}
	cityMatrix[cityMatrix.size()-1][cityMatrix.size()-1] = inv;


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
	cout << endl;
}

void City::printMatrix2()
{
	for (int i = 0; i < cityMatrix2.size(); i++)
	{
		for (int j = 0; j < cityMatrix2.size(); j++)
		{
			cout << setw(6) << setprecision(3) << cityMatrix2[i][j];
		}
		cout << endl;
	}
	cout << endl;
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


void City::duplicate()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		cityMatrix2.push_back(cityMatrix[i]);
	}
}

vector <vector <float>> City::Reduce(vector <vector <float>> m, float &r)		//moja wersja reduce ¿eby nie trzeba by³o odtwarzaæ nic!
{										//sprawdzi³em wypliuwa faktycznie tablicê z innymi wartoœciami (nie sprawdza³em poprawnoœci)
	vector <vector <float>> result = m;
	vector <float> a;
	a = FindSmallestH(result);
	SubtractH(a, result);
	for (int i = 0; i < a.size(); i++)r += a[i];
	a.clear();

	cout << endl;
	a = FindSmallestV(result);
	SubtractV(a, result);
	for (int i = 0; i < a.size(); i++)r += a[i];

	return result;
}

vector<float> City::FindSmallestH(vector <vector <float>> m)
{
	vector <float> smallest;
	for (int i = 0; i < m.size(); i++)
	{
		float help = INT_MAX;
		for (int j = 0; j < m.size(); j++)
		{
			if (help > m[i][j] && i != j)
			{
				help = m[i][j];
			}
		}
		smallest.push_back(help);
		//cout << help << endl;
	}
	return smallest;
}

vector<float> City::FindSmallestV(vector <vector <float>> m)
{
	vector <float> smallest;
	for (int i = 0; i < m.size(); i++)
	{
		float help = INT_MAX;
		for (int j = 0; j < m.size(); j++)
		{
			if (help > m[j][i] && i != j)
			{
				help = m[j][i];
			}
		}
		smallest.push_back(help);
		//cout << help << endl;
	}
	return smallest;
}

void City::SubtractH(vector <float> a, vector <vector <float>> &m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			if (i == j)continue;
			m[i][j] -= a[i];
		}
	}
}

void City::SubtractV(vector <float> a, vector <vector <float>> &m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			if (i == j)continue;
			m[j][i] -= a[i];
		}
	}
}


float City::findEdge(vector <vector <float>> m, int &row, int &column)
{
	vector <int> helpPath = { 0,0 };
	float max = -1, help;
	bestH = FindSmallestWithoutZeroH();			//potrzebe bardzo jeœli wybiorê koncepcje z odtwarzaniem 
	bestV = FindSmallestWithoutZeroV();
	for (int i = 0; i < cityMatrix2.size(); i++)
	{
		for (int j = 0; j < cityMatrix2.size(); j++)
		{
			if (cityMatrix2[i][j] == 0 && i != j)
			{
				help = bestH[i] + bestV[j];

				if (max < help)
				{
					max = help;
					row = i;
					column = j;
				}
			}
		}
	}
	//path.push_back(helpPath);

	return max;
}

vector<float> City::FindSmallestWithoutZeroH()
{
	vector <float> smallest;
	for (int i = 0; i < cityMatrix2.size(); i++)
	{
		float help = INT_MAX;
		for (int j = 0; j < cityMatrix2.size(); j++)
		{
			if (help > cityMatrix2[i][j] && i != j && cityMatrix2[j][i] != 0)
			{
				help = cityMatrix2[i][j];
			}
		}
		smallest.push_back(help);
		//cout << help << endl;
	}
	return smallest;
}

vector<float> City::FindSmallestWithoutZeroV()
{
	vector <float> smallest;
	for (int i = 0; i < cityMatrix2.size(); i++)
	{
		float help = INT_MAX;
		for (int j = 0; j < cityMatrix2.size(); j++)
		{
			if (help > cityMatrix2[j][i] && i != j && cityMatrix2[j][i] != 0)
			{
				help = cityMatrix2[j][i];
			}
		}
		smallest.push_back(help);
		//cout << help << endl;
	}
	return smallest;
}




//void City::TraverseTree(vector <vector <float>> matrix, vector <vector <int>> p, float LB)
//{
//	float r = Reduce(matrix);
//	int R=0, C=0;
//	if (LB + r < minSolution)
//	{
//		if (path.size() == cityMatrix.size()-2)
//		{
//			
//			vector <int> h;
//			h.push_back(0);
//			h.push_back(1);
//			p.push_back(h);
//			minSolution = LB + r;
//		}
//		else
//		{
//			float max = findEdge(matrix,R, C);
//			TraverseTree(deleteRowAndColumn(R, C), addEdge(R,C, p)	, LB + r);
//			if (LB + R + max < minSolution)
//			{
//				cityMatrix2[R][C] = 0;
//				TraverseTree(cityMatrix2, p, LB + r);
//			}
//		}
//	}
//	cout << minSolution << endl;
//}

vector <vector <int>>  City::addEdge(int a, int b, vector <vector <int>> help)
{
	vector <int> h;
	h.push_back(a);
	h.push_back(b);
	help.push_back(h);
	return help;
}

vector <vector <float>>  City::deleteRowAndColumn(int x, int y)
{
	vector <vector <float>> help;
	vector <float> h;
	for (int i = 0; i < cityMatrix2.size(); i++)
	{
		for (int j = 0; j < cityMatrix2.size(); j++)
		{
			if (i == x || j ==y)continue;
			else
			{
				h.push_back(cityMatrix2[i][j]);
			}

		}
		help.push_back(h);
		h.clear();
	}

	for (int i = 0; i < cityMatrix2.size(); i++)		//beznadziejne mo¿na by to zwa¿eæ w tym powyzej 
	{													// do dorobienia jak to poleci
		for (int j = 0; j < cityMatrix2.size(); j++)
		{
			if (i == j && cityMatrix2[i][j] != 0)cityMatrix2[i][j] = 0;
			
		}
		help.push_back(h);
		h.clear();
	}
	return help;
}

