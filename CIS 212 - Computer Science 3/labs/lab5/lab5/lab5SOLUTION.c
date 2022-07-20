#include <stdio.h>
#include <stdlib.h>
#include "ADTs/stringADT.h"
#include "ADTs/arraylist.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#define USESTR "usage: %s [-s] [FILE] ...\n"


void getStats(const String *stADT, const ArrayList *csv, bool doStat, FILE *fp) {
	const ArrayList *al;
	const Iterator *it;
	const Iterator *it2;

	char buf[BUFSIZ];
	while (fgets(buf, sizeof buf, fp) != NULL) {
		stADT->clear(stADT);
		stADT->append(stADT, buf);

		al = stADT->split(stADT, ",");

		it = al->itCreate(al);
		while(it->hasNext(it)) {
			char *temp;
			(void) it->next(it, (void **)&temp);
			(void) csv->add(csv, temp);
		}
		it->destroy(it);
	}	
		
	if(doStat) {
		long sum = 0;
		double mean = 0.0;
		double diff = 0.0;
		double stdev = 0.0;
		
		it2 = csv->itCreate(csv);	
		while(it->hasNext(it)) {
			char *temp;
			(void) it2->next(it2, (void **)&temp);
			sum += atoi(temp);
		}
		it2->destroy(it2);

		mean = (double)sum/csv->size(csv);
		
		for(int i = 0; i < csv->size(csv); i++) {
			char *temp;
			(void)csv -> get(csv, i, (void **)&temp);
			diff += pow((atoi(temp) - mean), 2);
		}
		stdev = sqrt((double)diff/csv->size(csv));

		printf("Mean: %.2f\n", mean);
		printf("Stdev: %.2f\n", stdev);
	}

	csv->destroy(csv);
	stADT->destroy(stADT);
	al->destroy(al);
	fclose(fp);
}


int main(int argc, char *argv[]) {
	const String *stADT = String_create("");
	const ArrayList *csv = ArrayList_create(0L, free);

	int opt;
	FILE * fp;

	bool doStat = false;

	opterr = 0;
	while((opt = getopt(argc, argv, "s")) != -1) {
		switch(opt) {
			case 's':
				doStat = true;
				break;
			default:
				fprintf(stderr, "%s: invalid option '-%c'\n", argv[0], optopt);
				fprintf(stderr, USESTR, argv[0]);
				return EXIT_FAILURE;
		}
	}

	fp = fopen(argv[optind], "r");
	if(fp == NULL) {
		fprintf(stderr, "%s: unable to open file: %s\n", argv[0], argv[optind]);
		return EXIT_FAILURE;
	}
	
	getStats(stADT, csv, doStat, fp);
}
