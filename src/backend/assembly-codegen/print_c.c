#include <stdio.h>


void print(int x, int type) {
    switch (type) {
        case 0:
            printf("%d", x);
            break;

        case 1:
            if (x)
                printf("true");
            else
                printf("false");
            break;

        default:
            break;
    }
}
