/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 02:02:06 by ocviller          #+#    #+#             */
/*   Updated: 2025/08/13 19:50:54 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server	*server;

void	handle_sig(int sig)
{
	if (server->bits < 8)
	{
		if (sig == 1)
			server->charc |= (sig << server->bits);
		server->bits++;
	}
	if (server->bits == 8)
	{
		write(1, &server->charc, 1);
		server->bits = 0;
		server->charc = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	server = malloc(sizeof(t_server));
	if (!server)
		return (1);
	sa.sa_handler = handle_sig;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
}
