#include <string.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};
int HT_INITIAL_BASE_SIZE = 50;
const int HT_PRIME_1 = 139;
const int HT_PRIME_2 = 163;

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

void ht_del_hash_table(ht_hash_table* ht) {
    for(int i = 0; i < ht->size; ++i) {
	ht_item* item = ht->items[i];
	if(item != NULL && item != &HT_DELETED_ITEM) {
	    ht_del_item(item);
	}
    }
    free(ht->items);
    free(ht);
}

static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;
    for(int i = 0; i < strlen(s); ++i) {
	hash += (long)pow(a, strlen(s) - (i + 1)) * s[i];
	hash %= m;
    }
    return (int)hash;
}

static int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while(cur_item && cur_item != &HT_DELETED_ITEM) {
	if(strcmp(cur_item->key, key) == 0) {
	    ht_del_item(cur_item);
	    ht->items[index] = item;
	    return;
	}
	index = ht_get_hash(item->key, ht->size, i++);
	cur_item = ht->items[index];
    }
    ht->items[index] = item;
    ++ht->count;
}

char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item) {
	if(item != &HT_DELETED_ITEM) {
	    if(strcmp(item->key, key) == 0) {
		return item->value;
	    }
	}
	index = ht_get_hash(key, ht->size, i++);
	item = ht->items[index];
    }
    return NULL;
}

bool ht_delete(ht_hash_table* ht, const char* key) {
    bool deleted = false;
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item) {
	if(item != &HT_DELETED_ITEM) {
	    if(strcmp(item->key, key) == 0) {
		ht_del_item(item);
		ht->items[index] = &HT_DELETED_ITEM;
		deleted = true;
		--ht->count;
	    }
	}
	index = ht_get_hash(key, ht->size, i++);
	item = ht->items[index];
    }
    return deleted;
}

static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

static void ht_resize(ht_hash_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and items
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
