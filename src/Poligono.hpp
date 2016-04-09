#ifndef POLYGON
#define POLYGON

#include "ObjetoGrafico.hpp"

class Poligono: public ObjetoGrafico {
public:
	Poligono(string nome, ListaEnc<Coordenada>* pontos) :
			ObjetoGrafico(nome, POLIGONO, pontos) {
	}
};
#endif
