??=include <stdio.h>
??=define putsw(...) puts(??=__VA_ARGS__)
int main() ??<
    putsw(Hello, World!);
??>