#include <gtk/gtk.h>

#include "TelaPrincipal.hpp"

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	new TelaPrincipal();
	return 0;
}
