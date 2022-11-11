#include "_webkit2gtk_.h"


#define B_NAME  "B"
#define B_VER   "0.1.0"


static void  on_activate(GApplication *, WebKitSettings *);




int main(int argc, char **argv)
{
  g_print("%s@%d, WebKitGtk: %u.%u.%u\n", __FUNCTION__, __LINE__,
          webkit_get_major_version(),
          webkit_get_minor_version(),
          webkit_get_micro_version());

  gtk_init(&argc, &argv);

  WebKitSettings *settings = webkit_settings_new();

  webkit_settings_set_enable_developer_extras(settings, TRUE);
  webkit_settings_set_enable_webgl(settings, TRUE);
  webkit_settings_set_enable_javascript(settings, TRUE);
  webkit_settings_set_enable_smooth_scrolling(settings, TRUE);

  GtkApplication *app
    = gtk_application_new("rocks.trunk." B_NAME,
                          G_APPLICATION_NON_UNIQUE);

  g_signal_connect(app, "activate", G_CALLBACK(on_activate), settings);
  g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return 0;
}


void
on_activate(GApplication *app, WebKitSettings *settings)
{
  g_print("%s@%d\n", __FUNCTION__, __LINE__);

  WebKitWebContext *ctx
    = g_object_new(WEBKIT_TYPE_WEB_CONTEXT,
                   "process-swap-on-cross-site-navigation-enabled", TRUE,
                   NULL);

  /* WebKitWebsitePolicies *policies */
  /*   = webkit_website_policies_new_with_policies */
  /*   ("autoplay", WEBKIT_AUTOPLAY_ALLOW_WITHOUT_SOUND, NULL); */


  WebKitWebView *webview
    = WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW,
                                   "web-context", ctx,
                                   "settings", settings,
                                   /* "website-policies", policies, */
                                   NULL));

  GtkWindow *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));

  gtk_application_add_window(GTK_APPLICATION(app), window);
  gtk_window_set_default_size(window, 800, 600);
  /* gtk_window_fullscreen(GTK_WINDOW(window)); */

  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));

  webkit_web_view_load_uri(webview, "https://www.bing.com");
  gtk_widget_show(GTK_WIDGET(webview));

  g_clear_object(&settings);
  g_object_unref(ctx);

  gtk_widget_grab_focus(GTK_WIDGET(webview));
  gtk_widget_show(GTK_WIDGET(window));
}
