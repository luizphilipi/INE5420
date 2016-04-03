#include "TelaPrincipal.hpp"

extern "C" {
gboolean callback_desenhar_tudo(GtkWidget *widget, cairo_t *cr,
		TelaPrincipal *telaPrincipal) {
	telaPrincipal->desenharTudo(cr);
	return false;
}

void abrir_popup_adicionar(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->abrirPopupAdicionar();
}

void mover_cima(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->moverCima();
	std::cout << telaPrincipal->radioTelaSelecionado() << std::endl;
}

void mover_baixo(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->moverBaixo();
}

void mover_esquerda(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->moverEsquerda();
}

void mover_direita(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->moverDireita();
}

void adicionar_objeto(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->adicionarObjeto();
}

void zoom_in(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->zoomIn();
}

void zoom_out(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->zoomOut();
}
}

void TelaPrincipal::atualizarTela() {
	GtkWidget *areaDesenho = GTK_WIDGET(
			gtk_builder_get_object( builder, AREA_DESENHO ));
	gtk_widget_queue_draw(areaDesenho);
}

TelaPrincipal::TelaPrincipal() {
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "main.glade", NULL);

	mundo = new Mundo();

	// signals
	GtkWidget *drawingArea = GTK_WIDGET(
			gtk_builder_get_object(builder, AREA_DESENHO));
	g_signal_connect(G_OBJECT(drawingArea), "draw",
			G_CALLBACK(callback_desenhar_tudo), this);

	GtkWidget *moveUpButton = GTK_WIDGET(
			gtk_builder_get_object (builder, MOVE_UP_BTN));
	g_signal_connect(G_OBJECT(moveUpButton), "clicked", G_CALLBACK(mover_cima),
			this);

	GtkWidget *moveDownButton = GTK_WIDGET(
			gtk_builder_get_object (builder, MOVE_DOWN_BTN));
	g_signal_connect(G_OBJECT(moveDownButton), "clicked",
			G_CALLBACK(mover_baixo), this);

	GtkWidget *moveLeftButton = GTK_WIDGET(
			gtk_builder_get_object (builder, MOVE_LEFT_BTN));
	g_signal_connect(G_OBJECT(moveLeftButton), "clicked",
			G_CALLBACK(mover_esquerda), this);

	GtkWidget *moveRightButton = GTK_WIDGET(
			gtk_builder_get_object (builder, MOVE_RIGHT_BTN));
	g_signal_connect(G_OBJECT(moveRightButton), "clicked",
			G_CALLBACK(mover_direita), this);

	GtkWidget *zoomInBtn = GTK_WIDGET(
			gtk_builder_get_object (builder, ZOOM_IN_BTN));
	g_signal_connect(G_OBJECT(zoomInBtn), "clicked", G_CALLBACK(zoom_in), this);

	GtkWidget *zoomOutBtn = GTK_WIDGET(
			gtk_builder_get_object (builder, ZOOM_OUT_BTN));
	g_signal_connect(G_OBJECT(zoomOutBtn), "clicked", G_CALLBACK(zoom_out),
			this);

	GtkWidget *addButton = GTK_WIDGET(
			gtk_builder_get_object(builder, "addObj"));
	g_signal_connect(G_OBJECT(addButton), "clicked",
			G_CALLBACK(abrir_popup_adicionar), this);

	GtkWidget *botaoAdicionarObjeto = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_ADICIONAR_OBJETO));
	g_signal_connect(G_OBJECT(botaoAdicionarObjeto), "clicked",
			G_CALLBACK(adicionar_objeto), this);

	// FAZ COM QUE NÃO DELETE A POP-UP, SÓ ESCONDA
	GtkWidget *modalAdicionarCoordenadas = GTK_WIDGET(
			gtk_builder_get_object (builder, MODAL_ADICIONAR_COORDENADAS));
	g_signal_connect(G_OBJECT(modalAdicionarCoordenadas), "delete_event",
			G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	// signals

	GtkWidget *telaPrincipal = GTK_WIDGET(
			gtk_builder_get_object(builder, TELA_PRINCIPAL));

	//para de rodar ao clicar no X
	g_signal_connect(telaPrincipal, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(telaPrincipal);
	gtk_main();
}

TelaPrincipal::~TelaPrincipal() {

}

void TelaPrincipal::adicionarObjeto() {
	GtkWidget *drawingArea = GTK_WIDGET(
			gtk_builder_get_object(builder, AREA_DESENHO));

	GtkEntry *inputObjeto = GTK_ENTRY(
			gtk_builder_get_object( builder, INPUT_NOME_OBJETO ));

	GtkNotebook *objNotebook = GTK_NOTEBOOK(
			gtk_builder_get_object( builder, ABAS_MODAL_ADICIONAR ));

	GtkListStore *listStoreObjetos = GTK_LIST_STORE(
			gtk_builder_get_object( builder, LIST_STORE_OBJETOS ));

	const char* nomeObjeto = gtk_entry_get_text(inputObjeto);
	nomeObjeto = (nomeObjeto[0] == '\0') ? "objeto" : nomeObjeto;

	int pageIndex = gtk_notebook_get_current_page(GTK_NOTEBOOK(objNotebook));

	switch (pageIndex) {
	case 0: {
		GtkSpinButton *spinPontoX = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_PONTO_X ));
		GtkSpinButton *spinPontoY = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_PONTO_Y ));
		mundo->adicionaPonto(nomeObjeto,
				Coordenada(gtk_spin_button_get_value(spinPontoX),
						gtk_spin_button_get_value(spinPontoY)));
	}
		break;
	case 1: {
		GtkSpinButton *spinLinhaX1 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_X1 ));
		GtkSpinButton *spinLinhaY1 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_Y1 ));
		Coordenada coord1 = Coordenada(gtk_spin_button_get_value(spinLinhaX1),
				gtk_spin_button_get_value(spinLinhaY1));

		GtkSpinButton *spinLinhaX2 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_X2 ));
		GtkSpinButton *spinLinhaY2 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_Y2 ));
		Coordenada coord2 = Coordenada(gtk_spin_button_get_value(spinLinhaX2),
				gtk_spin_button_get_value(spinLinhaY2));

		mundo->adicionaLinha(nomeObjeto, coord1, coord2);
	}
		break;
	case 2: {
		//TODO generalizar, ia ser muito bom...
		ListaEnc<Coordenada> *coordenadas = new ListaEnc<Coordenada>();

		GtkBox *boxPoligono = GTK_BOX(
				gtk_builder_get_object( builder, BOX_POLIGONO ));
		GList* children = gtk_container_get_children(
				GTK_CONTAINER(boxPoligono));
		GList *l;
		int i = 0;
		GtkSpinButton *input;
		for (l = children; i < g_list_length(children); l = l->next, ++i) {
			GtkGrid *coordGrid = GTK_GRID(l->data);

			input = GTK_SPIN_BUTTON(gtk_grid_get_child_at(coordGrid, 1, 0));
			int x = gtk_spin_button_get_value(input);

			input = GTK_SPIN_BUTTON(gtk_grid_get_child_at(coordGrid, 3, 0));
			int y = gtk_spin_button_get_value(input);

			coordenadas->adiciona(Coordenada(x, y));
		}
		mundo->adicionaPoligono(nomeObjeto, coordenadas);
	}
		break;
	}

	GtkTreeIter iter;
	gtk_list_store_append(listStoreObjetos, &iter);
	gtk_list_store_set(listStoreObjetos, &iter, 0, nomeObjeto, -1);

	atualizarTela();
	fecharPopupAdicionar();
}

