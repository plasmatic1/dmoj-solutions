#include <stdio.h>

#define v(...) # __VA_ARGS__

int main() {
    puts(v(Hello, World!));
}