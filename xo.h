#include "Matrix.h"
#pragma once
class XO
{
protected:
	Matrix<double> cells = Matrix<double>::colVector(9, 0);
	Matrix<double> arr = Matrix<double>::colVector(9, 1);
public:
	XO() {}

	void set(size_t i, double val) {
		cells[i][0] = val;
		if (val != 0) {
			arr[i][0] = 0;
		}
		else {
			arr[i][0] = 1;
		}
	}

	void set_board(const Matrix<double> board) {
		cells = board;
		for (size_t i = 0; i < 9; i++) {
			if (cells[i][0] == 0) { arr[i][0] = 1;  }
			else { arr[i][0] = 0; }
		}
	}

	double get(size_t i) {
		return cells[i][0];
	}

	bool check_victory(int color) {
		int counter=0;

		for (size_t i = 0; i < 3; i++) {
			if(int(cells[i][0])==color && int(cells[i+3][0])==color && int(cells[i+6][0])==color) return true;
		}
		for (size_t i = 0; i < 7; i+=3) {
			if (int(cells[i][0]) == color && int(cells[i + 1][0]) == color && int(cells[i + 2][0]) == color) return true;
		}
		if (int(cells[0][0]) == color && int(cells[4][0]) == color && int(cells[8][0]) == color) return true;
		if (int(cells[2][0]) == color && int(cells[4][0]) == color && int(cells[6][0]) == color) return true;
		return false;
		/*for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 7; j += 3) {
				if (int(cells[i+j][0]) == color) {
					counter++;
				}
				else counter = 0;
				if (counter == 3) return true;
			}
			counter = 0;
		}
		counter = 0;
		for (size_t i = 0; i < 7; i += 3) {
			for (size_t j = 0; j < 3; j++) {
				if (int(cells[i + j][0]) == color) counter++;
				else counter = 0;
				if (counter == 3) return true;
			}
			counter = 0;
		}
		counter = 0;
		for (size_t i = 0; i < 9; i += 4) {
			if (int(cells[i][0]) == color) counter++;
			else counter = 0;
			if (counter == 3) return true;
		}
		counter = 0;
		for (size_t i = 2; i < 7; i += 2) {
			if (int(cells[i][0]) == color) counter++;
			else counter = 0;
			if (counter == 3) return true;
		}
		return false;*/
	}

	bool check_draw() {
		for (size_t i = 0; i < 9; i++) {
			if (int(cells[i][0]) == 0) { return false; }
		}
		if (check_victory(1.0) || check_victory(-1.0)) {
			return false;
		}
		return true;
	}

	void restart() {
		for (size_t i = 0; i < 9; i++) {
			cells[i][0] = 0;
			arr[i][0] = 1;
		}
	}

	Matrix<double>* get_board() {
		return &cells;
	}

	Matrix<double>* get_arr() {
		return &arr;
	}

	void inversion() {
		for (size_t i = 0; i < 9; i++) {
			cells[i][0] *= (-1);
		}
	}

	void Print() {
		for (size_t i = 0; i < 9; i++) {
			if (i % 3 == 0) std::cout << std::endl;
			if (int(cells[i][0]) == 0) std::cout << " .";
			if (int(cells[i][0]) == 1) std::cout << " x";
			if (int(cells[i][0]) == -1) std::cout << " o";
			if (int(cells[i][0]) != 0 && (cells[i][0]) != 1 && (cells[i][0]) != -1) std::cout << cells[i][0];
		}
		std::cout << std::endl;
	}
};
