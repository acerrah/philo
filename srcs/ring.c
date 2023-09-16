#include "../include/philo.h"

void ft_initialize_ring(t_philo_ring* ring) {
    ring->head = NULL;
    ring->size = 0;
}

t_philo* ft_create_philo(t_data *data) {
    t_philo* new_philo;

    new_philo = malloc(sizeof(t_philo));
    new_philo->fork = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(new_philo->fork, NULL);
    new_philo->next = NULL;
    new_philo->prev = NULL;
    new_philo->status = ALIVE;
    new_philo->last_meal = 0;
    new_philo->data = data;
    return new_philo;
}

void ft_add_philo(t_philo_ring* ring, t_philo* new_philo) {
    if (ring->head == NULL) {
        ring->head = new_philo;
        new_philo->next = new_philo;
        new_philo->prev = new_philo;
        new_philo->philo_id = 1;
    } else {
        t_philo* last_philo = ring->head;
        new_philo->philo_id = last_philo->philo_id + 1;
        if (new_philo->philo_id == new_philo->data->philos)
            last_philo->next->prev = new_philo;
        new_philo->next = last_philo->next;
        new_philo->prev = last_philo;
        last_philo->next = new_philo;
        ring->head = new_philo;
    }
    ring->size++;
}
