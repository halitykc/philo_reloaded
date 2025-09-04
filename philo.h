


#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdint.h>

typedef struct s_rules
{
    size_t  time_to_die;//
    size_t  time_to_eat;//
    size_t  time_to_sleep;//
    size_t  sim_start;//
    int total_philo;//
    int must_eat;//
    int dead_or_alive;//

    pthread_mutex_t write_lock;//
    pthread_mutex_t meal_lock;//
    pthread_mutex_t dead_lock;//
    struct  s_philo    *philos; 
}               t_rules;



typedef struct s_philo
{
    pthread_t thread;
    int philo_id;//
    int meal_eatten;//
    int alive;
    pthread_mutex_t *l_fork;//
    pthread_mutex_t *r_fork;//
    size_t  last_meal; //
    t_rules *rules;//
}               t_philo;

typedef struct s_table
{
    t_philo philo[200];
    pthread_mutex_t fork[200];//
    t_rules rules;//
}               t_table;



size_t				get_current_time(void);
void	            ft_usleep(size_t milliseconds);
int	                ft_atoi(char *nptr);
void                init_mutex(t_table *table);
void                init_philos(t_table *table);
void                init_program(t_table *table, char **argv);
void                init_table(t_table *table, char **argv);
void                start_threads(t_table *table);
void                *routine(void    *args);
void                *bigbrother(void    *args);
void	            print_status(t_philo *philo, char *str);
void	print_death(t_philo *philo, char *str);


#endif