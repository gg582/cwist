#include <cwistaw/http.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_methods() {
    printf("Testing HTTP methods...\n");
    assert(strcmp(cwist_http_method_to_string(CWIST_HTTP_GET), "GET") == 0);
    assert(cwist_http_string_to_method("POST") == CWIST_HTTP_POST);
    printf("Passed methods.\n");
}

void test_request_lifecycle() {
    printf("Testing Request Lifecycle...\n");
    cwist_http_request *req = cwist_http_request_create();
    assert(req != NULL);
    assert(req->method == CWIST_HTTP_GET);
    assert(strcmp(req->version->data, "HTTP/1.1") == 0);

    cwist_http_header_add(&req->headers, "Content-Type", "application/json");
    cwist_http_header_add(&req->headers, "Host", "example.com");

    assert(strcmp(cwist_http_header_get(req->headers, "Host"), "example.com") == 0);
    assert(strcmp(cwist_http_header_get(req->headers, "Content-Type"), "application/json") == 0);
    assert(cwist_http_header_get(req->headers, "Invalid") == NULL);

    smartstring_assign(req->body, "{\"key\": \"value\"}");
    assert(strcmp(req->body->data, "{\"key\": \"value\"}") == 0);

    cwist_http_request_destroy(req);
    printf("Passed Request Lifecycle.\n");
}

void test_response_lifecycle() {
    printf("Testing Response Lifecycle...\n");
    cwist_http_response *res = cwist_http_response_create();
    assert(res != NULL);
    assert(res->status_code == CWIST_HTTP_OK);

    cwist_http_header_add(&res->headers, "Server", "Cwistaw/0.1");
    assert(strcmp(cwist_http_header_get(res->headers, "Server"), "Cwistaw/0.1") == 0);

    cwist_http_response_destroy(res);
    printf("Passed Response Lifecycle.\n");
}

int main() {
    test_methods();
    test_request_lifecycle();
    test_response_lifecycle();
    printf("All HTTP tests passed!\n");
    return 0;
}
