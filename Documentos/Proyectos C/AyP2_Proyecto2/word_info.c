#include "word_info.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

WordInfo* word_info_create(void) {
  WordInfo* new_instance = malloc(sizeof(WordInfo));

  new_instance->synonyms = NULL;
  new_instance->antonyms = NULL;

  return new_instance;
}

void word_info_destroy(WordInfo* self) {
  g_list_free_full(self->synonyms, g_free);
  g_list_free_full(self->antonyms, g_free);
  free(self);
}
