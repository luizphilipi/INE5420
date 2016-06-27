#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include <gtk/gtk.h>
#include <iostream>
#include "Consts.hpp"
#include "Mundo.hpp"

class TelaPrincipal {
public:

	GtkBuilder *builder;
	Mundo *mundo;

	void atualizarTela();

public:
	TelaPrincipal();

	virtual ~TelaPrincipal();

	void adicionarObjetoTeste();

	void adicionarObjeto();

	void desenharPonto(cairo_t *cr, Coordenada coords);

	void desenharLinha(cairo_t *cr, Coordenada coord1, Coordenada coord2);

	void desenharLinhaPoligono(cairo_t *cr, Coordenada coord1, Coordenada coord2);

	void desenhar(cairo_t *cr, ObjetoGrafico *obj);

	void desenharTudo(cairo_t *cr);

	void abrirPopupAdicionar();

	void fecharPopupAdicionar();

	void moverCima();

	void moverBaixo();

	void moverEsquerda();

	void moverDireita();

	void zoomIn();

	void zoomOut();

	void rotacaoMundo();

	void aplicarTranslacao();

	void aplicarEscalonamento();

	void aplicarRotacao();

	void adicionarCoordenadaPoligono();

	void adicionarCoordenadaBSpline();

	void adicionarCoordenadaObjeto3D();

	void adicionarCoordenadaSuperficieBezier();

	//exemplos
	void exemploCubo();
	void exemploEspiral();
	void exemploTeddy();
	void exemploSuperficie();


	void abrirMundo();

	void salvarMundo();

	vector<Coordenada> mapearNoMundo(ObjetoGrafico* obj);

private:
	int radioRotacaoSelecionada();
	int radioClippingSelecionado();
	char* getObjetoSelecionado();
	void adicionarObjetoNaLista(const char* nome);
	void limparLista();

	vector<Coordenada> coordenadas;

};

#endif
