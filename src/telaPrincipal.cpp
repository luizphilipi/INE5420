#include "telaPrincipal.hpp"

extern "C" {
gboolean callback_desenhar_tudo(GtkWidget *widget, cairo_t *cr,
		TelaPrincipal *window) {
	window->desenharTudo(cr);
	return false;
}

void mover_cima(GtkWidget *widget, TelaPrincipal *window) {
	window->moverCima();
}

void mover_baixo(GtkWidget *widget, TelaPrincipal *window) {
	window->moverBaixo();
}

void mover_esquerda(GtkWidget *widget, TelaPrincipal *window) {
	window->moverEsquerda();
}

void mover_direita(GtkWidget *widget, TelaPrincipal *window) {
	window->moverDireita();
}

void adicionar_objeto(GtkWidget *widget, TelaPrincipal *window) {
	window->adicionarObjeto();
}

void zoom_in(GtkWidget *widget, TelaPrincipal *window) {
	window->zoomIn();
}

void zoom_out(GtkWidget *widget, TelaPrincipal *window) {
	window->zoomOut();
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
	g_signal_connect(G_OBJECT(zoomInBtn), "clicked",
			G_CALLBACK(zoom_in), this);

	GtkWidget *zoomOutBtn = GTK_WIDGET(
			gtk_builder_get_object (builder, ZOOM_OUT_BTN));
	g_signal_connect(G_OBJECT(zoomOutBtn), "clicked",
			G_CALLBACK(zoom_out), this);

	GtkWidget *addButton = GTK_WIDGET(
			gtk_builder_get_object(builder, "addObj"));
	g_signal_connect(G_OBJECT(addButton), "clicked",
			G_CALLBACK(adicionar_objeto), this);
	// signals

	GtkWidget *window = GTK_WIDGET(
			gtk_builder_get_object(builder, TELA_PRINCIPAL));

	//para de rodar ao clicar no X
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();
}

TelaPrincipal::~TelaPrincipal() {

}

void TelaPrincipal::adicionarObjeto() {
	// TODO adicionar objeto
	mundo->adicionaPonto("Teste 2", Coordenada(300, 300));
	mundo->adicionaLinha("teste", Coordenada(50, 50), Coordenada(100, 100));
	ListaEnc<Coordenada>* coords = new ListaEnc<Coordenada>();
	coords->adiciona(Coordenada(150, 150));
	coords->adiciona(Coordenada(200, 330));
	coords->adiciona(Coordenada(150, 500));
	mundo->adicionaPoligono("poligono", coords);
	atualizarTela();
}

void TelaPrincipal::desenhar(cairo_t *cr, ListaEnc<Coordenada> coords) {
	cairo_move_to(cr, coords.recuperaDaPosicao(0).getX(),
			coords.recuperaDaPosicao(0).getY());
	cairo_line_to(cr, coords.recuperaDaPosicao(0).getX(),
			coords.recuperaDaPosicao(0).getY());

	for (int i = 1; i < coords.getSize(); i++) {
		cairo_line_to(cr, coords.recuperaDaPosicao(i).getX(),
				coords.recuperaDaPosicao(i).getY());
	}

	if (coords.getSize() == 1) {
		// um pixel, se não, não aparece :v
		cairo_line_to(cr, coords.recuperaDaPosicao(0).getX() + 3,
				coords.recuperaDaPosicao(0).getY() + 3);
	} else {
		cairo_line_to(cr, coords.recuperaDaPosicao(0).getX(),
				coords.recuperaDaPosicao(0).getY());
	}
	cairo_stroke(cr);
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
	Window window = mundo->getWindow();

	double Xvmax = gtk_widget_get_allocated_width(drawingArea);
	double Yvmax = gtk_widget_get_allocated_height(drawingArea);

	int x, y;

	ListaEnc<Coordenada> newcoords = ListaEnc<Coordenada>();

	for (int i = 0; i < obj.getPontos()->getSize(); ++i) {
		Coordenada coord = obj.getPontos()->recuperaDaPosicao(i);
		x = ((coord.getX() - window.Xmin()) / (window.Xmax() - window.Xmin()))
				* Xvmax;
		y = (1
				- (coord.getY() - window.Ymin())
						/ (window.Ymax() - window.Ymin())) * Yvmax;

		newcoords.adiciona(Coordenada(x, y));
	}

	return newcoords;
}
