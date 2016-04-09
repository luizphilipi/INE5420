#ifndef DESCRITOROBJ
#define DESCRITOROBJ

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>      /* c_str */
#include <stdlib.h>     /* atoi */
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


	ListaEnc<ObjetoGrafico> * ler(string caminho){
		string linha;
		ifstream arquivo(caminho);
		ListaEnc<ObjetoGrafico> * displayFile = new ListaEnc<ObjetoGrafico>();

		if(arquivo.is_open()){

			ObjetoGrafico * obj;

			while(getline(arquivo, linha)){

				ListaEnc<Coordenada> * coords;
				string nome;

				if(!linha.find("#")){
					obj = new ObjetoGrafico();
					nome = linha.erase(0,1);
					nome = split(nome, " ").front();
					obj->setNome(nome);

					coords = new ListaEnc<Coordenada>();

				} else if (!linha.find("v")){
					Coordenada *coord;
					vector<string> coordenadas = split(linha, " ");
					coord = new Coordenada(atoi(coordenadas[1].c_str()),
							atoi(coordenadas[2].c_str()),
							atoi(coordenadas[3].c_str()));
					coords->adiciona(*coord);

					} else if (!linha.find("f")){
						vector<string> f = split(linha, " ");
						if(f.size()== 2){
							std::cout<< nome << endl;
							obj->setTipo(PONTO);
							obj->setListaCoord(coords);
							displayFile->adiciona(*obj);

							std::cout << obj->transcreveObj() << endl; //teste

						} else if (f.size() == 3){
							obj->setTipo(LINHA);
							obj->setListaCoord(coords);
							displayFile->adiciona(*obj);

							std::cout << obj->transcreveObj() << endl; //teste

						} else {
							obj->setTipo(POLIGONO);
							obj->setListaCoord(coords);
							displayFile->adiciona(*obj);

							std::cout << obj->transcreveObj() << endl; //teste
						}
					}
				}
			arquivo.close();
		}
		return displayFile;
	}

	vector<string> split(string s, string delimitador) {
		vector<string> tokens;
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimitador)) != std::string::npos) {
			token = s.substr(0, pos);
			tokens.push_back(token);
			s.erase(0, pos + delimitador.length());
		}
		tokens.push_back(s);
		return tokens;
	}

};

#endif /* DESCRITOROBJ*/
