#include <cwistaw/smartstring.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_trim() {
    printf("Testing trim...\n");
    smartstring *s = smartstring_create();
    assert(s != NULL);

    smartstring_assign(s, "   hello world   ");
    assert(strcmp(s->data, "   hello world   ") == 0);

    smartstring_trim(s);
    printf("Trimmed: '%s'\n", s->data);
    assert(strcmp(s->data, "hello world") == 0);

    smartstring_destroy(s);
    printf("Passed trim.\n");
}

void test_resize() {
    printf("Testing resize...\n");
    smartstring *s = smartstring_create();
    smartstring_assign(s, "12345");
    assert(s->size == 5); 

    // Grow
    cwist_error_t err = smartstring_change_size(s, 10, false);
    assert(err.errtype == CWIST_ERR_INT8); // Success
    assert(s->size == 10);
    
    // Shrink safely
    err = smartstring_change_size(s, 5, false); // "12345" fits in 5
    assert(err.errtype == CWIST_ERR_INT8);

    // Shrink with data loss warning
    err = smartstring_change_size(s, 2, false); // "12345" -> 2 bytes?
    assert(err.errtype == CWIST_ERR_JSON); // Should fail

    // Shrink with blow_data
    err = smartstring_change_size(s, 2, true);
    assert(err.errtype == CWIST_ERR_INT8);
    
    assert(strcmp(s->data, "12") == 0);

    smartstring_destroy(s);
    printf("Passed resize.\n");
}

void test_seek() {
    printf("Testing seek...\n");
    smartstring *s = smartstring_create();
    smartstring_assign(s, "abcdef");
    
    char buffer[10];
    smartstring_seek(s, buffer, 2);
    assert(strcmp(buffer, "cdef") == 0);
    
    smartstring_destroy(s);
    printf("Passed seek.\n");
}

int main() {
    test_trim();
    test_resize();
    test_seek();
    printf("All tests passed!\n");
    return 0;
}
