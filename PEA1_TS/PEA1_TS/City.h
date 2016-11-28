#pragma once
class City
{
private:

	vector <vector <int>> cityTab;
	
	vector <vector <float>> cityMatrix2;


	int numberOfCities;
	vector <int> bestWay;
	float bestCost = INT_MAX;
	float LB;
	float minSolution;
	float inv;
	vector <int> xy;

	vector <float> bestH;
	vector <float> bestV;

	vector <vector <int>> path;
public:
	vector <vector <float>> cityMatrix;

	
	City();
	~City();
	City(string filename);
	void verticlesTab(string filename);
	void generateMatrix();

	void printMatrix();
	void printMatrix2();
	void printSomeMatrix(vector<vector<float>> m);
	void bruteForce();
	unsigned long factorial(unsigned long f);
	void printBestPermutation();
	void duplicate();

	vector<vector<float>> Reduce(vector<vector<float>> m, float & r);

	vector<float> FindSmallestH(vector<vector<float>> m);
	vector<float> FindSmallestV(vector<vector<float>> m);
	void SubtractH(vector<float> a, vector<vector<float>>& m);
	void SubtractV(vector<float> a, vector<vector<float>>& m);




	float findEdge(vector<vector<float>> m, int r, int c);

	float findEdge(vector<vector<float>> m, int & row, int & column);

	vector<float> FindSmallestWithoutZeroH();

	vector<float> FindSmallestWithoutZeroV();

	void TraverseTree(vector<vector<float>> matrix, vector<vector<int>> p, float LB);

	vector <vector <float>>  deleteRowAndColumn(int x, int y);

	vector<vector<int>> addEdge(int a, int b, vector<vector<int>> help);






};

