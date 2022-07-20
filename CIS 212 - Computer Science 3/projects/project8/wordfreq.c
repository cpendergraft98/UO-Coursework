#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "ADTs/stringADT.h"
#include "ADTs/arraylist.h"
#include"ADTs/hashcskmap.h"
#include <stdbool.h>
#include <unistd.h>

int keycmp(void *x1, void *x2) {
    MEntry *m1 = (MEntry *)x1;
    MEntry *m2 = (MEntry *)x2;
    return strcmp((char *)m1->key, (char *)m2->key);
}

int revkeycmp(void *x1, void *x2) {
    MEntry *m1 = (MEntry *)x1;
    MEntry *m2 = (MEntry *)x2;
    return strcmp((char *)m2->key, (char *)m1->key);
}

int valcmp(void *x1, void *x2) {
    MEntry *m1 = (MEntry *)x1;
    MEntry *m2 = (MEntry *)x2;
    return (long)m1->value < (long)m2->value;
}

int revvalcmp(void *x1, void *x2) {
    MEntry *m1 = (MEntry *)x1;
    MEntry *m2 = (MEntry *)x2;
    return (long)m1->value > (long)m2->value;
}

void printmap(const CSKMap *m, bool doFreq, bool doAlpha, bool doInvert, FILE *fp){
  long y;
  long num;
  long size;
  char *word;

  MEntry **array = m->entryArray(m, &size);

   if(doAlpha){
    sort((void**)array, size, keycmp);
        if(doInvert){
          sort((void**)array, size, revkeycmp);
        }
      }

  if(doFreq){
    sort((void**)array, size, valcmp);
    if(doInvert){
      sort((void**)array, size, revvalcmp);
    }
  }

  for(y = 0; y < size; y++){
    word = (char *)array[y] -> key;
    num = (long)array[y] -> value;
    fprintf(fp, "%8ld %s\n", num, word);
  }
  free((void*)array);
}
    
void wordfreq (FILE *fp, bool doPunct, bool doLower, const CSKMap *m, const String *stADT){
	char buf[BUFSIZ];
	while(fgets(buf, sizeof buf, fp) != NULL){
    const ArrayList *al;
		stADT -> clear(stADT);
    stADT -> append(stADT, buf);
    long i;

		if(doLower){
			stADT -> lower(stADT);
		}

		if(doPunct){
			stADT -> translate(stADT, "[:punct:]", ' ');
		}

		al = stADT -> split(stADT, "");

		if(al == NULL){
			continue;
		}

		for(i = 0; i < al -> size(al); i++){
			char *word;
      (void)al -> get(al, i, (void**)&word);
      long val;
			
			if(m -> get(m, word, (void**)&val)){
        val++; 

			}else{
        val = 1;
			}
      m -> put(m, word, (void*)val);
		}
    al -> destroy(al);
  }
}

void fileClose(void *x){
  FILE *fp = (FILE *)x;
  if(fp != stdin && fp != stdout && fp != stderr){
    fclose(fp);
  }
}

int main(int argc, char *argv[]){
	int i;
  int opt;
	FILE *fp;
  bool doAlpha = false;
  bool doFreq = false;
  bool doInvert = false;
  bool doLower = false;
  bool doPunct = false;

  const CSKMap *m = HashCSKMap(0L, 0.0, NULL);
  const ArrayList *alFiles = ArrayList_create(0L, fileClose);
  const String *stADT = String_create(" ");

  int EXIT_STATUS = EXIT_FAILURE;

  if(alFiles == NULL){
    fprintf(stderr, "Unable to create ArrayList instance.\n");
    goto cleanup;
  }

  if(stADT == NULL){
    fprintf(stderr, "Unable to create stADT instance.\n");
    goto cleanup;
  }

  if(m == NULL){
    fprintf(stderr, "Unable to create CSKMap Instance.\n");
    goto cleanup;
  }

	opterr = 0;
	while((opt = getopt(argc, argv, "afilp")) != -1){
		switch(opt){
			case 'a': doAlpha = true; break;
			case 'f': doFreq = true; break;
			case 'i': doInvert = true; break;
			case 'l': doLower = true; break;
			case'p': doPunct = true; break;
			default: fprintf(stderr, "%s: Illegal option, '-%c'\n", argv[0], optopt);
			EXIT_STATUS = EXIT_SUCCESS;
      goto cleanup;
		}
	}

  if(doAlpha && doFreq){
    fprintf(stderr, "Flags -a and -f can not be used together\n");
    goto cleanup;
  }

  if(doInvert){
    if(!(doAlpha || doFreq)){
      fprintf(stderr, "Flag -i illegal without flags -a or -f\n");
      goto cleanup;
    }
  }

  if(argv[optind] == NULL){
    (void) alFiles -> add(alFiles, (void*)stdin);
  }

  if(argv[optind] != NULL){
    for(i = optind; i < argc; i++){
      fp = fopen(argv[i], "r");
      if(fp == NULL){
        fprintf(stderr, "%s: unable to open file: %s\n", argv[0], argv[i]);
        goto cleanup;
      }
      (void)alFiles -> add(alFiles, (void*)fp);
    }
  }

  for(i = 0; alFiles -> get(alFiles, i, (void**)&fp); i++){
    wordfreq(fp,  doPunct, doLower, m, stADT);
  }

  printmap(m, doFreq, doAlpha, doInvert, stdout);
  EXIT_STATUS = EXIT_SUCCESS;
  
cleanup:
  if(alFiles != NULL)
    alFiles -> destroy(alFiles);
  if(m != NULL)
    m -> destroy(m);
  if(stADT != NULL)
    stADT -> destroy(stADT);
  return EXIT_STATUS;
}