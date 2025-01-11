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

volatile sig_atomic_t	wait_signal = 0;

void	pr(char *str);
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

void	xd(char*str)
{
	while (*str)
		write(1, str++, 1);
}

void	flush(char *str)
{
	while (*str)
	{
		*str = '\0';
		str++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}
static void	print_signal(int signal, siginfo_t * info, void *context)
{
	(void)context;
	//context++;
	static char	res[100];	
	static char	count = 0;
	static int	i = 0;
	static int	end = 0;
	char *tmp;
	int x = 0;
	while(x < 100)
		res[x++] = '\0';
	if (signal == SIGUSR1 && end != 2)
	{
		
		write(1,"ff\n", 3);
		count++;
		end = 0;	
		kill(info->si_pid, SIGUSR1);
	}
	if(signal == SIGUSR2 && end != 2)
	{
		write(1, "ff2\n", 4);
		tmp = ft_itoa(count);
		write(1, "COUNT:", 6);
		write(1, tmp, ft_strlen(tmp));
		write(1, "\n", 1);
		res[i] = count;
		write(1, "RES:", 4);
		write(1, &res[i], 1);
		write(1, "\n", 1);
		count = 0;
		i++;
		end++;
	}
	if (end == 2)
	{
		//i++;
		//i++;
		//res[i] = '\0';
		write(1, res, ft_strlen(res));
		i = 0;
		end = 0;
		count = 0;
		//write(1, "RES:\n", 5);
		//pr(res);
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
	struct sigaction sig;
	int	ret = 0;
	pid_t	pid;
	pid = getpid();
	char *tmp = ft_itoa(pid);
	pr(tmp);
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
