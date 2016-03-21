#include "../include/canvasController.hpp"

#include "consts.hpp"
#include "elements/include/geometria.hpp"
#include "elements/include/linha.hpp"
#include "elements/include/point.hpp"
#include "elements/include/poligono.hpp"
#include "elements/include/window.hpp"
#include <iostream>

cairo_surface_t *CanvasController::surface = NULL;
cairo_t *CanvasController::cr = NULL;
ListaEnc<Geometria> *CanvasController::figuras = new ListaEnc<Geometria>();
Window CanvasController::window = Window(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
GtkWidget *parent;

//Constructor
CanvasController::CanvasController() {
}

//
gboolean CanvasController::configureViewport(GtkWidget *widget,
		GdkEventConfigure *event, gpointer data) {
	parent = widget;
	if (surface) {
		cairo_surface_destroy(surface);
	}

	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
			CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));

	clearSurface();

	Geometria geo = Linha("Linha", 50, 50, 100, 100);
	drawGeometria(geo);

	geo = Point("Ponto", 200, 200);
	drawGeometria(geo);
	figuras->adiciona(geo);

	ListaEnc<BasePoint> *lista = new ListaEnc<BasePoint>();
	lista->adiciona(BasePoint(300, 300));
	lista->adicionaNoInicio(BasePoint(400, 350));
	lista->adicionaNoInicio(BasePoint(500, 200));

	geo = Poligono("Poligono", lista);
	drawGeometria(geo);
	figuras->adiciona(geo);

	return true;
}

//
gboolean CanvasController::draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	return false;
}

//
void CanvasController::clearSurface() {
	cr = cairo_create(surface);
	// fundo branco
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	// arestas do canvas
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);
	cairo_rectangle(cr, 10, 10, CANVAS_WIDTH - 20, CANVAS_HEIGHT - 20);
	cairo_stroke(cr);

	// eixo x, em azul
	cairo_set_source_rgb(cr, 0, 0, 1);
	cairo_move_to(cr, 10, CANVAS_HEIGHT / 2.0);
	cairo_line_to(cr, CANVAS_WIDTH - 10,
	CANVAS_HEIGHT / 2.0);
	cairo_stroke(cr);

	// eixo y, em azul
	cairo_set_source_rgb(cr, 0, 0, 1);
	cairo_move_to(cr, CANVAS_WIDTH / 2, 10);
	cairo_line_to(cr, CANVAS_WIDTH / 2, CANVAS_HEIGHT - 10);
	cairo_stroke(cr);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 2);
}

void CanvasController::drawLine(BasePoint p1, BasePoint p2) {
	cairo_move_to(cr, p1.getX() + window.getX(), p1.getY() + window.getY());
	cairo_line_to(cr, p2.getX() + window.getX(), p2.getY() + window.getY());
	cairo_stroke(cr);
}

void CanvasController::drawPoint(BasePoint p1) {
	cairo_move_to(cr, p1.getX() + window.getX(), p1.getY() + window.getY());
	cairo_arc(cr, p1.getX() + window.getX(), p1.getY() + window.getY(), 1.0,
			0.0, 2.0 * 3.14);
	cairo_fill_preserve(cr);
	cairo_stroke(cr);
}

void CanvasController::drawPolygon(ListaEnc<BasePoint> *points) {
	cairo_move_to(cr, points->recuperaDaPosicao(0).getX() + window.getX(),
			points->recuperaDaPosicao(0).getY() + window.getY());
	for (int i = 1; i < points->getSize(); ++i) {
		cairo_line_to(cr, points->recuperaDaPosicao(i).getX() + window.getX(),
				points->recuperaDaPosicao(i).getY() + window.getY());
	}
	cairo_close_path(cr);
	cairo_stroke(cr);
}

void CanvasController::drawGeometria(Geometria geometria) {
	switch (geometria.getTipo()) {
	case LINHA:
		drawLine(geometria.getPonto(0), geometria.getPonto(1));
		break;
	case PONTO:
		drawPoint(geometria.getPonto(0));
		break;
	case POLIGONO:
		drawPolygon(geometria.getPontos());
		break;
	}
}

void CanvasController::zoomIn(GtkWidget *widget, GdkEventButton *event){
	cout << "\nzoomIn";

	Geometria *geo = new Linha("Linha", 200, 400, 500, 200);
	drawGeometria(geo);


void CanvasController::redrawAll() {
	for (int i = 0; i < figuras->getSize(); ++i) {
		drawGeometria(figuras->recuperaDaPosicao(i));
	}
}


void CanvasController::zoomIn(GtkWidget *widget, GdkEventButton *event) {
	cout << "\nzoomIn";
	Geometria geo = Linha("ss", 50, 50, 500, 100);
	drawGeometria(geo);
}

void CanvasController::zoomOut(GtkWidget *widget, GdkEventButton *event) {
	cout << "\nzoomOut";
}

void CanvasController::upButton(GtkWidget *widget, GdkEventButton *event) {
	changeWindowPosition(0, -5);
}

void CanvasController::downButton(GtkWidget *widget, GdkEventButton *event) {
	changeWindowPosition(0, 5);
}

void CanvasController::leftButton(GtkWidget *widget, GdkEventButton *event) {
	changeWindowPosition(-5, 0);
}

void CanvasController::rightButton(GtkWidget *widget, GdkEventButton *event) {
	changeWindowPosition(5, 0);
}

void CanvasController::changeWindowPosition(int x, int y) {
	gtk_widget_queue_draw(parent);
	window.move(x, y);
	cout << window.getY();
	clearSurface();
	redrawAll();
}
