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
	DescritorObj() {
	}
	virtual ~DescritorObj() {
	}

	void escrever(Mundo * mundo, string caminho) {
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
	string transcreveObj(ObjetoGrafico* obj, int * countLinha) {
		string retorno = "o " + obj->getNome() + "\n";
		*countLinha = *countLinha + 1;
		string coordenadas;
		ListaEnc<Coordenada> * coords = obj->getListaCoord();
		for (int i = 0; i < coords->getSize(); i++) {
			Coordenada atual = coords->recuperaDaPosicao(i);
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

	Mundo * ler(string caminhoObj) {
		clock_t begin = clock();
		//percorre o arquivo.obj e guarda todas as coordenadas
		ListaEnc<double> * linhaCoord = new ListaEnc<double>;
		ListaEnc<Coordenada> * listaCoords = leCoordenadas(caminhoObj,
				linhaCoord);

		//percorre o arquivo.obj e busca arquivo de descrição de material .mtl
		string caminhoMtl = buscaMtl(caminhoObj);
		ListaEnc<string> * nomeCor = new ListaEnc<string>;
		ListaEnc<Coordenada> * rgb = new ListaEnc<Coordenada>;
		if (caminhoMtl != "") {
			lerMtl(caminhoMtl, nomeCor, rgb);
		}

		//le o arquivo .obj e cria todos os objetos num mundo
		Mundo* mundo = lerObj(caminhoObj, linhaCoord, listaCoords, nomeCor,
				rgb);

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Lendo arquivo " << caminhoObj << " em: " << elapsed_secs
				<< std::endl;

		return mundo;
	}

	Mundo * lerObj(string caminho, ListaEnc<double> *linhaCoord,
			ListaEnc<Coordenada> *listaCoords, ListaEnc<string> * nomeCor,
			ListaEnc<Coordenada> * rgb) {
		Mundo * m = new Mundo();
		string linha;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			ObjetoGrafico *obj;
			string nome;
			GdkRGBA corObjeto;
			bool preenchimento = false;
			while (getline(arquivo, linha)) {
				if (!linha.find("o")) {
					nome = linha.erase(0, 2);
					nome = split(nome, " ").front();
				} else if (!linha.find("usemtl")) {
					preenchimento = true;
					string aux = linha.erase(0, 7);
					corObjeto = setCor(nomeCor, rgb, aux);
				} else if (!linha.find("p") || !linha.find("l")) {
					vector<string> pontos = split(linha, " ");
					ListaEnc<Coordenada> *coordenadas = coordenadaObj(pontos,
							listaCoords, linhaCoord);
					switch (pontos.size()) {
					case 2:
						obj = new Ponto(nome,
								coordenadas->recuperaDaPosicao(0));
						break;
					case 3:
						obj = new Linha(nome, coordenadas->recuperaDaPosicao(0),
								coordenadas->recuperaDaPosicao(1));
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
			}
			arquivo.close();
		}
		return m;
	}

	GdkRGBA setCor(ListaEnc<string> * nomeCor, ListaEnc<Coordenada> * rgb,
			string aux) {
		GdkRGBA corObjeto;
		Coordenada coordRgb = rgb->recuperaDaPosicao(nomeCor->posicao(aux));
		corObjeto.red = coordRgb._x;
		corObjeto.green = coordRgb._y;
		corObjeto.blue = coordRgb._z;
		return corObjeto;
	}

	void lerMtl(string caminho, ListaEnc<string> * newmtl,
			ListaEnc<Coordenada> * kd) {
		string linha;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			string nome;
			while (getline(arquivo, linha)) {
				if (!linha.find("newmtl")) {
					nome = linha.erase(0, 7);
					newmtl->adiciona(nome);
				} else if (!linha.find("Kd")) {
					vector<string> valores = split(linha, " ");
					Coordenada * rgb = new Coordenada(atoi(valores[1].c_str()),
							atoi(valores[2].c_str()), atoi(valores[3].c_str()));
					kd->adiciona(*rgb);
				}
			}
			arquivo.close();
		}
	}

	ListaEnc<Coordenada> * coordenadaObj(vector<string> pontos,
			ListaEnc<Coordenada> *listaCoords, ListaEnc<double> * linhaCoord) {

		ListaEnc<Coordenada> *coordenadas = new ListaEnc<Coordenada>();
		for (int i = 0; i < pontos.size() - 1; i++) {
			double linhaPonto = atoi(pontos[i + 1].c_str());
			int pos = linhaCoord->posicao(linhaPonto);
			Coordenada c = listaCoords->recuperaDaPosicao(pos);
			coordenadas->adiciona(c);
		}
		return coordenadas;
	}

	string buscaMtl(string caminho) {
		string mtl = "";

		string linha;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			while (getline(arquivo, linha)) {
				if (!linha.find("mtllib")) {
					vector<string> coordenadas = split(linha, " ");
					mtl = coordenadas[1].c_str();
				}
			}
			arquivo.close();
		}
		return mtl;
	}

	ListaEnc<Coordenada> * leCoordenadas(string caminho,
			ListaEnc<double> * linhaCoord) {
		ListaEnc<Coordenada> * coords = new ListaEnc<Coordenada>();
		string linha;
		int count = 1;
		ifstream arquivo(caminho);
		if (arquivo.is_open()) {
			while (getline(arquivo, linha)) {
				if (!linha.find("v")) {
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
