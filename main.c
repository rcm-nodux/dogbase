#include "dog.h"

int main() {
	setlocale(LC_ALL, "Rus");
    const char* filename = "dogs.dat";
    load_database(filename);
    menu(filename);

    free(database);
    return 0;
}
