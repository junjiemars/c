#include <_leptonica_.h>
#include <posix/getopt.h>
#include <string.h>


#define MAX_PATH  256

static void usage(const char *program);
static void scale(const char *in, const char *out,
    double x_scale, double y_scale);


static struct option long_options[] = {
    {"help",   no_argument,         0, 'h'},
    {"in",     required_argument,   0, 'i'},
    {"out",    required_argument,   0, 'o'},
    {"x",      optional_argument,   0, 'x'},
    {"y",      optional_argument,   0, 'y'},
    {0,        no_argument,         0, '-'},
    {0,        0,                   0,  0 },
};


static char    opt_has_in[MAX_PATH]   =  {0};
static char    opt_has_out[MAX_PATH]  =  {0};
static double  opt_has_scale_x        =  0.75;
static double  opt_has_scale_y        =  0.75;
static int     opt_has_std_inout      =  0;


void
usage(const char *program)
{
    printf("Usage: %s [OPTION]... [FILE]...\n", program);
    printf("\n");
    printf("Scale input image and out.\n");
    printf("  -h, --help             print this message\n");
    printf("  -i, --in               input image path\n");
    printf("  -o, --out              output image path\n");
    printf("  -x, --x-scale          scale x, default is %lf\n", opt_has_scale_x);
    printf("  -y, --y-scale          scale y, default is %lf\n", opt_has_scale_x);
    printf("  --, --std              input from stdin and output to stdout\n");
}

void
scale(const char *in, const char *out, double x_scale, double y_scale)
{
    PIX   *pixs, *pixd;

    pixs = pixRead(in);
    pixd = pixScale(pixs, x_scale, y_scale);
    pixWrite(out, pixd, IFF_DEFAULT);
    pixDestroy(&pixs);
    pixDestroy(&pixd);
}

int
main(int argc, char **argv)
{
    int ch;

    while (-1 != (ch = getopt_long(argc, argv, "hi:o:x:y:-", long_options, 0))) {
        switch (ch) {
        case 'h':
            usage(argv[0]);
            return 0;
        case 'i':
            memcpy(opt_has_in, optarg, MAX_PATH - 1);
            break;
        case 'o':
            memcpy(opt_has_out, optarg, MAX_PATH - 1);
            break;
        case 'x':
            if (1 != sscanf(optarg, "%lf", &opt_has_scale_x)) {
                printf("invalid argument '%s' of option '-p'\n", optarg);
                return -1;
            }
            break;
        case 'y':
            if (1 != sscanf(optarg, "%lf", &opt_has_scale_y)) {
                printf("invalid argument '%s' of option '-p'\n", optarg);
                return -1;
            }
            break;
        case '-':
            opt_has_std_inout++;
            break;
        default:
            usage(argv[0]);
            return -1;
        }
    }

    scale(opt_has_in, opt_has_out, opt_has_scale_x, opt_has_scale_y);

    return 0;
}
