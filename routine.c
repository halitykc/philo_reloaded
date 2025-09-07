/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:17:38 by hyakici           #+#    #+#             */
/*   Updated: 2025/09/07 15:34:34 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->meal_lock);
	print_status(philo, "is eating");
	philo->last_meal = get_current_time();
	philo->meal_eatten++;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	ft_usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	ft_usleep(1);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dead_lock);
	if (philo->rules->dead_or_alive)
	{
		pthread_mutex_unlock(&philo->rules->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->dead_lock);
	if (philo->rules->total_philo == 1)
	{
		one_philo(philo);
		return ;
	}
	if (philo->philo_id % 2 != 0)
		take_fork1(philo);
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	lock_eat(philo);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dead_lock);
	if (philo->rules->dead_or_alive)
	{
		pthread_mutex_unlock(&philo->rules->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->dead_lock);
	print_status(philo, "is sleeping");
	ft_usleep(philo->rules->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dead_lock);
	if (philo->rules->dead_or_alive)
	{
		pthread_mutex_unlock(&philo->rules->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->dead_lock);
	print_status(philo, "is thinking");
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->philo_id % 2 == 0)
		ft_usleep(20);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->dead_lock);
		if (philo->rules->dead_or_alive)
		{
			pthread_mutex_unlock(&philo->rules->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->dead_lock);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (is_starving(philo))
			ft_usleep(1);
	}
	return (NULL);
}
