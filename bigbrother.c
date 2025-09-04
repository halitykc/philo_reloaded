

#include "philo.h"


int is_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->rules->meal_lock);
    if (get_current_time() - philo->last_meal >= philo->rules->time_to_die)
    {
        pthread_mutex_unlock(&philo->rules->meal_lock);
        return 1;
    }
    pthread_mutex_unlock(&philo->rules->meal_lock);
    return 0;
}

int check_dead(t_rules *rules)
{
    int i;

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
            return 1;
        }
    }
    return 0;
}

void    *bigbrother(void    *args)
{
    t_rules *rules;

    rules = (t_rules *) args;
    while (1)
    {
        if (check_dead(rules))
            break;
    }
    return NULL;
}