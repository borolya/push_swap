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

int check_decreasing_order(int *array, int size, int start)
{
	int i;

	i = 0;
	while (i < size - 1)
	{
		if (array[i + start] <= array[i + start + 1])
				return (0);
		i++;
	}
	return (1);
}

int	find_med(int *array, int size)//not index// mb faster
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < size -  1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
		//    printf("arrai[j]= %d array[j + 1] = %d\n", array[j], array[j+ 1]);
			if (array[j] > array[j + 1])
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
   // printf("ret = %d\n", size / 2 - 1);
	return (array[size / 2]);
}

int change_location(int *locations_in_stacks, int change_index, int a, int b)
{
	int i;
	int end;

	i = change_index;
	while (locations_in_stacks[i] != 0)
		i++;
	end = i;
	while (i > change_index + 1)
	{
		locations_in_stacks[i] = locations_in_stacks[i - 1];
		i--;
	}
	locations_in_stacks[i--] = b;
	locations_in_stacks[i] = a;
	if (change_index == 0)
		return (end);
	return (change_index - 1);
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
	return (push);
}

int push_b_biggest(t_stack *from, t_stack *to, int size, int *to_find_med)
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
			write(1, "pb\n", 3);
			do_push(from, to);
			push++;
		}
		else
		{
			write (1, "ra\n", 3);
			do_rotate(from);
		}
		i++;
	}
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
	return (push);
}
void rotate(int *location_in_stacks, int i)
{
	int tmp;
	int j;

	j = i;
	tmp = location_in_stacks[i];
	while (j > 0)
	{
		location_in_stacks[j] = location_in_stacks[j - 1];
		j--;
	}
	location_in_stacks[0] = tmp;
}

void sort(t_stack *a, t_stack *b)
{
	int		*to_find_med;
	int		*location_in_stacks;
	int		size;
	int		i;
	int 	j;
	int count;
	int count_end;

	
	if (check_ascending_order(a->array, a->size, a->start))
		return;
	size = a->size;
	to_find_med = ft_memalloc(sizeof(int)* size);
	location_in_stacks = ft_memalloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		location_in_stacks[i] = 0;
		i++;
	}
	
	location_in_stacks[0] = size;
	
	size = push_b_smallest(a, b, size, to_find_med);
	location_in_stacks[0] -= size;
	location_in_stacks[1] = 0;
	i = 0;
	write_array(location_in_stacks);
	while (!check_decreasing_order(b->array, b->size - b->start, b->start))
	{
		size = push_a_biggest(b, a,  b->size - b->start, to_find_med);//chose rb or rrb
		//change_location(location_in_stacks, i, location_in_stacks[i] - size, size);
		location_in_stacks[i + 1] = size;
		i++;
		write_stack(a, b);
		write_array(location_in_stacks);
	}
	j = 0;
	while (b->start != b->size)
	{
		write(1, "pa\n", 3);
		do_push(b, a);
		j++;
	}
		//change_location(location_in_stacks, i, location_in_stacks[i], j);
	location_in_stacks[i + 1] = j;
	write_stack(a, b);
	write_array(location_in_stacks);
	i++;



	count = 0;
	count_end = size + 100;
	while((a->start != 0 || !check_ascending_order(a->array, a->size - a->start, a->start)))//i  = 0;
	{
		count++;
		//write(1, "in case\n", 8);
		//write_stack(a, b);
		if (check_ascending_order(a->array, location_in_stacks[i], a->start))
		{
			write(1, "case1\n", 6);
			j = 0;
			while (j < location_in_stacks[i])
			{
				write(1, "ra\n", 3);
				do_rotate(a);
				j++;
			}
			rotate(location_in_stacks, i);
			printf("i = %d\n", i);
			write_stack(a, b);
			write_array(location_in_stacks);
		}
		else
		{
			write(1, "case2\n", 6);
			size = push_b_biggest(a, b, location_in_stacks[i], to_find_med);
			location_in_stacks[i] -= size;
			write_array(location_in_stacks);
			write_stack(a, b);
			while (!check_decreasing_order(b->array, b->size - b->start, b->start))
			{
				size = push_a_biggest(b, a,  b->size - b->start, to_find_med);//chose rb or rrb
				//change_location(location_in_stacks, i, location_in_stacks[i], size);
				location_in_stacks[i + 1] = size;
				i++;
				write_stack(a, b);
				write_array(location_in_stacks);
			}
			j = 0;
			while (b->start != b->size)
			{
				write(1, "pa\n", 3);
				do_push(b, a);
				j++;
			}
			//change_location(location_in_stacks, i, location_in_stacks[i], j);
			i++;
			printf("i = %d\n", i);
			location_in_stacks[i] = j;
			write_stack(a, b);
			write_array(location_in_stacks);
		}
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
	write_stack(a, b);
	return (0);
}