#ifndef DICTIONARY_FILES_MANAGEMENT_H
#define DICTIONARY_FILES_MANAGEMENT_H

#include "trie.h"

#define DEFAULT_DICTIONARY_FILENAME "default_dictionary.dic"

void generate_default_dictionary_file_if_missing(void);
Trie* load_dictionary_from(const char* filename);

#endif
