#include <_webkit2gtk_.h>
#include <stdio.h>


static void on_destroy_window(GtkWidget*, GtkWidget*);
static gboolean on_close_webview(WebKitWebView*, GtkWidget*);

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

  WebKitWebView *webview = WEBKIT_WEB_VIEW(webkit_web_view_new());

  gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webview));

  g_signal_connect(main_window, "destroy", G_CALLBACK(on_destroy_window),
                   NULL);
  g_signal_connect(webview, "close", G_CALLBACK(on_close_webview),
                   main_window);

  webkit_web_view_load_uri(webview, "https://www.webkitgtk.org");

  gtk_widget_grab_focus(GTK_WIDGET(webview));

  gtk_widget_show_all(main_window);

  gtk_main();

  return 0;
}


static void on_destroy_window(__attribute__((unused)) GtkWidget *widget,
                              __attribute__((unused)) GtkWidget *window)
{
  gtk_main_quit();
}

static gboolean on_close_webview(__attribute__((unused)) WebKitWebView *wv,
                                 GtkWidget *window)
{
  gtk_widget_destroy(window);
  return TRUE;
}
