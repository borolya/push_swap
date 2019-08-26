/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:23:40 by bharmund          #+#    #+#             */
/*   Updated: 2019/08/26 15:23:51 by bharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "libft.h"

void do_rotation_ss_instructions(t_stack *a, t_stack *b, char *str)
{
	if (ft_strequ(str, "ra"))
		do_rotate(a);
	else if (ft_strequ(str, "rb"))
		do_rotate(b);
	else if (ft_strequ(str, "rr"))
	{	
		do_rotate(a);
		do_rotate(b);
	}
	else if (ft_strequ(str, "rra"))
		do_rrotate(a);
	else if (ft_strequ(str, "rrb"))
		do_rrotate(b);
	else if (ft_strequ(str, "rrr"))
	{
		do_rrotate(a);
		do_rrotate(b);
	}
	else if (ft_strequ(str, "ss"))
	{
		do_swap(a);
		do_swap(b);
	}
}

void do_instructions(t_stack *a, t_stack *b)
{
	char *str;

	while (get_next_line(0, &str))
	{
		if (ft_strequ(str, "sa"))
			do_swap(a);
		else if (ft_strequ(str, "sb"))
			do_swap(b);	
		else if (ft_strequ(str, "pa"))
			do_push(b, a);
		else if (ft_strequ(str, "pb"))
			do_push(a, b);
		else if (ft_strequ(str, "ra") || ft_strequ(str, "rb") ||
				ft_strequ(str, "rrr") || ft_strequ(str, "rr") ||
				ft_strequ(str, "rra") || ft_strequ(str, "rrb") ||
				ft_strequ(str, "ss"))
			do_rotation_ss_instructions(a, b, str);
		else
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		free(str);
	}
}



int main(int argc, char **argv)
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
	create_stack(a->size, a->size, &b);
	i = 0;
	do_instructions(a, b);
	if (a->start != 0 || !check_ascending_order(a->array, a->size, a->start))
		write(1, "KO\n", 3);
	else 
		write(1, "OK\n", 3);
	free_stacks(a, b);
	return (0);
}
