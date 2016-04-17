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

	void abrirMundo();

	void salvarMundo();

	ListaEnc<Coordenada> mapearNoMundo(ObjetoGrafico* obj);
private:
	int radioRotacaoSelecionada();
	char* getObjetoSelecionado();
	void adicionarObjetoNaLista(const char* nome);

};

#endif
