#include "TelaPrincipal.hpp"
#include "DescritorObj.hpp"
#include <vector>

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

void rotacao_mundo(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->rotacaoMundo();
}

void atualizar_tela(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->atualizarTela();
}

void adicionar_coord_bspline(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->adicionarCoordenadaBSpline();
}

void adicionar_superficie_bezier(GtkWidget *widget, TelaPrincipal *telaPrincipal) {
	telaPrincipal->adicionarCoordenadaSuperficieBezier();
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

	GtkWidget *windowRotationBtn = GTK_WIDGET(
			gtk_builder_get_object (builder, WINDOW_ROTATION_BTN));
	g_signal_connect(G_OBJECT(windowRotationBtn), "clicked",
			G_CALLBACK(rotacao_mundo), this);

	GtkWidget *addButton = GTK_WIDGET(
			gtk_builder_get_object(builder, "addObj"));
	g_signal_connect(G_OBJECT(addButton), "clicked",
			G_CALLBACK(abrir_popup_adicionar), this);

	GtkWidget *botaoAdicionarObjeto = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_ADICIONAR_OBJETO));
	g_signal_connect(G_OBJECT(botaoAdicionarObjeto), "clicked",
			G_CALLBACK(adicionar_objeto), this);

	//signals novas coordenadas
	GtkWidget *addCoordButton = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_ADICIONAR_COORD_POLIGONO));
	g_signal_connect(G_OBJECT(addCoordButton), "clicked",
			G_CALLBACK(adicionar_coordenada_poligono), this);

	GtkWidget *botaoAdicionarCoordBSpline = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_ADICIONAR_COORD_BSPLINE));
	g_signal_connect(G_OBJECT(botaoAdicionarCoordBSpline), "clicked",
			G_CALLBACK(adicionar_coord_bspline), this);

	GtkWidget *botaoAdicionarBSurface = GTK_WIDGET(
			gtk_builder_get_object(builder, BOTAO_ADD_BEZIER_SURFACE));
	g_signal_connect(G_OBJECT(botaoAdicionarBSurface), "clicked",
			G_CALLBACK(adicionar_superficie_bezier), this);

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

	// Clipping
	GtkWidget *radioCohen = GTK_WIDGET(
			gtk_builder_get_object(builder, RADIO_COHEN));
	g_signal_connect(G_OBJECT(radioCohen), "toggled",
			G_CALLBACK(atualizar_tela), this);

	GtkWidget *radioLiang = GTK_WIDGET(
			gtk_builder_get_object(builder, RADIO_LIANG));
	g_signal_connect(G_OBJECT(radioLiang), "toggled",
			G_CALLBACK(atualizar_tela), this);

	GtkWidget *radioDesativarClipping = GTK_WIDGET(
			gtk_builder_get_object(builder, RADIO_DESATIVAR_CLIPPING));
	g_signal_connect(G_OBJECT(radioDesativarClipping), "toggled",
			G_CALLBACK(atualizar_tela), this);

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
		GtkSpinButton *spinPontoZ = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_PONTO_Z ));
		mundo->adicionaPonto(nomeObjeto,
				Coordenada(gtk_spin_button_get_value(spinPontoX),
						gtk_spin_button_get_value(spinPontoY),
						gtk_spin_button_get_value(spinPontoZ)));
	}
		break;
	case 1: {
		GtkSpinButton *spinLinhaX1 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_X1 ));
		GtkSpinButton *spinLinhaY1 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_Y1 ));
		GtkSpinButton *spinLinhaZ1 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_Z1 ));
		Coordenada coord1 = Coordenada(gtk_spin_button_get_value(spinLinhaX1),
				gtk_spin_button_get_value(spinLinhaY1),
				gtk_spin_button_get_value(spinLinhaZ1));

		GtkSpinButton *spinLinhaX2 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_X2 ));
		GtkSpinButton *spinLinhaY2 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_Y2 ));
		GtkSpinButton *spinLinhaZ2 = GTK_SPIN_BUTTON(
				gtk_builder_get_object( builder, SPIN_LINHA_Z2 ));
		Coordenada coord2 = Coordenada(gtk_spin_button_get_value(spinLinhaX2),
				gtk_spin_button_get_value(spinLinhaY2),
				gtk_spin_button_get_value(spinLinhaZ2));

		mundo->adicionaLinha(nomeObjeto, coord1, coord2);
	}
		break;
	case 2: {

		GtkToggleButton *botaoPreencher = GTK_TOGGLE_BUTTON(
				gtk_builder_get_object(builder, BOTAO_PREENCHER));
		GtkColorChooser *corPreenchimento = GTK_COLOR_CHOOSER(
				gtk_builder_get_object(builder, COR_PREENCHIMENTO));
		bool preenchimento = gtk_toggle_button_get_active(botaoPreencher);

		GdkRGBA cor;
		gtk_color_chooser_get_rgba(corPreenchimento, &cor);
		mundo->adicionaPoligono(nomeObjeto, coordenadas, preenchimento, cor);
		coordenadas = vector<Coordenada>();
	}
		break;
	case 3: {
		GtkBox *boxBezier = GTK_BOX(
				gtk_builder_get_object( builder, BOX_BEZIER ));
		GList* children = gtk_container_get_children(GTK_CONTAINER(boxBezier));
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
			int z = 0;
			for (l2 = children2; j < g_list_length(children2);
					l2 = l2->next, ++j) {
				if (j == 1) {
					GtkSpinButton *inputX = GTK_SPIN_BUTTON(l2->data);
					x = gtk_spin_button_get_value(inputX);
				} else if (j == 3) {
					GtkSpinButton *inputY = GTK_SPIN_BUTTON(l2->data);
					y = gtk_spin_button_get_value(inputY);
				} else if (j == 5) {
					GtkSpinButton *inputZ = GTK_SPIN_BUTTON(l2->data);
					z = gtk_spin_button_get_value(inputZ);
				}
			}
			coordenadas.push_back(Coordenada(x, y, z));
		}
		mundo->adicionaBezier(nomeObjeto, coordenadas);
		coordenadas = vector<Coordenada>();
	}
		break;

	case 4:
		mundo->adicionaBSpline(nomeObjeto, coordenadas);
		coordenadas = vector<Coordenada>();
		break;
	case 5:
		mundo->adicionaSuperficieBezier(nomeObjeto, coordenadas);
		coordenadas = vector<Coordenada>();
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

