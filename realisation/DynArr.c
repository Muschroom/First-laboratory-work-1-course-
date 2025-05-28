#include "headers/DynArr.h"
#include "headers/ERRORS.h"

static Funcs* int_funcs = NULL;
static Funcs* double_funcs = NULL;

void free_arr(Arr* arr) {
   if (arr != NULL) {
      if (arr->data.pdata != NULL) {
            free(arr->data.pdata);
      }
      free(arr);
   }
}

Arr* init(Funcs *funcs, int capacity) {
    if (funcs == NULL) {
        set_error(NULL_POINTER);
        return NULL;
    }
    
    if (capacity <= 0) {
        set_error(INVALID_INPUT);
        return NULL;
    }
    
    Arr *arr = malloc(sizeof(Arr));
    CHECK_MEM(arr);
    
    arr->funcs = funcs;
    int res = arr->funcs->data_alloc(&(arr->data),capacity);
    if (res == 0) {
        free(arr);
        set_error(MEMORY_ALLOC);
        return NULL;
    }
    
    return arr;
}

Funcs* init_int_arr() {
   if (int_funcs == NULL) {
      int_funcs = malloc(sizeof(Funcs));
      if (int_funcs == NULL) {
          set_error(MEMORY_ALLOC);
          return NULL;
      }
      
      int_funcs->data_alloc = &arr_data_alloc_int;
      int_funcs->push = &push_int;
      int_funcs->get = &get_int;
      int_funcs->set = &set_int;
      int_funcs->conjuct = &conjuct_int;
      int_funcs->map = &map_int;
      int_funcs->where = &where_int;
      int_funcs->sort = &sort_int;
   }

   return int_funcs;
}

Funcs* init_double_arr() {
   if (double_funcs == NULL) {
      double_funcs = malloc(sizeof(Funcs));
      if (double_funcs == NULL) {
          set_error(MEMORY_ALLOC);
          return NULL;
      }
      
      double_funcs->data_alloc = &arr_data_alloc_double;
      double_funcs->push = &push_double;
      double_funcs->get = &get_double;
      double_funcs->set = &set_double;
      double_funcs->conjuct = &conjuct_double;
      double_funcs->map = &map_double;
      double_funcs->where = &where_double;
      double_funcs->sort = &sort_double;
   }

   return double_funcs;
}

void push(Arr* arr, void* elem) {
    CHECK_NULL_VOID(arr);
    CHECK_NULL_VOID(elem);
    arr->funcs->push(&(arr->data), elem);
}

void push_int(Data* data, void* elem) {
    CHECK_NULL_VOID(data);
    CHECK_NULL_VOID(elem);
    
    if (data->capacity < data->size + 1) {
        data->capacity = data->capacity * 2;
        int* newArr = malloc(sizeof(int) * data->capacity);
        if (newArr == NULL) {
            set_error(MEMORY_ALLOC);
            return;
        }
        
        memcpy(newArr, data->pdata, data->size * sizeof(int));
        free(data->pdata);
        data->pdata = newArr;
    }

    ((int*)data->pdata)[data->size++] = *(int*)elem;
}

void push_double(Data* data, void* elem) {
    CHECK_NULL_VOID(data);
    CHECK_NULL_VOID(elem);
    
    if (data->capacity < data->size + 1) {
        data->capacity = data->capacity * 2;
        double* newArr = malloc(sizeof(double) * data->capacity);
        if (newArr == NULL) {
            set_error(MEMORY_ALLOC);
            return;
        }
        
        memcpy(newArr, data->pdata, data->size * sizeof(double));
        free(data->pdata);
        data->pdata = newArr;
    }

    ((double*)data->pdata)[data->size++] = *(double*)elem;
}

void* get(Arr *arr, int ind) {
    CHECK_NULL(arr);
    CHECK_INDEX(arr, ind);
    return arr->funcs->get(&(arr->data), ind);
}

void* get_int(Data* data, int ind) {
    return &((int*)data->pdata)[ind];
}

void* get_double(Data* data, int ind) {
    return &((double*)data->pdata)[ind];
}

