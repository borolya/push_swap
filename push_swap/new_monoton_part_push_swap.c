#include "libft.h"
#include "checker.h"
#include <stdio.h>

void write_array(int *array)
{
	int i;

	i = 0;
	printf("array =  ");
	while (array[i] != 0)
	{
		printf("%d ", array[i]);
		i++;
	}
	printf("\n");
}

void full_zero(int *array, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		array[i] = 0;
		i++;
	}
}

int take_monoton(t_stack *stack, int *mon_section, int size)
{
	int increas;
	int discreas;
	int i;
	int i_ms;

	full_zero(mon_section, size);
	i = stack->start;
	increas = 1;
	discreas = 1;
	i_ms = 0;
	while (i + 1 < stack->size)
	{
		if (stack->array[i] < stack->array[i + 1] && increas > 0)
		{
			increas++;
			discreas = 0;
		}
		else if (stack->array[i] > stack->array[i + 1] && discreas > 0)
		{
			increas = 0;
			discreas++;
		}
		else
		{
			mon_section[i_ms] = discreas > 1 ? -discreas : increas;
			i_ms++;
			discreas = 1;
			increas = 1;
		}
		i++;
	}
	mon_section[i_ms] = discreas > increas ? -discreas : increas;

	return (i_ms + 1);
}

void merge_increasing_and_increasing(t_stack *a, t_stack *b, int *a_mon, int *b_mon, int size)
{
	int i_mon;
	//int size_mon;
	int b_size;
	int a_size;

	a_size = take_monoton(a, a_mon, size);
	b_size = take_monoton(b, b_mon, size);
	i_mon = 0;
	
	write_array(a_mon);
	write_array(b_mon);
	/*
	while (i_mon < a_size && i_mon < b_size)
	{
		while(a_mon[i_mon] != 0 || b_mon[i_mon] != 0)
		{
			if ((b->start != b->size) && b_mon[i_mon] != 0 && (a->start == a->size || b->array[b->start] < a->array[a->start] || a_mon[i_mon] == 0))
			{
				write(1, "pa\n", 3);
				do_push(b, a);
				a_mon[i_mon]++;
				b_mon[i_mon]--;
			}
			else
			{
				write(1, "ra\n", 3);
				do_rotate(a);
				a_mon[i_mon]--;
			}
			write_stack(a, b);
			write_array(a_mon);
			write_array(b_mon);
		}
		i_mon++;
	}
	while (a_mon[i_mon] > 0)
	{
		write(1, "ra\n", 3);
		do_rotate(a);
		a_mon[i_mon]--;
	}
	*/
}

void merge_increasing_and_discresing(t_stack *a, t_stack *b, int *a_mon, int *b_mon, int size)
{
	int i_mon;
	int size_mon;
	int a_i_mon;

	a_i_mon = take_monoton(a, a_mon, size) - 1;
	size_mon = take_monoton(b, b_mon, size);
	i_mon = 0;
	///write_array(a_mon);
	//write_array(b_mon);
	while (i_mon < size_mon && a_i_mon >= 0)//a_mon = 0
	{
		take_monoton(a, a_mon, size);
		if (a_mon[1] == 0 && (b->start == b->size))
			return ;
		while (a_mon[a_i_mon] != 0 || b_mon[i_mon] != 0)
		{
			if ((b->start != b->size) && b_mon[i_mon] != 0 && (b->array[b->start] > a->array[a->size - 1] || a_mon[a_i_mon] == 0))
			{
				write(1, "pa\n", 3);
				do_push(b, a);
				b_mon[i_mon]++;
			}
			else
			{
				write(1, "rra\n", 4);
				do_rrotate(a);
				a_mon[a_i_mon]--;
			}
		//	write_stack(a, b);
		//	write_array(a_mon);
		//	write_array(b_mon);
		}
		i_mon++;
		a_i_mon--;
	}
	while (a_mon[i_mon] > 0 && i_mon < size_mon)
	{
		write(1, "rra\n", 4);
		do_rrotate(a);
		a_mon[i_mon]--;
	}
}

void sort(t_stack *a, t_stack *b)
{
	int *a_mon_sections;
	int *b_mon_sections;
	int size;
	int i;
	int i_ms;
	int size_ms;

	if (b->start != b->size)
		return ;
	if (check_ascending_order(a->array, a->size - a->start, a->start))
		return ;
	size = a->size;
	a_mon_sections = ft_memalloc(sizeof(int) * size);
	b_mon_sections = ft_memalloc(sizeof(int) * size);
	take_monoton(a, a_mon_sections, size);
	i = a->start;
	i_ms = 0;
	write_array(a_mon_sections);
	while (i < a->size)
	{
		if (a_mon_sections[i_ms] == 0)
				i_ms++;
		if (a_mon_sections[i_ms] < 0)
		{
			write(1, "pb\n", 3);
			do_push(a, b);
			a_mon_sections[i_ms]++;
		}
		else if (a_mon_sections[i_ms] > 0)
		{
			write(1, "ra\n", 3);
			do_rotate(a);
			a_mon_sections[i_ms]--;
		}
		i++;
	}
	merge_increasing_and_increasing(a, b, a_mon_sections, b_mon_sections, size);
	write_stack(a, b);
	while (a->start != 0 || !check_ascending_order(a->array, a->size - a->start, a->start))
	{
		size_ms = take_monoton(a, a_mon_sections, size);
		write_array(a_mon_sections);
		if (a_mon_sections[1] == 0)
			break;
		i_ms = 0;
		i = a->start;
		while (i_ms < size_ms / 2)
		{
			if (a_mon_sections[i_ms] == 0)
				i_ms++;
			else if (a_mon_sections[i_ms] > 0)
			{
				write(1, "pb\n", 3);
				do_push(a, b);
				a_mon_sections[i_ms]--;
			}
			i++;
		}
		write_stack(a, b);
		merge_increasing_and_discresing(a, b, a_mon_sections, b_mon_sections, size);
		write_stack(a, b);
	}
	
}


int main(int argc, char **argv)
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
	//change_to_number
	sort(a, b);
	//write_stack(a, b);
	return (0);
}