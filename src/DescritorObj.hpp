#ifndef DESCRITOROBJ
#define DESCRITOROBJ

#include <string>
#include <iostream>
#include <fstream>
#include "Mundo.hpp"

class DescritorObj {
public:
	DescritorObj(){}
	virtual ~DescritorObj(){}

	void escrever(Mundo * mundo, string caminho){
		ofstream arquivo;
		arquivo.open(caminho.c_str());
		if(arquivo.is_open()){
			for(int i = 0; i<mundo->getObjetos()->getSize(); ++i){
				ObjetoGrafico obj = mundo->getObjetos()->recuperaDaPosicao(i);
				arquivo << obj.transcreveObj();
			}
		}
		arquivo.close();
	}
};

#endif /* DESCRITOROBJ*/
