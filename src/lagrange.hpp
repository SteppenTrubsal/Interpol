#include "someFunc.hpp"
using namespace std;

vector<double> calcX(double a, double b, double n) {
	double it = (b - a) / n;
	vector<double> vecX;
	for (int i = 0; i < n;i++) {
		vecX.push_back(a + it * i);
	}
	vecX.push_back(b);
	return vecX;
}

vector<double> getBasisUpper(vector<double> n) {
	vector<double> upper;
	upper.push_back(1);
	for (int i = 0; i < n.size(); i++) {
		upper.push_back(coef(n, i)*con(i+1));
	}
	return upper;
}
double getbasisLower(vector<double> n, double xi) {
	double p = 1;
	for (int i = 0; i < n.size(); i++) { p *= (xi - n[i]); }
	return p;
}
vector<double> getIPol(vector<double> n, int idx) {
	double x = n[idx];
	n.erase(n.begin() + idx);
	double del = getbasisLower(n, x);
	vector<double> res = getBasisUpper(n);
	for (int i = 0; i < res.size(); i++) {
		res[i] = res[i] / del;
	}
	return res;
}
vector<double> getLagrange(double a, double b, double n, string func) {
	vector<double> X = calcX(a, b, n);
	vector<double> res(X.size()-1, 0);

	for (int i = 0; i < X.size(); i++) {
		vector<double> pol = getIPol(X, i);
		double yi = fun(func, X[i]);
		for (int i = 0; i < pol.size(); i++) {
			pol[i] *= yi;
			res[i] += pol[i];
		}
	}
	return res;
}

struct graphic {
	vector<double> x;
	vector<double> y;
};
graphic calcGraphic(double a, double b, double n, string func, int precision) {
	graphic res;
	double dx = (b - a) / precision;
	vector<double> multipliers = getLagrange(a, b, n, func);
	for (double x = a; x <= b; x += dx) {
		double y = 0;
		int maxPower = multipliers.size() - 1;
		for (int i = 0; i < multipliers.size(); i++) {
			y += pow(x, maxPower - i) * multipliers[i];
		}

		res.x.push_back(x);
		res.y.push_back(y);
	}
	return res;
}