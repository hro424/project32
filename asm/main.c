#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void
remove_comment(char *buf)
{
	while (*buf != '\0' && *buf != '#') {
		++buf;
	}

	if (*buf == '#') {
		*buf = '\0';
	}
}

void
parse(char *line)
{
	char *ptr;

	for (ptr = line; isspace(*ptr); ++ptr) ;

	for (;*ptr != '\0'; ++ptr) {
		if (isspace(*ptr)) {
			continue;
		}
		else if (*ptr == ':') {
		}
		else if (*ptr == ',') {
		}
	}
}

int
main(int argc, char *argv[])
{
	char buf[256];
	FILE *fp = fopen(argv[1], "r");

	while (fgets(buf, 256, fp)) {
		remove_comment(buf);
		printf("%s", buf);
	}

	return EXIT_SUCCESS;
}
