#include "philo.h"

int main(int argc, char **argv)
{
    t_args args;

    if (!parse_args(argc, argv, &args))
    {
        printf("Error: invalid arguments\n");
        return (1);
    }

    return (0);
}