#include "dictionary_files_management.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_info.h"

bool file_exists(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    return false;
  }
  fclose(file);
  return true;
}

void generate_default_dictionary_file_if_missing(void) {
  if (file_exists(DEFAULT_DICTIONARY_FILENAME)) {
    return;
  }

  FILE* file = fopen(DEFAULT_DICTIONARY_FILENAME, "w");

  fprintf(file, "s bajo pequeño\n");
  fprintf(file, "s bajo menudo\n");
  fprintf(file, "s bajo chico\n");
  fprintf(file, "s pequeño diminuto\n");
  fprintf(file, "s pequeño menudo\n");
  fprintf(file, "s pequeño breve\n");
  fprintf(file, "s pequeño chico\n");
  fprintf(file, "s alto grande\n");
  fprintf(file, "s alto elevado\n");
  fprintf(file, "s grande magno\n");
  fprintf(file, "s grande monumental\n");
  fprintf(file, "s grande notable\n");
  fprintf(file, "s grande extenso\n");
  fprintf(file, "s grande célebre\n");
  fprintf(file, "s chico muchacho\n");
  fprintf(file, "s muchacho niño\n");
  fprintf(file, "s muchacho joven\n");
  fprintf(file, "s niño prequeño\n");
  fprintf(file, "s niño crío\n");
  fprintf(file, "s mujer señora\n");
  fprintf(file, "s mujer esposa\n");
  fprintf(file, "s mujer dama\n");
  fprintf(file, "s esposa cónyuge\n");
  fprintf(file, "s esposa pareja\n");
  fprintf(file, "s hombre marido\n");
  fprintf(file, "s hombre varón\n");
  fprintf(file, "s hombre humano\n");
  fprintf(file, "s hombre individuo\n");
  fprintf(file, "s esposo cónyuge\n");
  fprintf(file, "s cónyuge consorte\n");
  fprintf(file, "s avión aeronave\n");
  fprintf(file, "s avión aeroplano\n");
  fprintf(file, "s vehículo coche\n");
  fprintf(file, "s barco navío\n");
  fprintf(file, "s barco embarcación\n");
  fprintf(file, "s barco buque\n");
  fprintf(file, "s pareja dos\n");
  fprintf(file, "s pareja duplo\n");
  fprintf(file, "s duplo doble\n");
  fprintf(file, "s doble copia\n");
  fprintf(file, "s copia imitación\n");
  fprintf(file, "s superior jefe\n");
  fprintf(file, "a pequeño grande\n");
  fprintf(file, "a pequeño alto\n");
  fprintf(file, "a pequeño adulto\n");
  fprintf(file, "a breve extenso\n");
  fprintf(file, "a breve largo\n");
  fprintf(file, "a breve duradero\n");
  fprintf(file, "a alto bajo\n");
  fprintf(file, "a largo corto\n");
  fprintf(file, "a superior inferior\n");
  fprintf(file, "a superior pésimo\n");
  fprintf(file, "a chico adulto\n");
  fprintf(file, "a extenso reducido\n");
  fprintf(file, "a vacío repleto\n");
  fprintf(file, "a vacío lleno\n");
  fprintf(file, "a claro oscuro\n");
  fprintf(file, "a limpio sucio\n");
  fprintf(file, "a nítido borroso\n");
  fprintf(file, "a cortar pegar\n");
  fprintf(file, "a cortar unir\n");
  fprintf(file, "a veloz lento\n");
  fprintf(file, "a veloz pausado\n");
  fprintf(file, "a pesado liviano\n");
  fprintf(file, "a rápido lento\n");
  fprintf(file, "a rápido pausado\n");
  fprintf(file, "a delgado gordo\n");
  fprintf(file, "a delgado ancho\n");
  fprintf(file, "a flaco gordo\n");
  fprintf(file, "a bueno malo\n");
  fprintf(file, "a alegre triste\n");
  fprintf(file, "a alegre apenado\n");
  fprintf(file, "a contento triste\n");
  fprintf(file, "a ágil torpe\n");
  fprintf(file, "a temprano tarde\n");
  fprintf(file, "a noche día\n");
  fprintf(file, "a ahora después\n");

  fclose(file);
}

void word_info_destroy_wrapper(void* word_info) {
  word_info_destroy(word_info);
}

Trie* load_dictionary_from(const char* filename) {
  if (!file_exists(filename)) {
    return NULL;
  }

  FILE* file = fopen(filename, "r");

  Trie* dictionary = trie_create(word_info_destroy_wrapper);
  char* command = malloc(sizeof(char) * 50);
  char* first_word = malloc(sizeof(char) * 50);
  char* second_word = malloc(sizeof(char) * 50);
  while (!feof(file)) {
    if (fscanf(file, "%49s %49s %49s ", command, first_word, second_word) != 3) {
      free(command);
      free(first_word);
      free(second_word);
      trie_destroy(dictionary);
      fclose(file);
      return NULL;
    }

    if (!trie_contains(dictionary, first_word)) {
      trie_put(dictionary, first_word, word_info_create());
    }
    WordInfo* first_word_info = trie_get(dictionary, first_word);

    if (!trie_contains(dictionary, second_word)) {
      trie_put(dictionary, second_word, word_info_create());
    }
    WordInfo* second_word_info = trie_get(dictionary, second_word);

    if (strcmp(command, "s") == 0) {
      first_word_info->synonyms = g_list_prepend(first_word_info->synonyms, g_strdup(second_word));
      second_word_info->synonyms = g_list_prepend(second_word_info->synonyms, g_strdup(first_word));
    } else if (strcmp(command, "a") == 0) {
      first_word_info->antonyms = g_list_prepend(first_word_info->antonyms, g_strdup(second_word));
      second_word_info->antonyms = g_list_prepend(second_word_info->antonyms, g_strdup(first_word));
    } else { // invalid command
      free(command);
      free(first_word);
      free(second_word);
      trie_destroy(dictionary);
      fclose(file);
      return NULL;
    }
  }
  free(command);
  free(first_word);
  free(second_word);
  fclose(file);

  return dictionary;
}