void set(Arr* arr, int ind, void* elem) {
    CHECK_NULL_VOID(arr);
    CHECK_NULL_VOID(elem);
    
    if (ind < 0 || ind >= arr->data.size) {
        set_error(OUT_OF_RANGE);
        return;
    }

    arr->funcs->set(&(arr->data), ind, elem);
}

void set_int(Data* data, int ind, void* elem) {
    ((int*)data->pdata)[ind] = *(int*)elem;
}

void set_double(Data* data, int ind, void* elem) {
    ((double*)data->pdata)[ind] = *(double*)elem;
}

int arr_data_alloc_int(Data* data, int size) {
    CHECK_NULL_VOID(data);
    
    if (size <= 0) {
        set_error(INVALID_INPUT);
        return 0;
    }
    
    data->capacity = size;
    data->size = 0;
    data->check = 1;
    data->pdata = malloc(sizeof(int) * data->capacity);
    
    if (data->pdata == NULL) {
        set_error(MEMORY_ALLOC);
        return 0;
    }
    
    return 1;
}

int arr_data_alloc_double(Data* data, int size) {
    CHECK_NULL_VOID(data);
    
    if (size <= 0) {
        set_error(INVALID_INPUT);
        return 0;
    }
    
    data->capacity = size;
    data->size = 0;
    data->check = 1;
    data->pdata = malloc(sizeof(double) * data->capacity);
    
    if (data->pdata == NULL) {
        set_error(MEMORY_ALLOC);
        return 0;
    }
    
    return 1;
}

Arr* conjuct(Arr* left, Arr* right) {
    CHECK_NULL(left);
    CHECK_NULL(right);
    
    if (left->funcs != right->funcs) {
        set_error(INVALID_INPUT);
        return NULL;
    }
    
    return left->funcs->conjuct(left, right);
}

Arr* conjuct_int(Arr* left, Arr* right) {
    Arr* newArr = init(init_int_arr(), left->data.size + right->data.size);
    CHECK_MEM(newArr);
    
    newArr->data.size = left->data.size + right->data.size;

    memcpy(newArr->data.pdata, left->data.pdata, left->data.size * sizeof(int));
    memcpy((int*)newArr->data.pdata + left->data.size, right->data.pdata, 
           right->data.size * sizeof(int));

    return newArr;
}

Arr* conjuct_double(Arr* left, Arr* right) {
    Arr* newArr = init(init_double_arr(), left->data.size + right->data.size);
    CHECK_MEM(newArr);
    
    newArr->data.size = left->data.size + right->data.size;

    memcpy(newArr->data.pdata, left->data.pdata, left->data.size * sizeof(double));
    memcpy((double*)newArr->data.pdata + left->data.size, right->data.pdata, 
           right->data.size * sizeof(double));

    return newArr;
}

Arr* map(Arr* arr, map_func_t func) {
    CHECK_NULL(arr);
    CHECK_NULL(func);
    return arr->funcs->map(&(arr->data), func);
}

Arr* map_int(Data* data, map_func_t func) {
    CHECK_NULL(data);
    CHECK_NULL(func);
    
    Arr* newArr = init(init_int_arr(), data->capacity);
    CHECK_MEM(newArr);
    
    newArr->data.size = data->size;

    for (int ind = 0; ind < data->size; ind++) {
        int* num = &(((int*)data->pdata)[ind]);
        ((int*)(newArr->data.pdata))[ind] = *(int*)func(num);
    }

    return newArr;
}

Arr* map_double(Data* data, map_func_t func) {
    CHECK_NULL(data);
    CHECK_NULL(func);
    
    Arr* newArr = init(init_double_arr(), data->capacity);
    CHECK_MEM(newArr);
    
    newArr->data.size = data->size; 

    for (int ind = 0; ind < data->size; ind++) {
        double* num = &(((double*)data->pdata)[ind]);
        double k = *(double*)func(num);
        ((double*)newArr->data.pdata)[ind] = k;
    }

    return newArr;
}

Arr* where(Arr* arr, comp_func comp) {
    CHECK_NULL(arr);
    CHECK_NULL(comp);
    return arr->funcs->where(&(arr->data), comp);
}

