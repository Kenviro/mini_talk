/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:03:50 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/25 10:48:25 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

char	*realloc_str(char *str, char c)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc(ft_strlen(str) + 2);
	if (!temp)
	{
		perror("Erreur de realloc");
		free(str);
		exit(EXIT_FAILURE);
	}
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = c;
	temp[i + 1] = '\0';
	free(str);
	return (temp);
}

char	*malloc_str(char *str)
{
	str = malloc(1);
	if (!str)
	{
		perror("Erreur de malloc");
		exit(EXIT_FAILURE);
	}
	str[0] = '\0';
	return (str);
}

void	good_malloc(char c, pid_t *client_pid)
{
	static char	*str = NULL;

	if (!str)
		str = malloc_str(str);
	if (c == '\0')
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		free (str);
		str = NULL;
		if (*client_pid)
		{
			if (kill(*client_pid, SIGUSR1) == -1)
				perror("Erreur lors de l'envoi du signal de confirmation");
			*client_pid = 0;
		}
	}
	else
		str = realloc_str(str, c);
}
