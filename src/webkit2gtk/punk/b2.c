#include "_webkit2gtk_.h"


#define B_NAME  "B"
#define B_VER   "0.1.0"


typedef struct b_opt_s
{
  gboolean  ver;
  gboolean  ver_config;

} b_opt_t;


typedef struct b_frame_s
{
  GtkWindow      *window;
  WebKitWebView  *webview;

} b_frame_t;


typedef struct b_s
{
  b_opt_t     opt;
  b_frame_t  *frames;

} b_t;



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


  gtk_main();

  exit(EXIT_SUCCESS);
}
