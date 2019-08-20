#ifndef CHECKER_H
# define CHECKER_H

# include <stddef.h>
typedef enum e_case
{
	RARB,
	RRARB,
	RARRB,
	RRARRB,
}	t_case;

typedef struct s_stack
{
	int *array;
	int start;
	int size;
}   t_stack;

typedef struct s_costelem
{
	int index;
	int cost;
	int ra;
	int rb;
	int rra;
	int rrb;
	t_case flag;
}			t_costelem;

int check_ascending_order(int *array, int size, int start);
int ft_atoi_check(const char *str);
void create_stack(int size, int start, t_stack **stack);
void check_uniq(t_stack *stack);
void do_swap(t_stack *stack);
void do_rotate(t_stack *stack);
void do_rrotate(t_stack *stack);
void do_push(t_stack *from, t_stack *to);
void write_stack(t_stack *a, t_stack *b);
void free_stack(t_stack *stack);
void write_stack(t_stack *a, t_stack *b);

#endif