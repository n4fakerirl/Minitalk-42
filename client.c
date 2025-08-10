/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:52:04 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/10 02:51:33 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	string_to_bit(char *str, int pid)
{
	int	i;
	int	y;

	y = 0;
	while (str[y])
	{
		i = 7;
		while (i >= 0)
		{
			if (str[y] & (1 << i))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i--;
			sleep(1);
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
		return (printf("Error\nUsage: ./client \"PID\" \"MSG\".\n"), 0);
	int pid;
	pid = ft_atoi(av[1]);
	string_to_bit(av[2], pid);
}