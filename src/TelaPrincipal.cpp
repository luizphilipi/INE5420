#include "TelaPrincipal.hpp"
#include "DescritorObj.hpp"

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

void abrir_mundo(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->abrirMundo();
}

void salvar_mundo(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->salvarMundo();
}

void zoom_in(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->zoomIn();
}

void zoom_out(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->zoomOut();
}

void aplicar_translacao(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->aplicarTranslacao();
}

void aplicar_escalonamento(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->aplicarEscalonamento();
}

void aplicar_rotacao(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->aplicarRotacao();
}

void adicionar_coordenada_poligono(GtkWidget *widget,
		TelaPrincipal *telaPrincipal) {
	telaPrincipal->adicionarCoordenadaPoligono();
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

	/*
	 *
	 * 	GtkWidget *addCoordButton = GTK_WIDGET(
	 * 				gtk_builder_get_object(builder, BOTAO_ADICIONAR_COORD_POLIGONO));
	 * 	g_signal_connect(G_OBJECT(addCoordButton), "clicked",
	 * 				G_CALLBACK(adicionar_coordenada_poligono), this);
	 */
	// FAZ COM QUE NÃO DELETE A POP-UP, SÓ ESCONDA
	GtkWidget *modalAdicionarCoordenadas = GTK_WIDGET(
			gtk_builder_get_object (builder, MODAL_ADICIONAR_COORDENADAS));
	g_signal_connect(G_OBJECT(modalAdicionarCoordenadas), "delete_event",
			G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	// signals

	GtkWidget *telaPrincipal = GTK_WIDGET(
			gtk_builder_get_object(builder, TELA_PRINCIPAL));

	// signals de transformações

	GtkWidget *botaoAplicarTranslacao = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_APLICAR_TRANSLACAO));
	g_signal_connect(G_OBJECT(botaoAplicarTranslacao), "clicked",
			G_CALLBACK(aplicar_translacao), this);

	GtkWidget *botaoAplicarEscalonamento = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_APLICAR_ESCALONAMENTO));
	g_signal_connect(G_OBJECT(botaoAplicarEscalonamento), "clicked",
			G_CALLBACK(aplicar_escalonamento), this);

	GtkWidget *botaoAplicarRotacao = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_APLICAR_ROTACAO));
	g_signal_connect(G_OBJECT(botaoAplicarRotacao), "clicked",
			G_CALLBACK(aplicar_rotacao), this);

	// fim signals de transformações


	//signal mundo abrir/salvar
	GtkWidget *botaoAbrirMundo = GTK_WIDGET(
			gtk_builder_get_object(builder, ABRIR_MUNDO));
	g_signal_connect(G_OBJECT(botaoAbrirMundo), "clicked",
			G_CALLBACK(abrir_mundo), this);

	GtkWidget *botaoSalvarMundo = GTK_WIDGET(
				gtk_builder_get_object(builder, SALVAR_MUNDO));
		g_signal_connect(G_OBJECT(botaoSalvarMundo), "clicked",
				G_CALLBACK(salvar_mundo), this);
	//FIM signal mundo abrir/salvar


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
			GtkBox *coordGrid = GTK_BOX(l->data);

			GList* children2 = gtk_container_get_children(
					GTK_CONTAINER(coordGrid));
			GList * l2;
			int i = 0;
			GtkSpinButton *input;
			int j = 0;
			int x = 0;
			int y = 0;
			for (l2 = children2; j < g_list_length(children2);
					l2 = l2->next, ++j) {
				if (j == 1) {
					GtkSpinButton *inputX = GTK_SPIN_BUTTON(l2->data);
					x = gtk_spin_button_get_value(inputX);
				} else if (j == 3) {
					GtkSpinButton *inputY = GTK_SPIN_BUTTON(l2->data);
					y = gtk_spin_button_get_value(inputY);
				}
			}

			coordenadas->adiciona(Coordenada(x, y));
		}
		mundo->adicionaPoligono(nomeObjeto, coordenadas);
	}
		break;
	}

	adicionarObjetoNaLista(nomeObjeto);

	atualizarTela();
	fecharPopupAdicionar();
}

void TelaPrincipal::adicionarObjetoNaLista(const char* nomeObjeto) {
	GtkListStore *listStoreObjetos = GTK_LIST_STORE(
			gtk_builder_get_object( builder, LIST_STORE_OBJETOS ));
	GtkTreeIter iter;
	gtk_list_store_append(listStoreObjetos, &iter);
	gtk_list_store_set(listStoreObjetos, &iter, 0, nomeObjeto, -1);
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
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->moverBaixo(gtk_spin_button_get_value(inputPasso));

	atualizarTela();
}

void TelaPrincipal::abrirMundo() {
	GtkEntry * caminhoArquivo = GTK_ENTRY(
			gtk_builder_get_object(builder, CAMINHO_ARQUIVO));
	string caminho = gtk_entry_get_text(caminhoArquivo);

	DescritorObj * dobj = new DescritorObj();
	ListaEnc<ObjetoGrafico> * df = new ListaEnc<ObjetoGrafico>;
	df = dobj->ler(caminho);
	for (int i = 0; i < df->size; i++) {
		ObjetoGrafico atual = df->recuperaDaPosicao(i);
		switch (atual.getTipo()) {
		case PONTO:
			mundo->adicionaPonto(atual.getNome(), atual.getCoord(0));
			break;
		case LINHA:
			mundo->adicionaLinha(atual.getNome(), atual.getCoord(0),
					atual.getCoord(1));
			break;
		case POLIGONO:
			mundo->adicionaPoligono(atual.getNome(), atual.getListaCoord());
			break;
		}
		adicionarObjetoNaLista(atual.getNome().c_str());
	}
	atualizarTela();

}

