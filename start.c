/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:19 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/27 17:43:01 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void starteating(list *free)
{
    pthread_mutex_lock(&free->s_stk->fork_mutex[free->l_forkid]);
    printthreadm(free->id, "has taken the left fork\n", free->s_stk);
    pthread_mutex_lock(&free->s_stk->fork_mutex[free->r_forkid]);
    printthreadm(free->id, "has taken the right fork\n", free->s_stk);
    printthreadm(free->id, "Eating.\n", free->s_stk);
    free->last_eat = gettime();
    usleep(free->s_stk->time_to_eat * 1000);
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
        
        printthreadm(free->id, "Sleeeeepinggg/ZzzZz\n", stk);
        usleep(free->s_stk->time_to_sleep * 1000);
        if (free->s_stk->dead == 1)
            break ;
        printthreadm(free->id, "Thinking.\n", stk);
    }
    return (NULL);
}

void createthread(philos *stk, int i)
{
    while (++i < stk->number_of_philo)
        pthread_create(&stk->link[i].th_id, NULL, start, &stk->link[i]);


}