#pragma once
class City
{
private:
	vector <vector <int>> cityTab;
	vector <vector <float>> cityMatrix;
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
	void verticlesTab();
	void print();
};

