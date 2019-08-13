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

void push_half_of_big(t_stack *from, t_stack *to, int size, int *tmp)
{
	int i;
	int m_med;

	//write(1, "big\n", 4);
	ft_memcpy(tmp, from->array + from->size - size, size * 4);
	i = 0;
	m_med = find_med(tmp, size);
   // printf("med = %d\n", m_med);
 	i = 0;
	while (i < size)
	{
		write (1, "rrb\n", 4);
		do_rrotate   (from);
		if (from->array[from->start] >= m_med)
		{
			write(1, "pa\n", 3);
			do_push(from, to);
		}
		i++;
	}
}

void push_half_of_small(t_stack *from, t_stack *to, int size, int *tmp)
{
	int i;
	int m_med;

	//write(1, "small\n", 6);
	ft_memcpy(tmp, from->array + from->size - size, size * 4);
	m_med = find_med(tmp, size);
   // printf("med = %d\n", m_med);
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
	int l_mediana;
	int iter;
	int count_numb;
	int *tmp;
	int i;

	size = a->size;
	count_numb = size;
	l_mediana = size / 2;
	i = a->start;
	tmp = ft_memalloc(sizeof(int) * a->size);
	while (i < size)
	{
		if (a->array[a->start] <= l_mediana) 
		{
			write(1, "pb\n", 3);
			do_push(a, b);
		}
		else
		{
			write (1, "ra\n", 3);
			do_rotate(a);
		}
		i++;
	}
	size = size / 2;
	//write_stack(a, b);
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