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

	static void upButton(GtkWidget *widget, GdkEventButton *event);
	static void downButton(GtkWidget *widget, GdkEventButton *event);
	static void leftButton(GtkWidget *widget, GdkEventButton *event);
	static void rightButton(GtkWidget *widget, GdkEventButton *event);

	static void zoomIn(GtkWidget *widget, GdkEventButton *event);
	static void zoomOut(GtkWidget *widget, GdkEventButton *event);


private:
	static void clearSurface(void);
	static cairo_surface_t *surface;
	static cairo_t *cr;
	static void drawGeometria(cairo_t *cr, Geometria *geometria);

};

#endif
