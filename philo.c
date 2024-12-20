/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:18:49 by yobourai          #+#    #+#             */
/*   Updated: 2024/12/20 02:40:33 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"
int ft_strlen(char *str) 
{
    int i = 0;
    while (str[i]) 
        i++;
    return i;
}

int ft_atoi(char *str, int *flag)
{
    int i ;
    int result ;
    int sign;
    
    i= 0;
    sign = 1;
    result = 0;
    while (str[i] == ' ' || str[i] == '\t' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+' || str[i] == '-') 
    {
        if (str[i] == '-') 
            sign = -1;
        i++;
    }
    if (!(str[i] >= '0' && str[i] <= '9')) 
    {
        *flag = 1;
        return 1;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if(str[i] != '\0' || result * sign <= 0) 
    {
        *flag = 1;
        return 1;
    }
    return result * sign;
}

void ft_free(int **arr)
{
    int i = 0;
    if(!arr)
        return ;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
       #include <sys/time.h>
int *parcing(int ac, char **av) 
{
    int i = 1; 
    int flag = 0;
    int *arr ;
    arr = (int *)malloc((ac - 1) * sizeof(int));
    if (!arr) 
       return NULL;
    while (i < ac) 
    {
        arr[i - 1] = ft_atoi(av[i], &flag);
        if (flag) 
        {
            printf("Error\n");
            free(arr);
            return NULL;
        }
        i++;
    }
    return arr;
}
unsigned long   ft_get_time_of_day(void)
{
        unsigned long   mili_sc;
        struct timeval  time;
        gettimeofday(&time, NULL);
        mili_sc = (time.tv_sec * 1000) + (time.tv_usec / 1000);
        // printf();
        return (mili_sc);
}

//hey 

void ft_usleep(unsigned long arg)
{
    unsigned long start_time;

    start_time = ft_get_time_of_day(); 

    while (arg > ft_get_time_of_day() - start_time)
    {
        usleep(100);
    }
}

void init_philosophers(t_philo *philos, t_data *data)
{
    int i = 0;
    while (i < data->number_of_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].last_meal_time = data->start_time;
        philos[i].meals_eaten = 0;
        philos[i].data = data;
        philos[i].data->matwldl97ba = 0;
        philos[i].right_fork = &data->forks[i];
        philos[i].left_fork = &data->forks[i+1];
        i++;
    }
    philos[i-1].left_fork = &data->forks[0];
} 
void init_data(t_data *data, int *arr, int ac)
{
    int i = 0;

    data->number_of_philosophers = arr[0];
    data->time_to_die = arr[1];
    data->time_to_eat = arr[2];
    data->time_to_sleep = arr[3];
    if (ac == 6)
        data->number_of_times_each_philosopher_must_eat = arr[4];
    else
        data->number_of_times_each_philosopher_must_eat = -1;
    data->start_time = ft_get_time_of_day();
    data->matwldl97ba = 0;
    data->stop_eating = data->number_of_times_each_philosopher_must_eat * data->number_of_philosophers;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks)
    {
        printf("Error: Unable to allocate memory for forks\n");
        return;
    }
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->meal_mutex, NULL);
}


int  check_out(t_philo *philo)
{
     pthread_mutex_lock(&philo->data->died);
    if (philo->data->matwldl97ba == 1)
    {
        pthread_mutex_unlock(&philo->data->died);
        return 1;
    }
    pthread_mutex_unlock(&philo->data->died);
       pthread_mutex_lock(&philo->data->meal_mutex);
        if (philo->data->stop_eating == 0)
        {
            pthread_mutex_unlock(&philo->data->meal_mutex);
            return 1;
        }
        pthread_mutex_unlock(&philo->data->meal_mutex);
    return 0;
}
int protect (t_philo *philo)
{
    int i = 0;
    //     printf("matwldl97ba = %d\n", philo->data->matwldl97ba);
    //     printf("flag = %d\n", philo->data->flag);
    //     printf("time_to_die = %lu\n", philo->data->time_to_die);
    //     printf("last_meal_time = %lu\n", ft_get_time_of_day() - philo->last_meal_time);
    while(i < philo->data->number_of_philosophers)
    {
                // printf("matwldl97ba = %d philo->id %d\n", philo->data->matwldl97ba, philo[i].id);
                //         printf("flag = %d\n", philo->data->flag);


        if (philo->data->time_to_die <= ft_get_time_of_day() - philo->last_meal_time || philo->data->flag == 1)
        {
            pthread_mutex_lock(&philo->data->print_mutex);
            pthread_mutex_lock(&philo->data->died);
            if (philo->data->matwldl97ba == 0)
            {
                printf("%lu %d has died\n",ft_get_time_of_day() - philo->data->start_time, philo->id);
                philo->data->matwldl97ba = 1;
                
                pthread_mutex_unlock(&philo->data->print_mutex);
                pthread_mutex_unlock(&philo->data->died); 
                exit(0);
            }
            pthread_mutex_lock(&philo->data->died);
            if (philo->data->matwldl97ba == 1)
            {
                pthread_mutex_unlock(&philo->data->print_mutex);
                pthread_mutex_unlock(&philo->data->died); 
                    return 1;
            }
            else
            {
                    pthread_mutex_unlock(&philo->data->print_mutex);
                    pthread_mutex_unlock(&philo->data->died);
                    return 0;
            }
        }
        i++;
    }
    return 0;
}
void forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    protect(philo);
   if(check_out(philo) == 1)
       {
            pthread_mutex_unlock(philo->left_fork);
            return ;
       }
    printf("%lu %d has taken a fork\n", ft_get_time_of_day() - philo->data->start_time, philo->id);
    pthread_mutex_lock(&philo->data->one_philo);
    protect(philo);
    if(check_out(philo) == 1 || philo->data->number_of_philosophers == 1)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(&philo->data->one_philo);
        philo->data->flag = 1;
        return ;
    }
    pthread_mutex_unlock(&philo->data->one_philo);
    pthread_mutex_lock(philo->right_fork);    
    printf("%lu %d has taken a fork\n", ft_get_time_of_day() - philo->data->start_time, philo->id);
    if(check_out(philo) == 1)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
}
void philosopher_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->died);
    if(philo->data->matwldl97ba == 0)
    {
        pthread_mutex_unlock(&philo->data->died);
            forks(philo);
            protect(philo);       
            pthread_mutex_lock(&philo->data->print_mutex);
        if(check_out(philo) == 1)
           {
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(&philo->data->print_mutex);
                return ;
           }
        printf("%lu %d is eating\n", ft_get_time_of_day() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        pthread_mutex_lock(&philo->data->meal_mutex);
        philo->data->stop_eating--;
        pthread_mutex_unlock(&philo->data->meal_mutex);
        pthread_mutex_lock(&philo->data->check);
        philo->last_meal_time = ft_get_time_of_day();
        pthread_mutex_unlock(&philo->data->check);
        ft_usleep(philo->data->time_to_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
    else
    {
            pthread_mutex_unlock(&philo->data->died);
            return ;
    }
}
void sleeping(t_philo * philo)
{
        protect(philo);
    if(check_out(philo) == 1)
        return ;
    pthread_mutex_lock(&philo->data->print_mutex);
    if(philo->data->matwldl97ba == 0)
    {
        printf("%lu %d is sleeping\n", ft_get_time_of_day() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        ft_usleep(philo->data->time_to_sleep );
    }
    else
        pthread_mutex_unlock(&philo->data->print_mutex);
}

void philosopher_think(t_philo *philo)
{
    protect(philo);
    if(check_out(philo) == 0)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        if (check_out(philo) == 0)
        {
            printf("%lu %d is thinking\n", ft_get_time_of_day()-philo->data->start_time, philo->id);
        }
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
}
void *philosopher_routine(void *arg) 
{
    t_philo *philo = (t_philo *)arg;
    if(philo->id % 2 == 0 && philo->data->matwldl97ba != 1)
            sleeping(philo);
    while (1)
    {
        if(protect(philo) == 1)
            break;
        if(check_out(philo) == 1)
            return NULL;
        philosopher_think(philo);
        if(protect(philo) == 1)
                break;;
        if(check_out(philo) == 1)
            return NULL;
        philosopher_eat(philo);
        if(protect(philo) == 1)
            break;
        if(check_out(philo) == 1)
            return NULL;
        sleeping(philo);
        if(protect(philo) == 1)
            break;
        if(check_out(philo) == 1)
                return NULL;
    }
    return NULL;
}

int create_philos(t_philo *philos, t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        // philos[i].last_meal_time = data->start_time;
        if (pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]) != 0)
        {
            printf("Error: Failed to create thread %d\n", i);
            return 1;
        }
        i++;
    }
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    return 0;
}

int main(int ac, char **av)
{
    t_data data;
    t_philo *philos;
    int *arr;
    if (ac != 5 && ac != 6)
    {
        printf("Error: Invalid number of arguments\n");
        return 1;
    }
    arr = parcing(ac, av);
    if (!arr)
        return 1;
    init_data(&data, arr, ac);
    philos = malloc(sizeof(t_philo) * data.number_of_philosophers);
    if (!philos)
    {
        printf("Error: Unable to allocate memory for philosophers\n");
        return 1;
    }
    init_philosophers(philos, &data);
    if(create_philos(philos, &data) != 0)
        return 1;
    free(data.forks);
    free(philos);
    free(arr);
    return 0;
}
