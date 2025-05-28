#include "DynArr.h"
#include "ERRORS.h"
#include <stdlib.h>
#include <stdio.h>

void* funci(void* num) {
    if (num == NULL) {
        set_error(NULL_POINTER);
        return NULL;
    }
    static int result;
    result = *(int*)num + 1;
    return &result;
}

void* funcd(void* num) {
    if (num == NULL) {
        set_error(NULL_POINTER);
        return NULL;
    }
    static double result;
    result = *(double*)num + 1;
    return &result;
}

int d_wh(void* num) {
    if (num == NULL) {
        set_error(NULL_POINTER);
        return 0;
    }
    return *(double*)num > 4;
}

int i_wh(void* num) {
    if (num == NULL) {
        set_error(NULL_POINTER);
        return 0;
    }
    return *(int*)num > 4;
}

int main() {
    FILE *file = fopen("input.txt", "r");
   

    char data[256];
    int test_number = 1;
    
    while (fscanf(file, "%s", data) == 1) {
        printf("%s %i\n", "TEST:", test_number++);
        int ok = 1;
        clear_error();

        if (strcmp(data, "II") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_int_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                int num;
                if (fscanf(file, "%d", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < size && ok; i++) {
                    int expected;
                    if (fscanf(file, "%d", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    int *actual = (int*)get(arr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }
            free(arr->data.pdata);
            free(arr);
        }
        else if (strcmp(data, "ID") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_double_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                double num;
                if (fscanf(file, "%lf", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < size && ok; i++) {
                    double expected;
                    if (fscanf(file, "%lf", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    double *actual = (double*)get(arr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }
            free(arr->data.pdata);
            free(arr);
        }
        else if (strcmp(data, "SETI") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_int_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                push(arr, &i);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            for (int i = 0; i < size && ok; i++) {
                int ind, num;
                if (fscanf(file, "%d%d", &ind, &num) != 2 || ind < 0 || ind >= size) {
                    ok = 0;
                    fprintf(stderr, "Invalid index or value\n");
                    continue;
                }
                set(arr, ind, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < size && ok; i++) {
                    int expected;
                    if (fscanf(file, "%d", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    int *actual = (int*)get(arr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }
            free(arr->data.pdata);
            free(arr);
        }
        else if (strcmp(data, "SETD") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_double_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                double val = i;
                push(arr, &val);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            for (int i = 0; i < size && ok; i++) {
                int ind;
                double num;
                if (fscanf(file, "%d%lf", &ind, &num) != 2 || ind < 0 || ind >= size) {
                    ok = 0;
                    fprintf(stderr, "Invalid index or value\n");
                    continue;
                }
                set(arr, ind, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < size && ok; i++) {
                    double expected;
                    if (fscanf(file, "%lf", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    double *actual = (double*)get(arr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }
            free(arr->data.pdata);
            free(arr);
        }
        else if (strcmp(data, "SORTI") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_int_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                int num;
                if (fscanf(file, "%d", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                sort(arr);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < size && ok; i++) {
                    int expected;
                    if (fscanf(file, "%d", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    int *actual = (int*)get(arr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }
            free(arr->data.pdata);
            free(arr);
        }
        else if (strcmp(data, "SORTD") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_double_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                double num;
                if (fscanf(file, "%lf", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                sort(arr);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < size && ok; i++) {
                    double expected;
                    if (fscanf(file, "%lf", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    double *actual = (double*)get(arr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }
            free(arr->data.pdata);
            free(arr);
        }
        else if (strcmp(data, "CONCI") == 0) {
            int size_a, size_b;
            if (fscanf(file, "%d%d", &size_a, &size_b) != 2 || size_a <= 0 || size_b <= 0) {
                fprintf(stderr, "Invalid sizes input\n");
                continue;
            }

            Arr* a = init(init_int_arr(), size_a);
            Arr* b = init(init_int_arr(), size_b);
            if (a == NULL || b == NULL) {
                print_last_error();
                if (a) free(a->data.pdata), free(a);
                if (b) free(b->data.pdata), free(b);
                continue;
            }

            for (int i = 0; i < size_a && ok; i++) {
                int num;
                if (fscanf(file, "%d", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(a, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            for (int i = 0; i < size_b && ok; i++) {
                int num;
                if (fscanf(file, "%d", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(b, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            Arr* c = NULL;
            if (ok) {
                c = conjuct(a, b);
                if (c == NULL) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                int size_c = c->data.size;
                for (int i = 0; i < size_c && ok; i++) {
                    int expected;
                    if (fscanf(file, "%d", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    int *actual = (int*)get(c, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }

            free(a->data.pdata); free(a);
            free(b->data.pdata); free(b);
            if (c) { free(c->data.pdata); free(c); }
        }
        else if (strcmp(data, "CONCD") == 0) {
            int size_a, size_b;
            if (fscanf(file, "%d%d", &size_a, &size_b) != 2 || size_a <= 0 || size_b <= 0) {
                fprintf(stderr, "Invalid sizes input\n");
                continue;
            }

            Arr* a = init(init_double_arr(), size_a);
            Arr* b = init(init_double_arr(), size_b);
            if (a == NULL || b == NULL) {
                print_last_error();
                if (a) free(a->data.pdata), free(a);
                if (b) free(b->data.pdata), free(b);
                continue;
            }

            for (int i = 0; i < size_a && ok; i++) {
                double num;
                if (fscanf(file, "%lf", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(a, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            for (int i = 0; i < size_b && ok; i++) {
                double num;
                if (fscanf(file, "%lf", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(b, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            Arr* c = NULL;
            if (ok) {
                c = conjuct(a, b);
                if (c == NULL) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                int size_c = c->data.size;
                for (int i = 0; i < size_c && ok; i++) {
                    double expected;
                    if (fscanf(file, "%lf", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    double *actual = (double*)get(c, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }

            free(a->data.pdata); free(a);
            free(b->data.pdata); free(b);
            if (c) { free(c->data.pdata); free(c); }
        }
        else if (strcmp(data, "WHI") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_int_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                int num;
                if (fscanf(file, "%d", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            Arr* newArr = NULL;
            if (ok) {
                newArr = where(arr, i_wh);
                if (newArr == NULL) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < newArr->data.size && ok; i++) {
                    int expected;
                    if (fscanf(file, "%d", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    int *actual = (int*)get(newArr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }

            free(arr->data.pdata); free(arr);
            if (newArr) { free(newArr->data.pdata); free(newArr); }
        }
        else if (strcmp(data, "WHD") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_double_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                double num;
                if (fscanf(file, "%lf", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            Arr* newArr = NULL;
            if (ok) {
                newArr = where(arr, d_wh);
                if (newArr == NULL) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < newArr->data.size && ok; i++) {
                    double expected;
                    if (fscanf(file, "%lf", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    double *actual = (double*)get(newArr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }

            free(arr->data.pdata); free(arr);
            if (newArr) { free(newArr->data.pdata); free(newArr); }
        }
        else if (strcmp(data, "MAPI") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_int_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                int num;
                if (fscanf(file, "%d", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            Arr* newArr = NULL;
            if (ok) {
                newArr = map(arr, funci);
                if (newArr == NULL) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < newArr->data.size && ok; i++) {
                    int expected;
                    if (fscanf(file, "%d", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    int *actual = (int*)get(newArr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }

            free(arr->data.pdata); free(arr);
            if (newArr) { free(newArr->data.pdata); free(newArr); }
        }
        else if (strcmp(data, "MAPD") == 0) {
            int size;
            if (fscanf(file, "%d", &size) != 1 || size <= 0) {
                fprintf(stderr, "Invalid size input\n");
                continue;
            }

            Arr* arr = init(init_double_arr(), size);
            if (arr == NULL) {
                print_last_error();
                continue;
            }

            for (int i = 0; i < size && ok; i++) {
                double num;
                if (fscanf(file, "%lf", &num) != 1) {
                    ok = 0;
                    continue;
                }
                push(arr, &num);
                if (last_error.type != NONE) {
                    ok = 0;
                    print_last_error();
                }
            }

            Arr* newArr = NULL;
            if (ok) {
                newArr = map(arr, funcd);
                if (newArr == NULL) {
                    ok = 0;
                    print_last_error();
                }
            }

            if (ok) {
                for (int i = 0; i < newArr->data.size && ok; i++) {
                    double expected;
                    if (fscanf(file, "%lf", &expected) != 1) {
                        ok = 0;
                        continue;
                    }
                    double *actual = (double*)get(newArr, i);
                    if (actual == NULL || *actual != expected) {
                        ok = 0;
                        if (actual == NULL) print_last_error();
                    }
                }
            }

            free(arr->data.pdata); free(arr);
            if (newArr) { free(newArr->data.pdata); free(newArr); }
        }
        else {
            fprintf(stderr, "Unknown test type: %s\n", data);
            continue;
        }

        if (ok) {
            printf("%s\n", "SUCCESS");
        } else {
            printf("%s", "FAILED");
            if (last_error.type != NONE) {
                printf(" - ");
                print_last_error();
            } else {
                printf("\n");
            }
        }
    }

    fclose(file);
    return 0;
}