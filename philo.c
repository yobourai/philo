#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

int main(int ac, char **av) 
{
    if (ac == 5 || ac == 6) 
    {
        int *arr = parcing(ac, av);
        if (arr) 
            printf("Parsing good\n");
    } 
    else 
        printf("Error in the number of argument\n");
    return 0;
}
