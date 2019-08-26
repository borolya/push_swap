#include "push_swap.h"
#include "libft.h"
static void    ft_choose_rotates(t_costelem *elem)
{
	int max;
	
	elem->flag = RARB;
	elem->cost = elem->ra > elem->rb ? elem->ra : elem->rb;
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

static int search_own_place(t_stack *a, int nbr)
{
	int j;
	
	j = a->start;
	while (j < a->size - 1)
	{
		if (a->array[j] < nbr && nbr < a->array[j + 1])
			return (j - a->start + 1);
		j++;
	}
	return (0);
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