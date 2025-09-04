
#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t milliseconds)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(150);
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	res;
	int	s;

	res = 0;
	s = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = s * -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i])
		res = res * 10 + (nptr[i++] - '0');
	return (s * res);
}

void	print_status(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->rules->write_lock);
	pthread_mutex_lock(&philo->rules->dead_lock);
	if (philo->rules->dead_or_alive)
	{
		pthread_mutex_unlock(&philo->rules->dead_lock);
		pthread_mutex_unlock(&philo->rules->write_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->dead_lock);
	time = get_current_time() - philo->rules->sim_start;
	printf("%zu %i %s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->rules->write_lock);
}

void	print_death(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->rules->write_lock);
	time = get_current_time() - philo->rules->sim_start;
	printf("%zu %i %s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(&philo->rules->write_lock);
}