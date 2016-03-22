#include "telaPrincipal.hpp"

extern "C" {
gboolean callback_desenhar_tudo(GtkWidget *widget, cairo_t *cr,
		TelaPrincipal *window) {
	std::cout << "draw";
	window->desenharTudo(cr);
	return false;
}

void mover_cima(GtkWidget *widget, TelaPrincipal *window) {
	window->moverCima();
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
	g_signal_connect(G_OBJECT(moveUpButton), "button_press_event", G_CALLBACK(mover_cima),
			this);
	// signals

	GtkWidget *window = GTK_WIDGET(
			gtk_builder_get_object(builder, TELA_PRINCIPAL));
	gtk_widget_show_all(window);
	gtk_main();
}

TelaPrincipal::~TelaPrincipal() {

}

void TelaPrincipal::adicionarObjeto() {
	// TODO adicionar objeto
	std::cout << "objeto adicionado :D";
}

void TelaPrincipal::desenhar(cairo_t *cr, ListaEnc<Coordenada> * coords) {
	cairo_move_to(cr, coords->recuperaDaPosicao(0).getX(),
			coords->recuperaDaPosicao(0).getY());
	cairo_line_to(cr, coords->recuperaDaPosicao(0).getX(),
			coords->recuperaDaPosicao(0).getY());

	for (int i = 1; i < coords->getSize(); i++) {
		cairo_line_to(cr, coords->recuperaDaPosicao(i).getX(),
				coords->recuperaDaPosicao(i).getY());
	}

	if (coords->getSize() == 1) {
		// um pixel, se não, não aparece :v
		cairo_line_to(cr, coords->recuperaDaPosicao(0).getX() + 1,
				coords->recuperaDaPosicao(0).getY() + 1);
	} else {
		cairo_line_to(cr, coords->recuperaDaPosicao(0).getX(),
				coords->recuperaDaPosicao(0).getY());
	}
	cairo_stroke(cr);
}

void TelaPrincipal::desenharTudo(cairo_t *cr) {
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);

	for (int i = 0; i < mundo->getObjetos().getSize(); ++i) {
		desenhar(cr, mundo->getObjetos().recuperaDaPosicao(i).getPontos());
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
	std::cout << builder;
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
