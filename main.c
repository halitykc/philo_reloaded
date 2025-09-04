

#include "philo.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}


int main(int argc, char *argv[])
{
    t_table table;

    if ((argc == 6 || argc == 5) && check_args(argv))
    {
        init_table(&table, argv);
        start_threads(&table);
    }
    
    return 0;
}
