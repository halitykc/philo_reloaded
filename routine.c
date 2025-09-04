

#include "philo.h"


void    philo_eat(t_philo *philo)
{
    if (philo->rules->dead_or_alive)
        return;
    if  (philo->rules->total_philo == 1)
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "Has taken a fork");
        ft_usleep(philo->rules->time_to_die);
        pthread_mutex_unlock(philo->l_fork);
        return;
    }
    if (philo->l_fork < philo->r_fork)
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "Has taken a fork");
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "Has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "Has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "Has taken a fork");
    }
    pthread_mutex_lock(&philo->rules->meal_lock);
    
    philo->last_meal = get_current_time();
    print_status(philo, "Is eating");
    philo->meal_eatten++;
    ft_usleep(philo->rules->time_to_eat);

    pthread_mutex_unlock(&philo->rules->meal_lock);

    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}


void philo_sleep(t_philo *philo)
{
    if (philo->rules->dead_or_alive)
        return;
    
    print_status(philo, "Is sleeping");
    ft_usleep(philo->rules->time_to_sleep);
}

void  philo_think(t_philo *philo)
{
    if (philo->rules->dead_or_alive)
        return;
    print_status(philo, "Is thinking");
}

void    *routine(void    *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    philo->last_meal = get_current_time();
    if (philo->philo_id % 2 == 0)
        ft_usleep(20);
    
    while (1)
    {
        pthread_mutex_lock(&philo->rules->dead_lock);
        if (philo->rules->dead_or_alive)
        {
            pthread_mutex_unlock(&philo->rules->dead_lock);
            break;
        }
        pthread_mutex_unlock(&philo->rules->dead_lock);

        philo_eat(philo);
        philo_sleep(philo);
        philo_think(philo);
    }
    return NULL;
}