#ifndef VIEWPORT_COMPONENT
#define VIEWPORT_COMPONENT

#include "../../controller/include/canvasController.hpp"

class PainelDireita {
public:
	GtkWidget * render() {
		GtkWidget *window = gtk_drawing_area_new();

		gtk_widget_set_size_request(window, CANVAS_WIDTH, CANVAS_HEIGHT);
		g_signal_connect(window, "draw", G_CALLBACK(CanvasController::draw),
		NULL);
		g_signal_connect(window, "configure-event",
				G_CALLBACK(CanvasController::configureViewport), NULL);
		gtk_widget_show(window);

		return window;
	}

};

#endif
