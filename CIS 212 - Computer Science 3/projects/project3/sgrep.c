#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void sgreps(FILE *fp, char *ss, bool flags[], bool multiple_files, char *name) {
	char buf[BUFSIZ];
	int cnt = 0;

	while (fgets(buf, sizeof buf, fp) != NULL) {
		if(!flags[0]){
			if(!flags[1]){
				if(!flags[2]){
					if (strstr(buf, ss) != NULL){
						if(multiple_files){
							printf("%s:%s", name, buf);
						}else{
							printf("%s", buf);
						}
					}
				}
			}
		}
		if (flags[0] && !flags[2]){
			if (strcasestr(buf, ss) != NULL){
				if(!multiple_files){
					printf("%s", buf);
				}else{
					printf("%s:%s", name, buf);
				}
			}
		}else{
		if(flags[0] && flags[2]){
			if(strcasestr(buf, ss) != NULL){
				cnt++;
			}
		}else{
		if(flags[2] && flags[1]){
			if(strstr(buf, ss) == NULL){
				cnt++;
			}
		}else{
		if(flags[1] && !flags[2]){
			if(strstr(buf, ss) == NULL) {
				if(!multiple_files) {
					printf("%s", buf);
				}else{
					printf("%s:%s", name, buf);
				}
			}
		}
		if(strstr(buf, ss) != NULL){
			cnt++;
				}	
			}
		}
	}
	if (flags[2] && flags[0]){
		if (multiple_files){
			printf("%s:%d\n", name, cnt);
		}else{
			printf("%d\n", cnt);
		}
	}else{
	if (flags[2] && flags[1]){
		if(flags[3]){
			printf("%s:%d\n", name, cnt);
		}else{
			printf("%d\n", cnt);
				}
			}
		}
	}
}

int main (int argc, char *argv[]) {
	int opt;
	bool doNoCase;
	bool doInvert;
	bool doSuppress;
	bool multiple_files;
	bool haveFlag;
	FILE *fp;
	doNoCase = doInvert = doSuppress = haveFlag = multiple_files = false;
	opterr = 0;

	while((opt = getopt(argc, argv, "ivc")) != -1) {
		switch(opt) {
			case 'i': doNoCase = haveFlag = true; break;
			case 'v': doInvert = haveFlag = true; break;
			case 'c': doSuppress = haveFlag = true; break;
			default: fprintf(stderr, "%s: illegal option, '-%c'\n", argv[0], optopt);
		}
	}

	bool flags[4] = {doNoCase, doInvert, doSuppress, multiple_files};
	if (argc - optind >= 2){
		multiple_files = true;
	}

	if (argv[optind] == NULL) {
		fprintf(stderr, "Hello, I am an error message, you did something wrong!.");
		goto cleanup;
	}
	else if (argv[optind + 1] == NULL) {
		sgreps(stdin, argv[optind], flags, multiple_files, NULL);
		goto cleanup;

	}else{

		for (int i = optind+1; argv[i] != NULL; i++) {
				char *fn = argv[i];
				fp = fopen(argv[i], "r");
				if (access(argv[i], F_OK) != 0){
					printf("./sgreps: open(%s) error \n", argv[i]);
					return EXIT_FAILURE;
				}
				sgreps(fp, argv[optind], flags, multiple_files, fn);
				fclose(fp);
			}
		}
	goto cleanup;
	cleanup:
		return EXIT_SUCCESS;
}