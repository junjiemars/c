#include "_webkit2gtk_.h"


#define B_NAME  "B"
#define B_VER   "0.1.0"


struct b_opt_s
{
  gboolean  ver;
  gboolean  ver_config;

};


struct b_frame_s
{
  struct b_frame_s  *next;
  GtkWindow         *window;
  WebKitWebView     *webview;

};


struct b_s
{
  struct b_opt_s     opt;
  struct b_frame_s  *frames;

};

typedef struct b_s        b_t;
typedef struct b_opt_s    b_opt_t;
typedef struct b_frame_s  b_frame_t;


static b_frame_t *new_frame(WebKitWebView *);
static WebKitWebView *new_webview(b_frame_t *, WebKitWebView *);


static b_t  B = {0};


static GOptionEntry opts[] =
  {
    {
      "version", 'v', 0, G_OPTION_ARG_NONE, &B.opt.ver,
      "Show version and exit", NULL
    },

    {
      "Version", 'V', 0, G_OPTION_ARG_NONE, &B.opt.ver_config,
      "show version and configure options then exit", NULL
    },

    {NULL}
  };


int main(int argc, char **argv)
{
  GError  *err  =  NULL;

  B.opt.ver = FALSE;
  B.opt.ver_config = FALSE;

  /* initialize gtk+ */
  if (!gtk_init_with_args(&argc, &argv, "X", opts, NULL, &err))
    {
      fprintf(stderr, "%s\n", err->message);
      g_error_free(err);

      exit(EXIT_FAILURE);
    }

  if (B.opt.ver)
    {
      printf("%s version: %s/%s\n", B_NAME, B_NAME, B_VER);
      exit(EXIT_SUCCESS);
    }

  if (B.opt.ver_config)
    {
      printf("%-16s: %s/%s\n", B_NAME, B_NAME, B_VER);
      printf("%-16s: compile/%d.%d.%d, run/%d.%d.%d\n", "webkit",
             WEBKIT_MAJOR_VERSION,
             WEBKIT_MINOR_VERSION,
             WEBKIT_MICRO_VERSION,
             webkit_get_major_version(),
             webkit_get_minor_version(),
             webkit_get_micro_version());
      printf("%-16s: compile/%d.%d.%d, run/%d.%d.%d\n", "gtk",
             GTK_MAJOR_VERSION,
             GTK_MINOR_VERSION,
             GTK_MICRO_VERSION,
             gtk_major_version,
             gtk_minor_version,
             gtk_micro_version);

      exit(EXIT_SUCCESS);
    }

  new_frame(NULL);


  gtk_main();

  exit(EXIT_SUCCESS);
}


b_frame_t *
new_frame(WebKitWebView *webview)
{
  b_frame_t  *frame;

  frame = g_slice_new0(b_frame_t);

  frame->webview   = new_webview(frame, webview);
  /* c->finder    = webkit_web_view_get_find_controller(c->webview); */
  /* g_signal_connect(c->finder, "counted-matches", G_CALLBACK(on_counted_matches), c); */

  /* c->page_id   = webkit_web_view_get_page_id(c->webview); */
  /* c->inspector = webkit_web_view_get_inspector(c->webview); */

  return frame;
}

WebKitWebView *
new_webview(b_frame_t *frame, WebKitWebView *view)
{
  WebKitWebView *new;

  g_assert(frame);
  g_assert(view);
  new = NULL;

  return new;
}
