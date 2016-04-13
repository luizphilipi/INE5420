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
		int count = 1;
		int *pcount = &count;

		ofstream arquivo;
		arquivo.open(caminho.c_str());
		if(arquivo.is_open()){
			for(int i = 0; i<mundo->getObjetos()->getSize(); ++i){
				ObjetoGrafico obj = mundo->getObjetos()->recuperaDaPosicao(i);
				arquivo << transcreveObj(mundo->getObjetos()->recuperaDaPosicao(i), pcount);
			}
		}
		arquivo.close();
	}

	/*
	 * Transcreve um objeto gráfico para o formato .obj
	 * nome, tipo, vértices e arestas
	 * Ex: To describe a polygon, the file first describes each point
	 * with the "v"keyword, then describes the face with the "f" keyword.
	 *   1    v 0.0 0.0 0.0
	 *   2   v 0.0 1.0 0.0
	 *   3   v 1.0 0.0 0.0
	 *   4   f 1 2 3
	 */
	string transcreveObj(ObjetoGrafico obj, int * count){
		string retorno = "o " + obj.getNome() + "\n";
		*count = *count+1;
		string final;
		ListaEnc<Coordenada> * coords = obj.getListaCoord();
		for(int i = 0; i<coords->getSize(); i++){
			Coordenada atual = coords->recuperaDaPosicao(i);
			retorno += "v " +
					std::to_string(atual.getX()) + " " +
					std::to_string(atual.getY()) + " " +
					std::to_string(atual.getZ()) + "\n";
			final += " " + std::to_string(*count);
			*count = *count+1;
		}
		if(obj.getTipo() == PONTO){
			retorno += "p" + final + "\n";
		} else {
			retorno += "l" + final + "\n";
		}
		*count = *count+1;
		return retorno;
	}

	ListaEnc<ObjetoGrafico> * ler(string caminho){
		ListaEnc<ObjetoGrafico> * displayFile = new ListaEnc<ObjetoGrafico>();
		string linha;
		ListaEnc<int> * linhaCoord = new ListaEnc<int>;
		ListaEnc<Coordenada> * listaCoords = leCoordenadas(caminho, linhaCoord);
		ifstream arquivo(caminho);
		if(arquivo.is_open()){
			ObjetoGrafico * obj;
			while(getline(arquivo, linha)){
				string nome;
				if(!linha.find("o")){
					obj = new ObjetoGrafico();
					nome = linha.erase(0,2);
					nome = split(nome, " ").front();
					obj->setNome(nome);
				} else if (!linha.find("p") || !linha.find("l")){
					vector<string> pontos = split(linha, " ");
					switch(pontos.size()){
					case 2:
						obj->setTipo(PONTO);
						break;
					case 3:
						obj->setTipo(LINHA);
						break;
					default:
						obj->setTipo(POLIGONO);
					}
					for(int i = 0; i<pontos.size()-1; i++){
						int linhaPonto = atoi(pontos[i+1].c_str() );
						int pos = linhaCoord->posicao(linhaPonto);
						Coordenada c = listaCoords->recuperaDaPosicao(pos);
						obj->setCoord(c, i);

					}
					displayFile->adiciona(*obj);
				}
			}
			arquivo.close();
		}
		return displayFile;
	}


	ListaEnc<Coordenada> * leCoordenadas(string caminho, ListaEnc<int> * linhaCoord){
		ListaEnc<Coordenada> * coords = new ListaEnc<Coordenada>();
		string linha;
		int count = 1;
		ifstream arquivo(caminho);
		if(arquivo.is_open()){
			while(getline(arquivo, linha)){
				if (!linha.find("v")){
					Coordenada *coord;
					vector<string> coordenadas = split(linha, " ");
					coord = new Coordenada(atoi(coordenadas[1].c_str()),
							atoi(coordenadas[2].c_str()),
							atoi(coordenadas[3].c_str()));
					coords->adiciona(*coord);
					linhaCoord->adiciona(count);
					}
				count++;
				}
			arquivo.close();
		}
		return coords;
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
