#pragma once
#include <iostream>
#include "grid.h"
//Alpay Nacar
using namespace std;

template <class T>
grid<T>::grid() {
	board = new T * [9];
	for (int i = 0; i < 9; i++) {
		board[i] = new T[9];
	}
}

template <class T>
grid<T>::grid(const grid& copy) {
	board = new T * [9];
	for (int i = 0; i < 9; i++) {
		board[i] = new T[9];
		for (int j = 0; j < 9; j++) {
			board[i][j] = copy.board[i][j];
		}
	}
}


template <class T>
grid<T>::~grid() {
	for (int i = 0; i < 9; i++) {
		delete[] board[i];
	}
	delete[] board;
}


template <class T>
T& grid<T>::get(int row, int col) {
	return board[row][col];
}

template <class T>
void grid<T>::set(int row, int col, T& val) {
	board[row][col] = val;
}

template <class T>
bool grid<T>::isEmpty(int row, int col) {
	return !board[row][col];
}

template <class T>
grid<T> grid<T>::operator=(grid rhs) {
	if (this == &rhs) return *this;

	for (int i = 0; i < 9; i++) {
		delete[] board[i];
	}
	delete[] board;

	board = new T * [9];
	for (int i = 0; i < 9; i++) {
		board[i] = new T[9];
		for (int j = 0; j < 9; j++) {
			board[i][j] = rhs.board[i][j];
		}
	}
	return *this;
}