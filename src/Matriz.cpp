#ifndef __QS_MAdoubleRIX_CPP
#define __QS_MAdoubleRIX_CPP

#include "Matriz.h"

// Parameter Constructor

Matriz::Matriz(int _linhas, int _colunas) {
	mat.resize(_linhas);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(_colunas, 0.0);
	}
	linhas = _linhas;
	colunas = _colunas;
}

// Copy Constructor

Matriz::Matriz(const Matriz& matrizB) {
	mat = matrizB.mat;
	linhas = matrizB.get_linhas();
	colunas = matrizB.get_colunas();
}

// (Virtual) Destructor

Matriz::~Matriz() {
}

// Assignment Operator

Matriz& Matriz::operator=(const Matriz& matrizB) {
	if (&matrizB == this)
		return *this;

	int new_linhas = matrizB.get_linhas();
	int new_colunas = matrizB.get_colunas();

	mat.resize(new_linhas);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(new_colunas);
	}

	for (int i = 0; i < new_linhas; i++) {
		for (int j = 0; j < new_colunas; j++) {
			mat[i][j] = matrizB(i, j);
		}
	}
	linhas = new_linhas;
	colunas = new_colunas;

	return *this;
}

// Addition of two matrices

Matriz Matriz::operator+(const Matriz& matrizB) {
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			result(i, j) = this->mat[i][j] + matrizB(i, j);
		}
	}

	return result;
}

// Cumulative addition of this matrix and another

Matriz& Matriz::operator+=(const Matriz& matrizB) {
	int linhas = matrizB.get_linhas();
	int colunas = matrizB.get_colunas();

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			this->mat[i][j] += matrizB(i, j);
		}
	}

	return *this;
}

// Subtraction of this matrix and another

Matriz Matriz::operator-(const Matriz& matrizB) {
	int linhas = matrizB.get_linhas();
	int colunas = matrizB.get_colunas();
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			result(i, j) = this->mat[i][j] - matrizB(i, j);
		}
	}

	return result;
}

// Cumulative subtraction of this matrix and another

Matriz& Matriz::operator-=(const Matriz& matrizB) {
	int linhas = matrizB.get_linhas();
	int colunas = matrizB.get_colunas();

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			this->mat[i][j] -= matrizB(i, j);
		}
	}

	return *this;
}

// Left multiplication of this matrix and another

Matriz Matriz::operator*(const Matriz& matrizB) {
	int linhas = matrizB.get_linhas();
	int colunas = matrizB.get_colunas();
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			for (int k = 0; k < linhas; k++) {
				result(i, j) += this->mat[i][k] * matrizB(k, j);
			}
		}
	}

	return result;
}

// Cumulative left multiplication of this matrix and another

Matriz& Matriz::operator*=(const Matriz& matrizB) {
	Matriz result = (*this) * matrizB;
	(*this) = result;
	return *this;
}

// Calculate a transpose of this matrix

Matriz Matriz::transpose() {
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			result(i, j) = this->mat[j][i];
		}
	}

	return result;
}

// Matrix/scalar addition

Matriz Matriz::operator+(const double& matrizB) {
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			result(i, j) = this->mat[i][j] + matrizB;
		}
	}

	return result;
}

// Matrix/scalar subtraction

Matriz Matriz::operator-(const double& matrizB) {
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			result(i, j) = this->mat[i][j] - matrizB;
		}
	}

	return result;
}

// Matrix/scalar multiplication

Matriz Matriz::operator*(const double& matrizB) {
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			result(i, j) = this->mat[i][j] * matrizB;
		}
	}

	return result;
}

// Matrix/scalar division

Matriz Matriz::operator/(const double& matrizB) {
	Matriz result(linhas, colunas);

	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			result(i, j) = this->mat[i][j] / matrizB;
		}
	}

	return result;
}

// Multiply a matrix with a vector

ListaEnc<double> Matriz::operator*(const ListaEnc<double>& matrizB) {
	ListaEnc<double> result = ListaEnc<double>();

	for (int i = 0; i < linhas; i++) {
		double valor = 0.0;
		for (int j = 0; j < colunas; j++) {
			valor += this->mat[i][j] * matrizB.recuperaDaPosicao(j);
		}
		result.adiciona(valor);
	}

	return result;
}

// Obtain a vector of the diagonal elements

ListaEnc<double> Matriz::get_diagonal_principal() {
	ListaEnc<double> result = ListaEnc<double>();

	for (int i = 0; i < linhas; i++) {
		result.adiciona(this->mat[i][i]);
	}

	return result;
}

double& Matriz::operator()(const int& row, const int& col) {
	return this->mat[row][col];
}

const double& Matriz::operator()(const int& row, const int& col) const {
	return this->mat[row][col];
}

int Matriz::get_linhas() const {
	return this->linhas;
}

int Matriz::get_colunas() const {
	return this->colunas;
}

static Matriz Matriz::matrizIdentidade(int tamanho) {
	Matriz matriz = Matriz(tamanho, tamanho);
	for (int i = 0; i < tamanho; ++i) {
		matriz.mat[i][i] = 1.0;
	}

	return matriz;
}

#endif