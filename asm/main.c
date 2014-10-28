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
add_label(const char *begin, const char *end)
{

}

void
process(const char *str, int *state)
{
	switch (*state) {
	case STATE_INITIAL:
		break;
	case STATE_LABEL:
		break;
	case STATE_OPCODE:
		break;
	case STATE_OPERAND:
		break;
	}
}

void
lex(char *line)
{
	static char *sep = ",: \t";
	char *word, *last;
	int state;

	for (word = strtok_r(line, sep, &last);
	     word;
	     word = strtok_r(NULL, sep, &last)) {
		process(word, &state);
	}

	save = line;
	for (const char *cur = line; cur != '\0'; ++cur) {
		if (isspace(*cur)) {
			++save;
			continue;
		}
		else if (*cur == ':') {
			parse_label(save, cur);
		}
		else if (*cur == 
	}

	label = strtok_r(line, ":", &last);
	inst = strtok_r(NULL, ":", &last);
	parse_label(label);
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
