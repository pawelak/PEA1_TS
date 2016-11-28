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

	

	
public:
	vector <vector <int>> path;
	vector <vector <float>> cityMatrix;

	
	City();
	~City();
	City(string filename);
	void verticlesTab(string filename);
	void generateMatrix();

	void printMatrix();
	void printMatrix2();
	//void printSomeMatrix(vector<vector<float>> m);
	void bruteForce();
	unsigned long factorial(unsigned long f);
	void printBestPermutation();
	void duplicate();

	vector<vector<float>> Reduce(vector<vector<float>> m, float & r);

	vector<float> FindSmallestH(vector<vector<float>> m);
	vector<float> FindSmallestV(vector<vector<float>> m);
	void SubtractH(vector<float> a, vector<vector<float>>& m);
	void SubtractV(vector<float> a, vector<vector<float>>& m);




	float findEdge(vector<vector<float>> m, int & row, int & column);

	vector<float> FindSmallestWithoutZeroH(vector<vector<float>> m);

	vector<float> FindSmallestWithoutZeroV(vector<vector<float>> m);


	void TraverseTree(vector<vector<float>> matrix, vector<vector<int>>* p, float LB);

	vector<vector<float>> deleteRowAndColumn(int x, int y, vector<vector<float>> m);








};

