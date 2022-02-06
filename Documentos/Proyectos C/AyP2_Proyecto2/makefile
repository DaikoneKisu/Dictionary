objects := dictionary.o dictionary_files_management.o word_info.o trie.o

diccionario : dictionary.o dictionary_files_management.o word_info.o trie.o
	gcc $(shell pkg-config --cflags glib-2.0) -o diccionario $(objects) $(shell pkg-config --libs glib-2.0)

dictionary.o : dictionary.c
	gcc $(shell pkg-config --cflags glib-2.0) -std=c11 -c dictionary.c $(shell pkg-config --libs glib-2.0)
dictionary_files_management.o : dictionary_files_management.c
	gcc $(shell pkg-config --cflags glib-2.0) -std=c11 -c dictionary_files_management.c $(shell pkg-config --libs glib-2.0)
word_info.o : word_info.c
	gcc $(shell pkg-config --cflags glib-2.0) -std=c11 -c word_info.c $(shell pkg-config --libs glib-2.0)
trie.o : trie.c
	gcc $(shell pkg-config --cflags glib-2.0) -std=c11 -c trie.c $(shell pkg-config --libs glib-2.0)

dictionary.c : word_info.h dictionary_files_management.h
dictionary_files_management.c : dictionary_files_management.h word_info.h
word_info.c : word_info.h
trie.c : trie.h

dictionary_files_management.h : trie.h

.PHONY : clean

clean :
	rm -f $(objects)
