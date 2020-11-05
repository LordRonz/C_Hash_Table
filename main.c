#include <stdio.h>
#include "hash_table.h"

void print_key(ht_hash_table* ht, const char* key);
void delete_item(ht_hash_table* ht, const char* key);

int main(int argc, char** argv) {
    ht_hash_table* ht = ht_new();
    ht_insert(ht, "Kntl", "Meki");
    printf("%d\n", ht->count);
    print_key(ht, "Kntl");
    ht_insert(ht, "Memek", "Jmbut");
    printf("%d\n", ht->count);
    print_key(ht, "Memek");
    ht_insert(ht, "Memek", "Puqy");
    printf("%d\n", ht->count);
    print_key(ht, "Memek");
    delete_item(ht, "Kntl");
    delete_item(ht, "Kontol");
    ht_insert(ht, "Kntl", "Kntl");
    printf("%d\n", ht->count);
    print_key(ht, "Kntl");
    ht_del_hash_table(ht);
    return 0;
}

void print_key(ht_hash_table* ht, const char* key) {
    char *s = ht_search(ht, key);
    if(s) {
	printf("# Key : %s\n", key);
	printf("Value : %s\n", s);
    }
    else {
	printf("Key not found!\n");
    }
}

void delete_item(ht_hash_table* ht, const char* key) {
    if(ht_delete(ht, key)) {
	printf("Item with key \"%s\" was successfully deleted.\n", key);
    }
    else {
	printf("Item with key \"%s\" was not found in the table!\n", key);
    }
}
