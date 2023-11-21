#include <stdio.h>
#include <stdbool.h>

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

void print_int(int x) {
    printf("%d\n", x);
}

void print_bool(int x) {
    printf("%s\n", x ? "true" : "false");
}

bool equals(int x, int y) {
    return x == y;
}


bool compare_fib_result(int num, int result) {
    int array[13] = {0,1,1,2,3,5,8,13,21,34,55,89,144};
    return array[num] == result;
}
