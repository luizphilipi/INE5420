#ifndef __MATRIZ_H
#define __MATRIZ_H

#include <vector>
#include <ostream>
#include "Coordenada.hpp"

class Matriz {
private:
	std::vector<std::vector<double> > mat;
	int linhas;
	int colunas;

public:
	Matriz(int _linhas, int _colunas);
	Matriz(const Matriz& matrizB);
	Matriz(Coordenada coord);
	Matriz(Coordenada *coord);
	virtual ~Matriz();

	Matriz& operator=(const Matriz& matrizB);

	// Matrix mathematical operations
	Matriz operator+(const Matriz& matrizB);
	Matriz& operator+=(const Matriz& matrizB);
	Matriz operator-(const Matriz& matrizB);
	Matriz& operator-=(const Matriz& matrizB);
	Matriz operator*(const Matriz& matrizB);
	Matriz& operator*=(const Matriz& matrizB);
	Matriz transpose();

	// Matrix/scalar operations
	Matriz operator+(const double& matrizB);
	Matriz operator-(const double& matrizB);
	Matriz operator*(const double& matrizB);
	Matriz operator/(const double& matrizB);

	// Access the individual elements
	double& operator()(const int& row, const int& col);
	const double& operator()(const int& row, const int& col) const;

	// Access the row and column sizes
	int get_linhas() const;
	int get_colunas() const;

	static Matriz matrizIdentidade(int tamanho);

	friend std::ostream& operator<<(std::ostream& os, const Matriz& obj);
};


#endif