void TelaPrincipal::desenharPonto(cairo_t *cr, Coordenada coord) {
	cairo_move_to(cr, coord._x, coord._y);
	cairo_arc(cr, coord._x, coord._y, 1.0, 0.0, 2.0 * 3.14);
	cairo_fill_preserve(cr);
}

void TelaPrincipal::desenharLinha(cairo_t *cr, Coordenada coord1,
		Coordenada coord2) {
	cairo_line_to(cr, coord1._x, coord1._y);
	cairo_line_to(cr, coord2._x, coord2._y);
}

//void TelaPrincipal::desenharQuadrado(cairo_t *cr, Coordenada coord1, Coordenada coord2,
//		Coordenada coord3, Coordenada coord4){
//	cairo_move_to(cr, coord1._x, coord1._y);
//	cairo_line_to(cr, coord1._x, coord1._y);
//	cairo_line_to(cr, coord2._x, coord2._y);
//	cairo_line_to(cr, coord3._x, coord3._y);
//	cairo_line_to(cr, coord4._x, coord4._y);
//	cairo_close_path(cr);
//	double blue = ((double)rand() / (double)(RAND_MAX));
//	cairo_set_source_rgb(cr, 0, 0, blue);
//	cairo_fill(cr);
//	cairo_stroke(cr);
//}

void TelaPrincipal::desenhar(cairo_t *cr, ObjetoGrafico* obj) {
	vector<Coordenada> coords = mapearNoMundo(obj);
	if (coords.size() > 0) {
		clock_t begin = clock();
		cairo_set_source_rgb(cr, 0, 0, 0);
		switch (obj->getTipo()) {
		case PONTO:
			desenharPonto(cr, coords[0]);
			break;
		case POLIGONO:
			cairo_move_to(cr, coords[0]._x, coords[0]._y);
			for (int i = 0; i < coords.size() - 1; i++) {
				desenharLinha(cr, coords[i], coords[i + 1]);
			}
			if (obj->isPreenchido()) {
				GdkRGBA cor = obj->getCor();
				cairo_set_source_rgb(cr, (double) cor.red, (double) cor.green,
						(double) cor.blue);
				cairo_fill(cr);
			}
			cairo_close_path(cr);
			break;
		case LINHA:
		case BEZIER:
		case BSPLINE:
		case SUPERFICIE_BEZIER:
			for (int i = 0; i < coords.size() - 1; i++) {
				desenharLinha(cr, coords[i], coords[i + 1]);
			}
			break;
		case OBJETO3D:
			for (int i = 0; i < coords.size() - 1; i += 2) {
				desenharLinha(cr, coords[i], coords[i + 1]);
			}
			break;
		}
		cairo_stroke(cr);
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		/*
		 std::cout << "Desenhando objeto " << obj->getNome() << " em: "
		 << elapsed_secs << std::endl;
		 */
	}
}

