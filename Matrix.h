#ifndef MATRIX_H
#define MATRIX_H

#include "common.h"

class Matrix {
public:
	Matrix();
	Matrix(const int &, const int &); // row, column
	Matrix(const Matrix &);

	Matrix & operator =(const Matrix &);

	int getRow() const;
	int getColumn() const;

	void setRow(const int &);
	void setColumn(const int &);

	RTdouble getValue(const int &, const int &) const;
	void setValue(const int &, const int &, const RTdouble &);

	Matrix operator *(const Matrix &);
	Matrix & operator *=(const Matrix &);

	Matrix pow(const int &);
	
	void print(const string &) const;
private:
	vector <vector <RTdouble> > vals;
};

#endif