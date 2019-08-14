#include "libft.h"
#include "checker.h"
/*
void merge(t_stack *a, t_stack *b)
{
	int a_max;
	int b_max;
	int i;
	

}
*/
#include <stdio.h>

int	find_med(int *array, int size)//not index// mb faster
{
	int i;
	int j;
	int tmp;
	int k;

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

void push_half_of_big(t_stack *from, t_stack *to, int size, int *tmp, int *array_location, int *k1, int *k2)
{
	int i;
	int m_med;
	int push_count;
	//write(1, "big\n", 4);
	ft_memcpy(tmp, from->array + from->size - size, size * 4);
	i = 0;
	m_med = find_med(tmp, size);
   // printf("med = %d\n", m_med);
 	i = 0;
	push_count = 0;
	while (i < size)
	{
		
		if (from->array[from->start] >= m_med)
		{
			write(1, "pa\n", 3);
			do_push(from, to);
			push_count++;
			*k1++;
			array_location[*k1] = 1;
			*k2--;
		}
		else
		{
			write (1, "rb\n", 3);
			do_rotate(from);
			*k2--;
		}
		i++;
	}

	if (*k2 < 0)
		*k2 = size - 1;
	while (array_location[*k2] != 2)
	{
		*k2--;
		if (*k2 < 0)
			*k2 = size - 1;
	}
	while (push_count > 0)
	{
		write (1, "ra\n", 3);
		do_rotate(to);
		push_count--;
		*k1--;
	}
	if (*k1 < 0)
		*k1 = size - 1;
	while (array_location[*k1] != 1)
	{
		*k1--;
		if (*k1 < 0)
			*k1 = size - 1;
	}
}

void push_half_of_small(t_stack *from, t_stack *to, int size, int *tmp)
{
	int i;
	int m_med;

	//write(1, "small\n", 6);
	ft_memcpy(tmp, from->array + from->size - size, size * 4);
	m_med = find_med(tmp, size);
	//printf("med = %d\n", m_med);
	i = 0;
	while (i < size)
	{
		write (1, "rra\n", 4);
			do_rrotate(from);
		if (from->array[from->start] < m_med)
		{
			write(1, "pb\n", 3);
			do_push(from, to);
		}
		i++;
	}
}

void sort(t_stack *a, t_stack *b)//begin for deg 2 and massiv  [1 , a_size]
{
	int size;
	int l_med;
	int iter;
	int count_numb;
	int *tmp;
	int i;
	int *array_location;
	int k1;
	int k2;
	int count_push;
   
	size = a->size;
	array_location = ft_memalloc(sizeof(int) * size);
	count_numb = size;

	tmp = ft_memalloc(sizeof(int) * a->size);
	ft_memcpy(tmp, a->array, a->size * 4);
	l_med = find_med(tmp,size);
	
	i = a->start;
	count_push = 0;
	while (i < size)
	{
		if (a->array[a->start] <= l_med) 
		{
			write(1, "pb\n", 3);
			do_push(a, b);
			count_push++;
		}
		else
		{
			write (1, "ra\n", 3);
			do_rotate(a);
		}
		i++;
	}
	i = -1;
	while (++i < size - count_push)
		array_location[i] = 1;
	while (i < size)
	{
		array_location[i] = 2;
		i++;
	}
	//size = size / 2;
	k1 = count_push - size - 1;
	k2 = size - 1;

	if (k2 > k1)
	{
		push_half_of_big(b, a, k2 - k1, tmp, array_location, &k1, &k2);

	}






	while (size > 2)
	{
		iter = (count_numb / 2) / size;
		while (--iter >= 0)
		{
			push_half_of_small(a, b, size, tmp);
			i = 0;
			//write_stack(a, b);
			while (i < size)
			{
				do_rrotate(b);
				write(1, "rrb\n", 4);
				i++;
			}
			//write_stack(a, b);
		}
	//	i = 0;
	/*
		while (i < size / 2)
		{
			do_rrotate(a);
			write(1, "rra\n", 4);
			i++;s
		}
	*/
		iter = (count_numb / 2) / size;
		while (--iter >= 0)
		{
			i = 0;
			while (i < size / 2)
			{
				do_rrotate(a);
				do_rrotate(b);
				write(1, "rrr\n", 4);
				i++;
			}
			//write_stack(a, b);
			push_half_of_big(b, a, size, tmp);
			//write_stack(a, b);
		}
		//push_half_of_big(b, a, size, tmp);
		size = size / 2;
		//write_stack(a, b);
	}
	write_stack(a, b);
	//merge(a, b);
}


int main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		i;
	char	*str;

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
	return (0);
}