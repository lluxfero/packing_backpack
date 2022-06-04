#include <iostream>
#include <Windows.h>
#include <clocale>
using namespace std;

int err_n() {
	int m, ival = 1;
	cin >> m;
	while (ival == 1) {
		if (cin.fail() || m < 1) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка! Попробуйте еще раз: ";
			cin >> m;
		}
		else
			ival = 0;
	}
	return m;
}

int err_wv() {
	int m, ival = 1;
	cin >> m;
	while (ival == 1) {
		if (cin.fail() || m < 0) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка! Попробуйте еще раз: ";
			cin >> m;
		}
		else
			ival = 0;
	}
	return m;
}

void sorting(float* spec_v, int** w_v, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (spec_v[j] < spec_v[j + 1]) {
				swap(spec_v[j], spec_v[j + 1]);
				for (int k = 0; k < 2; k++) {
					swap(w_v[j][0], w_v[j + 1][0]);
					swap(w_v[j][1], w_v[j + 1][1]);
				}
			}
}

void packing_backpack(int** w_v, int n, int W) {
	int help_w = 0, i = 0;
	float help_v = 0;
	while (help_w < W && i < n) {
		if ((help_w + w_v[i][0]) <= W) {
			help_w = help_w + w_v[i][0];
			help_v = help_v + w_v[i][1];
		}
		else {
			help_v = float(help_v) + ((float(W) - float(help_w)) / float(w_v[i][0])) * float(w_v[i][1]);
			help_w = W;
		}
		i++;
	}
	cout << "Ценность уложенных в рюкзак предметов: " << help_v << endl;
}

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите вместимость рюкзака: ";
	int W = err_wv();

	cout << "Введите количество предметов: ";
	int n = err_n();

	int** w_v = new int* [n];
	for (int i = 0; i < n; i++)
		w_v[i] = new int[2];

	cout << "Введите вес и ценность каждого предмета: " << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 2; j++)
			w_v[i][j] = err_wv();


	float* spec_v = new float [n];
	for (int i = 0; i < n; i++)
		spec_v[i] = w_v[i][1] / w_v[i][0];

	sorting(spec_v, w_v, n);
	packing_backpack(w_v, n, W);
}