
#include "hashtable.h"
#include "philphix.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

HashTable *dictionary;

int main(int argc, char **argv){
  if(argc != 3){
    /* Note, you can print everything you want to standard error, it will be
       ignored by the autograder */
    fprintf(stderr, "Specify an input dictionary file and a text file\n");
    return 0;
  }
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);
  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");
  fprintf(stderr, "Processing stdin\n");
  processInput(argv[2]);
  return 0;
}

/* Define a hash function */
unsigned int stringHash(void *s){
  char *string = (void *) s;
  /* Printing string is to prevent a compiler warning until you
     actually implement this function */
  /* fprintf(stderr, "need to implement stringHash%s\n", string); */

  unsigned int hashCode = 0;
  unsigned int coef = 1;
  while (*string) {
    hashCode += coef * (*string);
    coef *= 31;
    string++;
  }
  printf("%s %d\n", (char*)s, hashCode);
  return hashCode;
}

int stringEquals(void *s1, void *s2){
  return stringHash(s1) == stringHash(s2) ? 1 : 0;  /* return: 1 equal, 0 not equal */
}

void readDictionary(char *name){
  FILE *inputFile = fopen(name, "r");
  if (!inputFile) {
    fprintf(stderr, "Error: open dictionary file failed: %s\n", name);
    exit(1);
  }
  char key[1024], value[1024];
  while (fscanf(inputFile, " %1023s", key) == 1) {
      if (fscanf(inputFile, " %1023s", value) == 1) {
        fprintf(stderr, "readDictionary: insert (%s, %s)\n", key, value);
        insertData(dictionary, key, value);
      }
  }
  fclose(inputFile);
}

void processInput(char *name){
  FILE *inputFile = fopen(name, "r");
  if (!inputFile) {
    fprintf(stderr, "Error: open text file failed: %s\n", name);
    exit(1);
  }
  char buf[1024];
  while (fscanf(inputFile, " %1023s", buf) == 1) {
    char *newbuf = (char*) findData(dictionary, buf);
    //if (!newbuf) newbuf = buf;
    if (newbuf) fprintf(stderr, "%s\n", newbuf);
  }
  fclose(inputFile);
}
