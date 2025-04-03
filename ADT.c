#include "stack.h"
#include "queue.h"
#include <string.h>

int stack(void) 
{
	StackType* s = (StackType*)malloc(sizeof(StackType));
	
	if(s == NULL)
	{
		printf("Failed to allocate memory\n");
		return -1;
	}
	
	char str[30];
	
	initi_Stack(s);

	fgets(str, sizeof(str), stdin);
	

	for(int i = 0; str[i] != '\0'; i++)
	{

		if(str[i] == ')' || str[i + 1] == '\0')
			for (; s->top != -1;)
			{
				char p = pop(s);

				if (p != '(')
					printf("%c", p);
			}

		else if(str[i] == '(' || str[i] == '+' || str[i] == '*' || str[i] == '/' )
			push(s, str[i]);
		else
			printf("%c", str[i]);
	}

	if(s->top != -1)
		printf("%c", pop(s));

	free(s);
	return 0;
}

int linear_queue(void)
{
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	if (q == NULL)
	{
		return -1;
	}
	init_linear_queue(q);

	enQueue(q, 'A');
	enQueue(q, 'B');
	enQueue(q, 'C');

	deQueue(q);
	for (int i = 0; i + q->front < 3; i++)
		printf("%c", q->data[q->front + i]);
	printf("\n");

	deQueue(q);
	for (int i = 0; i + q->front < 3; i++)
		printf("%c", q->data[q->front]);
	printf("\n");

	deQueue(q);
	for (int i = 0; i + q->front < 3; i++)
		printf("%c", q->data[q->front]);
	printf("\n");

	free(q);
	return 0;
}

int main(void)
{
	linear_queue();

	return 0;
}