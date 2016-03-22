#ifndef TELA_PRINCIPAL_HPP
#define TELA_PRINCIPAL_HPP

#include <gtk/gtk.h>
#include "mundo.hpp"
#include "consts.hpp"
#include <iostream>

class TelaPrincipal {
public:

	GtkBuilder *builder;
	Mundo *mundo;

	void atualizarTela();

public:
	TelaPrincipal();

	virtual ~TelaPrincipal();

	void adicionarObjeto();

	void desenhar(cairo_t *cr, ListaEnc<Coordenada> coords);

	void desenharTudo(cairo_t *cr);

	void abrirPopupAdicionar();

	void fecharPopupAdicionar();

	void moverCima();

	void moverBaixo();

	void moverEsquerda();

	void moverDireita();

	void zoomIn();

	void zoomOut();

	ListaEnc<Coordenada> mapearNoMundo(ObjetoGrafico obj);
};

#endif
