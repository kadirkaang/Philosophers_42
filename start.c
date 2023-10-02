/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoc <kgoc@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:10:28 by kgoc              #+#    #+#             */
/*   Updated: 2023/09/29 18:50:38 by kgoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	exit_launcher(t_game_rules *rules, t_philo *philos)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < rules->num_philos)
		pthread_join(philos[i].thread_id, NULL);
	while (++j < rules->num_philos)
		pthread_mutex_destroy(&(rules->forks[j]));
	pthread_mutex_destroy(&(rules->write_status));
	pthread_mutex_destroy(&(rules->check_eat));
	free(rules->philosophers);
	free(rules->forks);
}

void	philo_eats(t_philo *philo)
{
	t_game_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->fork_left]));
	print_status(rules, philo->id_philo, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->fork_right]));
	print_status(rules, philo->id_philo, "has taken a fork");
	pthread_mutex_lock(&(rules->check_eat));
	print_status(rules, philo->id_philo, "is eating");
	philo->last_time_eat = timestamp();
	pthread_mutex_unlock(&(rules->check_eat));
	eat_philo(rules->time_eat, rules);
	(philo->num_eat_philo)++;
	pthread_mutex_unlock(&(rules->forks[philo->fork_left]));
	pthread_mutex_unlock(&(rules->forks[philo->fork_right]));
}

void	*p_thread(void *philo_param)
{
	t_philo			*philo;
	t_game_rules	*rules;

	philo = (t_philo *)philo_param;
	rules = philo->rules;
	if (philo->id_philo % 2 == 1)
		usleep(1500);
	while (!(rules->died))
	{
		if (rules->all_philos_ate)
			break ;
		philo_eats(philo);
		print_status(rules, philo->id_philo, "is sleeping");
		sleep_philo(rules->time_sleep, rules);
		print_status(rules, philo->id_philo, "is thinking");
	}
	return (NULL);
}

int	start_dinner(t_game_rules *rules)
{
	int			i;
	t_philo		*philo;

	i = -1;
	philo = rules->philosophers;
	rules->start_time = timestamp();
	while (++i < rules->num_philos)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, p_thread, &(philo[i])))
			return (1);
		philo[i].last_time_eat = timestamp();
	}
	check_death(rules, rules->philosophers);
	exit_launcher(rules, philo);
	return (0);
}
