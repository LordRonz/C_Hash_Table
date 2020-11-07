#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

void print_key(ht_hash_table* ht, const char* key);
void delete_item(ht_hash_table* ht, const char* key);
void add_item_input(ht_hash_table* ht);
void print_key_input(ht_hash_table* ht);
void del_item_input(ht_hash_table* ht);

int main(int argc, char** argv) {
    ht_hash_table* ht = ht_new();
    int input = -1;
    char line[5];
    bool run = true;
    printf("---MY HASH TABLE---\n");
    while(run) {
	printf("1. Add item\n");
	printf("2. Print item\n");
	printf("3. Delete item\n");
	if(fgets(line, 5, stdin)) {
	    input = atoi(line);
	    switch(input) {
		case 1:
		    add_item_input(ht);
		    break;
		case 2:
		    print_key_input(ht);
		    break;
		case 3:
		    del_item_input(ht);
		    break;
		default:
		    run = false;
		    break;
	    }
	}
    }
    ht_del_hash_table(ht);
    return 0;
}

void print_key(ht_hash_table* ht, const char* key) {
    char *s = ht_search(ht, key);
    if(s) {
	printf("# Key : %s\n", key);
	printf("Value : %s\n", s);
    }
    else
	printf("Key not found!\n");
}

void delete_item(ht_hash_table* ht, const char* key) {
    if(ht_delete(ht, key))
	printf("Item with key \"%s\" was successfully deleted.\n", key);
    else
	printf("Item with key \"%s\" was not found in the table!\n", key);
}

void add_item_input(ht_hash_table* ht) {
    char value[50];
    char key[50];
    printf("Enter your key: \n");
    fgets(key, 50, stdin);
    if(strlen(key) > 0 && key[strlen(key) - 1] == '\n')
	key[strlen(key) - 1] = '\0';
    printf("Enter your string: \n");
    fgets(value, 50, stdin);
    if(strlen(value) > 0 && value[strlen(value) - 1] == '\n')
	value[strlen(value) - 1] = '\0';
    ht_insert(ht, strdup(key), strdup(value));
    printf("Item with value %s has been added to the table.\n", value);
}

void print_key_input(ht_hash_table* ht) {
    char key[50];
    printf("Enter your key: \n");
    fgets(key, 50, stdin);
    if(strlen(key) > 0 && key[strlen(key) - 1] == '\n')
	key[strlen(key) - 1] = '\0';
    print_key(ht, key);
}

void del_item_input(ht_hash_table* ht) {
    char key[50];
    printf("Enter your key: \n");
    fgets(key, 50, stdin);
    if(strlen(key) > 0 && key[strlen(key) - 1] == '\n')
	key[strlen(key) - 1] = '\0';
    delete_item(ht, key);
}
