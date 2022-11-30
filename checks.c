/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:26:46 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/30 17:34:15 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	deadcheck(t_philos *stk, int i, uint64_t time)
{
	while (stk && stk->check == -1)
	{	
		time = stk->link[i].last_eat;
		if (stk->time_to_die < gettime() - time)
		{
			printthreadm(stk->link[i].id, YELLOW"died\n"RESET, stk);
			stk->dead = 1;
			i = 0;
			if (stk->number_of_philo == 1)
			{
				while (i < stk->number_of_philo)
					pthread_mutex_destroy(&stk->fork_mutex[i++]);
				pthread_mutex_destroy(&stk->random);
				return (0);
			}
		}
		if (stk->dead == 1)
			return (0);
		i++;
		if (i == stk->number_of_philo)
			i = 0;
	}
	return (1);
}

int	eatcheck(t_list *stk)
{
	if (stk->count_eat >= stk->s_stk->must_eat && stk->s_stk->must_eat != -1)
	{
		stk->s_stk->check = 1;
		return (0);
	}
	return (1);
}

int	checkargs(char **av, int i)
{
	while (av[i])
	{
		if (ft_atoi(av[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
