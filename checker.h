#ifndef CHECKER_H
# define CHECKER_H

# include <stddef.h>

typedef struct s_stack
{
    int *array;
    int start;
    int size;
}   t_stack;


int ft_atoi_check(const char *str);
void create_stack(int size, int start, t_stack **stack);
void check_uniq(t_stack *stack);
void do_swap(t_stack *stack);
void do_rotate(t_stack *stack);
void do_rrotate(t_stack *stack);
void do_push(t_stack *from, t_stack *to);
void write_stack(t_stack *a, t_stack *b);
void free_stack(t_stack *stack);

#endif