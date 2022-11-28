/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:50:01 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/28 12:48:18 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "stdlib.h"
#include "pthread.h"

typedef struct addion
{
    int         id;
    int         l_forkid;
    int         r_forkid;
    int         count_eat;
    uint64_t    last_eat;
    pthread_t   th_id;
    struct p_stk *s_stk;
} list;

typedef struct p_stk
{
    int             id;
    int             must_eat;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_philo;
    int             dead;
    list          *link;
    uint64_t        start_time;
    pthread_mutex_t random;
    pthread_mutex_t *fork_mutex;
} philos;

int         ft_atoi (char *s);
uint64_t	gettime(void);

void printthreadm(int id, char *s, philos *stk);
void	passtime(int time, list *stk);
int createthread(philos *stk, int i);
int deadcheck(philos *stk);

#endif