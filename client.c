/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:49:12 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/25 11:21:45 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

volatile int	g_message_acknowledged = 0;

void	confirmation_handler(int sig)
{
	(void)sig;
	g_message_acknowledged = 1;
}

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR2) == -1)
				perror("Error sending SIGUSR2");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				perror("Error sending SIGUSR1");
		}
		usleep(300);
		i--;
	}
}

void	send_message(int pid, const char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0');
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = confirmation_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("Error setting up signal handler");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	const char			*message;

	if (argc != 3)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Error: Invalid PID\n", 1);
		return (1);
	}
	message = argv[2];
	setup_signal_handlers();
	g_message_acknowledged = 0;
	send_message(pid, message);
	while (!g_message_acknowledged)
		pause();
	ft_putstr_fd("Message successfully received by the server.\n", 1);
	return (0);
}
