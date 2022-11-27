/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurmus <bdurmus@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 14:27:37 by bdurmus           #+#    #+#             */
/*   Updated: 2022/11/27 17:42:26 by bdurmus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_atoi (char *s)
{
    int a;
    int b;
    int c;

    a = 0;
    b = 1;
    c = 0;
    while (s[a] < '0' || s[a] > '9')
    {
        printf("Wrong arguments.");
        return (-1);
    }
    while (s[a] <= 32)
        a++;
    if (s[a] == '-' || s[a] == '+')
    {
        if (s[a] == '-')
            b *= -1;
        a++;
    }
    while (s[a] >= '0' && s[a] <= '9')
        c = c * 10 + (s[a++] - '0');
    return (c * b);
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
        printf("%d %s",id, s);
        pthread_mutex_unlock(&stk->random);
    }
}
