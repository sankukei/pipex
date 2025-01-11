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
//	write(1, "THANKS FOR RESPONSE\n", 21);
}
int	main(int ac, char **av)
{
	int	i;
	char	count;
	int cint = 0;// le nombre de compte
	char *tmp;
	int pint = 0; // ca pr de passage de lettre 
	
	i = 0;
	count = av[2][i];
	struct sigaction sig;
	sig.sa_sigaction = wow;
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	if (ac == 3)
	{
		while (av[2][i])
		{
				
			write(1, &count, 1);
			while (count--)
			{
					
				cint++;
				wait_signal = 0;
				kill(atoi(av[1]), SIGUSR1);
				//count++;
				while (!wait_signal)
					;
			}
			kill(atoi(av[1]), SIGUSR2);\
			pint++;
			write(1, "sent SIGUSR2\n", 13);
			i++;
			count = av[2][i];
		}
		kill(atoi(av[1]), SIGUSR2);
		write(1, "sent SIGUSR2\n", 13);

	}
	else
		write(1, "ERROR: Need 2 parameters (pid, string to send)", 46);
	tmp = ft_itoa(cint);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
	tmp = ft_itoa(pint);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);


	return (0);
}
