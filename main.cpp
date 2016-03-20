#include <gtk/gtk.h>
#include "consts.hpp"
#include "view/include/painelDireita.hpp"
#include "view/include/painelEsquerda.hpp"
#include "view/include/telaPrincipal.hpp"

int main(int argc, char *argv[]) {
	TelaPrincipal mainWindow;
	PainelEsquerda painelEsquerda;
	PainelDireita viewportComponent;

	gtk_init(&argc, &argv);

	//Init Widgets
	mainWindow.render();

	//Adds widget to container
	mainWindow.adicionarWidget(painelEsquerda.render(), MARGIN_LEFT, MARGIN_TOP);
	mainWindow.adicionarWidget(viewportComponent.render(), MARGIN_LEFT + 190, MARGIN_TOP);

	//Starts application
	gtk_main();
	return 0;
}
