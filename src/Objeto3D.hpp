#ifndef OBJ3D
#define OBJ3D

#include "ObjetoGrafico.hpp"

class Objeto3D: public ObjetoGrafico {
public:
	Objeto3D(std::string nome, std::vector<Coordenada> pontos) :
			ObjetoGrafico(nome, OBJETO3D, pontos) {
	}

	std::vector<Coordenada> clip(int status) {
		//TODO
		return coordenadasTela;
	}
};
#endif
