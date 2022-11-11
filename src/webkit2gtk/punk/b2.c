#include "_webkit2gtk_.h"


#define B_NAME  "B"
#define B_VER   "0.1.0"


static gboolean  opt_ver         =  FALSE;
static gboolean  opt_ver_config  =  FALSE;

static GOptionEntry opts[] =
  {
    {
      "version", 'v', 0, G_OPTION_ARG_NONE, &opt_ver,
      "Show version and exit", NULL
    },

    {
      "Version", 'V', 0, G_OPTION_ARG_NONE, &opt_ver_config,
      "show version and configure options then exit", NULL
    },

    {NULL}
  };


int main(int argc, char **argv)
{
  GError  *err  =  NULL;

  /* initialize gtk+ */
  if (!gtk_init_with_args(&argc, &argv, "X", opts, NULL, &err))
    {
      fprintf(stderr, "%s\n", err->message);
      g_error_free(err);

      exit(EXIT_FAILURE);
    }

  if (opt_ver)
    {
      printf("%s version: %s/%s\n", B_NAME, B_NAME, B_VER);
      exit(EXIT_SUCCESS);
    }

  if (opt_ver_config)
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
    }

  exit(EXIT_SUCCESS);
}
