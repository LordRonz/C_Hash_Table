#include <stdio.h>
#include "hash_table.h"

void print_key(ht_hash_table* ht, const char* key);

int main(int argc, char** argv) {
    ht_hash_table* ht = ht_new();
    ht_insert(ht, "Kntl", "Meki");
    print_key(ht, "Kntl");
    ht_insert(ht, "Memek", "Jmbut");
    print_key(ht, "Memek");
    ht_delete(ht, "Kntl");
    //`print_key(ht, "Kntl");
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
