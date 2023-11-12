#include "shell.h"

int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		update_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			break;
		}
		input[strcspn(input,"\n")] = '\0';
