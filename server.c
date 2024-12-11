/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:57:15 by leothoma          #+#    #+#             */
/*   Updated: 2024/12/11 02:57:15 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

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

static void	print_signal(int signal, siginfo_t * info, void *context)
{

	if (signal == 10)
	{
		printf("SIGUSR1 RECEIVED [%d]\n", info->si_pid);
	}
	else
		printf("SIGUSR2 RECEIVED [%d]", info->si_pid);
}

void	pr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	main(void)
{
	int	count = 0;
	struct sigaction sig;
	int	ret = 0;
	pid_t	pid;
	pid = getpid();
	char *tmp = ft_itoa(pid);
	pr(tmp);
	write(1, "\n", 1);
	sig.sa_sigaction = print_signal;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	sig.sa_flags = SA_RESTART | SA_SIGINFO; 
	ret = pause();
	if (ret == -1)
		printf("aurevoir\n");
	return (0);
}
