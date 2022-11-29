/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:50:01 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/29 16:54:24 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define BLUE    "\x1b[34m"
# define CYAN    "\x1b[36m"
# define PINK    "\x1B[35m"
# define BLACK   "\x1B[30m"
# define YELLOW  "\x1B[33m"
# define RESET   "\x1b[0m"

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

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
    int             check;
    list            *link;
    uint64_t        start_time;
    pthread_mutex_t random;
    pthread_mutex_t *fork_mutex;
} philos;

int         ft_atoi (char *s);
int         createthread(philos *stk, int i, uint64_t time);
int         deadcheck(philos *stk, int i, uint64_t time);
int checkargs(char **av, int i);
void	    passtime(int time, list *stk);
void        printthreadm(int id, char *s, philos *stk);
uint64_t	gettime(void);
int eatcheck(list *stk);

# endif