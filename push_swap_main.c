#include "push_swap.h"
#include "libft.h"

void rotate_stack(t_stack *a, int min)
{
	int i;
	int rr_flag;

	rr_flag = 0;
	i = 0;
	while (a->array[i] != min)
		i++;
	if (i > a->size - i)
	{
		i = a->size - i;
		rr_flag = 1;
	}
	while (--i > -1)
	{
		if (rr_flag)
		{
			write(1, "rra\n", 4);
			do_rrotate(a);
		}
		else
		{
			write(1, "ra\n", 3);
			do_rotate(a);
		}
	}
}

void take_extrem(t_stack *stack, int *max, int *min)
{
	int i;

	i = stack->start;
	*max = stack->array[i];
	*min = stack->array[i];
	while (i < stack->size)
	{
		if (stack->array[i] > *max)
			*max = stack->array[i];
		if (stack->array[i] < *min)
			*min = stack->array[i];
		i++;
	}
}

void	sort(t_stack *a, t_stack *b)
{
	int *tmp;
	t_costelem cost;
	int max;
	int min;

	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	if (!(tmp = ft_memalloc(sizeof(int) * a->size)))
		return ;
	take_extrem(a, &max, &min);	
	if (a->size > 2)
		stay_three_elem(a, b, min, max);
    while (a->start != 0)
	{
		cost = take_min_cost(a, b);
		move_to_place(a, b, cost);
	}
	rotate_stack(a, min);
	free(tmp);
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i; 

	if (argc == 1)
		return (0);
	if (argc == 2)
		split_case(argv[1], &a);
	else
	{
		create_stack(argc - 1, 0, &a);
		i = -1;
		while (++i < argc - 1)
			a->array[i] = ft_atoi_check(argv[i + 1]);
	}
	check_uniq(a);
	create_stack(a->size , a->size, &b);
	sort(a, b);
	free_stacks(a, b);
	return (0);
}