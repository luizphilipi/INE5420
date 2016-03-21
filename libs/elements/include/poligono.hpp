#ifndef POLYGON
#define POLYGON

#include "basepoint.hpp"

class Poligono: public Geometria {
public:
	Poligono(char const* nome, ListaEnc<BasePoint>* pontos) :
			Geometria(nome, POLIGONO, pontos) {
	}
};
#endif
