#include "Matrix.h"
#include "Constants.h"

Matrix::Matrix() {
	vals.resize(0);
}

Matrix::Matrix(const int &r, const int &c) {
	vals.resize(r);
	for(int i = 0; i < r; i++) {
		vals[i].resize(c);
	}
}

Matrix & Matrix::operator =(const Matrix &mat) {
	int r, c;
	setRow(r = mat.getRow());
	setColumn(c = mat.getColumn());
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			setValue(i, j, mat.getValue(i, j));
		}
	}
	return *this;
}

// Copy Constructor
Matrix::Matrix(const Matrix &mat){
	*this=mat;
}

int Matrix::getRow() const {
	return vals.size();
}

void Matrix::setRow(const int &r) {
	vals.resize(r);
}

int Matrix::getColumn() const {
	if(getRow() < 1) {
		return 0;
	}
	return vals[0].size();
}

void Matrix::setColumn(const int &c) {
	int r = getRow();
	for(int i = 0; i < r; i++) {
		vals[i].resize(c);
	}
}

RTdouble Matrix::getValue(const int &i, const int &j) const {
	// should check i, j with boundary
	// fake now
	return vals[i][j];
}

void Matrix::setValue(const int &i, const int &j, const RTdouble &v) {
	// should check i, j with boundary
	// fake now
	vals[i][j] = v;
}
Matrix Matrix::operator *(const Matrix &mat) {
	if(getColumn() == mat.getRow()) {
		int r = getRow(), c = mat.getColumn(), t = getColumn();
		Matrix temp(r, c);
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				RTdouble temp_val = RT_ZERO;
				for(int k = 0; k < t; k++) {
					temp_val += getValue(i, k) * mat.getValue(k, j);
				}
				temp.setValue(i, j, temp_val);
			}
		}
		return temp;
	}
	else {
		// should check!!!!
		printf("column(a) != row(b), operation deprecated!\n");
		printf("Matrix a returned!\n");
		return *this;
	}
}

Matrix & Matrix::operator *=(const Matrix &mat) {
	return *this = Matrix(*this) * mat;
}

void Matrix::print(const string &prompt) const {
	int r = getRow(), c = getColumn();
	printf("Matrix %s |row=%d, column=%d|>\n", prompt.c_str(), r, c);
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			printf("%.2lf%c", getValue(i, j), j == c - 1?'\n':' ');
		}
	}
	printf("END\n");
}