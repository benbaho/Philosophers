/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:19 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/29 16:49:57 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void starteating(list *free)
{
    pthread_mutex_lock(&free->s_stk->fork_mutex[free->l_forkid]);
    printthreadm(free->id, BLUE"has taken the left fork\n"RESET, free->s_stk);
    pthread_mutex_lock(&free->s_stk->fork_mutex[free->r_forkid]);
    printthreadm(free->id, BLUE"has taken the right fork\n"RESET, free->s_stk);
    printthreadm(free->id, PINK"is eating\n"RESET, free->s_stk);
    free->last_eat = gettime();
    passtime(free->s_stk->time_to_eat, free);
    pthread_mutex_unlock(&free->s_stk->fork_mutex[free->l_forkid]);
    pthread_mutex_unlock(&free->s_stk->fork_mutex[free->r_forkid]);
    free->count_eat++ ;
}

void    *start(void *stk)
{
    list *free;

    free = (list *)stk;
    if (free->id % 2)
        usleep(1000);
    while (free->s_stk->dead == 0)
    {
        if (free->s_stk->dead == 1)
            break ;
        starteating(free);
        if (!eatcheck(free))
            break ;
        if (free->s_stk->dead == 1)
            break ;
        printthreadm(free->id, RED"is sleeping\n"RESET, free->s_stk);
        passtime(free->s_stk->time_to_sleep, free);
        if (free->s_stk->dead == 1)
            break ;
        printthreadm(free->id, CYAN"is thinking\n"RESET, free->s_stk);
    }
    return (NULL);
}

int createthread(philos *stk, int i, uint64_t time)
{
    while (i < stk->number_of_philo)
    {
        pthread_create(&stk->link[i].th_id, NULL, start, &stk->link[i]);
        i++;
    }
    if(!deadcheck(stk, 0, time) || stk->dead == 1)
        return (0);
    i = 0;
    while (i < stk->number_of_philo)
        pthread_join(stk->link[i++].th_id, NULL);
    while (i < stk->number_of_philo)
        pthread_mutex_destroy(&stk->fork_mutex[i--]);
    pthread_mutex_destroy(&stk->random);
    return (1);
}