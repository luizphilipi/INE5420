#ifndef VIEWPORT_CONTROLLER
#define VIEWPORT_CONTROOLER

#include <gtk/gtk.h>
#include "elements/include/geometria.hpp"

class CanvasController {
public:
	CanvasController();
	static gboolean configureViewport(GtkWidget *widget,
			GdkEventConfigure *event, gpointer data);
	static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data);
	static void drawGeometria(Geometria *geometria);

private:
	static void clearSurface(void);
	static cairo_t *cr;
	static cairo_surface_t *surface;
	static void drawLine(BasePoint p1, BasePoint p2);
	static void drawPoint(BasePoint p1);
	static void drawPolygon(ListaEnc<BasePoint> *points);

};
#endif
