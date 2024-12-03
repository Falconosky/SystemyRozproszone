#include <gtk/gtk.h>
#include "connection_manager.h"
#include "../main.h"

// Funkcja obsługi sygnału kliknięcia przycisku "Start serwer"
extern "C" void start_server_clicked(GtkButton *button, gpointer user_data) {
    int position = 3;
    // Pobierz rodzica przycisku (kontener) i usuń przycisk
    GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(button));
    gtk_container_remove(GTK_CONTAINER(parent), GTK_WIDGET(button));

    // Utwórz nową etykietę z napisem "Serwer włączony"
    GtkWidget *label = gtk_label_new("Serwer włączonyyyyyyyyyyyyyyyyyyyyyyy");

    // Dodaj etykietę do tego samego kontenera
    gtk_box_pack_start(GTK_BOX(parent), label, TRUE, TRUE, 10);
    gtk_box_reorder_child(GTK_BOX(parent), label, position);

    // Wyświetl nową etykietę
    gtk_widget_show(label);

    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkEntry *port_entry = GTK_ENTRY(gtk_builder_get_object(builder, "port_enter"));
    gtk_editable_set_editable(GTK_EDITABLE(port_entry), FALSE);
}

// Funkcja otwierająca nowe okno
void open_connection_manager_window() {
    // Inicjalizacja GtkBuilder
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    // Ładowanie pliku connection_manager.glade
    if (gtk_builder_add_from_file(builder, "../connection_manager/connection_manager.glade", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    // Pobierz główne okno z connection_manager.glade
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(builder, "connection_window"));
    g_signal_connect(new_window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // Sprawdź, czy okno zostało poprawnie załadowane
    if (!new_window) {
        g_printerr("Could not load the window from connection_manager.glade\n");
        return;
    }

    // Pokaż nowe okno
    gtk_widget_show_all(new_window);
}
