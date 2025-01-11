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
	write(1, "THANKS FOR RESPONSE\n", 21);
}
int	main(int ac, char **av)
{
	int	i;
	char	count;
	
	i = 0;
	count = 0;
	struct sigaction sig;
	sig.sa_sigaction = wow;
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	if (ac == 3)
	{
		while (av[2][i])
		{
			while (count != av[2][i])
			{
				wait_signal = 0;
				kill(atoi(av[1]), SIGUSR1);
				count++;
				while (!wait_signal)
					;
			}
			kill(atoi(av[1]), SIGUSR2);
			write(1, "sent SIGUSR2\n", 13);
			i++;
			count = 0;
		}
		kill(atoi(av[1]), SIGUSR2);
		write(1, "sent SIGUSR2\n", 13);

	}
	else
		write(1, "ERROR: Need 2 parameters (pid, string to send)", 46);
	write(1, "b", 1);
	return (0);
}
