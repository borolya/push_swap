#include "push_swap.h"
#include "libft.h"
static int	find_med(t_stack *stack)//not index// mb faster
{
	int i;
	int j;
	int tmp;
	int *cpy;

	if (!(cpy = ft_memalloc(sizeof(int) * stack->size)))
		exit (1);
	ft_memcpy(cpy, stack->array + stack->start, stack->size * 4);
	i = -1;
	while (++i < stack->size -  1)
	{
		j = -1;
		while (++j < stack->size - 1 - i)
		{
			if (cpy[j] > cpy[j + 1])
			{
				tmp = cpy[j];
				cpy[j] = cpy[j + 1];
				cpy[j + 1] = tmp;
			}
		}
	}
	tmp = cpy[stack->size / 2];
	free(cpy);
	return (tmp);
}

static void sort_tree(t_stack *a, int min, int max)
{
	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	if (a->array[a->start] == max && a->array[a->start + 1] == min)
	{
		write(1, "rra\n", 4);
		do_rotate(a);
	}
	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	if (a->array[a->start] > a->array[a->start + 1])
	{
		write(1, "sa\n", 3);
		do_swap(a);
	}
	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	write(1, "rra\n", 4);
	do_rrotate(a);
	if (!check_ascending_order(a->array, a->size - a->start, a->start))
	{
		write(1, "sa\n", 3);
		do_swap(a);
	}
}

void	stay_three_elem(t_stack *a, t_stack *b, int min, int max)
{
	int med;
	int j;
    
	med = find_med(a);
	j = 0;
	while (a->size - a->start != 3)//check to correct
	{
		if (a->array[a->start] == min || a->array[a->start] == max ||
			(a->array[a->start] < med && j < a->size))
		{
			write(1, "ra\n", 3);
			do_rotate(a);
		}
		else
		{
			write(1, "pb\n", 3);
			do_push(a, b);
		}
		j++;
	}
	sort_tree(a, min, max);
}