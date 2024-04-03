#pragma once
#include <muParser.h>
using namespace std;

vector<double> reverse(vector<double>& n) {
	vector<double> rev;
	for (int i = n.size() - 1; i >= 0; i--) { rev.push_back(n[i]); }
	return rev;
}
vector<double> getSpline(vector<double> n, int st, int fn) {
	return vector<double>(n.begin() + st, n.begin() + n.size() - fn);
}
double coef(vector<double> n, int h) {
	if (h == 0) { return 1; }
	double sum = 0;
	vector<double> spline = getSpline(n, h - 1, 0);
	spline = reverse(spline);
	for (int i = 0; i < spline.size(); i++) {
		sum += spline[i] * coef(getSpline(n, 0, i + 1), h - 1);
	}
	return sum;
}

int con(int t) {
	if (t % 2 == 1) { return -1; }
	else { return 1; }
}

vector<double> calcX(double a, double b, double n) {
	double it = (b - a) / n;
	vector<double> vecX;
	if (n == 1) { it = 0; }
	for (int i = 0; i < n;++i) {
		vecX.push_back(a + it * i);
	}
	vecX.push_back(b);
	return vecX;
}

double fun(string& fun, double x) {
	mu::Parser parser;
	parser.SetExpr(fun);
	parser.DefineVar("x", &x);
	return parser.Eval();
}

struct graphic {
	vector<double> x;
	vector<double> y;


	graphic() {}

	graphic(const graphic& other) {
		x = other.x;
		y = other.y;
	}


	graphic& operator=(const graphic& other) {
		if (this != &other) { 
			x = other.x;
			y = other.y;
		}
		return *this;
	}
};

graphic getGraph(double a, double b, double n, string func, double precision) {
	graphic res;
	double dx = (b - a) / precision;
	for (double x = a; x <= b; x += dx) {
		double y = fun(func, x);

		res.x.push_back(x);
		res.y.push_back(y);
	}
	return res;
}

double getDiff(graphic a, graphic b) {
	double diff = 0;
	for (int i = 0; i < a.x.size(); i++) {
		diff = (diff > abs(a.y[i] - b.y[i])) ? diff : abs(a.y[i] - b.y[i]);
	}
	return diff;
}