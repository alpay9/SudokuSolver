#include <iostream>
#include <string>
#include "sudoku.h"
//Alpay Nacar
using namespace std;

int main() {
	sudoku game; 
	game.generate();
	string ans = "";
	string m = "quit, solve, set";
	int r, c, n;

	while (ans!="quit" && ans!="solve") {
		if (ans == "Invalid") cout << ans << endl;
		else game.print();
		cout << m << endl;
		cin >> ans;
		if (ans == "set") {
			cout << "row:"; cin >> r;
			cout << "col:"; cin >> c;
			cout << "num:"; cin >> n;
			if (game.isValid(r - 1, c - 1, n)) {
				game.setMat(r-1, c-1, n);
			}
			else {
				ans = "Invalid";
			}
		}
	}
	if (ans == "solve") {
		game.brute_force();
		game.print();
		cout << "Game solved" << endl;
	}

	return 0;
}