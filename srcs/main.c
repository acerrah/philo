#include "../include/philo.h"

long long	time_present(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void is_any_dead(t_philo *philo)
{
    pthread_mutex_lock(philo->data->death);
    philo->status = philo->data->dead;
    pthread_mutex_unlock(philo->data->death);
}

void print_in_format(t_philo *philo, long long time, char *str)
{
    pthread_mutex_lock(philo->data->print);
    is_any_dead(philo);
    if (philo->data->dead == ALIVE)
        printf("%lld %d %s\n", time, philo->philo_id, str);
    pthread_mutex_unlock(philo->data->print);
}

int dying(t_philo *philo)
{
    static int game_over = 1;

    pthread_mutex_lock(philo->data->print);
    if (philo->data->dead == ALIVE && time_present() - philo->data->start_time - philo->last_meal > philo->data->to_die)
    {
        if(game_over)
        {
            game_over = 0;
            printf("%lld %d died\n", time_present() - philo->data->start_time, philo->philo_id);
        }
        pthread_mutex_lock(philo->data->death);
        philo->data->dead = DEAD;
        pthread_mutex_unlock(philo->data->death);
        pthread_mutex_unlock(philo->data->print);
        return(DEAD);
    }
    pthread_mutex_unlock(philo->data->print);
    return (ALIVE);
}

void eating(t_philo *philo)
{
    long long time;

    time = time_present() - philo->data->start_time;
    pthread_mutex_lock(philo->prev->fork);
    pthread_mutex_lock(philo->fork);
    print_in_format(philo, time_present() - philo->data->start_time, "has taken a fork");
    print_in_format(philo, time_present() - philo->data->start_time, "has taken a fork");
    print_in_format(philo, time_present() - philo->data->start_time, "is eating");
    while (dying(philo) == ALIVE && philo->data->dead == ALIVE)
    {
        if (time_present() - philo->data->start_time - time == philo->data->to_eat)
        {
            philo->last_meal = time_present() - philo->data->start_time;
            break;
        }
        usleep(50);
    }
    pthread_mutex_unlock(philo->prev->fork);
    pthread_mutex_unlock(philo->fork);
}

void sleeping(t_philo *philo)
{
    long long time;

    print_in_format(philo, time_present() - philo->data->start_time, "is sleeping");
    time = time_present() - philo->data->start_time;
    while (dying(philo) == ALIVE && philo->data->dead == ALIVE)
    {
        if (time_present() - philo->data->start_time - time == philo->data->to_sleep)
            break;
        usleep(50);
    }
}

void thinking(t_philo *philo)
{
    print_in_format(philo, time_present() - philo->data->start_time, "is thinking");
}

void *ft_philo(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    while(philo->status == ALIVE)
    {
        eating(philo);
        if (philo->data->dead == DEAD)
            break;
        sleeping(philo);
        if (philo->data->dead == DEAD)
            break;
        thinking(philo);
        if (philo->data->dead == DEAD)
            break;
    }
    return (NULL);
}

void *ft_one_philo(void *philo_ptr)
{
    t_philo *philo;
    long long time;

    philo = (t_philo *)philo_ptr;
    pthread_mutex_lock(philo->fork);
    print_in_format(philo, time_present() - philo->data->start_time, "has taken a fork");
    time = time_present() - philo->data->start_time;
    while(dying(philo) == ALIVE && philo->data->dead == ALIVE)
    {
        if (time_present() - philo->data->start_time - time == philo->data->to_die)
        {
            print_in_format(philo, time_present() - philo->data->start_time, "died");
            break;
        }
        usleep(50);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    int i;
    t_data data;
    t_philo_ring ring;
    int error;

    i = 0;
    ft_check_errors(ac, av);
    ft_get_data(&data, ac, av);
    ft_initialize_ring(&ring);
    while (i < data.philos)
    {
        ft_add_philo(&ring, ft_create_philo(&data));
        i++;
    }
    ring.head = ring.head->next;
    i = 0;
    data.start_time = time_present();
    if (ring.size == 1)
    {
        error = pthread_create(&ring.head->id, NULL, ft_one_philo, ring.head);
        if (error)
        {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }
    }
    while (i++ < ring.size)
	{
		error = pthread_create(&ring.head->id, NULL, ft_philo, ring.head);
		if (error)
        {
            printf("Error: pthread_create() failed\n");
            exit(EXIT_FAILURE);
        }
        ring.head = ring.head->next;
	}
    ring.head = ring.head->next;
    i = 0;
    while(i++ < ring.size)
    {
        pthread_join(ring.head->id, NULL);
        ring.head = ring.head->next;
    }
    return (0);
}