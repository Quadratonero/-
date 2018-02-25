// DZClass.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "conio.h"


using namespace std;

class Company {

public:
	Company(string _name, int _revenue, int _employees) {
		name = _name;
		revenue = _revenue;
		employees = _employees;
	}
	Company() {
		name = "Name";
		revenue = 1;
		employees = 1000;
	}

	void setRevenue(int _revenue) {
		revenue = _revenue;
	}
	int getRevenue() {
		return revenue;
	}

	string getName() {
		return name;
	}

	void makeMoney() {
		revenue += 1;
	}



private:
	int revenue;
	int employees;
	string name;


};

void sortByRevenue(Company companies[], int size) {

	int temp;
	//пузырьком
	for (int i = 0; i < size - 1; i++)
		for (int j = size - 1; j > i; j--)
		{
			if (companies[j].getRevenue() < companies[j - 1].getRevenue())
			{
				temp = companies[j - 1].getRevenue();
				companies[j - 1].setRevenue(companies[j].getRevenue());
				companies[j].setRevenue(temp);
			}
		}

	//вывод отсортированного массива
	for (int i = 0; i < 4; i++) {
		cout << companies[i].getName() << " - " << companies[i].getRevenue() << endl;
	}
	cout << endl;
}



Company findByName(Company companies[], int size, string name) {
	bool found = false;
	int i = 0;
	while (i < size) {
		if (companies[i].getName() == name) {
			found = true;
			break;
		}
		i++;
	}

	if (found) {
		return companies[i];
	}
	else
	{
		return new Company();
	}

}


int main()
{

	Company companies[4];

	companies[0] = new Company apple("Apple", 129, 123000);;
	companies[1] = new Company tesla("Tesla", 11, 33000);;
	companies[2] = new Company intel("Intel", 62, 106000);;
	companies[3] = new Company netflix("Netflix", 11, 5400);

	//вывод массива
	for (int i = 0; i < 4; i++) {
		cout << companies[i].getName() << " - " << companies[i].getRevenue() << endl;
	}
	cout << endl;

	sortByRevenue(companies, 4);

	findByName(companies, 4, "Tesla");
	findByName(companies, 4, "Microsoft");

	_getch();
}

