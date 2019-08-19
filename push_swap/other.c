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
#include "checker.h"

#include <stdio.h>

int check_ascending_order(int *array, int size, int start)
{
	int i;

	i = 0;
	while (i < size - 1)
	{
		if (array[i + start] >= array[i + start + 1])
				return (0);
		i++;
	}
	return (1);
}

int ft_atoi_check(const char *str)//spase simbols?
{
	int nbr;
	int i;
	int sign;

	sign = 1;
	if (*str == '+')
		str++;//else ? +-?? -+?? norm?
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	nbr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
		{
			ft_putstr("Error");
			exit(1);
		}
		if (nbr == sign * 214748364 && ((sign == -1 && str[i] > '8') || (sign == 1 && str[i] > '7'))) 
		{
			ft_putstr("Error");
			exit(1);
		}
		nbr = nbr * 10 + sign * (str[i] - '0');
		i++;
	}
	if (i == 0)
	{
		ft_putstr("Error");
		exit(1);
	}
	//printf("nbr = %d\n", nbr);
	return (nbr);
}

void write_stack(t_stack *a, t_stack *b)
{
	int i;
    ft_putstr("\n");
	ft_putstr("a ");
	i = a->start;
	while (i < a->size)
	{
		ft_putstr(ft_itoa(a->array[i]));
		ft_putstr(" ");
		i++;
	}
	ft_putstr("\nb ");
	i = b->start;
	while (i < b->size)
	{
		ft_putstr(ft_itoa(b->array[i]));
		ft_putstr(" ");
		i++;
	}
    ft_putstr("\n");
	ft_putstr("\n");
}

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

void check_uniq(t_stack *stack)//may be to order
{
	int i;
	int j;

	i = stack->start;
	while(i < stack->size)
	{
		j = i;
		while (++j < stack->size)
		{
			if (stack->array[i] == stack->array[j])
			{
				ft_putstr("Error\n");
				exit(1);
			}
		}
		i++;
	}
	//ft_putstr("all_correct\n");
}

void free_stack(t_stack *stack)
{
	free(stack->array);
	free(stack);
}

void create_stack(int size, int start, t_stack **stack)
{
	*stack = ft_memalloc(sizeof(t_stack));
	if (stack == NULL)
		exit(1);
	(*stack)->array = ft_memalloc(sizeof(int) * size);
	if ((*stack)->array == NULL)
		exit (1);
	(*stack)->size = size;
	(*stack)->start = start;
}




