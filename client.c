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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	wow(int signal)
{
	write(1, "THANKS FOR RESPONSE", 21);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	struct sigaction sig;
	sig.sa_handler = wow;
	sigaction(SIGUSR1, &sig, NULL);
	if (ac == 3)
	{
		while (i < 7)
		{
			if ((av[2][i] >> i) & 1)
				kill(atoi(av[1]), SIGUSR1);
			else
				kill(atoi(av[1]), SIGUSR2);
			pause();
			i++;
		}
	}
	else
		write(1, "ERROR: Need 2 parameters (pid, string to send)", 46);
	return (0);
}