void TelaPrincipal::desenhar(cairo_t *cr, ListaEnc<Coordenada> coords) {
	if (coords.getSize() == 1) {
		cairo_move_to(cr, coords.recuperaDaPosicao(0).getX(),
				coords.recuperaDaPosicao(0).getY());
		cairo_arc(cr, coords.recuperaDaPosicao(0).getX(),
				coords.recuperaDaPosicao(0).getY(), 1.0, 0.0, 2.0 * 3.14);
		cairo_fill_preserve(cr);
		cairo_stroke(cr);
	} else {
		cairo_move_to(cr, coords.recuperaDaPosicao(0).getX(),
				coords.recuperaDaPosicao(0).getY());
		cairo_line_to(cr, coords.recuperaDaPosicao(0).getX(),
				coords.recuperaDaPosicao(0).getY());

		for (int i = 1; i < coords.getSize(); i++) {
			cairo_line_to(cr, coords.recuperaDaPosicao(i).getX(),
					coords.recuperaDaPosicao(i).getY());
		}

		cairo_close_path(cr);

		cairo_stroke(cr);
	}
}

void TelaPrincipal::desenharTudo(cairo_t *cr) {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);

	for (int i = 0; i < mundo->getObjetos()->getSize(); ++i) {
		desenhar(cr, mapearNoMundo(mundo->getObjetos()->recuperaDaPosicao(i)));
	}
}

