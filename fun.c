#include "dog.h"

Dog* database = NULL;
size_t database_size = 0;

void load_database(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Не удалось открыть файл для чтения\nНачинаем с пустой базы данных\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    database_size = file_size / sizeof(Dog);
    database = malloc(database_size * sizeof(Dog));
    if (!database) {
        printf("Ошибка выделения памяти\n");
        fclose(file);
        exit(1);
    }

    fread(database, sizeof(Dog), database_size, file);
    fclose(file);
}

void save_database(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Не удалось открыть файл для записи\n");
        return;
    }

    fwrite(database, sizeof(Dog), database_size, file);
    fclose(file);
}

void display_database() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    printf("\nБаза данных собак:\n");
    for (size_t i = 0; i < database_size; i++) {
        printf("%zu. Имя: %s, Возраст: %d, Порода: %s\n", i + 1, database[i].name, database[i].age, database[i].breed);
    }
}

void add_dog() {
    Dog new_dog;

    printf("Введите имя собаки: ");
    scanf("%s", new_dog.name);
    printf("Введите возраст собаки: ");
    scanf("%d", &new_dog.age);
    printf("Введите породу собаки: ");
    scanf("%s", new_dog.breed);

    Dog* new_database = realloc(database, (database_size + 1) * sizeof(Dog));
    if (!new_database) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    database = new_database;
    database[database_size++] = new_dog;

    printf("Собака успешно добавлена\n");
}

void delete_dog() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    size_t index;
    printf("Введите номер собаки для удаления: ");
    scanf("%zu", &index);

    if (index < 1 || index > database_size) {
        printf("Неверный номер\n");
        return;
    }

    for (size_t i = index - 1; i < database_size - 1; i++) {
        database[i] = database[i + 1];
    }

    Dog* new_database = realloc(database, (database_size - 1) * sizeof(Dog));
    if (!new_database && database_size - 1 > 0) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    database = new_database;
    database_size--;

    printf("Собака успешно удалена\n");
}

void edit_dog() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    size_t index;
    printf("Введите номер собаки для редактирования: ");
    scanf("%zu", &index);

    if (index < 1 || index > database_size) {
        printf("Неверный номер\n");
        return;
    }

    Dog* dog = &database[index - 1];

    printf("Редактирование собаки: %s\n", dog->name);
    printf("Введите новое имя: ");
    scanf("%s", dog->name);
    printf("Введите новый возраст: ");
	int new_age;
    scanf("%d", &new_age);
	dog->age = new_age;
    printf("Введите новую породу: ");
    scanf("%s", dog->breed);

    printf("Собака успешно обновлена\n");
}

void search_dog() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    char query[MAX_LEN];
    printf("Введите имя или породу для поиска: ");
    scanf("%s", query);

    printf("\nРезультаты поиска:\n");
    for (size_t i = 0; i < database_size; i++) {
        if (strstr(database[i].name, query) || strstr(database[i].breed, query)) {
            printf("%zu. Имя: %s, Возраст: %d, Порода: %s\n", i + 1, database[i].name, database[i].age, database[i].breed);
        }
    }
}

void menu(const char* filename) {
    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Показать всех собак\n");
        printf("2. Добавить новую собаку\n");
        printf("3. Удалить собаку\n");
        printf("4. Редактировать собаку\n");
        printf("5. Искать собак\n");
        printf("6. Выйти\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_database();
                break;
            case 2:
                add_dog();
                break;
            case 3:
                delete_dog();
                break;
            case 4:
                edit_dog();
                break;
            case 5:
                search_dog();
                break;
            case 6:
                save_database(filename);
                printf("Выход из программы\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 6);
}