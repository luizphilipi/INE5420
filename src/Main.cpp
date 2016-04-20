#include <gtk/gtk.h>

#include "TelaPrincipal.hpp"
#include "Matriz.h"
#include <ctime>
#include <vector>

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	new TelaPrincipal();
	return 0;
}
