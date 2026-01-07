#include <cwistaw/http.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Helpers --- */

const char *cwist_http_method_to_string(cwist_http_method_t method) {
    switch (method) {
        case CWIST_HTTP_GET: return "GET";
        case CWIST_HTTP_POST: return "POST";
        case CWIST_HTTP_PUT: return "PUT";
        case CWIST_HTTP_DELETE: return "DELETE";
        case CWIST_HTTP_PATCH: return "PATCH";
        case CWIST_HTTP_HEAD: return "HEAD";
        case CWIST_HTTP_OPTIONS: return "OPTIONS";
        default: return "UNKNOWN";
    }
}

cwist_http_method_t cwist_http_string_to_method(const char *method_str) {
    if (strcmp(method_str, "GET") == 0) return CWIST_HTTP_GET;
    if (strcmp(method_str, "POST") == 0) return CWIST_HTTP_POST;
    if (strcmp(method_str, "PUT") == 0) return CWIST_HTTP_PUT;
    if (strcmp(method_str, "DELETE") == 0) return CWIST_HTTP_DELETE;
    if (strcmp(method_str, "PATCH") == 0) return CWIST_HTTP_PATCH;
    if (strcmp(method_str, "HEAD") == 0) return CWIST_HTTP_HEAD;
    if (strcmp(method_str, "OPTIONS") == 0) return CWIST_HTTP_OPTIONS;
    return CWIST_HTTP_UNKNOWN;
}

/* --- Header Manipulation --- */

cwist_error_t cwist_http_header_add(cwist_http_header_node **head, const char *key, const char *value) {
    cwist_error_t err = make_error(CWIST_ERR_INT16);
    
    cwist_http_header_node *node = (cwist_http_header_node *)malloc(sizeof(cwist_http_header_node));
    if (!node) {
        err = make_error(CWIST_ERR_JSON);
        err.error.err_json = cJSON_CreateObject();
        cJSON_AddStringToObject(err.error.err_json, "http_error", "Failed to allocate header");
        return err;
    }

    node->key = smartstring_create();
    node->value = smartstring_create();
    node->next = NULL;

    smartstring_assign(node->key, (char *)key);
    smartstring_assign(node->value, (char *)value);

    node->next = *head;
    *head = node;

    err.error.err_i16 = 0; // Success
    return err;
}

char *cwist_http_header_get(cwist_http_header_node *head, const char *key) {
    cwist_http_header_node *curr = head;
    while (curr) {
        // Case-insensitive comparison for headers is standard, but keeping it strict for now for simplicity
        if (curr->key->data && strcmp(curr->key->data, key) == 0) {
            return curr->value->data;
        }
        curr = curr->next;
    }
    return NULL;
}

void cwist_http_header_free_all(cwist_http_header_node *head) {
    cwist_http_header_node *curr = head;
    while (curr) {
        cwist_http_header_node *next = curr->next;
        smartstring_destroy(curr->key);
        smartstring_destroy(curr->value);
        free(curr);
        curr = next;
    }
}

/* --- Request Lifecycle --- */

cwist_http_request *cwist_http_request_create(void) {
    cwist_http_request *req = (cwist_http_request *)malloc(sizeof(cwist_http_request));
    if (!req) return NULL;

    req->method = CWIST_HTTP_GET; // Default
    req->path = smartstring_create();
    req->query = smartstring_create();
    req->version = smartstring_create();
    req->headers = NULL;
    req->body = smartstring_create();

    // Defaults
    smartstring_assign(req->version, "HTTP/1.1");
    smartstring_assign(req->path, "/");

    return req;
}

void cwist_http_request_destroy(cwist_http_request *req) {
    if (req) {
        smartstring_destroy(req->path);
        smartstring_destroy(req->query);
        smartstring_destroy(req->version);
        smartstring_destroy(req->body);
        cwist_http_header_free_all(req->headers);
        free(req);
    }
}

/* --- Response Lifecycle --- */

cwist_http_response *cwist_http_response_create(void) {
    cwist_http_response *res = (cwist_http_response *)malloc(sizeof(cwist_http_response));
    if (!res) return NULL;

    res->version = smartstring_create();
    res->status_code = CWIST_HTTP_OK;
    res->status_text = smartstring_create();
    res->headers = NULL;
    res->body = smartstring_create();

    // Defaults
    smartstring_assign(res->version, "HTTP/1.1");
    smartstring_assign(res->status_text, "OK");

    return res;
}

void cwist_http_response_destroy(cwist_http_response *res) {
    if (res) {
        smartstring_destroy(res->version);
        smartstring_destroy(res->status_text);
        smartstring_destroy(res->body);
        cwist_http_header_free_all(res->headers);
        free(res);
    }
}
