#pragma once

#include <vector>
#include <iostream>
using namespace std;

namespace MatrixOp {
	typedef vector<double> Vector;
	typedef vector<Vector> Matrix;
	// overload operators as independent functions
	Vector operator*(const Matrix& C, const Vector& V);
	Vector operator*(const double& a, const Vector& V);
	Vector operator*(const Vector& V, const Vector& W);
	Vector operator+(const double& a, const Vector& V);
	Vector operator+(const Vector& V, const Vector& W);  // referece to const for V and W, V + W -> U, V and W do not change
	Vector operator=(const Vector& V, const Vector& W);
	Vector operator+=(const Vector& V, const Vector& W);
	Vector exp(const Vector& V);
	Vector operator-(const Vector& V, const Vector& W); // vector substraction
	Vector operator^(const Vector& V, const Vector& W); // dot product without summation
	ostream& operator<<(ostream& out, Vector& V);	// Overload cout for Vector
	ostream& operator<<(ostream& out, Matrix& W);	// Overload cout for Matrix
	Matrix ConstMatrix(double c,int nrow, int ncol);
	Vector ConstVector(double c,int size);
}