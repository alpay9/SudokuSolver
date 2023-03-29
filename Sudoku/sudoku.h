#pragma once
#include <iostream>
#include <random>
#include "grid.h"
//Alpay Nacar
using namespace std;

class sudoku
{
private:
	grid<int> mat;
	grid<int> init;
	grid<int*> poss;

public:
	sudoku();
	void generate();

	void setMat(int row, int col, int num);
	void setInit(int row, int col, int num);
	void count_and_make(int row, int col);
	void setPoss(int row, int col, int num);
	void set(int row, int col, int num);
	void unset(int row, int col);
	bool isInit(int row, int col);
	bool isValid(int row, int col, int val);
	bool isPoss(int row, int col, int val);
	bool isSolved();
	
	bool backtracker(mt19937& gen, int row, int col);
	void solve_backtrack();
	bool brute_force(int row, int col);

	void print();
	void printPoss();
};

#include "sudoku.cpp"