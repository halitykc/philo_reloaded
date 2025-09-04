

#include "philo.h"

void    *bigbrother(void    *args)
{
    t_rules *rules;
    int i;
    size_t  last_meal_time;

    rules = (t_rules *) args;
    ft_usleep(100);
    while (1)
    {
        i = 0;
        while (i < rules->total_philo)
        {
            pthread_mutex_lock(&rules->meal_lock);
            last_meal_time = get_current_time() - rules->philos[i].last_meal;
            pthread_mutex_unlock(&rules->meal_lock);
            if (!(last_meal_time <= rules->time_to_die))
            {
                pthread_mutex_lock(&rules->dead_lock);
                printf("%i %zu < %zu\n", i + 1 ,last_meal_time, rules->time_to_die);
                rules->dead_or_alive = 1;
                rules->philos[i].alive = 1;
                print_status(&rules->philos[i], "Is dead");
                pthread_mutex_unlock(&rules->dead_lock);
                return NULL;
            }
            ft_usleep(100);

            i++;
        }
        
    }
    return NULL;
}