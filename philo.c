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
    int i = 0;
    int sign = 1;
    int result = 0;

    while (str[i] == ' ' || str[i] == '\t' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+' || str[i] == '-') 
    {
        if (str[i] == '-'); 
            sign = -1;
        i++;
    }
    if (!(str[i] >= '0' && str[i] <= '9')) 
    {
        write(2, "Error\n", 6);
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
        write(2, "Error\n", 6);
        *flag = 1;
        return 1;
    }
    return result * sign;
}

int *parcing(int ac, char **av) 
{
    int i = 1; 
    int flag = 0;
    int *arr = malloc((ac - 1) * sizeof(int));
    if (!arr) 
       return NULL;
    while (i < ac) 
    {
        arr[i - 1] = ft_atoi(av[i], &flag);
        if (flag) 
        {
            free(arr);
            return NULL;
        }
        i++;
    }
    return arr;
}
t_philo init_argument(int *arr, int ac)
{
    t_philo arg;
    arg.number_of_philosophers = arr[0];
    arg.time_to_die = arr[1];
    arg.time_to_eat = arr[2];
    arg.time_to_sleep = arr[3];
    if (ac == 5)
        arg.number_of_times_each_philosopher_must_eat = arr[4];
    else
        arg.number_of_times_each_philosopher_must_eat = -1;

    return arg;
}
int creat_philos(t_philo *arr)
{
    int i = 0;
    pthread_t *philos = malloc(sizeof(pthread_t) * arr->number_of_philosophers);
    if (!philos)
        return 1;

    while (i < arr->number_of_philosophers)
    {
        if (pthread_create(&philos[i], NULL, NULL, arr) != 0)
        {
            printf("Error creating thread %d\n", i);
            free(philos);
            return 1;
        }
        i++;
    }
    i = 0;
    while( i < arr->number_of_philosophers)
    {
        pthread_join(philos[i], NULL);
        i++;
    }
    free(philos);
    return 0;
}

int main(int ac, char **av) 
{
    int *arr ;
    if (arr  &&  ac == 5 || ac == 6) 
    {
        arr = parcing(ac, av);
        if (arr) 
            printf("Parsing good\n");
        else 
            return 1;
    } 
    else 
    {
        printf("Error in the number of argument\n");
            return 1;
    }
    t_philo args ;
        args = init_argument(arr, ac - 1);
    return 0;
}
