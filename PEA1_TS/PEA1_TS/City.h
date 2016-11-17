#pragma once
class City
{
private:
	vector <vector <int>> cityTab;
	vector <vector <float>> cityMatrix;
	vector <vector <float>> cityMatrix2;

	int numberOfCities;
	vector <int> bestWay;
	float bestCost = INT_MAX;

public:
	City();
	~City();
	City(string filename);
	void verticlesTab(string filename);
	void generateMatrix();
	void printMatrix();
	void bruteForce();
	unsigned long factorial(unsigned long f);
	void printBestPermutation();
	void duplicate();
	void LittlesAlgotithm();
	vector<float> FindSmallestH();

	vector<float> FindSmallestWithout0H();

	vector<float> FindSmallestV();

	void SubtractH(vector<float> a);

	void SubtractV(vector<float> a);

	float addLB(int a, vector<float> b);



};

