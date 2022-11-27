/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:49:54 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/27 17:35:37 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int initphilos(philos *stk, int ac)
{
    ac = 0;
    stk->link = malloc(sizeof(list) * stk->number_of_philo);
    if (!stk->link)
        return (0);
    while (ac < stk->number_of_philo)
    {
        stk->link[ac].id = ac;
        stk->link[ac].l_forkid = ac;
        stk->link[ac].r_forkid = (ac + 1) % stk->number_of_philo;
        stk->link[ac].count_eat = 0;
        stk->link[ac].s_stk = stk;
        stk->link[ac].last_eat = gettime();
        ac++;
    }
    return (1);
}

int initarguments(int ac, char **av, philos *stk)
{
    stk->number_of_philo = ft_atoi(av[1]);
    stk->time_to_die = ft_atoi(av[2]);
    stk->time_to_eat = ft_atoi(av[3]);
    stk->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        stk->must_eat = ft_atoi(av[5]);
    else
        stk->must_eat = -1;
    stk->dead = 0;
    stk->fork_mutex = malloc(sizeof(stk->number_of_philo));
    if (!stk->fork_mutex)
        return (0);
    ac = 0;
    pthread_mutex_init(&stk->random, NULL);
    while (stk->number_of_philo > ac)
        pthread_mutex_init(&stk->fork_mutex[ac++], NULL);
    initphilos(stk, ac);
    return (1);
}

int main (int ac, char **av)
{
    philos   *stk;

    stk = malloc(sizeof(philos));
    if (ac != 5 && ac != 6)
    {
        printf("More or not enough arguments.");
        return (0);
    }
    initarguments(ac, av, stk);
    createthread(stk, 0);
}