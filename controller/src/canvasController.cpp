#include "../include/canvasController.hpp"

#include "consts.hpp"
#include "elements/include/geometria.hpp"
#include "elements/include/linha.hpp"
#include <iostream>

cairo_surface_t *CanvasController::surface = NULL;

//Constructor
CanvasController::CanvasController() {
}

//
gboolean CanvasController::configureViewport(GtkWidget *widget,
		GdkEventConfigure *event, gpointer data) {
	if (surface) {
		cairo_surface_destroy(surface);
	}

	surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
			CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));

	clearSurface();

	return true;
}

//
gboolean CanvasController::draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	return false;
}

//
void CanvasController::clearSurface(void) {
	cairo_t *cr = cairo_create(surface);

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

	Geometria *geo = new Linha("Teste", 50, 50, 100, 100);
	drawGeometria(cr, geo);

}

void CanvasController::drawGeometria(cairo_t *cr, Geometria *geometria) {
	switch (geometria->getTipo()) {
	case LINHA:
		cout << "Linha";
	}
	BasePoint ponto1 = geometria->getPonto(0);
	BasePoint ponto2 = geometria->getPonto(1);

	cairo_move_to(cr, ponto1.getX(), ponto1.getY());
	cairo_line_to(cr, ponto2.getX(), ponto2.getY());
	cairo_stroke(cr);
}
