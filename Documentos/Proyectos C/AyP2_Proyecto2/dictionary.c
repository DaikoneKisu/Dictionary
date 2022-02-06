#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_info.h"
#include "dictionary_files_management.h"

void show_synonyms_of(Trie* dictionary, const char* word) {
  WordInfo* word_info = trie_get(dictionary, word);

  printf("sinónimos de %s: ", word);
  if (!word_info || !word_info->synonyms) {
    printf("(no hay)");
  } else {
    GList* first_synonym = word_info->synonyms;
    printf("%s", (const char*) first_synonym->data);
    for (GList* synonym = first_synonym->next; synonym; synonym = synonym->next) {
      printf(", %s", (const char*) synonym->data);
    }
  }
  printf("\n");
}

void show_antonyms_of(Trie* dictionary, const char* word) {
  WordInfo* word_info = trie_get(dictionary, word);

  printf("antónimos de %s: ", word);
  if (!word_info || !word_info->antonyms) {
    printf("(no hay)");
  } else {
    GList* first_antonym = word_info->antonyms;
    printf("%s", (const char*) first_antonym->data);
    for (GList* antonym = first_antonym->next; antonym; antonym = antonym->next) {
      printf(", %s", (const char*) antonym->data);
    }
  }
  printf("\n");
}

void show_synonyms_and_antonyms_of_words_matching(Trie* dictionary, const char* pattern) {
  GList* words_matching_pattern = trie_keys_matching(dictionary, pattern);

  if (g_list_length(words_matching_pattern) == 0) {
    printf("(no hay palabras que coincidan con el patrón dado)\n");
    return;
  }

  for (GList* word = words_matching_pattern; word; word = word->next) {
    show_synonyms_of(dictionary, (const char*) word->data);
    show_antonyms_of(dictionary, (const char*) word->data);
  }

  g_list_free(words_matching_pattern);
}

void show_help(void) {
  printf("Los argumentos válidos para la línea de comandos son s palabra\n"
         "y a palabra, que busca los sinónimos y antónimos de `palabra`,\n"
         "respectivamente. Y las órdenes del modo interactivo son:\n"
         "  cargar archivo - carga el diccionario desde archivo\n"
         "  s palabra - busca los sinónimos de `palabra`\n"
         "  a palabra - busca los antónimos de `palabra`\n"
         "  e expresión - muestra los sinónimos y antónimos de todas las\n"
         "                palabras que coincidan con el regex construido\n"
         "                a partir de `expresión`\n"
         "  ayuda - muestra esta entrada\n"
         "  salir - salir de la aplicación\n");
}

void run_non_interactive_mode(int argument_count, char* arguments[]) {
  Trie* dictionary = load_dictionary_from(DEFAULT_DICTIONARY_FILENAME);

  int current_argument = 0;
  do {
    char* command = arguments[current_argument++];
    char* argument = arguments[current_argument++];

    if (strcmp(command, "s") == 0) {
      show_synonyms_of(dictionary, argument);
    } else if (strcmp(command, "a") == 0) {
      show_antonyms_of(dictionary, argument);
    } else {
      fprintf(stderr, "Error: Comando no reconocido (%s)\n", command);
      break;
    }
  } while (current_argument < argument_count);

  trie_destroy(dictionary);
}

void run_interactive_mode(void) {
  Trie* dictionary = load_dictionary_from(DEFAULT_DICTIONARY_FILENAME);

  char* command = malloc(sizeof(char) * 50);
  char* argument = malloc(sizeof(char) * 50);
  for (;;) {
    printf("> ");
    scanf("%49s", command);

    if (strcmp(command, "s") == 0) {
      scanf("%49s", argument);
      show_synonyms_of(dictionary, argument);
    } else if (strcmp(command, "a") == 0) {
      scanf("%49s", argument);
      show_antonyms_of(dictionary, argument);
    } else if (strcmp(command, "e") == 0) {
      scanf("%49s", argument);
      show_synonyms_and_antonyms_of_words_matching(dictionary, argument);
    } else if (strcmp(command, "cargar") == 0) {
      scanf("%49s", argument);
      trie_destroy(dictionary);
      dictionary = load_dictionary_from(argument);
      if (!dictionary) {
        fprintf(stderr, "Error: No se pudieron cargar los datos del diccionario\n");
      }
    } else if (strcmp(command, "ayuda") == 0) {
      show_help();
    } else if (strcmp(command, "salir") == 0) {
      break;
    } else {
      fprintf(stderr, "Error: Comando no reconocido (%s)\n", command);
    }
  }
  free(command);
  free(argument);

  trie_destroy(dictionary);
}

int main(int argument_count, char* arguments[]) {
  generate_default_dictionary_file_if_missing();
  if (argument_count <= 1) {
    run_interactive_mode();
  } else if (argument_count % 2 == 0) {
    run_non_interactive_mode(argument_count, arguments);
  } else {
    fprintf(stderr, "Error: Número erróneo de argumentos\n");
  }
}
