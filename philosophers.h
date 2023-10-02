/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoc <kgoc@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:10:15 by kgoc              #+#    #+#             */
/*   Updated: 2023/09/29 22:11:02 by kgoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

typedef struct s_philo
{
	int					id_philo;
	int					num_eat_philo;
	int					fork_left;
	int					fork_right;
	int					did_it_eat;
	long long			last_time_eat;
	struct s_game_rules	*rules;
	pthread_t			thread_id;
}t_philo;

typedef struct s_game_rules
{
	int				num_philos;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				num_limit_eat;
	int				died;
	int				all_philos_ate;
	int				total_meal;
	long long		start_time;
	pthread_mutex_t	check_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_status;
	t_philo			*philosophers;
}t_game_rules;

int			ft_atoi(const char *str);
long long	timestamp(void);
long long	time_result(long long start, long long finish);
void		sleep_philo(long long time, t_game_rules *rules);
void		print_status(t_game_rules *rules, int id, char *str);
int			start_dinner(t_game_rules *rules);
void		eat_philo(long long time, t_game_rules *rules);
void		check_death(t_game_rules *r, t_philo *p);

#endif