#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 1000

int stack[STACK_SIZE];
int top = -1;

void push(int value)
{
	if (top == STACK_SIZE - 1)
	{
		fprintf(stderr, "L%d: stack overflow\n", line_number);
		exit(EXIT_FAILURE);
	}
	stack[++top] = value;
}

void pall(void)
{
	int i;

	for (i = top; i >= 0; i--)
	{
		printf("%d\n", stack[i]);
	}
}

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		if (line[0] == '\n' || line[0] == '#')
		{

			continue;
		}

		char *opcode = strtok(line, " \n");
		if (opcode == NULL)
		{
			fprintf(stderr, "L%d: opcode missing\n", line_number);
			exit(EXIT_FAILURE);
		}

		if (strcmp(opcode, "push") == 0)
		{
			char *arg = strtok(NULL, " \n");
			if (arg == NULL)
			{
				fprintf(stderr, "L%d: usage: push integer\n", line_number);
				exit(EXIT_FAILURE);
			}

			int value = atoi(arg);
			push(value);
		} else if (strcmp(opcode, "pall") == 0) {
			pall();
		} else {
			fprintf(stderr, "L%d: unknown opcode %s\n", line_number, opcode);
			exit(EXIT_FAILURE);
		}
	}

	fclose(file);
	if (line)
		free(line);
	return 0;
}

