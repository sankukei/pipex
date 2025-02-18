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

volatile sig_atomic_t	g_wait_signal = 0;

void	pr(char *str);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		n += '0';
		write(fd, &n, 1);
	}
}

void	set_null(int *a, int *b, char *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static void	print_signal(int signal, siginfo_t *info, void *context)
{
	static char	res[1000000] = {0};	
	static char	count = 0;
	static int	i = 0;
	static int	end = 0;

	(void)context;
	if (signal == SIGUSR1 && end != 2)
	{
		count++;
		end = 0;
		kill(info->si_pid, SIGUSR1);
	}
	if (signal == SIGUSR2 && end != 2)
	{
		res[i] = count;
		count = 0;
		i++;
		end++;
	}
	if (end == 2)
	{
		res[i] = '\0';
		set_null(&i, &end, &count);
		pr(res);
	}
}

void	pr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int	main(void)
{
	struct sigaction	sig;
	int					ret;
	pid_t				pid;

	ret = 0;
	pid = getpid();
	ft_putnbr_fd(pid, 0);
	write(1, "\n", 1);
	sig.sa_sigaction = print_signal;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	sig.sa_flags = SA_RESTART | SA_SIGINFO;
	while (1)
	{
		ret = pause();
	}
	if (ret == -1)
		printf("aurevoir\n");
	return (0);
}
