#ifndef WORD_INFO_H
#define WORD_INFO_H

#include <glib.h>

typedef struct WordInfo {
  GList* synonyms;
  GList* antonyms;
} WordInfo;

WordInfo* word_info_create(void);
void word_info_destroy(WordInfo* self);

#endif
