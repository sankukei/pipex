/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 03:55:17 by leothoma          #+#    #+#             */
/*   Updated: 2024/12/11 03:55:17 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t	wait_signal = 0;

static int	ft_chackal(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int nb)
{
	char	*res;
	int		size;
	long	n;
	int		neg;

	neg = 0;
	n = nb;
	size = ft_chackal(n);
	if (n < 0)
	{
		n *= -1;
		neg = 1;
	}
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	res[size] = '\0';
	while (--size >= 0)
	{
		res[size] = n % 10 + 48;
		n /= 10;
		if (size == 0 && neg == 1)
			res[size] = '-';
	}
	return (res);
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	wow(int signal, siginfo_t * info, void *context)
{
	signal = 0;
	info = 0;
	context = 0;
	signal++;
	info++;
	context++;
	wait_signal = 1;
}
int	main(int ac, char **av)
{
	int	i;
	char	count;
	
	i = 0;
	struct sigaction sig;
	sig.sa_sigaction = wow;
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	if (ac == 3)
	{
		while (av[2][i])
		{
			count = av[2][i];
			while (count--)
			{
				usleep(100);
				wait_signal = 0;
				kill(atoi(av[1]), SIGUSR1);
				while (!wait_signal)
					;
			}
			usleep(100);
			kill(atoi(av[1]), SIGUSR2);\
			i++;
		}
		usleep(100);
		kill(atoi(av[1]), SIGUSR2);
	}
	else
		write(1, "ERROR: Need 2 parameters (pid, string to send)", 46);
	return (0);
}
