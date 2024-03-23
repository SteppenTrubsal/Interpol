#include <vector>
#include <muParser.h>
using namespace std;

vector<double> reverse(vector<double> n) {
	vector<double> rev;
	for (int i = 0; i < n.size(); i++) { rev.push_back(n[i]); }
	return rev;
}
vector<double> getSpline(vector<double> n, int st, int fn) {
	return vector<double>(n.begin() + st, n.begin() + n.size() - fn);
}
double coef(vector<double> n, int h) {
	if (h == 0) { return 1; }
	int sum = 0;
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

double fun(string& fun, double x) {
	mu::Parser parser;
	parser.SetExpr(fun);
	parser.DefineVar("x", &x);
	return parser.Eval();
}