void TelaPrincipal::desenharTudo(cairo_t *cr) {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);

	for (int i = 0; i < mundo->getObjetos()->getSize(); ++i) {
		desenhar(cr, mundo->getObjetos()->recuperaDaPosicao(i));
	}

	// borda vermelha do canvas
	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_set_line_width(cr, 1);

	GtkWidget *drawingArea = GTK_WIDGET(
			gtk_builder_get_object(builder, AREA_DESENHO));
	int Xvmax = gtk_widget_get_allocated_width(drawingArea) - 10;
	int Yvmax = gtk_widget_get_allocated_height(drawingArea) - 10;

	cairo_move_to(cr, 10, 10);
	cairo_line_to(cr, Xvmax, 10);
	cairo_line_to(cr, Xvmax, Yvmax);
	cairo_line_to(cr, 10, Yvmax);
	cairo_line_to(cr, 10, 10);

	cairo_stroke(cr);
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

//	vector<Coordenada> c;
//	c.push_back(Coordenada(-100, 300, 100));
//	c.push_back(Coordenada(0, 300, 100));
//	c.push_back(Coordenada(100, 300, 100));
//	c.push_back(Coordenada(200, 300, 100));
//
//	c.push_back(Coordenada(-100, 300, 200));
//	c.push_back(Coordenada(0, -200, 200));
//	c.push_back(Coordenada(100, -200, 200));
//	c.push_back(Coordenada(200, 300, 200));
//
//	c.push_back(Coordenada(-100, 300, 300));
//	c.push_back(Coordenada(0, -200, 300));
//	c.push_back(Coordenada(100, -200, 300));
//	c.push_back(Coordenada(200, 300, 300));
//
//	c.push_back(Coordenada(-100, 300, 400));
//	c.push_back(Coordenada(0, 300, 400));
//	c.push_back(Coordenada(100, 300, 400));
//	c.push_back(Coordenada(200, 300, 400));
//
//	mundo->adicionaSuperficieBezier("teste", c);
//	adicionarObjetoNaLista("teste");

	atualizarTela();
}

void TelaPrincipal::moverBaixo() {
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->moverBaixo(gtk_spin_button_get_value(inputPasso));

	atualizarTela();
}
#include <iostream>
void TelaPrincipal::abrirMundo() {
	GtkEntry * caminhoArquivo = GTK_ENTRY(
			gtk_builder_get_object(builder, CAMINHO_ARQUIVO));
	std::string caminho = gtk_entry_get_text(caminhoArquivo);

	DescritorObj * dobj = new DescritorObj();

	mundo = dobj->ler(caminho);
	for (int i = 0; i < mundo->getObjetos()->size; i++) {
		ObjetoGrafico *atual = mundo->getObjetos()->recuperaDaPosicao(i);
		adicionarObjetoNaLista(atual->getNome().c_str());
	}
	atualizarTela();

}

void TelaPrincipal::salvarMundo() {
	GtkEntry * caminhoArquivo = GTK_ENTRY(
			gtk_builder_get_object(builder, CAMINHO_ARQUIVO));
	std::string caminho = gtk_entry_get_text(caminhoArquivo);

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

void TelaPrincipal::rotacaoMundo() {
	GtkSpinButton *inputPasso = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, INPUT_PASSO ));
	mundo->rotacionar(gtk_spin_button_get_value(inputPasso));
	atualizarTela();
}

void TelaPrincipal::aplicarTranslacao() {
	GtkSpinButton *spinX = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_TRANSLACAO_X ));
	GtkSpinButton *spinY = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_TRANSLACAO_Y ));
	GtkSpinButton *spinZ = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_TRANSLACAO_Z ));

	mundo->transladar(getObjetoSelecionado(),
			Coordenada(gtk_spin_button_get_value(spinX),
					gtk_spin_button_get_value(spinY),
					gtk_spin_button_get_value(spinZ)));

	atualizarTela();
}

void TelaPrincipal::aplicarEscalonamento() {
	GtkSpinButton *spinX = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_ESCALONAMENTO_X ));
	GtkSpinButton *spinY = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_ESCALONAMENTO_Y ));
	GtkSpinButton *spinZ = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_ESCALONAMENTO_Z ));

	mundo->escalonar(getObjetoSelecionado(),
			Coordenada(gtk_spin_button_get_value(spinX),
					gtk_spin_button_get_value(spinY),
					gtk_spin_button_get_value(spinZ)));

	atualizarTela();
}

