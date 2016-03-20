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

private:
	static void clearSurface(void);
	static cairo_surface_t *surface;
	static void drawGeometria(cairo_t *cr, Geometria *geometria);
};

#endif
