#include <gtk/gtk.h>
#include "telaPrincipal.hpp"

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	new TelaPrincipal();
	return 0;
}
