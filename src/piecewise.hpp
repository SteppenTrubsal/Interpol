#include "someFunc.hpp"
using namespace std;

struct piece{
	double xa;
	double xb;
	double a;
	double b;
};

vector<piece> createPiecewise(double a, double b, double n) {
	vector<piece> res;
	vector<double> X = calcX(a, b, n);
	for (int i = 0; i < X.size()-1; i++) {
		piece onePiece;
		onePiece.xa = X[i];
		onePiece.xb = X[i + 1];
		res.push_back(onePiece);
	}
	return res;
}

void calcA(vector<piece>& n, string func) {
	for (int i = 0; i < n.size(); i++) {
		n[i].a = (fun(func, n[i].xb) - fun(func, n[i].xa)) / (n[i].xb - n[i].xa);
	}
}

void calcB(vector<piece>& n, string func) {
	for (int i = 0; i < n.size(); i++) {
		n[i].b = fun(func, n[i].xa) - n[i].a * n[i].xa;
	}
}

graphic calcPieceGraphic(double a, double b, double n, string func, int precision) {
	vector<piece> piecewiseLinear = createPiecewise(a, b, n);
	calcA(piecewiseLinear, func);
	calcB(piecewiseLinear, func);

	graphic res;
	double dx = (b - a) / precision;
	for (int i = 0; i < piecewiseLinear.size(); i++) {
		double y = 0;
		double x = piecewiseLinear[i].xa;
		for (; x < piecewiseLinear[i].xb;x += dx) {
			y = piecewiseLinear[i].a * x + piecewiseLinear[i].b;

			res.x.push_back(x);
			res.y.push_back(y);
		}
	}
	return res;
}