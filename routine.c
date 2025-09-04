

#include "philo.h"


void    philo_eat(t_philo *philo)
{
    print_status(philo, "Is eating");

    ft_usleep(philo->rules->time_to_eat);

}


void philo_sleep(t_philo *philo)
{
    print_status(philo, "Is Sleeping");
    ft_usleep(philo->rules->time_to_sleep);
}

void  philo_think(t_philo *philo)
{
    print_status(philo, "Is Thinking");
}

void    *routine(void    *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    philo->last_meal = get_current_time();
    printf("addr: %p\n", &philo->rules->write_lock);

    while (1)
    {
        // pthread_mutex_lock(&philo->rules->dead_lock);
        // if (philo->rules->dead_or_alive)
        // {
        //     pthread_mutex_unlock(&philo->rules->dead_lock);
        //     break;
        // }
        // pthread_mutex_unlock(&philo->rules->dead_lock);

        // philo_eat(philo);
        // philo_sleep(philo);
        // philo_think(philo);
        print_status(philo, "sa");
    }
    
    return NULL;
}