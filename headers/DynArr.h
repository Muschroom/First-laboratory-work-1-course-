#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void* (*map_func_t) (void* data);
typedef int (*comp_func) (void* data);


typedef void* (*get_elem)(struct DynArr*,int);
typedef int (*data_alloc_f)(struct DynArrData*, int);
typedef void (*push_data)(struct DynArr*, void*);
typedef void (*set_elem)(struct DynArr*, int, void*);
typedef struct DynArr* (*conjuct_arr)(struct DynArr*, struct DynArr*);
typedef struct DynArr* (*map_arr)(struct DynArr*, map_func_t);
typedef struct DynArr* (*where_arr)(struct DynArr* ,comp_func);
typedef void (*sort_arr)(struct DynArr*, int, int);

typedef struct DynArrData{
    int capacity;
    int size;
    int check;
    void *pdata;
} Data;

typedef struct DynArrFuncs{
    data_alloc_f data_alloc;
    push_data push;
    get_elem get;
    set_elem set;
    conjuct_arr conjuct;
    map_arr map;
    where_arr where;
    sort_arr sort; 
} Funcs;

typedef struct  DynArr
{
    Data data;
    Funcs *funcs;
} Arr;


Arr* init(Funcs* funcs, int size);

int check_type(void* data);

void push(Arr* arr, void* elem);
void push_int(Data* data, void* elem);
void push_double(Data * data, void* elem);

void* get(Arr* arr, int ind);
void* get_int(Data* data, int ind);
void* get_double(Data* data, int ind);

void set(Arr* arr, int ind, void* elem);
void set_int(Data* arr, int ind, void* elem);
void set_double(Data* arr, int ind, void* elem);

Arr* map(Arr* arr, map_func_t func);
Arr* map_int(Data* data, map_func_t func);
Arr* map_double(Data* data, map_func_t func);

Arr* conjuct(Arr* left, Arr* right);
Arr* conjuct_int(Arr* left, Arr* right);
Arr* conjuct_double(Arr* left, Arr* right);

Arr* where(Arr* arr, comp_func func);
Arr* where_int(Data* data, comp_func func);
Arr* where_double(Data* data, comp_func func);

void sort(Arr* arr);
void sort_int(Data* data, int l, int r);
void merge_int(Data* data, int l, int r, int mid);
void sort_double(Data* data, int l, int r);
void merge_double(Data* data, int l, int r, int mid);

Funcs* init_int_arr();
Funcs* init_double_arr();

int arr_data_alloc(Arr* arr, int size);
int arr_data_alloc_int(Data* data,int size);
int arr_data_alloc_double(Data* data, int size);

void print_last_error();
void free_arr();
