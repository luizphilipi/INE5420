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
	mainWindow.adicionarWidget(painelEsquerda.render(), MARGIN_LEFT,
			MARGIN_TOP);
	mainWindow.adicionarWidget(viewportComponent.render(), MARGIN_LEFT + 190,
			MARGIN_TOP);

	//Starts application
	gtk_main();
	return 0;

//	GtkBuilder *builder;
//	GtkWidget *window;
//	GError *error = NULL;
//
//	/* Init GTK+ */
//	gtk_init(&argc, &argv);
//
//	/* Create new GtkBuilder object */
//	builder = gtk_builder_new();
//	/* Load UI from file. If error occurs, report it and quit application.
//	 * Replace "tut.glade" with your saved project. */
//	if (!gtk_builder_add_from_file(builder, "tut.glade", &error)) {
//		g_warning("%s", error->message);
//		g_free(error);
//		return (1);
//	}
//
//	/* Get main window pointer from UI */
//	window = GTK_WIDGET(gtk_builder_get_object(builder, "modalPonto"));
//
//	/* Connect signals */
//	gtk_builder_add_callback_symbol(builder, "cb_clicked",
//			G_CALLBACK(main::on_entry_icon_release));
//	gtk_builder_connect_signals(builder, NULL);
//
//	/* Destroy builder, since we don't need it anymore */
//	g_object_unref(G_OBJECT(builder));
//
//	/* Show window. All other widgets are automatically shown by GtkBuilder */
//	gtk_widget_show(window);
//
//	/* Start main loop */
//	gtk_main();
//
//	return (0);
}
