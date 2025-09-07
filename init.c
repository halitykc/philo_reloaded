/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:17:46 by hyakici           #+#    #+#             */
/*   Updated: 2025/09/07 15:32:43 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->rules.total_philo)
	{
		pthread_mutex_init(&table->fork[i], NULL);
	}
	pthread_mutex_init(&table->rules.dead_lock, NULL);
	pthread_mutex_init(&table->rules.write_lock, NULL);
	pthread_mutex_init(&table->rules.meal_lock, NULL);
}

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->rules.total_philo)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].meal_eatten = 0;
		table->philo[i].l_fork = &table->fork[i];
		table->philo[i].r_fork = &table->fork[(i + 1)
			% table->rules.total_philo];
		table->philo[i].rules = &table->rules;
		table->philo[i].dead = 0;
		table->philo[i].last_meal = get_current_time();
	}
}

void	init_program(t_table *table, char **argv)
{
	table->rules.total_philo = ft_atoi(argv[1]);
	table->rules.dead_or_alive = 0;
	init_mutex(table);
	if (argv[5])
		table->rules.must_eat = ft_atoi(argv[5]);
	else
		table->rules.must_eat = -1;
	table->rules.time_to_die = ft_atoi(argv[2]);
	table->rules.time_to_eat = ft_atoi(argv[3]);
	table->rules.time_to_sleep = ft_atoi(argv[4]);
	table->rules.philos = table->philo;
}

void	init_table(t_table *table, char **argv)
{
	init_program(table, argv);
	init_philos(table);
}

void	start_threads(t_table *table)
{
	pthread_t	bigbro;
	int			i;
	int			c;

	i = -1;
	table->rules.sim_start = get_current_time();
	pthread_create(&bigbro, NULL, bigbrother, &table->rules);
	while (++i < table->rules.total_philo)
	{
		pthread_create(&table->philo[i].thread, NULL, routine,
			&table->philo[i]);
		ft_usleep(1);
	}
	c = -1;
	pthread_join(bigbro, NULL);
	while (++c < table->rules.total_philo)
		pthread_join(table->philo[c].thread, NULL);
}
