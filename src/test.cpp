#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> reverse(vector<int> n) {
	vector<int> temp;
	for (int i = n.size() - 1; i >= 0; i--) {
		temp.push_back(n[i]);
	}
	return temp;
}

vector<int> getSpline(vector<int> n, int st, int fin) {
	vector<int> spline(n.begin() + st, n.begin() + n.size()-fin);
	return spline;
}

int mul(vector<int> n, int h) {
	if (h == 0) { return 1; }
	int sum = 0;
	vector<int> spline = getSpline(n,h-1,0);
	spline = reverse(spline);
	for (int i = 0; i < spline.size(); i++) {
		sum += spline[i] * mul(getSpline(n,0,i+1), h - 1);
	}
	return sum;
}

vector<int> coef(vector<int> n) {
	for (int i = 0; i < n.size(); i++) {

	}
	return { 1 };
}

int main() {
	vector<int> gg = { 2,7,5,9 };
	cout << "hui" << mul(gg, 1) << endl;
	cout << mul(gg, 2) << endl;
	cout << mul(gg, 3) << endl;
	cout << mul(gg, 4) << endl;
}