#include <stdio.h>
#include <cwistaw/smartstring.h>

int main() {
    printf("=== SmartString Getting Started ===\n");

    // 1. Create a smartstring instance
    smartstring *s = smartstring_create();
    if (!s) {
        fprintf(stderr, "Failed to create smartstring\n");
        return 1;
    }

    // 2. Assign some data (with leading/trailing spaces)
    printf("\n[Assign]\n");
    const char *initial_text = "   Hello, SmartString!   ";
    printf("Original text: '%s'\n", initial_text);
    s->assign(s, (char *)initial_text);

    // 3. Trim the string
    printf("\n[Trim]\n");
    s->trim(s);
    printf("Trimmed text:  '%s'\n", s->data);

    // 4. Seek (Extract substring)
    printf("\n[Seek]\n");
    char buffer[64];
    // Let's skip "Hello, " (7 chars) to get "SmartString!"
    if (s->seek(s, buffer, 7).errtype == CWIST_ERR_INT8) { 
        printf("Seek(7):       '%s'\n", buffer);
    } else {
        printf("Seek failed!\n");
    }

    // 5. Change size (safe resize)
    printf("\n[Change Size]\n");
    printf("Current size: %zu\n", s->size);
    
    // Resize to a smaller size (truncate)
    // Warning: Data loss expected if new size < current length
    cwist_error_t err = s->change_size(s, 5, true); // true = allow blow data
    if (err.errtype == CWIST_ERR_INT8) {
        printf("Resized to 5:  '%s'\n", s->data);
    } else {
        printf("Resize failed or warned!\n");
    }

    // 6. Clean up
    smartstring_destroy(s);
    printf("\n=== Done ===\n");

    return 0;
}
