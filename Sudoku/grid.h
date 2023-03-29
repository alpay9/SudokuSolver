#pragma once
#include <iostream>
//Alpay Nacar
using namespace std;

template <typename T>
class grid
{
private:
	T** board;
public:
	grid();
	grid(const grid& copy);
	~grid();

	T& get(int row, int col);
	void set(int row, int col, T& val);
	bool isEmpty(int row, int col);

	grid operator=(grid rhs);
	
	friend class sudoku;
};

#include "grid.cpp"