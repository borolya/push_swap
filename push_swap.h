#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include "common.h"

typedef enum e_case
{
	RARB,
	RRARB,
	RARRB,
	RRARRB,
}	t_case;

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

t_costelem  take_min_cost(t_stack *a, t_stack *b);
void        stay_three_elem(t_stack *a, t_stack *b, int min, int max);
void        move_to_place(t_stack *a, t_stack *b, t_costelem cost);
#endif