/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:13:30 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/08 12:10:11 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == FALSE)
				return(FALSE);
			if ((ft_atoi(argv[i]) <= 0))
				return(FALSE);
			j++;
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		printf("Wrong number of args\n");
	else if (!check_args(argv))
		printf("Args not valid (not number or negative)\n");
	return (0);
}