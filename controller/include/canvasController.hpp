#ifndef VIEWPORT_CONTROLLER
#define VIEWPORT_CONTROOLER

#include <gtk/gtk.h>
#include "elements/include/geometria.hpp"
#include "elements/include/window.hpp"

class CanvasController {
public:
	CanvasController();

	static gboolean configureViewport(GtkWidget *widget,
			GdkEventConfigure *event, gpointer data);
	static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data);
	static void drawGeometria(Geometria geometria);

	static void upButton(GtkWidget *widget, GdkEventButton *event);
	static void downButton(GtkWidget *widget, GdkEventButton *event);
	static void leftButton(GtkWidget *widget, GdkEventButton *event);
	static void rightButton(GtkWidget *widget, GdkEventButton *event);

	static void zoomIn(GtkWidget *widget, GdkEventButton *event);
	static void zoomOut(GtkWidget *widget, GdkEventButton *event);

private:
	static void clearSurface(void);
	static cairo_t *cr;
	static ListaEnc<Geometria> *figuras;
	static cairo_surface_t *surface;
	static Window window;

	static void redrawAll();
	static void drawLine(BasePoint p1, BasePoint p2);
	static void drawPoint(BasePoint p1);
	static void drawPolygon(ListaEnc<BasePoint> *points);
	static void changeWindowPosition(int x, int y);

};
#endif
