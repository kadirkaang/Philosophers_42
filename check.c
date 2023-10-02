/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoc <kgoc@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:48:38 by kgoc              #+#    #+#             */
/*   Updated: 2023/10/02 18:48:39 by kgoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

int	check_meals(t_game_rules *r, t_philo *p)
{
	int	i;

	i = 0;
	while (i < r->num_philos)
	{
		if (p[i].num_eat_philo == r->num_limit_eat)
		{
			if (p[i].did_it_eat == 0)
			{
				p[i].did_it_eat = 1;
				r->total_meal++;
			}
		}
		i++;
	}
	if (r->total_meal == r->num_philos)
		return (1);
	return (0);
}

void	check_death(t_game_rules *r, t_philo *p)
{
	int	i;

	while (!(r->all_philos_ate))
	{
		i = -1;
		while (++i < r->num_philos && !(r->died))
		{
			pthread_mutex_lock(&(r->check_eat));
			if (time_result(p[i].last_time_eat, timestamp()) > r->time_death)
			{
				print_status(r, i, "died");
				r->died = 1;
			}
			pthread_mutex_unlock(&(r->check_eat));
			usleep(500);
		}		
		if (r->died)
			break ;
		if (r->num_limit_eat != -1)
			r->all_philos_ate = check_meals(r, p);
	}
}