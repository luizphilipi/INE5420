#ifndef GEOMETRIA
#define GEOMETRIA

#include "Coordenada.hpp"
#include "MatrizUtil.hpp"
#include <string>
#include <gtk/gtk.h>
#include <vector>
#include "ListaEnc.hpp"

using namespace std;

enum tipoGeometria {
	PONTO, LINHA, POLIGONO, BEZIER, BSPLINE, OBJETO3D, SUPERFICIE_BEZIER
};

class ObjetoGrafico {
protected:
	ObjetoGrafico(std::string nome, tipoGeometria tipo) :
			nome(nome), tipo(tipo), preenchido(false) {
	}

	ObjetoGrafico(std::string nome, tipoGeometria tipo,
			std::vector<Coordenada> coords) :
			nome(nome), tipo(tipo), coordenadasMundo(coords), coordenadasTela(
					coords), preenchido(false) {
	}

	ObjetoGrafico(std::string nome, tipoGeometria tipo,
			std::vector<Coordenada> coords, bool preenchimento) :
			nome(nome), tipo(tipo), coordenadasMundo(coords), preenchido(
					preenchimento) {
		for (int i = 0; i < coords.size(); ++i) {
			coordenadasTela.push_back(Coordenada());
		}
	}

	ObjetoGrafico(std::string nome, tipoGeometria tipo,
			std::vector<Coordenada> coords, bool preenchimento, GdkRGBA cor) :
			nome(nome), tipo(tipo), coordenadasMundo(coords), preenchido(
					preenchimento), cor(cor) {
		for (int i = 0; i < coords.size(); ++i) {
			coordenadasTela.push_back(Coordenada());
		}
	}

	std::string nome;
	tipoGeometria tipo;
	std::vector<Coordenada> coordenadasMundo;
	std::vector<Coordenada> coordenadasTela;  //coord normalizadas
	bool preenchido = false;
	GdkRGBA cor;
	Coordenada *centroObj = NULL;

public:
	ObjetoGrafico() :
			nome(""), tipo(PONTO), preenchido(false) {
	}

	virtual ~ObjetoGrafico() {
	}

	// status = 0 é desativado, 1 = Sutherland, 2 = Liang Barsky
	virtual std::vector<Coordenada> clip(int status) = 0;

	std::string getNome() {
		return nome;
	}

	void setNome(std::string nome) {
		this->nome = nome;
	}

	bool isPreenchido() {
		return preenchido;
	}

	tipoGeometria getTipo() {
		return tipo;
	}
	void setTipo(tipoGeometria t) {
		tipo = t;
	}

	GdkRGBA getCor() {
		return cor;
	}

	void setCor(GdkRGBA cor) {
		this->cor = cor;
	}


	int getQuantidadeCoords() {
		return coordenadasMundo.size();
	}

	std::vector<Coordenada> getListaCoord() {
		return coordenadasMundo;
	}

	std::vector<Coordenada> getListaCoordTela() {
		return coordenadasTela;
	}

	void setListaCoord(std::vector<Coordenada> l) {
		coordenadasMundo = l;
	}

	Coordenada getCoord(int i) {
		return coordenadasMundo[i];
	}

	/* Centro do objeto = (Cx, Cy)
	 * Cx = [ SOMA(xi) i=1 até n ] / n
	 * Cy = [ SOMA(yi) i=1 até n ] / n
	 */
	Coordenada centro() {
//		if (!centroObj) {
		int x = 0;
		int y = 0;
		int z = 0;

		for (auto &coordenada : coordenadasMundo) {
			x += coordenada._x;
			y += coordenada._y;
			z += coordenada._z;
		}

		int tamanho = coordenadasMundo.size();
		x = x / tamanho;
		y = y / tamanho;
		z = z / tamanho;

		return Coordenada(x, y, z);
//		}
//		return *centroObj;
	}

	/* Aplica o deslocamento (Dx, Dy) a todas as coordenadas [x y 1]
	 * 						 |1  0	0|
	 * [x' y' 1] = [x y 1] * |0	 1	0|
	 * 						 |Dx Dy	1|
	 */
	void transladar(Coordenada vetorDeslocamento) {
		Matriz matrizTransformacao = MatrizUtil::matrizTranslacao3D(vetorDeslocamento);
		aplicarTransformacao(matrizTransformacao);
	}

