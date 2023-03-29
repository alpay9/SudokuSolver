#pragma once
#include <iostream>
#include <random>
#include "sudoku.h"
#include "grid.h"
//Alpay Nacar
using namespace std;

sudoku::sudoku() {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			mat.board[row][col] = 0;
			init.board[row][col] = 0;
			poss.board[row][col] = new int[9];
			for (int num = 1; num <= 9; num++) {
				poss.board[row][col][num - 1] = num;
			}
		}
	}
}

void sudoku::generate() {
	std::random_device rd;
	std::mt19937 gen(rd());

	solve_backtrack();

	// Remove some numbers to create the puzzle
	int num_removed = 0;
	int difficulty = 40;
	while (num_removed < difficulty) {
		int row = uniform_int_distribution<>(0, 8)(gen);
		int col = uniform_int_distribution<>(0, 8)(gen);
		int val = mat.get(row, col);
		if (val) {
			unset(row, col);
			num_removed++;
		}
	}
}

void sudoku::setMat(int row, int col, int num) {
	mat.board[row][col] = num;
}

void sudoku::setInit(int row, int col, int num) {
	init.board[row][col] = num;
}

void sudoku::count_and_make(int row, int col) {
	int n = 0;
	for (int i = 0; i < 9 && n != -1; i++) {
		if (poss.board[row][col][i]) {
			if (n) n = -1;
			else n = i + 1;
		}
	}
	if (n != -1) {
		setMat(row, col, n);
		printPoss();
		print();
	}
}

void sudoku::setPoss(int row, int col, int num) {
	int start_row = row / 3 * 3,
		end_row = row / 3 * 3 + 2,
		start_col = col / 3 * 3,
		end_col = col / 3 * 3 + 2;
	for (int i = 0; i < 9; i++) {
		// Column
		if (i<start_col || i>end_col) {
			if (poss.board[row][i][num - 1]) {
				poss.board[row][i][num - 1] = 0;
				count_and_make(row, i);
			}
		}
		// Row
		if (i<start_row || i>end_row) {
			if (poss.board[i][col][num - 1]) {
				poss.board[i][col][num - 1] = 0;
				count_and_make(i, col);
			}
		}
		// Square
		if (row / 3 * 3 + i / 3 != row || col / 3 * 3 + i % 3 != col)
			if (poss.board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3][num - 1]) {
				poss.board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3][num - 1] = 0;
				count_and_make(row / 3 * 3 + i / 3, col / 3 * 3 + i % 3);
			}
		// cell itself
		if (i != num - 1) poss.board[row][col][i] = 0;
	}
}

void sudoku::set(int row, int col, int num) {
	setMat(row, col, num);
	setInit(row, col, num);
	setPoss(row, col, num);
}

void sudoku::unset(int row, int col) {
	int val = mat.board[row][col];
	if (val) {
		mat.board[row][col] = 0;
		for (int i = 0; i < 9; i++) {
			poss.board[row][i][val - 1] = val;
			poss.board[i][col][val - 1] = val;
			poss.board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3][val - 1] = val;
		}
	}
}

bool sudoku::isInit(int row, int col) { return init.board[row][col]; }

bool sudoku::isValid(int row, int col, int val) {
	if (row < 0 || row>8 || col < 0 || row>8) return false;
	for (int i = 0; i < 9; i++) {
		if (i != col && mat.board[row][i] == val) return false;
		if (i != row && mat.board[i][col] == val) return false;
		if ((row != row / 3 * 3 + i / 3 || col != col / 3 * 3 + i % 3) && mat.board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] == val) return false;
	}
	return true;
}

bool sudoku::isPoss(int row, int col, int val) {
	return poss.board[row][col][val - 1];
}

bool sudoku::isSolved() {
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (!mat.board[row][col]) return false;
		}
	}
	return true;
}

bool sudoku::backtracker(mt19937& gen, int row = 0, int col = 0) {
	if (row == 9) return true;
	if (!mat.board[row][col]) {
		int rnd = uniform_int_distribution<>(0, 8)(gen);
		for (int n = 1; n <= 9; n++) {
			if (isValid(row, col, ((n + rnd) % 9 + 1))) {
				mat.board[row][col] = (n + rnd) % 9 + 1;
				if (backtracker(gen, row + (col + 1) / 9, (col + 1) % 9)) return true;
			}
		}
		mat.board[row][col] = 0;
		return false;
	}
	else {
		return backtracker(gen, row + (col + 1) / 9, (col + 1) % 9);
	}
}

void sudoku::solve_backtrack() {
	std::random_device rd;
	std::mt19937 gen(rd());

	if (!backtracker(gen)) cout << "error";
}

bool sudoku::brute_force(int row = 0, int col = 0) {
	if (row == 9) return true;
	if (!mat.board[row][col]) {
		for (int n = 1; n <= 9; n++) {
			if (isValid(row, col, n)) {
				mat.board[row][col] = n;
				if (brute_force(row + (col + 1) / 9, (col + 1) % 9)) return true;
			}
		}
		mat.board[row][col] = 0;
		return false;
	}
	else {
		return brute_force(row + (col + 1) / 9, (col + 1) % 9);
	}
}

void sudoku::print() {
	system("cls");
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (mat.board[row][col])
				cout << mat.board[row][col];
			else
				cout << " ";
			if (col == 2 || col == 5) cout << "|";
		}
		cout << endl;
		if (row == 2 || row == 5) cout << "---+---+---" << endl;
	}
}

// for debug purposes
void sudoku::printPoss() { 
	system("cls");
	for (int row = 0; row < 9; row++) {
		for (int cell_row = 0; cell_row < 3; cell_row++) {
			for (int col = 0; col < 9; col++) {
				for (int cell_col = 0; cell_col < 3; cell_col++) {
					cout << poss.board[row][col][cell_row * 3 + cell_col];
				}
				if (col != 8) cout << "|";
				if (col == 2 || col == 5) cout << "|";
			}
			cout << endl;
		}
		if (row == 2 || row == 5) cout << "---+---+---++---+---+---++---+---+---" << endl;
		if (row != 8) cout << "---+---+---++---+---+---++---+---+---" << endl;
	}
	cout << endl;
}
