#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <gtk/gtk.h>

class TelaPrincipal {
public:
	TelaPrincipal();
	virtual GtkWidget * render();
	void adicionarWidget(GtkWidget * widget, int x, int y);

private:
	GtkWidget * fixedContainer;
};

#endif
