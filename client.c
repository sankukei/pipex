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

volatile sig_atomic_t	wait_signal = 1;

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
	wait_signal = 1;
	write(1, "THANKS FOR RESPONSE\n", 21);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	struct sigaction sig;
	sig.sa_sigaction = wow;
	sig.sa_flags = 0;
	sigaction(SIGUSR1, &sig, NULL);
	if (ac == 3)
	{
		while (i < 8)
		{
			wait_signal = 0;
			if ((av[2][i] >> i) & 1)
				kill(atoi(av[1]), SIGUSR2);
			else
				kill(atoi(av[1]), SIGUSR1);
			while (!wait_signal)
				;
			i++;
		}
	}
	else
		write(1, "ERROR: Need 2 parameters (pid, string to send)", 46);
	return (0);
}