Arr* where_int(Data* data, comp_func comp) {
    CHECK_NULL(data);
    CHECK_NULL(comp);
    
    Arr* newArr = init(init_int_arr(), data->capacity);
    CHECK_MEM(newArr);

    for (int ind = 0; ind < data->size; ind++) {
        int* num = &(((int*)data->pdata)[ind]);
        if (comp(num)) {
            push(newArr, num);
        }
    }

    return newArr;
}

Arr* where_double(Data* data, comp_func comp) {
    CHECK_NULL(data);
    CHECK_NULL(comp);
    
    Arr* newArr = init(init_double_arr(), data->capacity);
    CHECK_MEM(newArr);

    for (int ind = 0; ind < data->size; ind++) {
        double* num = &(((double*)data->pdata)[ind]);
        if (comp(num)) {
            push(newArr, num);
        }
    }

    return newArr;
}

void sort(Arr* arr) {
    CHECK_NULL_VOID(arr);
    arr->funcs->sort(&(arr->data), 0, arr->data.size - 1);
}

void sort_int(Data* data, int l, int r) {
    CHECK_NULL_VOID(data);
    
    if (l < 0 || r >= data->size || l > r) {
        set_error(OUT_OF_RANGE);
        return;
    }
    
    if (l < r) {
        int mid = l + (r - l) / 2;
        sort_int(data, l, mid);
        sort_int(data, mid + 1, r);
        merge_int(data, l, r, mid);
    }
}

void merge_int(Data* data, int l, int r, int mid) {
    int l_size = mid - l + 1;
    int r_size = r - mid;
    int* l_arr = malloc(sizeof(int) * l_size);
    if (l_arr == NULL) {
        set_error(MEMORY_ALLOC);
        return;
    }
    
    int* r_arr = malloc(sizeof(int) * r_size);
    if (r_arr == NULL) {
        free(l_arr);
        set_error(MEMORY_ALLOC);
        return;
    }

    for (int i = 0; i < l_size; i++) {
        int* num = &((int*)data->pdata)[l + i];
        l_arr[i] = *num;
    }
    for (int i = 0; i < r_size; i++) {
        int* num = &((int*)data->pdata)[mid + i + 1];
        r_arr[i] = *num;
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < l_size || j < r_size) {
        if ((i < l_size && j < r_size && l_arr[i] <= r_arr[j]) || (r_size <= j)) {
            ((int*)data->pdata)[k] = l_arr[i];
            i++;
        } else {
            ((int*)data->pdata)[k] = r_arr[j];
            j++;
        }
        k++;
    }

    free(l_arr);
    free(r_arr);
}

void sort_double(Data* data, int l, int r) {
    CHECK_NULL_VOID(data);
    
    if (l < 0 || r >= data->size || l > r) {
        set_error(OUT_OF_RANGE);
        return;
    }
    
    if (l < r) {
        int mid = l + (r - l) / 2;
        sort_double(data, l, mid);
        sort_double(data, mid + 1, r);
        merge_double(data, l, r, mid);
    }
}

void merge_double(Data* data, int l, int r, int mid) {
    int l_size = mid - l + 1;
    int r_size = r - mid;
    double* l_arr = malloc(sizeof(double) * l_size);
    if (l_arr == NULL) {
        set_error(MEMORY_ALLOC);
        return;
    }
    
    double* r_arr = malloc(sizeof(double) * r_size);
    if (r_arr == NULL) {
        free(l_arr);
        set_error(MEMORY_ALLOC);
        return;
    }

    for (int i = 0; i < l_size; i++) {
        double* num = &((double*)data->pdata)[l + i];
        l_arr[i] = *num;
    }
    for (int i = 0; i < r_size; i++) {
        double* num = &((double*)data->pdata)[mid + i + 1];
        r_arr[i] = *num;
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < l_size || j < r_size) {
        if ((i < l_size && j < r_size && l_arr[i] <= r_arr[j]) || (r_size <= j)) {
            ((double*)data->pdata)[k] = l_arr[i];
            i++;
        } else {
            ((double*)data->pdata)[k] = r_arr[j];
            j++;
        }
        k++;
    }

    free(l_arr);
    free(r_arr);
}
