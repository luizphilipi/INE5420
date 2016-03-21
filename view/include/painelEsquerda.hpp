#ifndef NAVIGATION_COMPONENT
#define NAVIGATION_COMPONENT

#include <gtk/gtk.h>

class PainelEsquerda {
public:
	GtkWidget * render() {
		GtkWidget *window;
		GtkWidget *vbox;
		GtkWidget *hbox;

		GtkWidget *upButton;
		GtkWidget *downButton;
		GtkWidget *leftButton;
		GtkWidget *rightButton;

		GtkWidget *zoomInButton;
		GtkWidget *zoomOutButton;

		//Init Widgets
		window = gtk_frame_new("Navegação");
		vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, DEFAULT_SPACING);
		hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, DEFAULT_SPACING);
		leftButton = gtk_button_new_from_icon_name("go-previous",
				GTK_ICON_SIZE_MENU);
		rightButton = gtk_button_new_from_icon_name("go-next",
				GTK_ICON_SIZE_MENU);
		upButton = gtk_button_new_from_icon_name("go-up", GTK_ICON_SIZE_MENU);
		downButton = gtk_button_new_from_icon_name("go-down",
				GTK_ICON_SIZE_MENU);
		zoomInButton = gtk_button_new_with_label("+");
		zoomOutButton = gtk_button_new_with_label("-");

		// Tamanhos
		gtk_widget_set_size_request(upButton, 160, 20);
		gtk_widget_set_size_request(downButton, 160, 20);
		gtk_widget_set_size_request(leftButton, 80, 20);
		gtk_widget_set_size_request(rightButton, 80, 20);

		//Adds widget to container
		gtk_container_add(GTK_CONTAINER(window), vbox);
		gtk_container_add(GTK_CONTAINER(vbox), upButton);
		gtk_container_add(GTK_CONTAINER(vbox), hbox);
		gtk_container_add(GTK_CONTAINER(hbox), leftButton);
		gtk_container_add(GTK_CONTAINER(hbox), rightButton);
		gtk_container_add(GTK_CONTAINER(vbox), downButton);
		gtk_container_add(GTK_CONTAINER(vbox), zoomInButton);
		gtk_container_add(GTK_CONTAINER(vbox), zoomOutButton);

		//Show widgets
		gtk_widget_show(window);
		gtk_widget_show_all(vbox);
		gtk_widget_show_all(hbox);

		//signals
		g_signal_connect(upButton, "button_press_event", G_CALLBACK(CanvasController::upButton), NULL);
		g_signal_connect(downButton, "button_press_event", G_CALLBACK(CanvasController::downButton), NULL);
		g_signal_connect(leftButton, "button_press_event", G_CALLBACK(CanvasController::leftButton), NULL);
		g_signal_connect(rightButton, "button_press_event", G_CALLBACK(CanvasController::rightButton), NULL);

		g_signal_connect(zoomInButton, "button_press_event", G_CALLBACK(CanvasController::zoomIn), NULL);
		g_signal_connect(zoomOutButton, "button_press_event", G_CALLBACK(CanvasController::zoomOut), NULL);

		return window;
	}

};

#endif
