#include "libft.h"
#include "checker.h"
#include <stdio.h>

void	take_location(t_stack *stack, int *tmp)
{
	int now;
	int pr;
	int i;
	int j;
	int save_j;

	//pr = -2147483648;
	now = stack->array[0];
	j = 0;
	while (j < stack->size)
	{
		if (stack->array[j] < now)
		{
			now = stack->array[j];
			tmp[j] = 0;
		}
		j++;
	}
	i = 1;
	pr = now;
	while (++i < stack->size)
	{
		j = 0;
		save_j = 0;
		now = stack->array[0];
		while (j < stack->size)
		{
			if (stack->array[j] > pr && stack->array[j] < now)
			{
				now = stack->array[j];
				save_j = j;
			}
			j++;
		}
		tmp[save_j] = i;
		pr = now;
		i++;
	}
	ft_memcpy(stack->array, tmp, stack->size * 4);
}

void sort_tree(t_stack *a)
{
	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	if (a->array[a->start] == a->size -1 && a->array[a->start + 1] == 0)
	{
		write(1, "rra\n", 3);
		do_rotate(a);
	}
	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	if (a->array[a->start] > a->array[a->start + 1])
	{
		write(1, "sa\n", 3);
		do_swap(a);
	}
	write(1, "rra\n", 4);
	do_rrotate(a);
	if (!check_ascending_order(a->array, a->size - a->start, a->start))
	{
		write(1, "sa\n", 3);
		do_swap(a);
	}
}

void	stay_three_elem(t_stack *a, t_stack *b)
{
	int i;

	i = 0;
	while (a->size - a->start != 3)
	{
		if (a->array[a->start] == 0 || a->array[a->start] == a->size - 1)
		{
			write(1, "ra\n", 3);
			do_rotate(a);
		}
		else
		{
			write(1, "pb\n", 3);
			do_push(a, b);
		}
	}
	sort_tree(a);
}

int	search_own_place(t_stack *a, int nbr)
{
	int j;
	
	j = a->start;
	while (j < a->size - 1)
	{
		if (a->array[j] < nbr && nbr < a->array[j + 1])
			return (a->start - j + 1);
		j++;
	}
	return (0);
}

void ft_choose_rotates(t_costelem *elem)
{
	int max;
	
	elem->flag = RARB;
	elem->cost = elem->ra > elem->ra ? elem->ra : elem->rb;
	if (elem->cost > elem->rra + elem->rb)
	{
		elem->cost = elem->rra + elem->rb;
		elem->flag = RRARB;
	}
	if (elem->cost > elem->ra + elem->rrb)
	{
		elem->cost = elem->ra + elem->rrb;
		elem->flag = RARRB;
	}
	max = elem->rra > elem->rrb ? elem->rra : elem->rrb;
	if (elem->cost > max)
	{
		elem->cost = max;
		elem->flag = RRARRB;
	}
}

t_costelem	take_min_cost(t_stack *a, t_stack *b)
{
	t_costelem cost;
	t_costelem min_cost;
	int i;

	i = b->start;
	min_cost.rb = i - b->start;
	min_cost.rrb = b->size - i;
	min_cost.index = i;
	min_cost.ra = search_own_place(a, b->array[i]);
	min_cost.rra = min_cost.ra == 0 ? 0 : a->size - a->start - min_cost.ra;
	ft_choose_rotates(&min_cost);
	while (++i < b->size)
	{
		cost.rb = i - b->start;
		cost.rrb = b->size - i;	
		cost.ra = search_own_place(a, b->array[i]);
		cost.rra = cost.ra == 0 ? 0 : a->size - a->start - cost.ra;
		cost.index = i;
		ft_choose_rotates(&cost);
		if (min_cost.cost > cost.cost)
			min_cost = cost;
	}
	return (min_cost);
}

void move_to_place(t_stack *a, t_stack *b, t_costelem cost)
{
	if (cost.flag == RARB)
	{
		while (cost.ra > 0 && cost.rb > 0)
		{
			write(1, "rr\n", 3);
			do_rotate(a);
			do_rotate(b);
			cost.ra--;
			cost.rb--;
		}
		while (cost.ra > 0 || cost.rb > 0)
		{
			if (cost.ra > 0)
			{
				write(1, "ra\n", 3);
				do_rotate(a);
				cost.ra--;
			}
			else 
			{
				write(1, "rb\n", 3);
				do_rotate(b);
				cost.rb--;
			}
		}
	}
	else if (cost.flag == RRARRB)
	{
		while (cost.rra > 0 && cost.rrb > 0)
		{
			write(1, "rrr\n", 3);
			do_rrotate(a);
			do_rrotate(b);
			cost.rra--;
			cost.rrb--;
		}
		while (cost.rra > 0 || cost.rrb > 0)
		{
			if (cost.rra > 0)
			{
				write(1, "rra\n", 3);
				do_rrotate(a);
				cost.rra--;
			}
			else 
			{
				write(1, "rrb\n", 3);
				do_rrotate(b);
				cost.rrb--;
			}
		}
	}
	else if (cost.flag == RRARB)
	{
		while (cost.rra > 0)
		{
			write(1, "rra\n", 4);
			do_rrotate(a);
			cost.rra--;
		}
		while (cost.rb > 0)
		{
			write(1, "rb\n", 3);
			do_rotate(b);
			cost.rb--;
		}
	}
	else if (cost.flag == RARRB)
	{
		while (cost.ra > 0)
		{
			write(1, "ra\n", 3);
			do_rotate(a);
			cost.ra--;
		}
		while (cost.rrb > 0)
		{
			write(1, "rrb\n", 4);
			do_rrotate(b);
			cost.rrb--;
		}
	}
}

void rotate_stack(t_stack *a)
{
	int i;
	int rr_flag;

	rr_flag = 0;
	i = 0;//a->start = 0;
	while (a->array[i] != 0)
		i++;
	if (i < a->size - i)
	{
		i = a->size - i;
		rr_flag = 1;
	}
	if (rr_flag == 1)
	{
		while (i > 0)
		{
			write(1, "rra\n", 4);
			do_rrotate(a);
			i++;
		}
	}
	else
	{
		while (i > 0)
		{
			write(1, "ra\n", 3);
			do_rotate(a);
			i++;
		}
	}
}

void	sort(t_stack *a, t_stack *b)
{
	int *tmp;
	//t_costelem cost;

	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	tmp = ft_memalloc(sizeof(int) * a->size);
	take_location(a, tmp);
	
	write_stack(a, b);
	/*
	if (a->size > 2)
		stay_three_elem(a, b);
	while (a->start != 0)
	{
		cost = take_min_cost(a, b);
		move_to_place(a, b, cost);
	}
	rotate_stack(a);
*/
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;

	if (argc == 1)
		return (0);
	create_stack(argc - 1, 0, &a);
	i = -1;
	while (++i < argc - 1)
		a->array[i] = ft_atoi_check(argv[i + 1]);
	check_uniq(a);
	create_stack(argc - 1, argc - 1, &b);
	sort(a, b);
	write_stack(a, b);
	return (0);
}