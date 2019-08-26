#include "libft.h"
#include "common.h"

void do_push(t_stack *from, t_stack *to)
{
	if (from->size == from->start)
		return ;
	to->array[to->start - 1] = from->array[from->start];
	to->start--;
	from->start++;
}

void do_rrotate(t_stack *stack)
{
	int i;
	int tmp;

	if (stack->size - stack->start < 2)
		return ;
	i = stack->size - 1;
	tmp = stack->array[i];
	i--;
	while (i >= stack->start)
	{
		stack->array[i + 1] = stack->array[i];
		i--;
	}
	stack->array[stack->start] = tmp;
}

void do_rotate(t_stack *stack)
{
	int i;
	int tmp;

	if (stack->size - stack->start < 2)
		return ;
	i = stack->start;
	tmp = stack->array[i];
	while (++i < stack->size)
		stack->array[i - 1] = stack->array[i];
	stack->array[stack->size - 1] = tmp;
}

void do_swap(t_stack *stack)
{
	int tmp;

	if (stack->start + 1 < stack->size)
	{
		tmp = stack->array[stack->start];
		stack->array[stack->start] = stack->array[stack->start + 1];
		stack->array[stack->start + 1] = tmp;
	}
}