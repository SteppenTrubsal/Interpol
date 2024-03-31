#include<iostream>
#include "lagrange.hpp"
#include "piecewise.hpp"
#include "Window.hpp"
using namespace std;

int main() {
	double a = -10;
	double b = 10;
	double n = 5;
	int precision = 10;
	Window window;
	window.start();
	/*
	cout << "Enter an equation: ";
	string func;
	getline(cin, func);

	graphic lg = calcLagGraphic(a, b, n, func, precision);
	graphic pw = calcPieceGraphic(a, b, n, func, precision);

	for (int i = 0; i < pw.x.size(); i++) {
		cout << pw.x[i] << " " << pw.y[i] << endl;
	}

	if (true) {
		graphic gr = getGraph(a, b, n, func, precision);
		cout << getDiff(gr, pw) << endl;
	}*/
}