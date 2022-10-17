/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:23:40 by ljahn             #+#    #+#             */
/*   Updated: 2022/10/17 13:27:55 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	all_chars(char **strstr, t_charfun toApply, t_cub *data)
{
	int	i;
	int	j;

	if (!strstr)
		return ;
	i = 0;
	while (strstr[i])
	{
		j = 0;
		while (strstr[i][j])
		{
			toApply(strstr[i][j], data);
			j++;
		}
		i++;
	}
}

// Overload with coordinate functions
void	all_chars2(char **strstr, t_coorfun toApply, t_cub *data)
{
	int	i;
	int	j;

	if (!strstr)
		return ;
	i = 0;
	while (strstr[i])
	{
		j = 0;
		while (strstr[i][j])
		{
			toApply(strstr, i, j, data);
			j++;
		}
		i++;
	}
}

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

int	ft_rstrstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i] && strstr[i][0] != '\n')
		i++;
	return (i);
}

void	free_all(char **splitters)
{
	int	i;

	i = 0;
	while (splitters && splitters[i])
	{
		// free(splitters[i]); TAG1
		i++;
	}
	if (splitters)
		// free(splitters); TAG1
		;
}

void	error_msg(char *msg, t_cub *data, char **matrix)
{
	(void)data;
	if (data)
	{
		if (data->n_path)
			// free(data->n_path); TAG1
			;
		if (data->w_path)
			// free(data->w_path); TAG1
			;
		if (data->s_path)
			// free(data->s_path); TAG1
			;
		if (data->e_path)
			// free(data->e_path); TAG1
			;
		// free(data); TAG1
	}
	if (matrix)
	{
		free_all(matrix);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

unsigned int	toRGB(char *r, char *g, char *b, t_cub *forFree)
{
	int	rgb;
	{
		int converted;
		{
			char	*colors[4] = {b, g, r};
			char	*sucess;
			int	i;
			rgb = 0;
			i = 0;

			while (colors[i])
			{
				converted = strtol(colors[i], &sucess, 10);
				if (*sucess || (converted > 255\
				|| converted < 0))
					error_msg("'F' and/or 'C' attribute value invalid", forFree, NULL);
				rgb += converted << (i * 8);
				i++;
			}
		}
	}
	return (rgb);
}

void	setColor(int* attr, char *value, t_cub *forFree)
{
	char	**splitters;
	char	*tmp;
	int		i;

	if (!value)
		error_msg("No value to 'F' and/or 'C' attribute", forFree, NULL);
	splitters = ft_split(value, ',');
	if (ft_strstrlen(splitters) != 3)
		error_msg("Invalid number of values to 'F' and/or 'C' attribute", forFree, NULL);
	i = 0;
	while (splitters[i])
	{
		tmp = ft_strtrim(splitters[i], " ");
		splitters[i] = tmp;
		i++;
	}
	*attr = toRGB(splitters[0], splitters[1], splitters[2], forFree);
	free_all(splitters);
}

int	space_str(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