void TelaPrincipal::aplicarRotacao() {
	GtkSpinButton *spinAngulo = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_ANGULO_ROTACAO ));
	double angulo = gtk_spin_button_get_value(spinAngulo);

	GtkComboBox *comboBoxRotacao = GTK_COMBO_BOX(
			gtk_builder_get_object( builder, COMBO_BOX_ROTACAO ));
	int index = gtk_combo_box_get_active(comboBoxRotacao);

	if (getObjetoSelecionado() != NULL) {
		switch (this->radioRotacaoSelecionada()) {
		case 1: {
			mundo->rotacionar(getObjetoSelecionado(), angulo, index);
		}
			break;
		case 2:
			mundo->rotacionar(getObjetoSelecionado(), angulo, Coordenada(0, 0),
					index);
			break;
		case 3:
			GtkSpinButton *spinX = GTK_SPIN_BUTTON(
					gtk_builder_get_object( builder, SPIN_ROTACAO_X ));
			GtkSpinButton *spinY = GTK_SPIN_BUTTON(
					gtk_builder_get_object( builder, SPIN_ROTACAO_Y ));
			mundo->rotacionar(getObjetoSelecionado(), angulo,
					Coordenada(gtk_spin_button_get_value(spinX),
							gtk_spin_button_get_value(spinY)), index);
			break;
		}

		atualizarTela();
	}
}

std::vector<Coordenada> TelaPrincipal::mapearNoMundo(ObjetoGrafico *obj) {
	clock_t begin = clock();

	GtkWidget *drawingArea = GTK_WIDGET(
			gtk_builder_get_object( builder, AREA_DESENHO ));
	Canvas canvas = mundo->getCanvas();

	double Xvmax = gtk_widget_get_allocated_width(drawingArea) - 20;
	double Yvmax = gtk_widget_get_allocated_height(drawingArea) - 20;

	int x, y;

	std::vector<Coordenada> coordenadas;
	std::vector<Coordenada> clipped = obj->clip(radioClippingSelecionado());

	for (auto &coord : clipped) {
		x = 10 + ((coord._x + 1) / 2) * Xvmax;
		y = 10 + (1 - (coord._y + 1) / 2) * Yvmax;
		coordenadas.push_back(Coordenada(x, y));
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	/*
	 std::cout << "Mapeando objeto " << obj->getNome() << " com "
	 << coordenadas.size() << " pontos em: " << elapsed_secs
	 << std::endl;

	 */
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

int TelaPrincipal::radioClippingSelecionado() {
	GtkRadioButton *radioCohen = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_COHEN));
	GtkRadioButton *radioLiang = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_LIANG));
	GtkRadioButton *radioDesativar = GTK_RADIO_BUTTON(
			gtk_builder_get_object (builder, RADIO_DESATIVAR_CLIPPING));

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioCohen))) {
		return 1;
	} else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioLiang))) {
		return 2;
	} else if (gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(radioDesativar))) {
		return 0;
	}
	return -1;
}

void TelaPrincipal::adicionarCoordenadaBSpline() {
	GtkSpinButton *spinBSplineX = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_BSPLINE_X ));
	GtkSpinButton *spinBSplineY = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_BSPLINE_Y ));
	GtkSpinButton *spinBSplineZ = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_BSPLINE_Z ));
	Coordenada bspline = Coordenada(gtk_spin_button_get_value(spinBSplineX),
			gtk_spin_button_get_value(spinBSplineY),
			gtk_spin_button_get_value(spinBSplineZ));
	coordenadas.push_back(bspline);
	bspline.print();
}

void TelaPrincipal::adicionarCoordenadaPoligono() {
	GtkSpinButton *spinPoligonoX = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_POLIGONO_X ));
	GtkSpinButton *spinPoligonoY = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_POLIGONO_Y ));
	GtkSpinButton *spinPoligonoZ = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_POLIGONO_Z ));
	Coordenada pol = Coordenada(gtk_spin_button_get_value(spinPoligonoX),
			gtk_spin_button_get_value(spinPoligonoY),
			gtk_spin_button_get_value(spinPoligonoZ));
	coordenadas.push_back(pol);
	pol.print();
}

void TelaPrincipal::adicionarCoordenadaSuperficieBezier() {
	GtkSpinButton *spin3DX1 = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_3D_X1 ));
	GtkSpinButton *spin3DY1 = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_3D_Y1 ));
	GtkSpinButton *spin3DZ1 = GTK_SPIN_BUTTON(
			gtk_builder_get_object( builder, SPIN_3D_Z1 ));
	Coordenada c1 = Coordenada(gtk_spin_button_get_value(spin3DX1),
			gtk_spin_button_get_value(spin3DY1),
			gtk_spin_button_get_value(spin3DZ1));

	coordenadas.push_back(c1);
}
