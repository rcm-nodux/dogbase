#include "dog.h"

int main() {
    const char* filename = "dogs.dat";
    load_database(filename);
    menu(filename);

    free(database);
    return 0;
}
