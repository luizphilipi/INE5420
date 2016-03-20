#include <telaPrincipal.hpp>
#include "consts.hpp"

//Constructor
TelaPrincipal::TelaPrincipal() {
}

GtkWidget * TelaPrincipal::render() {
	//Init Widgets
	GtkWidget * window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	fixedContainer = gtk_fixed_new();

	gtk_window_set_default_geometry((GtkWindow*) window, APP_WIDTH, APP_HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	//Connect events
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	//Adds widget to container
	gtk_container_add(GTK_CONTAINER(window), fixedContainer);

	//Show widgets
	gtk_widget_show(window);
	gtk_widget_show(fixedContainer);

	return window;
}

void TelaPrincipal::adicionarWidget(GtkWidget * widget, int x, int y) {
	gtk_fixed_put((GtkFixed*) fixedContainer, widget, x, y);
}
