#include<iostream>
#include "lagrange.hpp"
using namespace std;

int main() {
	double a = -5;
	double b = 5;
	double n = 10;
	int precision = 20;


	cout << "Enter an equation: ";
	string func;
	getline(cin, func);

	graphic gr = calcGraphic(a, b, n, func, precision);

	for (int i = 0; i < gr.x.size(); i++) {
		cout << gr.x[i] << " " << gr.y[i] << endl;
	}
}