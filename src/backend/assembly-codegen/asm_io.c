#include <stdio.h>

void print(int x, int type) {
    switch (type) {
        case 0:
            printf("%d\n", x);
            break;

        case 1:
            if (x)
                printf("true\n");
            else
                printf("false\n");
            break;

        default:
            printf("..");
            break;
    }
}

void print_bool(int x) {
    printf("%s\n", x ? "true" : "false");
}