void TelaPrincipal::salvarMundo() {
	GtkEntry * caminhoArquivo = GTK_ENTRY(
			gtk_builder_get_object(builder, CAMINHO_ARQUIVO));
	string caminho = gtk_entry_get_text(caminhoArquivo);

	DescritorObj * dobj = new DescritorObj();
	dobj->escrever(mundo, caminho);
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

void TelaPrincipal::aplicarTranslacao() {
	GtkSpinButton *spinX = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_TRANSLACAO_X ));
	GtkSpinButton *spinY = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_TRANSLACAO_Y ));

	mundo->transladar(getObjetoSelecionado(),
			Coordenada(gtk_spin_button_get_value(spinX),
					gtk_spin_button_get_value(spinY)));

	atualizarTela();
}

void TelaPrincipal::aplicarEscalonamento() {
	GtkSpinButton *spinX = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_ESCALONAMENTO_X ));
	GtkSpinButton *spinY = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_ESCALONAMENTO_Y ));

	mundo->escalonar(getObjetoSelecionado(),
			Coordenada(gtk_spin_button_get_value(spinX),
					gtk_spin_button_get_value(spinY)));

	atualizarTela();
}

void TelaPrincipal::aplicarRotacao() {
	GtkSpinButton *spinAngulo = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_ANGULO_ROTACAO ));
	double angulo = gtk_spin_button_get_value(spinAngulo);

	if (getObjetoSelecionado() != NULL) {
		switch (this->radioRotacaoSelecionada()) {
		case 1:
			mundo->rotacionar(getObjetoSelecionado(), angulo);
			break;
		case 2:
			mundo->rotacionar(getObjetoSelecionado(), angulo, Coordenada(0, 0));
			break;
		case 3:
			GtkSpinButton *spinX = GTK_SPIN_BUTTON(
					gtk_builder_get_object( builder, SPIN_ROTACAO_X ));
			GtkSpinButton *spinY = GTK_SPIN_BUTTON(
					gtk_builder_get_object( builder, SPIN_ROTACAO_Y ));
			mundo->rotacionar(getObjetoSelecionado(), angulo,
					Coordenada(gtk_spin_button_get_value(spinX),
							gtk_spin_button_get_value(spinY)));
			break;
		}

		atualizarTela();
	}
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

char* TelaPrincipal::getObjetoSelecionado() {
	GtkTreeSelection *selection = gtk_tree_view_get_selection(
			GTK_TREE_VIEW(gtk_builder_get_object( builder, ARVORE_OBJETOS )));
	GtkTreeModel *model;
	GtkTreeIter iter;

	if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
		gchar *name;
		gtk_tree_model_get(model, &iter, 0, &name, -1);
		return name;
	}

	GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	GtkWidget *dialog = gtk_message_dialog_new(
			GTK_WINDOW(gtk_builder_get_object( builder, TELA_PRINCIPAL )),
			flags, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Selecione um objeto");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	return NULL;
}

int TelaPrincipal::radioRotacaoSelecionada() {
	GtkRadioButton *radioCentroObjeto = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_ROTACAO_CENTRO_OBJETO));
	GtkRadioButton *radioCentroTela = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_ROTACAO_ORIGEM));
	GtkRadioButton *radioCentroPonto = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_ROTACAO_PONTO));

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioCentroObjeto))) {
		return 1;
	} else if (gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(radioCentroTela))) {
		return 2;
	} else if (gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(radioCentroPonto))) {
		return 3;
	}
	return -1;
}

void TelaPrincipal::adicionarCoordenadaPoligono() {
	GtkBox *boxPoligono = GTK_BOX(
			gtk_builder_get_object(builder, BOX_POLIGONO));

	GtkBox *boxNovo = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0));

	GtkWidget *labelX = gtk_label_new("X: ");
	GtkWidget *labelY = gtk_label_new("Y: ");

	GtkAdjustment *adjustmentX = gtk_adjustment_new(0.0, -9999.0, 9999.0, 1.0,
			10.0, 0.0);

	GtkWidget *spinX = gtk_spin_button_new(adjustmentX, 1.0, 0);

	GtkAdjustment *adjustmentY = gtk_adjustment_new(0.0, -9999.0, 9999.0, 1.0,
			10.0, 0.0);

	GtkWidget *spinY = gtk_spin_button_new(adjustmentY, 1.0, 0);

	gtk_box_pack_end(boxNovo, labelX, false, true, 0);
	gtk_box_pack_end(boxNovo, spinX, false, true, 0);
	gtk_box_pack_end(boxNovo, labelY, false, true, 0);
	gtk_box_pack_end(boxNovo, spinY, false, true, 0);

	gtk_box_pack_end(boxPoligono, GTK_WIDGET(boxNovo), false, true, 0);

	gtk_widget_queue_draw(GTK_WIDGET(boxPoligono));
}
