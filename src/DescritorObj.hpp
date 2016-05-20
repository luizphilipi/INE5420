#ifndef DESCRITOROBJ
#define DESCRITOROBJ

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>      /* c_str */
#include <stdlib.h>     /* atoi */
#include "Mundo.hpp"
#include <algorithm>
#include <map>

class DescritorObj {
public:
	DescritorObj() {
	}
	virtual ~DescritorObj() {
	}

	void escrever(Mundo * mundo, std::string caminho) {
		int count = 1;
		int *pcount = &count;

		ofstream arquivo;
		arquivo.open(caminho.c_str());
		if (arquivo.is_open()) {
			for (int i = 0; i < mundo->getObjetos()->getSize(); ++i) {
				ObjetoGrafico *obj = mundo->getObjetos()->recuperaDaPosicao(i);
				arquivo << transcreveObj(obj, pcount);
			}
		}
		arquivo.close();
	}

	/*
	 * Transcreve um objeto gráfico para o formato .obj
	 * nome, tipo, vértices e arestas
	 * Ex: To describe a polygon, the file first describes each point
	 * with the "v"keyword, then describes the face with the "f" keyword.
	 *   1   v 0.0 0.0 0.0
	 *   2   v 0.0 1.0 0.0
	 *   3   v 1.0 0.0 0.0
	 *   4   f 1 2 3
	 */
	std::string transcreveObj(ObjetoGrafico* obj, int * countLinha) {
		std::string retorno = "o " + obj->getNome() + "\n";
		*countLinha = *countLinha + 1;
		std::string coordenadas;
		std::vector<Coordenada> coords = obj->getListaCoord();
		for (auto &atual : coords) {
			retorno += "v " + std::to_string(atual.getX()) + " "
					+ std::to_string(atual.getY()) + " "
					+ std::to_string(atual.getZ()) + "\n";
			coordenadas += " " + std::to_string(*countLinha);
			*countLinha = *countLinha + 1;
		}
		if (obj->getTipo() == PONTO) {
			retorno += "p" + coordenadas + "\n";
		} else {
			retorno += "l" + coordenadas + "\n";
		}
		*countLinha = *countLinha + 1;
		return retorno;
	}

	Mundo * ler(std::string caminhoObj) {
		clock_t begin = clock();
		//percorre o arquivo.obj e guarda todas as coordenadas
		std::map<int, Coordenada> listaCoords = leCoordenadas(caminhoObj);

		//percorre o arquivo.obj e busca arquivo de descrição de material .mtl
		std::string caminhoMtl = buscaMtl(caminhoObj);
		std::map<std::string, GdkRGBA> cores;
		if (caminhoMtl != "") {
			cores = lerMtl(caminhoMtl);
		}
		//le o arquivo .obj e cria todos os objetos num mundo
		Mundo* mundo = lerObj(caminhoObj, listaCoords, cores);

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//std::cout << "Lendo arquivo " << caminhoObj << " em: " << elapsed_secs
		//		<< std::endl;

		return mundo;
	}

	Mundo * lerObj(std::string caminho, std::map<int, Coordenada> listaCoords,
			std::map<std::string, GdkRGBA> cores) {
		Mundo * m = new Mundo();
		std::string linha;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			ObjetoGrafico *obj;
			std::string nome;
			GdkRGBA corObjeto;
			bool preenchimento = false;
			bool bezier = false;
			while (getline(arquivo, linha)) {
				if (!linha.find("o")) {
					nome = linha.erase(0, 2);
					nome = split(nome, " ").front();
				} else if (!linha.find("usemtl")) {
					preenchimento = true;
					std::string cor = linha.erase(0, 7);
					corObjeto = cores[cor];
				} else if (!linha.find("p") || !linha.find("l") || !linha.find("f")) {
					std::vector<Coordenada> coordenadas = coordenadaObj(linha,
							listaCoords);
					switch (coordenadas.size()) {
					case 1:
						obj = new Ponto(nome, coordenadas[0]);
						break;
					case 2:
						obj = new Linha(nome, coordenadas[0], coordenadas[1]);
						break;
					default:
						if (preenchimento) {
							obj = new Poligono(nome, coordenadas, preenchimento,
									corObjeto);
							preenchimento = false;
						} else {
							obj = new Poligono(nome, coordenadas,
									preenchimento);
						}
					}

					m->adicionaObj(obj);
				}
				else if (!linha.find("cstype bezier")) {
					bezier = true;
				}
				else if (!linha.find("curv")) {
					std::vector<Coordenada> coordenadas = coordenadaObj(linha,
														listaCoords);
					if(bezier){
						obj = new Bezier(nome, coordenadas);
						bezier = false;
					}
					else{
						obj = new BSpline(nome, coordenadas);
					}
				m->adicionaObj(obj);
				}
			}
			arquivo.close();
		}
		return m;
	}

	std::map<std::string, GdkRGBA> lerMtl(std::string caminho) {
		std::map<std::string, GdkRGBA> cores;
		std::string linha;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			std::string nome;
			while (getline(arquivo, linha)) {
				if (!linha.find("newmtl")) {
					nome = linha.erase(0, 7);
				} else if (!linha.find("Kd")) {
					std::vector<std::string> valores = split(linha, " ");
					GdkRGBA corObjeto;
					corObjeto.red = atoi(valores[1].c_str());
					corObjeto.green = atoi(valores[2].c_str());
					corObjeto.blue = atoi(valores[3].c_str());
					cores[nome] = corObjeto;
				}
			}
			arquivo.close();
		}
		return cores;
	}

	std::vector<Coordenada> coordenadaObj(string linha,
			std::map<int, Coordenada> listaCoords) {
		std::vector<Coordenada> coordenadas;
		std::vector<std::string> pontos = split(linha, " ");

		for (int i = 1; i < pontos.size(); i++) {
			int posicao = atoi(pontos[i].c_str());
			coordenadas.push_back(listaCoords[posicao]);
		}
		return coordenadas;
	}

	std::string buscaMtl(std::string caminho) {
		std::string mtl = "";

		std::string linha;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			while (getline(arquivo, linha)) {
				if (!linha.find("mtllib")) {
					std::vector<std::string> coordenadas = split(linha, " ");
					mtl = coordenadas[1].c_str();
				}
			}
			arquivo.close();
		}
		return mtl;
	}

	std::map<int, Coordenada> leCoordenadas(std::string caminho) {
		std::map<int, Coordenada> coords;
		std::string linha;
		int posicao = 1;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			while (getline(arquivo, linha)) {
				if (linha.at(0) == 'v') {
					std::vector<std::string> coordenadas = split(linha, " ");
					double x = atof(coordenadas[1].c_str());
					double y = atof(coordenadas[2].c_str());
					double z = atof(coordenadas[3].c_str());
					std::cout << x << ", " << y << std::endl;
					coords[posicao] = Coordenada(x, y, z);
				}
				posicao++;
			}
			arquivo.close();
		}
		return coords;
	}

	std::vector<std::string> split(std::string s, std::string delimitador) {
		std::vector<std::string> tokens;
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
