#ifndef POLYGON
#define POLYGON

#include "ObjetoGrafico.hpp"

class Poligono: public ObjetoGrafico {
public:
	Poligono(string nome, ListaEnc<Coordenada>* pontos, bool preenchimento) :
			ObjetoGrafico(nome, POLIGONO, pontos, preenchimento) {
	}

	ListaEnc<Coordenada>* clip() {
		return coordenadasMundo;
	}
};
#endif
