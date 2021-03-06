#include <kore/kore.h>
#include <kore/http.h>

int		page(struct http_request *);

int
page(struct http_request *req)
{
	char		*custom;

	/*
	 * We'll lookup if the X-Custom-Header is given in the request.
	 * If it is we'll set it as a response header as well.
	 *
	 * The value returned by http_request_header() must be freed.
	 *
	 * NOTE: All custom headers you set must be in lower case due to
	 * the SPDYv3 specification requiring this.
	 */
	if (http_request_header(req, "x-custom-header", &custom)) {
		http_response_header(req, "x-custom-header", custom);
		kore_mem_free(custom);
	}

	/* Return 200 with "ok\n" to the client. */
	http_response(req, 200, "ok\n", 3);

	return (KORE_RESULT_OK);
}
