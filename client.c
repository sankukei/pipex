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

volatile sig_atomic_t	g_wait_signal = 0;

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

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)info;
	(void)context;
	g_wait_signal = 1;
}

void	send_signal(int ms, int signal, int pid)
{
	usleep(ms);
	kill(pid, signal);
}

int	main(int ac, char **av)
{
	int					i;
	char				count;
	struct sigaction	sig;

	if (ac != 3)
		return (write(1, "error", 5));
	i = 0;
	sig.sa_sigaction = handle_signal;
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	while (av[2][i])
	{
		count = av[2][i];
		while (count--)
		{
			g_wait_signal = 0;
			send_signal(100, SIGUSR1, atoi(av[1]));
			while (!g_wait_signal)
				;
		}
		send_signal(100, SIGUSR2, atoi(av[1]));
		i++;
	}
	send_signal(100, SIGUSR2, atoi(av[1]));
	return (0);
}
