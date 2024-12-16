#ifndef	DOG_H
#define	DOG_H

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

typedef struct {
    char name[MAX_LEN];
    int age;
    char breed[MAX_LEN];
} Dog;

extern Dog* database;
extern size_t database_size;

void menu(const char* filename);
void search_dog();
void edit_dog();
void delete_dog();
void add_dog();
void display_database();
void save_database(const char* filename);
void load_database(const char* filename);

#endif