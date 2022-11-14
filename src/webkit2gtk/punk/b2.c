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
  struct b_frame_s    *next;
  GtkWindow           *window;
  WebKitWebView       *webview;
  guint64              page_id;
  WebKitWebInspector  *inspector;
};


struct b_s
{
  struct b_opt_s     opt;
  struct b_frame_s  *frame;
  WebKitWebContext  *webctx;
};

typedef struct b_s        b_t;
typedef struct b_opt_s    b_opt_t;
typedef struct b_frame_s  b_frame_t;


static void            setup(void);
static void            show_frame(b_frame_t *, WebKitWebView *);
static b_frame_t      *new_frame(WebKitWebView *);
static GtkWindow      *new_window(b_frame_t *);
static WebKitWebView  *new_webview(b_frame_t *, WebKitWebView *);



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

  setup();

  b_frame_t *frame = new_frame(NULL);
  show_frame(frame, NULL);


  gtk_main();

  exit(EXIT_SUCCESS);
}

void
setup(void)
{
  /* !TODO: */
  char *udd = g_build_filename(g_get_user_data_dir(), B_NAME, NULL);
  if (!g_file_test(udd, G_FILE_TEST_IS_DIR))
    {
      g_mkdir_with_parents(udd, 0755);
    }

  char *ucd = g_build_filename(g_get_user_cache_dir(), B_NAME, NULL);
  if (!g_file_test(ucd, G_FILE_TEST_IS_DIR))
    {
      g_mkdir_with_parents(ucd, 0755);
    }

  WebKitWebsiteDataManager *wdm = NULL;
  wdm = webkit_website_data_manager_new
    ("base-data-directory", udd,
     "base-cache-directory", ucd,
     NULL);

  B.webctx = webkit_web_context_new_with_website_data_manager(wdm);
  webkit_web_context_set_process_model
    (B.webctx, WEBKIT_PROCESS_MODEL_MULTIPLE_SECONDARY_PROCESSES);
  webkit_web_context_set_cache_model
    (B.webctx, WEBKIT_CACHE_MODEL_WEB_BROWSER);

}

void
show_frame(b_frame_t *frame, WebKitWebView *view)
{
  frame->window = GTK_WINDOW(new_window(frame));

  g_assert(view);
}

b_frame_t *
new_frame(WebKitWebView *webview)
{
  b_frame_t  *frame;

  frame = g_slice_new0(b_frame_t);
  frame->next = B.frame;
  B.frame = frame;

  frame->webview   = new_webview(frame, webview);
  frame->page_id   = webkit_web_view_get_page_id(frame->webview);
  frame->inspector = webkit_web_view_get_inspector(frame->webview);

  return frame;
}

GtkWindow *
new_window(b_frame_t *frame)
{
  GtkWidget  *new;

  new = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_role(GTK_WINDOW(new), "");
  gtk_window_set_default_size(GTK_WINDOW(new), 800, 600);

  g_assert(frame);

  return GTK_WINDOW(new);
}

WebKitWebView *
new_webview(b_frame_t *frame, WebKitWebView *view)
{
  WebKitWebView             *new;
  WebKitUserContentManager  *ucm;
  WebKitWebContext          *ctx;

  ucm = webkit_user_content_manager_new();
  if (view)
    {
      new = WEBKIT_WEB_VIEW
        (g_object_new(WEBKIT_TYPE_WEB_VIEW,
                      "user-content-manager", ucm,
                      "related-view", view,
                      NULL));
    }
  else
    {
      new = WEBKIT_WEB_VIEW
        (g_object_new(WEBKIT_TYPE_WEB_VIEW,
                      "user-content-manager", ucm,
                      "web-context", B.webctx,
                      NULL));
    }

  ctx = webkit_web_view_get_context(new);

  g_assert(frame);
  g_assert(ctx);

  return new;
}
