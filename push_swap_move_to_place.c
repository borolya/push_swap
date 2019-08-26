#include "libft.h"
#include "push_swap.h"

void rarb(t_stack *a, t_stack *b, t_costelem cost)
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

void rrarrb(t_stack *a, t_stack *b, t_costelem cost)
{
	while (cost.rra > 0 && cost.rrb > 0)
	{
		write(1, "rrr\n", 4);
		do_rrotate(a);
		do_rrotate(b);
		cost.rra--;
		cost.rrb--;
	}
	while (cost.rra > 0 || cost.rrb > 0)
	{
		if (cost.rra > 0)
		{
			write(1, "rra\n", 4);
			do_rrotate(a);
			cost.rra--;
		}
		else 
		{
			write(1, "rrb\n", 4);
			do_rrotate(b);
			cost.rrb--;
		}
	}
}

void rrarb(t_stack *a, t_stack *b, t_costelem cost)
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

void move_to_place(t_stack *a, t_stack *b, t_costelem cost)
{
	if (cost.flag == RARB)
		rarb(a, b, cost);
	else if (cost.flag == RRARRB)
		rrarrb(a, b, cost);
	else if (cost.flag == RRARB)
		rrarb(a, b, cost);
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
	write(1, "pa\n", 3);
	do_push(b, a);
}