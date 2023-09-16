#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "../lib/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

# define TypeError "Wrong number of arguments"
# define TypeError2 "Wrong type of arguments"
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define ALIVE 1
# define DEAD 0

typedef struct s_data
{
    long long philos;
    long long to_die;
    long long to_eat;
    long long to_sleep;
    long long must_eat;
    long long start_time;
    int dead;
    pthread_mutex_t *death;
    pthread_mutex_t *print;
}  t_data;

typedef struct s_philo
{
    t_data *data;
    pthread_t id;
    int philo_id;
    pthread_mutex_t *fork;
    int status;
    long long last_meal;
    struct s_philo* next;
    struct s_philo* prev;

}   t_philo;

typedef struct s_philo_ring {
    t_philo* head;
    int size;
} t_philo_ring;

void ft_check_errors(int ac, char **av);
void ft_get_data(t_data *data, int ac, char **av);
void ft_initialize_ring(t_philo_ring* ring);    
t_philo* ft_create_philo();
void ft_add_philo(t_philo_ring* ring, t_philo* new_philo);

#endif
