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
	write(1, "\n", 1);
}

int push_b_smallest(t_stack *from, t_stack *to, int size, int *to_find_med)//from a to b
{
	int i;
	int med;
	int push;

	ft_memcpy(to_find_med, from->array + from->start, size * 4);
	med = find_med(to_find_med, size);
	
	i = 0;
	push = 0;
	while (i < size)
	{
		if (from->array[from->start] < med)
		{
			write(1, "pb\n", 3);
			do_push(from, to);
			push++;
		}
		else
		{
			write(1, "ra\n", 3);
			do_rotate(from);
		}
		i++;
	}
	i = 0;
//	write(1, "after pb\n", 9);
//	write_stack(from, to);
	while (i < push)//первый раз не надо
	{
		write(1, "rb\n", 3);
		do_rotate(to);
		i++;
	}
//	write_stack(from, to);
	return (push);
}

int push_a_biggest(t_stack *from, t_stack *to, int size, int *to_find_med)
{
	int i;
	int med;
	int push;

	ft_memcpy(to_find_med, from->array + from->start, size * 4);
	med = find_med(to_find_med, size);
	i = 0;
	push = 0;
	while (i < size)
	{
		if (from->array[from->start] >= med)
		{
			write(1, "pa\n", 3);
			do_push(from, to);
			push++;
		}
		else
		{
			write (1, "rb\n", 3);
			do_rotate(from);
		}
		i++;
	}
//	write(1, "after pa\n", 9);
//	write_stack(to, from);
	i = 0;
	while (i < push)
	{

		write (1, "ra\n", 3);
		do_rotate(to);
		i++;
	}
//	write_stack(to, from);
	return (push);
}




void case3(t_stack *a, t_stack *b)
{
	int start;
	int flag;

	flag = 0;
	start = a->start;
	if (a->array[start] > a->array[start - 1] && a->array[start] > a->array[start - 2])
	{
		flag = 1;
		write(1, "pb\n", 3);
		do_push(a, b);
	}
	if (a->array[start] > a->array[start - 1])
	{
		write(1, "sa\n", 3);
		do_swap(a);
	}
	write(1, "ra\n", 3);
	write(1, "ra\n", 3);
	do_rotate(a);
	do_rotate(a);
	if (flag == 1)
	{
		write(1, "pa\n", 3);
		do_push(b, a);
	}
	else
	write(1, "ra\n", 3);
	do_rotate(a);
}

void merge(t_stack *a, t_stack *b, int *location_in_stacks, int i)
{
	int flag_stack;

	flag_stack = 2;
	if (location_in_stacks[i + 1] != 0)
		write(1, "error\n", 6);
	while (i >= 0)
	{
		if (flag_stack == 2)
		{
			if (location_in_stacks[i] == 2 )
			{
				if (b->array[b->start] > b->array[b->start - 1])
				{
					write(1, "sb\n", 3);
					do_swap(b);
				}
				write(1, "pa\n", 3);
				do_push(b, a);
				write(1, "pa\n", 3);
				do_push(b, a);
				write(1, "ra\n", 3);
				do_rotate(a);
				write(1, "ra\n", 3);
				do_rotate(a);
			}
			else
			{
				write(1, "pa\n", 3);
				do_push(b, a);
				write(1, "ra\n", 3);
				do_rotate(a);
			}
			flag_stack = 1;
		}
		else 
		{
			if (location_in_stacks[i]  == 3)
				case3(a, b);
			else if (location_in_stacks[i] == 2)
			{
				if (a->array[a->start] > a->array[a->start - 1])
				{
					write(1, "sa\n", 3);
					do_swap(a);
				}
				write(1, "ra\n", 3);
				do_rotate(a);
				write(1, "ra\n", 3);
				do_rotate(a);
			}
			flag_stack = 2;
		}
		i--;
		//write_stack(a, b);
	}
}

void sort(t_stack *a, t_stack *b)
{
	int *to_find_med;
	int *location_in_stacks;
	int size;
	int i;
	int flag_stack;
	int push;

	size = a->size;
	to_find_med = ft_memalloc(sizeof(int)* size);
	location_in_stacks = ft_memalloc(sizeof(int) * size);
	location_in_stacks[0] = size;
	i = 0;
	flag_stack = 1;
	while (location_in_stacks[i] > 2)
	{
		if (location_in_stacks[i] > 2)
		{
			if (flag_stack == 1)
			{
				push = push_b_smallest(a, b, location_in_stacks[i], to_find_med);//end?? 
				i = change_location(location_in_stacks, i, location_in_stacks[i] - push, push);
				flag_stack = 2;
				//write_array(location_in_stacks);
			}
			else
			{
				push = push_a_biggest(b, a, location_in_stacks[i], to_find_med);//end?? 
				i = change_location(location_in_stacks, i, push, location_in_stacks[i] - push);
				flag_stack = 1;
				//write_array(location_in_stacks);
			}
		}
		/*else if (location_in_stacks[i] == 2)
		{
			write(1, "loc2\n", 5);
			if (flag_stack == 1)
			{
				if (a->array[a->start] > a->array[a->start - 1])
				{
					write(1, "sa\n", 3);
					do_swap(a);
				}
				write (1, "ra\n", 3);
				write (1, "ra\n", 3);
				do_rotate(a);
				do_rotate(a);
				flag_stack = 2;
			}
			else 
			{
				if (b->array[b->start] > b->array[b->start - 1])
				{
					write(1, "sb\n", 3);
					do_swap(b);
				}
				write (1, "rb\n", 3);
				write (1, "rb\n", 3);
				do_rotate(b);
				do_rotate(b);
				flag_stack = 1;
			}
			//write_stack(a, b);
			i--;
		}
		else if (location_in_stacks[i] == 1)
		{
			write(1, "loc1\n", 5);
			if (flag_stack == 1)
			{
				write (1, "ra\n", 3);
				do_rotate(a);
				flag_stack = 2;
			}
			else
			{
				write (1, "rb\n", 3);
				do_rotate(b);
			}
			i--;
		}
		else 
		{
			write(1, "error\n", 6);
			break;
		}
		
	}
	*/
	}
	//write_stack(a, b);
	merge(a, b, location_in_stacks, i);
	//write_stack(a, b);
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
	write_stack(a, b);
	return (0);
}