void TelaPrincipal::abrirPopupAdicionar() {
	GtkWindow *modal = GTK_WINDOW(
			gtk_builder_get_object( builder, MODAL_ADICIONAR_COORDENADAS ));
	gtk_window_present(modal);
}

void TelaPrincipal::fecharPopupAdicionar() {
	GtkWindow *modal = GTK_WINDOW(
			gtk_builder_get_object(builder, MODAL_ADICIONAR_COORDENADAS));
	gtk_window_close(modal);
}

void TelaPrincipal::moverCima() {
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->moverCima(gtk_spin_button_get_value(inputPasso));

	atualizarTela();
}

void TelaPrincipal::moverBaixo() {
//	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
//			gtk_builder_get_object( builder, INPUT_PASSO ));
//	mundo->moverBaixo(gtk_spin_button_get_value(inputPasso));

	mundo->escalonar();

	atualizarTela();
}

void TelaPrincipal::moverEsquerda() {
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->moverEsquerda(gtk_spin_button_get_value(inputPasso));

	atualizarTela();
}

void TelaPrincipal::moverDireita() {
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->moverDireita(gtk_spin_button_get_value(inputPasso));

	atualizarTela();
}

void TelaPrincipal::zoomIn() {
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->zoomIn(gtk_spin_button_get_value(inputPasso));

	atualizarTela();
}

void TelaPrincipal::zoomOut() {
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->zoomOut(gtk_spin_button_get_value(inputPasso));

	atualizarTela();
}

ListaEnc<Coordenada> TelaPrincipal::mapearNoMundo(ObjetoGrafico obj) {
	GtkWidget *drawingArea = GTK_WIDGET(
			gtk_builder_get_object( builder, AREA_DESENHO ));
	Canvas canvas = mundo->getCanvas();

	double Xvmax = gtk_widget_get_allocated_width(drawingArea);
	double Yvmax = gtk_widget_get_allocated_height(drawingArea);

	int x, y;

	ListaEnc<Coordenada> coordenadas = ListaEnc<Coordenada>();

	for (int i = 0; i < obj.getListaCoord()->getSize(); ++i) {
		Coordenada coord = obj.getListaCoord()->recuperaDaPosicao(i);
		x = ((coord.getX() - canvas.Xmin()) / (canvas.Xmax() - canvas.Xmin()))
				* Xvmax;
		y = (1
				- (coord.getY() - canvas.Ymin())
						/ (canvas.Ymax() - canvas.Ymin())) * Yvmax;

		coordenadas.adiciona(Coordenada(x, y));
	}

	return coordenadas;
}

int TelaPrincipal::radioTelaSelecionado() {
	GtkRadioButton *radioTela = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_TELA));
	GtkRadioButton *radioObjeto = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_OBJETO));

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioTela))) {
		return 1;
	} else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioObjeto))) {
		return 2;
	}
	return -1;
}
