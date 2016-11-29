#include "stdafx.h"
#include "Generator.h"


Generator::Generator()
{
}


Generator::~Generator()
{
}


Generator::Generator(int cityAmount, int horizontalBorderDown, int horizontalBorderUp, int verticalBorderLeft, int verticalBorderRight)
{
	vector <int> tab;
	srand(time(NULL));
	fstream plik("plik.txt", ios::out);				//wpisuje do pliku 
	if (plik.good())
	{
		plik << cityAmount << "\n";
		for (int i = 0; i < cityAmount; i++)
		{
			tab.push_back(rand() % (horizontalBorderUp - horizontalBorderDown) + horizontalBorderDown);
			tab.push_back(rand() % (verticalBorderRight - verticalBorderLeft) + verticalBorderLeft);
			plik <<i <<" "<<tab[0] << " " << tab[1] << "\n";
			tab.clear();
		}
	}

	plik.close();
}