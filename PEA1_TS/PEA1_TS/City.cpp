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
	int useless;

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
			for (int j = 0; j < 3; j++)
			{
				if (j==0)
					file >> useless;
				else {
					file >> help;
					tmp.push_back(help);
				}
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
	for (int j = 0; j < numberOfCities; j++)			
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


	//i tu pobieranie i liczenie odleg�o�ci i wpisywanie w poprawne miejsce w macierzy 
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


//---------------------------------- dynamic -----------------------------------------
void City::dynamic() {

	for (int i = 0; i < cityMatrix.size(); i++) {
		for (int j = 0; j < cityMatrix.size(); j++) {
			if (i == j)
				cityMatrix[i][j] = 0;
		}
	}


	printMatrix();
	cout << endl;


	vector <float> help;
	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < pow(2,numberOfCities); j++) {
			help.push_back(0);
		}
		g.push_back(help);
		p.push_back(help);
		help.clear();
	}

	cout << tsphelper() << endl;
}

int City::tsp(int start, int set) {
	int masked, mask, result = -1, temp;
	if (g[start][set] != -1) {
		return g[start][set];
	}
	else {
		for (int x = 0; x < numberOfCities; x++) {
			mask = pow(2, numberOfCities) - 1 - (int)pow(2, x);
			masked = set & mask;
			if (masked != set) {
				temp = cityMatrix[start][x] + tsp(x, masked);
				if (result == -1 || result > temp)
					result = temp;
				p[start][set] = x;
			}
		}
	}
	g[start][set] = result;
	return result;
}
int City::tsphelper() {
	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < pow(2, numberOfCities); j++) {
			g[i][j] = -1;
			p[i][j] = -1;
		}
	}

	// init matrix g ,from distance matrix graph
	for (int i = 0; i < numberOfCities; i++) {
		g[i][0] = cityMatrix[i][0];
	}

	return tsp(0, pow(2, numberOfCities) - 2);
}

void City::FloydWarshallAlgorithms() {


	vector <float> help;
	vector <int> help2;
	for (int i = 0; i < numberOfCities; i++) {
		for (int j = 0; j < numberOfCities; j++) {
			if (i == j) 
				help.push_back(0);
			else
				help.push_back(666);

			help2.push_back(-1);
			help2.push_back(-1);

		}
		shortestPath.push_back(help);
		streamManager.push_back(help2);
		help.clear();
		help2.clear();
	}

	
		for (int k = 0; k<numberOfCities; k++) {
			for (int i = 0; i<numberOfCities; i++) {
				for (int j = 0; j<numberOfCities; j++) {
					if (shortestPath[i][j]>shortestPath[i][k] + shortestPath[k][j]) { //jezeli droga z i do j, poprzez wierzcholek posredni k jest krotsza niz aktualnie najkrotsza znana trasa i->j to zaktualizuj
						shortestPath[i][j] = shortestPath[i][k] + shortestPath[k][j];
						streamManager[i][j] = k; //oznacza to ze idac po sciezce i~>j trzeba przejsc przez k
					}
				}
			}
		}

		for (int i = 0; i < numberOfCities; i++) {
			for (int j = 0; j < numberOfCities; j++) {
				cout << i + 1 << "->" << j + 1 << " dl. " << shortestPath[i][j] << ", przebieg: " << i + 1 << " ";
				droga(i, j);
				cout << j + 1 << endl;
			}
		}
}

void City::droga(int u, int v) { //odtwarza najkrotsza sciezke miedzy danymi wierzcholkami wykorzystujac macierz kierowania ruchem
	if (streamManager[u][v] != -1) { //dopoki nie dojdziemy do zwyklej krawedzi po ktorej trzeba wejsc to zchodz rekurencyjnie i wypisuj wierzcholek posredni k
		droga(u, streamManager[u][v]);
		cout << streamManager[u][v] + 1 << " ";
		droga(streamManager[u][v], v);
	}
}




//--------------------   bruteforce ---------------------------------------------------
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


//----------------------------- to wszystko jest do B&B---------------------------------
void City::duplicate()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		cityMatrix2.push_back(cityMatrix[i]);
	}
}

