#include "../include/philo.h"

void ft_check_errors(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    if (ac != 5 && ac != 6)
    {
        printf("%s", TypeError);
        exit(EXIT_FAILURE);
    }
    while (av[i])
    {
        j = 0;
        while (ft_isdigit(av[i][j]))
            j++;
        if (av[i++][j])
        {
            printf("%s", TypeError2);
            exit(EXIT_FAILURE);
        }
    }
}

void ft_get_data(t_data *data, int ac, char **av)
{
    data->philos = ft_atoi(av[1]);
    data->to_die = ft_atoi(av[2]);
    data->to_eat = ft_atoi(av[3]);
    data->to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        data->must_eat = ft_atoi(av[5]);
    else
        data->must_eat = -1;
    data->dead = ALIVE;
    data->death = malloc(sizeof(pthread_mutex_t));
    data->print = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(data->death, NULL);
    pthread_mutex_init(data->print, NULL);
}
