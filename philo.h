/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:19:02 by yobourai          #+#    #+#             */
/*   Updated: 2024/12/21 04:50:17 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
    int number_of_philosophers;
    unsigned long time_to_die;
    unsigned long time_to_eat;
    unsigned long time_to_sleep;
    int number_of_times_each_philosopher_must_eat; 
    unsigned long start_time;
    unsigned long stop_eating;
    int check_death;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    struct s_philo *philos;
    int flag;
    int matwldl97ba;
    pthread_mutex_t meal_mutex; 
    pthread_mutex_t died;
    pthread_mutex_t check;
    pthread_mutex_t one_philo;
        
} t_data;


typedef struct s_philo
{
    int id;
    unsigned long last_meal_time;  
    int meals_eaten;            
    t_data *data;                  
    pthread_mutex_t *left_fork;
    pthread_t thread;
    pthread_mutex_t *right_fork; 

} t_philo;


#endif
