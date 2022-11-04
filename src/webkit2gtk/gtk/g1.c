#include "_webkit2gtk_.h"


static void on_destroy_window(GtkWidget*, gpointer);
static void on_click_button(GtkWidget*, gpointer);


int main(int argc, char **argv)
{
  GtkWidget *window;
  GtkWidget *button;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(on_destroy_window), NULL);

  gtk_window_set_title (GTK_WINDOW (window), "B");
  gtk_container_set_border_width(GTK_CONTAINER(window), 20);

  button = gtk_button_new_with_label("X");
  g_signal_connect(button, "clicked", G_CALLBACK(on_click_button), "button");
  gtk_container_add(GTK_CONTAINER(window), button);

  gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}


static void on_destroy_window(__attribute__((unused)) GtkWidget *widget,
                              __attribute__((unused)) gpointer data)
{
  gtk_main_quit();
}

static void on_click_button(__attribute__((unused)) GtkWidget *widget,
                            __attribute__((unused)) gpointer data)
{
  g_print("click\n");
}
