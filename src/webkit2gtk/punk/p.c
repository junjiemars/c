#include "_webkit2gtk_.h"


#define B_NAME  "B"
#define B_VER   "0.1.0"


static void  on_activate(GApplication *, WebKitSettings *);
/* static WebKitWebView *new_view(WebKitSettings *); */
static void on_auto_started(WebKitWebContext *,
                            WebKitAutomationSession *,
                            GtkApplication *);
static GtkWidget *on_auto_new_view(WebKitAutomationSession *,
                                   GtkApplication *);



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
  webkit_settings_set_enable_media_stream(settings, TRUE);

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
  webkit_web_context_set_automation_allowed(ctx, TRUE);

  g_signal_connect(ctx, "automation-started",
                   G_CALLBACK(on_auto_started), app);

  GtkWindow *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));

  gtk_application_add_window(GTK_APPLICATION(app), window);
  gtk_window_set_default_size(window, 800, 600);
  /* gtk_window_fullscreen(GTK_WINDOW(window)); */


  WebKitWebView *webview
    = WEBKIT_WEB_VIEW(webkit_web_view_new_with_settings(settings));
    /* = new_view(settings); */

  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));

  gtk_widget_show(GTK_WIDGET(webview));
  webkit_web_view_load_uri(webview, "https://www.bing.com");

  g_clear_object(&settings);
  g_object_unref(ctx);

  gtk_widget_grab_focus(GTK_WIDGET(webview));
  gtk_widget_show(GTK_WIDGET(window));
}

/* WebKitWebView * */
/* new_view(WebKitSettings *settings) */
/* { */
/*   WebKitWebView *webview */
/*     = WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW, */
/*                                    "settings", settings, */
/*                                    NULL)); */

/*   /\* browser_window_append_view(window, webView); *\/ */

/*   return webview; */
/* } */


void on_auto_started(__attribute__((unused)) WebKitWebContext *ctx,
                     __attribute__((unused)) WebKitAutomationSession *session,
                     GtkApplication *app)
{
  g_print("%s@%d\n", __FUNCTION__, __LINE__);

  WebKitApplicationInfo *info = webkit_application_info_new();

  webkit_application_info_set_version(info,
                                      WEBKIT_MAJOR_VERSION,
                                      WEBKIT_MINOR_VERSION,
                                      WEBKIT_MICRO_VERSION);
  webkit_automation_session_set_application_info(session, info);
  webkit_application_info_unref(info);

  g_signal_connect(session, "create-web-view::window",
                   G_CALLBACK(on_auto_new_view),
                   app);
}

GtkWidget *
on_auto_new_view(__attribute__((unused)) WebKitAutomationSession *session,
                 GtkApplication *app)
{
  g_print("%s@%d\n", __FUNCTION__, __LINE__);

  __attribute__((unused)) GtkWindow *window
    = gtk_application_get_active_window(app);

  return NULL;
}
