/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:19:34 by raweber           #+#    #+#             */
/*   Updated: 2022/10/17 17:34:37 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <unistd.h>

// initializes the wall structs and sets all variables to zero
int	init_walls(t_cub *data)
{
	if (allocate_walls(data))
		return (1);
	data->n_wall->mlx_img = NULL;
	data->n_wall->mlx_img_addr = NULL;
	data->n_wall->bits_per_pxl = 0;
	data->n_wall->line_len = 0;
	data->n_wall->endian = 0;
	data->s_wall->mlx_img = NULL;
	data->s_wall->mlx_img_addr = NULL;
	data->s_wall->bits_per_pxl = 0;
	data->s_wall->line_len = 0;
	data->s_wall->endian = 0;
	data->e_wall->mlx_img = NULL;
	data->e_wall->mlx_img_addr = NULL;
	data->e_wall->bits_per_pxl = 0;
	data->e_wall->line_len = 0;
	data->e_wall->endian = 0;
	data->w_wall->mlx_img = NULL;
	data->w_wall->mlx_img_addr = NULL;
	data->w_wall->bits_per_pxl = 0;
	data->w_wall->line_len = 0;
	data->w_wall->endian = 0;
	return (0);
}

// initializes all ray data and sets floor/ceiling color
void	init_ray_data(t_cub *data)
{
	set_view_direction(data);
	data->perp_dir.x = data->dir.y;
	data->perp_dir.y = data->dir.x * -1;
	data->plane.x = data->perp_dir.x;
	data->plane.y = data->perp_dir.y;
	data->perp_wall_dist = 0;
	data->ray_dir.x = 0;
	data->ray_dir.y = 0;
	data->side_hit = 0;
	data->f_col = -1;
	data->c_col = -1;
	data->map_x = 0;
	data->map_y = 0;
	data->side_dist.x = 0;
	data->side_dist.y = 0;
	data->delta_dist.x = 0;
	data->delta_dist.y = 0;
}

// initializes main struct, player position, view, ray data and textures
int	init_data(t_cub *data)
{
	set_view_direction(data);
	init_ray_data(data);
	data->mlx_data = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx_data)
		return (1);
	init_mlx(data->mlx_data);
	init_walls(data);
	return (0);
}

// initializes the required mlx data
void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_img = NULL;
	mlx->win_ptr = NULL;
	mlx->mlx_img_addr = NULL;
	mlx->win_width = SCREENWIDTH;
	mlx->win_height = SCREENHEIGHT;
	mlx->bits_per_pxl = 0;
	mlx->line_len = 0;
	mlx->endian = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, \
					mlx->win_width, mlx->win_height, "Cub3d");
	mlx->mlx_img = mlx_new_image(mlx->mlx_ptr, \
					mlx->win_width, mlx->win_height);
	mlx->mlx_img_addr = mlx_get_data_addr(mlx->mlx_img, \
					&mlx->bits_per_pxl, &mlx->line_len, &mlx->endian);
}

/*
starts and runs the whole cub3d application
for mac: mlx_hook(data->mlx_data->win_ptr, 2, (1L << 0), &deal_key, data);
for linux: mlx_key_hook(data->mlx_data->win_ptr, &deal_key, data);
*/
int	main(int ac, char **av)
{
	t_cub	*data;

	if (ac != 2)
		error_msg("Invalid number of arguments", NULL, NULL);
	data = (t_cub *)ft_calloc(1, sizeof(t_cub));
	if (!data)
	{
		ft_printf("Error: Could not allocate cub3d struct");
		return (1);
	}

	// Neesd to be freed
	char	*trimmed_all;
	{
		char	*all;
		{
			int		total = 0;
			int		fd;
			{
				int		old_total = 0;
				char	buffer[42];
				const char test[11] = "./test.cub";

				fd = open(test, O_RDONLY);
				printf("This is my path: %s\n", av[1]);
				if (fd == -1)
					perror("File could not be open");
				while (old_total < (total += read(fd, buffer, 42)))
					old_total = total;
				close(fd);
			}
			all = malloc(total + 1);
			fd = open(av[1], O_RDONLY);
			read(fd, all, total);
			close(fd);
			all[total] = '\0';
		}
		trimmed_all = ft_strtrim(all, " \n");
	}

	// Only upper layer needs to be freed
	char	**lines;
	{
		int	nb_linebr;
		nb_linebr = 0;
		{
			int	i;

			i = 0;
			while (trimmed_all[i])
			{
				if (trimmed_all[i++] == '\n')
					nb_linebr++;
			}
			nb_linebr++;
		}
		lines = ft_calloc(sizeof(char *), nb_linebr + 1);
		lines[0] = &trimmed_all[0];
		lines[nb_linebr] = NULL;
		{//Reuse
			int	i;
			int	elem;

			elem = 0;
			i = 0;
			while (trimmed_all[i])
			{
				if (trimmed_all[i++] == '\n')
				{
					trimmed_all[i - 1] = '\0';
					lines[++elem] = &trimmed_all[i];
				}
			}
		}
		// PROBLEMATIC
		int	i;
		int	j;

		i = 0;
		while (lines[i])
		{
			j = i;
			if (space_str(lines[i]))
			{
				while (lines[j])
				{
					lines[j] = lines[j + 1];
					j++;
				}
			}
			i++;
		}
	}

	init_attr(data);

	//Setting attributes (need to be freed)
	{
		int		i;
		char	**splitters;

		i = 0;
		while (lines[i])
		{
			splitters = ft_split(lines[i], ' ');

			// Repetitive
			// int	j = 0;
			// while (splitters[j])
			// 	printf("Splitters: %s\n", splitters[j++]);

			if (!ft_strncmp("NO", splitters[0], 3))
				data->n_path = ft_strdup(splitters[1]);
			else if (!ft_strncmp("EA", splitters[0], 3))
				data->e_path = ft_strdup(splitters[1]);
			else if (!ft_strncmp("SO", splitters[0], 3))
				data->s_path = ft_strdup(splitters[1]);
			else if (!ft_strncmp("WE", splitters[0], 3))
				data->w_path = ft_strdup(splitters[1]);
			else if (!ft_strncmp("F", splitters[0], 2))
				setColor(&data->f_col, ft_strchr(lines[i], ' '), data);
			else if(!ft_strncmp("C", splitters[0], 2))
				setColor(&data->c_col, ft_strchr(lines[i], ' '), data);
			free_all(splitters);
			i++;
		}
		i = 0;
		char *directions[4] = {data->n_path, data->e_path, data->s_path, data->w_path};
		while (i < 4)
		{
			printf("N path: %s\n", data->n_path);
			printf("E path: %s\n", data->e_path);
			printf("S path: %s\n", data->s_path);
			printf("W path: %s\n", data->w_path);
			if (!directions[i++])
				error_msg("At least one attribute is not set", data, NULL);
		}
		if (data->f_col == - 1 || data->c_col == -1)
			error_msg("Either the 'F' or 'C' attribute is not set", data, NULL);
	}


	// Setting worldMap (only upper layer needs to be freed)
	{
		int	firstMap;
		{
			firstMap = ft_strstrlen(lines) - 1;
			while(firstMap >= 0 && ft_strncmp(lines[firstMap], "", 1))
				firstMap--;
			firstMap++;
		}
		data->world_map = malloc(ft_strstrlen(&lines[firstMap]));
		int	j = 0;
		while (lines[firstMap])
			data->world_map[j++] = lines[firstMap++];
		data->world_map[j] = NULL;
	}

	// Test player and characters
	{
		{
			int			i;
			t_charfun	tests[2] = {if_wrong_char, if_excessPlayers};
		
			i = 0;
			while (i < 2)
			{
				all_chars(data->world_map, tests[i], data);
				i++;
			}
		}
		{
			int			i;
			t_coorfun	tests[5] = {if_0sourrounded, if_0sourrounded, if_0sourrounded, if_0sourrounded, if_0sourrounded};
		
			i = 0;
			while (i < 5)
			{
				all_chars2(data->world_map, tests[i], data);
				i++;
			}
		}
	}

	int	i = 0;
	while (data->world_map[i])
		printf("%s\n", data->world_map[i++]);

	exit(0);
	// valid_map();
	if (init_data(data))
		return (1);
	raycasting(data);
	mlx_hook(data->mlx_data->win_ptr, 2, (1L << 0), &deal_key, data);
	mlx_hook(data->mlx_data->win_ptr, 17, 0, &destroy_no_msg, data);
	mlx_loop(data->mlx_data->mlx_ptr);
	return (0);
}
