/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharmund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:07:34 by bharmund          #+#    #+#             */
/*   Updated: 2019/08/09 16:14:54 by bharmund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ft_atoi_check(char *str)//spase simbols?
{
	int nbr;
	int i;
	int len;

	i = ft_strlen(str);
	while (--i > 0)
	{
		if (str[i] > '9' || str[i] < '0')
			{
				ft_putstr("Error");
				exit(1);
			}
		else if (nbr <= nbr * 10 + str[i] - '0')
		{
			ft_putstr("Error");
			exit(1);
		}
		else
			nbr = nbr * 10 + (str[i] - '0');
	}
	if (str[i] == '-')//-
	+
}

void do_push(long int *from, long int *to)
{

}

int main(int argc, char **argv)
{
	long int	*a_stack;
	long int	*b_stack;
	int			i;
	char		*str;

	if (argc == 1)
		return (0);
	if (!(a_stack = ft_memalloc(sizeof(long int) * (argc - 1))))
		exit(1);
	i = -1;
	while(++i < argc - 1)
		a_stack[i] = ft_atoi_chaeck(argv[i]);
	check_uniq(a_stack);
	if (!(b_stack = ft_memalloc(sizeof(long int) * (argc - 1))))
		exit(1);
	while (get_next_line(0, &str))
	{
		if (ft_strequ(str, "sa"))
			do_swap(a_stack);
		else if (ft_strequ(str, "sb"))
			do_swap(b_stack);	
		else if (ft_strequ(str, "ss"))
		{
			do_swap(a_stack);
			do_swap(b_stack);
		}
		else if (ft_strequ(str, "pa"))
			do_push(b_stack, a_stack);
		else if (ft_strequ(str, "pb"))
			do_push(a_stack, b_stack);
		else if (ft_strequ(str, "ra"))
			do_rotate(a_stack);
		else if (ft_strequ(str, "rb"))
			do_rotate(b_stack);
		else if (ft_strequ(str, "rr"))
			{
				do_rotate(a_stack);
				do_rotate(b_stack);
			}
		else if (ft_strequ(str, "rra"))
			do_rrotate(a_stack);
		else if (ft_strequ(str, "rrb"))
			do_rrotate(b_stack);
		else if (ft_strequ(str, "rrr"))
		{
			do_rrotate(a_stack);
			do_rratate(b_stack);
		}
		else
		{
			ft_putstr("Error");
			exit(1);
		}
	}
	check_ascending_order(a_stack);
	return (0);
}
