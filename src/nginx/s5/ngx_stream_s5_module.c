#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>

typedef struct {
    size_t                      preread_buffer_size;
    ngx_msec_t                  preread_timeout;
    ngx_stream_complex_value_t  text;
} ngx_stream_s5_srv_conf_t;


typedef struct {
    u_char  ver;
    u_char  n_methods;
    u_char  methods;
} ngx_stream_s5_method_req_t;


typedef struct {
    size_t        left;
    size_t        size;
    size_t        ext;
    u_char       *pos;
    u_char       *dst;
    u_char        buf[4];
    u_char        version[2];
    ngx_str_t     host;
    ngx_str_t     alpn;
    ngx_log_t    *log;
    ngx_pool_t   *pool;
    ngx_uint_t    state;
    ngx_chain_t  *out;
} ngx_stream_s5_ctx_t;


static void ngx_stream_s5_handler(ngx_stream_session_t *s);
/* static void ngx_stream_s5_write_handler(ngx_event_t *ev); */

static void *ngx_stream_s5_create_srv_conf(ngx_conf_t *cf);
static char *ngx_stream_s5(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);


static ngx_command_t  ngx_stream_s5_commands[] = {
    { ngx_string("s5"),
      NGX_STREAM_SRV_CONF|NGX_CONF_TAKE1,
      ngx_stream_s5,
      NGX_STREAM_SRV_CONF_OFFSET,
      0,
      NULL },

    ngx_null_command
};


static ngx_stream_module_t  ngx_stream_s5_module_ctx = {
    NULL,                                  /* preconfiguration */
    NULL,                                  /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    ngx_stream_s5_create_srv_conf,     /* create server configuration */
    NULL                                   /* merge server configuration */
};


ngx_module_t  ngx_stream_s5_module = {
    NGX_MODULE_V1,
    &ngx_stream_s5_module_ctx,         /* module context */
    ngx_stream_s5_commands,            /* module directives */
    NGX_STREAM_MODULE,                     /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static void
ngx_stream_s5_handler(ngx_stream_session_t *s)
{
    /* u_char                    *last; */
    /* u_char                    *p; */
    /* size_t                     size; */
    /* ssize_t                    n; */
    /* ngx_int_t                  rc; */
    ngx_connection_t          *c;
    /* ngx_stream_s5_ctx_t       *ctx; */
    /* ngx_stream_s5_srv_conf_t  *sscf; */

    c = s->connection;

    ngx_log_debug0(NGX_LOG_DEBUG_STREAM, c->log, 0, "s5 preread handler");

    (void) c;
}


/* static void */
/* ngx_stream_s5_write_handler(ngx_event_t *ev) */
/* { */
/*     ngx_connection_t      *c; */
/*     ngx_stream_s5_ctx_t   *ctx; */
/*     ngx_stream_session_t  *s; */

/*     c = ev->data; */
/*     s = c->data; */

/*     if (ev->timedout) { */
/*         ngx_connection_error(c, NGX_ETIMEDOUT, "connection timed out"); */
/*         ngx_stream_finalize_session(s, NGX_STREAM_OK); */
/*         return; */
/*     } */

/*     ctx = ngx_stream_get_module_ctx(s, ngx_stream_s5_module); */

/*     if (ngx_stream_top_filter(s, ctx->out, 1) == NGX_ERROR) { */
/*         ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR); */
/*         return; */
/*     } */

/*     ctx->out = NULL; */

/*     if (!c->buffered) { */
/*         ngx_log_debug0(NGX_LOG_DEBUG_STREAM, c->log, 0, */
/*                        "stream return done sending"); */
/*         ngx_stream_finalize_session(s, NGX_STREAM_OK); */
/*         return; */
/*     } */

/*     if (ngx_handle_write_event(ev, 0) != NGX_OK) { */
/*         ngx_stream_finalize_session(s, NGX_STREAM_INTERNAL_SERVER_ERROR); */
/*         return; */
/*     } */

/*     ngx_add_timer(ev, 5000); */
/* } */


static void *
ngx_stream_s5_create_srv_conf(ngx_conf_t *cf)
{
    ngx_stream_s5_srv_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_stream_s5_srv_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    return conf;
}


static char *
ngx_stream_s5(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                           *value;
    ngx_stream_s5_srv_conf_t            *rscf  =  conf;
    ngx_stream_core_srv_conf_t          *cscf;
    ngx_stream_compile_complex_value_t   ccv;

    if (rscf->text.value.data) {
        return "is duplicate";
    }

    value = cf->args->elts;

    ngx_memzero(&ccv, sizeof(ngx_stream_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &rscf->text;

    if (ngx_stream_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    cscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_core_module);

    cscf->handler = ngx_stream_s5_handler;

    return NGX_CONF_OK;
}


/* eof */