vector <vector <float>> City::Reduce(vector <vector <float>> m, float &r)		
{										
	vector <float> a;
	a = FindSmallestH(m);
	SubtractH(a, m);
	for (int i = 0; i < a.size(); i++)
	{
		r += a[i];
		//cout << a[i] << " ";
	}
	//cout << endl;
	a.clear();

	a = FindSmallestV(m);
	SubtractV(a, m);
	for (int i = 0; i < a.size(); i++)
	{
		r += a[i];
		//cout << a[i] << " ";
	}
	//cout << endl;
	//cout << "wynik r= " << r << endl;
	return m;
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
			if (i != j)m[i][j] -= a[i];
		}
	}
}

void City::SubtractV(vector <float> a, vector <vector <float>> &m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			if (i != j)m[j][i] -= a[i];
			
		}
	}
}

float City::findEdge(vector <vector <float>> m, int &row, int &column)
{
	vector <float> bestH;
	vector <float> bestV;
	vector <int> helpPath = { 0,0 };
	float max = -1, help;
	bestH = FindSmallestWithoutZeroH(m);			//potrzebe bardzo je�li wybior� koncepcje z odtwarzaniem 
	bestV = FindSmallestWithoutZeroV(m);
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			if (m[i][j] == 0 && i != j && m[i][j] != inv)
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

	return max;
}

vector<float> City::FindSmallestWithoutZeroH(vector <vector <float>> m)
{
	vector <float> smallest;
	for (int i = 0; i < m.size(); i++)
	{
		float help = INT_MAX;
		for (int j = 0; j < m.size(); j++)
		{
			if (help > m[i][j] && i != j && m[j][i] != 0)
			{
				help = m[i][j];
			}
		}
		smallest.push_back(help);
		//cout << help << endl;
	}
	return smallest;
}

vector<float> City::FindSmallestWithoutZeroV(vector <vector <float>> m)
{
	vector <float> smallest;
	for (int i = 0; i < m.size(); i++)
	{
		float help = INT_MAX;
		for (int j = 0; j < m.size(); j++)
		{
			if (help > m[j][i] && i != j && m[j][i] != 0)
			{
				help = m[j][i];
			}
		}
		smallest.push_back(help);
		//cout << help << endl;
	}
	return smallest;
}

void City::TraverseTree(vector <vector <float>> matrix, vector <vector <int>> *p, float LB)
{
	//cout << p->size() << endl;
	float r = 0;
	Reduce(matrix, r);
	int R=0, C=0;
	if (LB + r < minSolution)
	{
		if (p->size() == cityMatrix.size()-2)
		{
			//cout << "jest: " << r << endl;
			vector <int> h;
			h.push_back(0);
			h.push_back(1);
			p->push_back(h);
			minSolution = LB + r;
			path = *p;
		}
		else
		{
			float max = findEdge(matrix, R, C);

			vector <int> h;
			h.push_back(R);
			h.push_back(C);
			p->push_back(h);

			TraverseTree(deleteRowAndColumn(R, C, matrix), p, LB + r);
			if (LB + R + max < minSolution)
			{
				matrix[R][C] = inv;
				TraverseTree(matrix, p, LB + r);
			}
		}
		p->pop_back();
	}
	//cout << "mS: " << minSolution << endl;
}

float City::getMinSol() {
	return minSolution;
}
	
vector <vector <float>>  City::deleteRowAndColumn(int x, int y, vector <vector <float>> m)
{								
	vector <vector <float>> mNew;
	
	for (int i = 0; i < m.size(); i++)
	{
		vector <float> h;
		
		for (int j = 0; j < m.size(); j++)
		{
			if (j != y)
			{
				h.push_back(m[i][j]);
			}

		}
		if(i != x)mNew.push_back(h);
		h.clear();
	}
	

	for (int i = 0; i < mNew.size(); i++)		
	{													
		for (int j = 0; j < mNew.size(); j++)
		{
			if (i == j && mNew[i][j] != inv)mNew[i][j] = inv;
			
		}
	}
	//h.clear();
	return mNew;
}

