#ifndef CHECKER_H
# define CHECKER_H

# include <stddef.h>

typedef struct s_stack
{
    int *array;
    size_t start;
    size_t size;
}   t_stack;

#endif