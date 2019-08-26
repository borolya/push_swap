#include "common.h"
#include "libft.h"

void write_stack(t_stack *a, t_stack *b)
{
	int i;

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
}

void split_case(char *str, t_stack **a)//if free arg?
{
	char **split;
	int i;
	
	split = ft_strsplit(str, ' ');
	i = 0;
	while (split[i])
		i++;
	create_stack(i, 0, a);
	i = 0;
	while (split[i])
	{
		(*a)->array[i] = ft_atoi_check(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}

void free_stacks(t_stack *a, t_stack *b)
{
	free(a->array);
	free(b->array);
	free(a);
	free(b);
}

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
}

void create_stack(int size, int start, t_stack **stack)
{
	*stack = ft_memalloc(sizeof(t_stack));
	if (stack == NULL)
		exit (1);
	(*stack)->array = ft_memalloc(sizeof(int) * size);
	if ((*stack)->array == NULL)
		exit (1);
	(*stack)->size = size;
	(*stack)->start = start;
}

static int take_nbr(const char *str, int sign)
{
	int nbr;
	int i;

	nbr = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0' || 
		(nbr == sign * 214748364 && ((sign == -1 && str[i] > '8') ||
						(sign == 1 && str[i] > '7'))))
		{
			ft_putstr("Error\n");
			exit(1);
		}
		nbr = nbr * 10 + sign * (str[i] - '0');
		i++;
	}
	if (i == 0)
	{
		ft_putstr("Error\n");
		exit(1);
	}
	return (nbr);
}

int ft_atoi_check(const char *str)//spase simbols?
{
	int sign;

	sign = 1;
	if (*str == '+')
		str++;//else ? +-?? -+?? norm?
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	return (take_nbr(str, sign));
}


