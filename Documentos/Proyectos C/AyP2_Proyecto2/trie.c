#include "trie.h"

#include <stdlib.h>
#include <string.h>

struct Trie {
  char* key;
  void* value;
  GHashTable* children;
  CleanupFunction cleanup;
};

void trie_destroy_wrapper(void* trie) {
  trie_destroy(trie);
}

Trie* trie_create(CleanupFunction cleanup) {
  Trie* new_instance = malloc(sizeof(Trie));

  new_instance->key = NULL;
  new_instance->value = NULL;
  new_instance->children = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, trie_destroy_wrapper);
  new_instance->cleanup = cleanup;

  return new_instance;
}

void trie_destroy(Trie* self) {
  g_free(self->key);
  if (self->value && self->cleanup) {
    self->cleanup(self->value);
  }
  g_hash_table_destroy(self->children);
  free(self);
}

Trie* trie_get_child(Trie* self, const char* key) {
  if (!strlen(key)) {
    return NULL;
  }
  Trie* child = self;
  for (int i = 0; child && i < strlen(key); ++i) {
    child = g_hash_table_lookup(child->children, GINT_TO_POINTER(key[i]));
  }
  return child;
}

void* trie_get(Trie* self, const char* key) {
  Trie* key_edge = trie_get_child(self, key);
  return key_edge ? key_edge->value : NULL;
}

void trie_put(Trie* self, const char* key, void* value) {
  Trie* key_edge = self;
  for (int i = 0; i < strlen(key); ++i) {
    if (!g_hash_table_contains(key_edge->children, GINT_TO_POINTER(key[i]))) {
      g_hash_table_insert(key_edge->children, GINT_TO_POINTER(key[i]), trie_create(self->cleanup));
    }
    key_edge = g_hash_table_lookup(key_edge->children, GINT_TO_POINTER(key[i]));
  }
  if (!key_edge->key) {
    key_edge->key = g_strdup(key);
  } else {
    if (key_edge->cleanup) {
      key_edge->cleanup(key_edge->value);
    }
  }
  key_edge->value = value;
}

void trie_remove(Trie* self, const char* key) {
  Trie* key_edge = trie_get_child(self, key);
  if (!key_edge) {
    return;
  }
  g_free(key_edge->key);
  key_edge->key = NULL;
  if (key_edge->cleanup) {
    key_edge->cleanup(key_edge->value);
    key_edge->value = NULL;
  }
}

bool trie_contains(Trie* self, const char* key) {
  return trie_get_child(self, key);
}

void trie_keys_impl(Trie* self, GList** keys) {
  GHashTableIter children_iterator;
  Trie* current_child;

  g_hash_table_iter_init(&children_iterator, self->children);
  while (g_hash_table_iter_next(&children_iterator, NULL, (void**) &current_child)) {
    if (current_child->key) {
      *keys = g_list_prepend(*keys, current_child->key);
    }
    trie_keys_impl(current_child, keys);
  }
}

GList* trie_keys(Trie* self) {
  GList* keys = NULL;
  trie_keys_impl(self, &keys);
  return keys;
}

GList* trie_keys_with_prefix(Trie* self, const char* prefix) {
  Trie* words_with_given_prefix = trie_get_child(self, prefix);
  if (!words_with_given_prefix) {
    return NULL;
  }
  return trie_keys(words_with_given_prefix);
}

GList* trie_keys_matching(Trie* self, const char* pattern) {
  GRegex* regex = g_regex_new(pattern, 0, 0, NULL);
  if (!regex) {
    return NULL;
  }
  
  GList* keys = trie_keys(self);
  for (GList* key = keys; key;) {
    if (!g_regex_match(regex, (const char*) key->data, 0, NULL)) {
      GList* tmp = key->next;
      keys = g_list_delete_link(keys, key);
      key = tmp;
    } else {
      key = key->next;
    }
  }

  return keys;
}
