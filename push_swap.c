#include "libft.h"
#include "checker.h"

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
		if (a->array[i] > l_mediana) 
		{
			write(1, "pb\n", 3);
			do_push(a, b);
		}
		i++;
	}
	size = size / 2;

	while (size > 2)
	{
		iter = (count_numb / 2) / size;
		while (--iter >= 0)
		{
			push_half_of_small(a, b, size, tmp);
			i = 0;
			while (i < size)
			{
				rotate(b);
				write(1, "rb\n", 3);
				i++;
			}
		}
		i = 0;
		while (i < size / 2)
		{
			rotate(a);
			write(1, "ra\n", 3);
			i++;
		}
		iter = (count_numb / 2) / size;
		while (--iter > 0)
		{
			push_half_of_big(b, a, size, tmp);
			i = 0;
			while (i < size / 2)
			{
				rotete(a);
				rotate(b);
				write(1, "rr\n", 3);
				i++;
			}
		}
		push_half_of_big(b, a, size, tmp);
		size = size / 2;
	}
}

int	find_med(int *array, int size)//not index// mb faster
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < size)
	{
		j = i;
		while (j < size - 1)
		{
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
	return (array[size / 2 ]);
}

void push_half_of_big(t_stack *from, t_stack *to, int size, int *tmp)
{
	int i;
	int l_med;

	ft_memcpy(tmp, from->array[from->start], (from->size - from->start) * 4);
	l_med = find_med(tmp, (from->size - from->start));
	i = 0;
	while (i < size)
	{
		if (from->array[from->start] > l_med)
		{
			write(1, "pb\n", 3);
			do_push(from, to);
		}
		i++;
	}
}

void push_half_of_small(t_stack *from, t_stack *to, int size, int *tmp)
{
	int i;
	int l_med;

	ft_memcpy(tmp, from->array[from->start], (from->size - from->start) * 4);
	l_med = find_med(tmp, (from->size - from->start));
	i = 0;
	while (i < size)
	{
		if (from->array[from->start] <= l_med)
		{
			write(1, "pa\n", 3);
			do_push(from, to);
		}
		i++;
	}
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