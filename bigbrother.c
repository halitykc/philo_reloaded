/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigbrother.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:17:48 by hyakici           #+#    #+#             */
/*   Updated: 2025/09/07 15:29:00 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->rules->time_to_die)
	{
		pthread_mutex_unlock(&philo->rules->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->meal_lock);
	return (0);
}

int	is_starving(t_philo *philo)
{
	size_t	diff;

	pthread_mutex_lock(&philo->rules->meal_lock);
	diff = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	if (diff > philo->rules->time_to_die / 2)
		return (1);
	return (0);
}

int	check_dead(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->total_philo)
	{
		if (is_dead(&rules->philos[i]))
		{
			print_status(&rules->philos[i], "is dead");
			pthread_mutex_lock(&rules->dead_lock);
			rules->philos[i].dead = 1;
			rules->dead_or_alive = 1;
			pthread_mutex_unlock(&rules->dead_lock);
			return (1);
		}
	}
	return (0);
}

int	all_ate(t_rules *rules)
{
	int	i;

	if (rules->must_eat <= 0)
		return (0);
	i = -1;
	while (++i < rules->total_philo)
	{
		pthread_mutex_lock(&rules->meal_lock);
		if (rules->philos[i].meal_eatten < rules->must_eat)
		{
			pthread_mutex_unlock(&rules->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&rules->meal_lock);
	}
	pthread_mutex_lock(&rules->dead_lock);
	rules->dead_or_alive = 1;
	pthread_mutex_unlock(&rules->dead_lock);
	return (1);
}

void	*bigbrother(void *args)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)args;
	ft_usleep(30);
	while (1)
	{
		if (check_dead(rules) || all_ate(rules))
			break ;
		i = -1;
		while (++i < rules->total_philo)
		{
			if (is_starving(&rules->philos[i]))
				ft_usleep(1);
		}
	}
	return (NULL);
}
