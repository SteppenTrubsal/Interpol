#include "someFunc.hpp"
using namespace std;

vector<double> getBasisUpper(vector<double> n) {
	vector<double> upper(n.size() + 1);
	for (int i = 0; i < upper.size(); i++) {
		upper[i] = (coef(n, i)*con(i));
	}
	return upper;
}
double getbasisLower(vector<double> n, double xi) {
	double p = 1;
	for (int i = 0; i < n.size(); i++) { 
		p *= (xi - n[i]); 
	}
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
	vector<double> res(X.size(), 0);

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

 graphic calcLagGraphic(double a, double b, double n, string func, int precision) {
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