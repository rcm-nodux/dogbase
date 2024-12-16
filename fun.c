#include "dog.h"

Dog* database = NULL;
size_t database_size = 0;

void load_database(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("�� ������� ������� ���� ��� ������\n�������� � ������ ���� ������\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    database_size = file_size / sizeof(Dog);
    database = malloc(database_size * sizeof(Dog));
    if (!database) {
        printf("������ ��������� ������\n");
        fclose(file);
        exit(1);
    }

    fread(database, sizeof(Dog), database_size, file);
    fclose(file);
}

void save_database(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("�� ������� ������� ���� ��� ������\n");
        return;
    }

    fwrite(database, sizeof(Dog), database_size, file);
    fclose(file);
}

void display_database() {
    if (database_size == 0) {
        printf("���� ������ �����\n");
        return;
    }

    printf("\n���� ������ �����:\n");
    for (size_t i = 0; i < database_size; i++) {
        printf("%zu. ���: %s, �������: %d, ������: %s\n", i + 1, database[i].name, database[i].age, database[i].breed);
    }
}

void add_dog() {
    Dog new_dog;

    printf("������� ��� ������: ");
    scanf("%s", new_dog.name);
    printf("������� ������� ������: ");
    scanf("%d", &new_dog.age);
    printf("������� ������ ������: ");
    scanf("%s", new_dog.breed);

    Dog* new_database = realloc(database, (database_size + 1) * sizeof(Dog));
    if (!new_database) {
        printf("������ ��������� ������\n");
        return;
    }

    database = new_database;
    database[database_size++] = new_dog;

    printf("������ ������� ���������\n");
}

void delete_dog() {
    if (database_size == 0) {
        printf("���� ������ �����\n");
        return;
    }

    size_t index;
    printf("������� ����� ������ ��� ��������: ");
    scanf("%zu", &index);

    if (index < 1 || index > database_size) {
        printf("�������� �����\n");
        return;
    }

    for (size_t i = index - 1; i < database_size - 1; i++) {
        database[i] = database[i + 1];
    }

    Dog* new_database = realloc(database, (database_size - 1) * sizeof(Dog));
    if (!new_database && database_size - 1 > 0) {
        printf("������ ��������� ������\n");
        return;
    }

    database = new_database;
    database_size--;

    printf("������ ������� �������\n");
}

void edit_dog() {
    if (database_size == 0) {
        printf("���� ������ �����\n");
        return;
    }

    size_t index;
    printf("������� ����� ������ ��� ��������������: ");
    scanf("%zu", &index);

    if (index < 1 || index > database_size) {
        printf("�������� �����\n");
        return;
    }

    Dog* dog = &database[index - 1];

    printf("�������������� ������: %s\n", dog->name);
    printf("������� ����� ���: ");
    scanf("%s", dog->name);
    printf("������� ����� �������: ");
	int new_age;
    scanf("%d", &new_age);
	dog->age = new_age;
    printf("������� ����� ������: ");
    scanf("%s", dog->breed);

    printf("������ ������� ���������\n");
}

void search_dog() {
    if (database_size == 0) {
        printf("���� ������ �����\n");
        return;
    }

    char query[MAX_LEN];
    printf("������� ��� ��� ������ ��� ������: ");
    scanf("%s", query);

    printf("\n���������� ������:\n");
    for (size_t i = 0; i < database_size; i++) {
        if (strstr(database[i].name, query) || strstr(database[i].breed, query)) {
            printf("%zu. ���: %s, �������: %d, ������: %s\n", i + 1, database[i].name, database[i].age, database[i].breed);
        }
    }
}

void menu(const char* filename) {
    int choice;

    do {
        printf("\n����:\n");
        printf("1. �������� ���� �����\n");
        printf("2. �������� ����� ������\n");
        printf("3. ������� ������\n");
        printf("4. ������������� ������\n");
        printf("5. ������ �����\n");
        printf("6. �����\n");
        printf("������� ��� �����: ");
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
                printf("����� �� ���������\n");
                break;
            default:
                printf("�������� �����\n");
        }
    } while (choice != 6);
}