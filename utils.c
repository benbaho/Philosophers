/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:27:37 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/29 16:52:06 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_atoi (char *s)
{
    int a;
    int c;

    a = 0;
    c = 0;
    while (s[a])
    {
        if(s[a] >= '0' && s[a] <= '9')
            a++;
        else
        {
            printf(RED"Wrong arguments.\n"RESET);
            return (-1);
        }
    }
    a = 0;
    while (s[a] <= 32)
        a++;
    while (s[a] >= '0' && s[a] <= '9')
        c = c * 10 + (s[a++] - '0');
    return (c);
}

uint64_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void printthreadm(int id, char *s, philos *stk)
{
    if (stk->dead == 0)
    {
        pthread_mutex_lock(&stk->random);
        printf(GREEN"%llu " RESET,gettime() - stk->start_time);
        printf(BLACK"%d %s"RESET, id, s);
        pthread_mutex_unlock(&stk->random);
    }
}

void	passtime(int time, list *stk)
{
	uint64_t	start;

	start = gettime();
	while (stk->s_stk->dead == 0)
	{
		if (gettime() - start >= time)
			break ;
		usleep(10);
	}
}

int deadcheck(philos *stk, int i, uint64_t time)
{
    while (stk && stk->check == 0)
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

int eatcheck(list *stk)
{
    if (stk->count_eat >= stk->s_stk->must_eat)
    {
        stk->s_stk->check = 1;
        return (0);
    }
    return (1);
}
int checkargs(char **av, int i)
{
    while (av[i])
    {
        if (ft_atoi(av[i]) == -1)
            return (0);
        i++;
    }
    return (1);
}