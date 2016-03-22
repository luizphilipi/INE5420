#ifndef POLYGON
#define POLYGON

#include "objetografico.hpp"

class Poligono: public ObjetoGrafico {
public:
	Poligono(char const* nome, ListaEnc<Coordenada>* pontos) :
			ObjetoGrafico(nome, POLIGONO, pontos) {
	}
};
#endif
