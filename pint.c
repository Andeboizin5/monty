#include "monty.h"
#include <stdlib.h>

/*
 * pint - prints the value at the top of the stack
 * @stack: input
 * Return: Always 0
 */
void pint(stack_t *stack)
{
	if (stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", 64);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", stack->n);
}
