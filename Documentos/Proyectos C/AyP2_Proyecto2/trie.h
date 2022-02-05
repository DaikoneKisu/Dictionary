#ifndef TRIE_H
#define TRIE_H

#include <glib.h>
#include <stdbool.h>

typedef struct Trie Trie;

typedef void (*CleanupFunction)(void* value);

Trie* trie_create(CleanupFunction cleanup);
void trie_destroy(Trie* self);

void* trie_get(Trie* self, const char* key);
void trie_put(Trie* self, const char* key, void* value);
void trie_remove(Trie* self, const char* key);
bool trie_contains(Trie* self, const char* key);

GList* trie_keys(Trie* self);
GList* trie_keys_with_prefix(Trie* self, const char* prefix);
GList* trie_keys_matching(Trie* self, const char* pattern);

#endif
