

#include "philo.h"

void    *bigbrother(void    *args)
{
    t_rules *rules;
    int i;
    int f;
    size_t  last_meal_time;

    rules = (t_rules *) args;
    ft_usleep(100);
    while (1)
    {
        i = 0;
        f = 0;
        while (i < rules->total_philo)
        {
            pthread_mutex_lock(&rules->meal_lock);
            last_meal_time = get_current_time() - rules->philos[i].last_meal;
            if (rules->must_eat != -1 && rules->philos[i].meal_eatten >= rules->must_eat)
                f++;
            pthread_mutex_unlock(&rules->meal_lock);
            
            if (!(last_meal_time <= rules->time_to_die))
            {
                pthread_mutex_lock(&rules->dead_lock);
                rules->dead_or_alive = 1;
                rules->philos[i].alive = 1;
                pthread_mutex_unlock(&rules->dead_lock);
                print_death(&rules->philos[i], "Is dead");
                return NULL;
            }    
            i++;
        }
        if (rules->must_eat != -1 && f == rules->total_philo)
        {
            pthread_mutex_lock(&rules->dead_lock);
            rules->dead_or_alive = 1;
            pthread_mutex_unlock(&rules->dead_lock);
            return NULL;
        }
        
    }
    return NULL;
}