	/* Escalonamento natural
	 * Aplica o fator [Sx, Sy] a todas as coordenadas [x y 1] usando o centro [Cx, Cy]
	 * 						 	|1   0	 0|	  |Sx	0	0|   |1		0	0|
	 * [x'' y'' 1] = [x y 1] *	|0	 1	 0| * |0	Sy	0| * |0		1	0|
	 * 							|-Cx -Cy 1|	  |0	0	1|   |Cx	Cy	1|
	 */
	void escalonar(Coordenada fator) {
		Matriz matrizEscalonamento = MatrizUtil::matrizEscalonamento3D(fator);
		aplicarTransformacao(matrizEscalonamento, this->centro());
	}

	/* Rotaciona em torno do centro [Dx, Dy] com o angulo Θ
	 * 						 	|1   0	 0|		|cos(Θ) -sin(Θ) 0|	|1	0	0|
	 * [x'' y'' 1] = [x y 1] *	|0	 1	 0| *	|sin(Θ)	 cos(Θ)	0| *|0	1	0|
	 * 							|-Dx -Dy 1|		|0		0		1|	|Dx	Dy	1|
	 */
	void rotacionar(double anguloEmGraus, int index) {
		Matriz matrizRotacao = Matriz(4,4);
		switch(index){
		case 0:
			matrizRotacao = MatrizUtil::matrizRotacao3DX(anguloEmGraus);
			break;
		case 1:
			matrizRotacao = MatrizUtil::matrizRotacao3DY(anguloEmGraus);
			break;
		case 2:
			matrizRotacao = MatrizUtil::matrizRotacao3DZ(anguloEmGraus);
			break;
		}
		aplicarTransformacao(matrizRotacao, this->centro());
	}

	void rotacionar(Coordenada emTornoDe, double anguloEmGraus, int index) {
		Matriz matrizRotacao = Matriz(4,4);
		switch(index){
		case 0:
			matrizRotacao = MatrizUtil::matrizRotacao3DX(anguloEmGraus);
			break;
		case 1:
			matrizRotacao = MatrizUtil::matrizRotacao3DY(anguloEmGraus);
			break;
		case 2:
			matrizRotacao = MatrizUtil::matrizRotacao3DZ(anguloEmGraus);
			break;
		}
		aplicarTransformacao(matrizRotacao, emTornoDe);
	}

	void normalizar(Coordenada centroTela, double xOffset, double yOffset,
			double zOffset, Matriz matrizNormalizacao) {
		coordenadasTela.clear();

		for (auto &coord : coordenadasMundo) {
			Matriz matrizCoordenadas = Matriz(coord) * matrizNormalizacao;

			double xNormalizado = (matrizCoordenadas(0, 0) - centroTela._x)
					/ (xOffset);
			double yNormalizado = (matrizCoordenadas(0, 1) - centroTela._y)
					/ (yOffset);
			double zNormalizado = (matrizCoordenadas(0, 2) - centroTela._z)
					/ (zOffset);

			Coordenada coordenadaNormalizada = Coordenada(xNormalizado,
					yNormalizado, zNormalizado);
			coordenadasTela.push_back(coordenadaNormalizada);
		}
	}

private:

	// [x' y' z' ... ] = [x y z ...] * matriz transformação
	void aplicarTransformacao(Matriz matrizTransformacao) {
		for (auto &coord : coordenadasMundo) {
			Matriz resultado = Matriz(coord) * matrizTransformacao;
			coord._x = resultado(0, 0);
			coord._y = resultado(0, 1);
			coord._z = resultado(0, 2);
//			coordenadasMundo[i] = coord;
		}
	}

	void aplicarTransformacao(Matriz matrizTransformacao, Coordenada posicao) {
		Matriz resultado = MatrizUtil::matrizTranslacao3D(posicao.negativa()) * matrizTransformacao
				* MatrizUtil::matrizTranslacao3D(posicao);
		aplicarTransformacao(resultado);
	}

};

#endif
