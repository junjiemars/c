#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static ngx_int_t ngx_http_hello_handler(ngx_http_request_t *r);
static char *ngx_http_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t  ngx_http_hello_commands[] = {
    {
        ngx_string("hello"),
        NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
        ngx_http_hello,
        0,
        0,
        NULL
    },
    ngx_null_command
};


static ngx_http_module_t  ngx_http_hello_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

ngx_module_t  ngx_http_hello_module = {
    NGX_MODULE_V1,
    &ngx_http_hello_module_ctx,
    ngx_http_hello_commands,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};


static ngx_str_t  ngx_http_hello_text = ngx_string("Hello, world!\n");


static ngx_int_t
ngx_http_hello_handler(ngx_http_request_t *r)
{
    ngx_buf_t    *b;
    ngx_int_t     rc;
    ngx_chain_t   out;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http hello handler");

    /* ignore client request body if any */
    if (ngx_http_discard_request_body(r) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    /* send header */
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = ngx_http_hello_text.len;

    rc = ngx_http_send_header(r);

    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }

    /* send body */
    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        return NGX_ERROR;
    }

    b->pos = ngx_http_hello_text.data;
    b->last = ngx_http_hello_text.data + ngx_http_hello_text.len;
    b->memory = 1;
    b->last_buf = (r == r->main) ? 1 : 0;
    b->last_in_chain = 1;

    out.buf = b;
    out.next = NULL;
	
    return ngx_http_output_filter(r, &out);
}

static char *
ngx_http_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf;
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_handler;
    return NGX_CONF_OK;
}
		
