#include "../inc/cub3d.h"

static int		_0_sourrounded(char **matrix, int i, int j)
{
	(void)i;
	(void)j;
	(void)matrix;
	char	*trimmed_line;

	trimmed_line = ft_strdup(matrix[i]);

// 	printf("INPUT: %s\n", matrix[i]);
// 	trimmed_line = ft_strtrim(trimmed_line, " ");
// 	printf("Trimmed line: %s\n", trimmed_line);
// 	// if (!matrix[i + 1])
// 	// {
// 	// 	if (trimmed_line[i] != '1')
// 	// 	{
// 	// 		printf("Point one\n");
// 	// 		free(trimmed_line);
// 	// 		return (1);
// 	// 	}
// 	// }
// 	// if (i == 0 || j == 0)
// 	// {
// 	// 	if (trimmed_line[ft_strlen(trimmed_line) - 1] != '1')
// 	// 	{
// 	// 		printf("Point two\n");
// 	// 		free(trimmed_line);
// 	// 		return (1);
// 	// 	}
// 	// 	if (trimmed_line[0] != '1')
// 	// 	{
// 	// 		printf("Point three\n");
// 	// 		free(trimmed_line);
// 	// 		return (1);
// 	// 	}
// 	// }
// 	// (!trimmed_line) ? free(trimmed_line) : (void)trimmed_line; TAG1
	return (0);
}

void	if_0sourrounded(char **matrix, int i, int j, t_cub *data)
{
	(void)matrix;
	(void)i;
	(void)j;
	(void)data;

	// i = 0;
	// while (matrix[i])
	// 	printf("%s\n", matrix[i++])

	if (_0_sourrounded(matrix, i, j))
		//error_msg("Map is not sourrounded by ones", data, NULL)
		;
	
}

static int	wrong_char(char c)
{
	int		allowed;
	char	set[8] = " 01NOSW";

	allowed = 0;
	while (set[allowed])
	{
		if (c == set[allowed])
			return (0);
		allowed++;
	}
	return (1);
}

void	if_wrong_char(char c, t_cub *data)
{
	if (wrong_char(c))
		error_msg("Map contains invalid characters", data, NULL);
}

static int	excessPlayers(char c)
{
	static	int onePlayer = 0;
	char	set[5] = "NESW";
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			if (onePlayer)
				return (1);
			onePlayer = 1;
		}
		i++;
	}
	return (0);
}

void	if_excessPlayers(char c, t_cub *data)
{
	if (excessPlayers(c))
		error_msg("Map contains not exactly one player", data, NULL);
}

void	setPlayer(char **str, int i, int j, t_cub *data)
{
	char	set[5] = "NESW";
	int		k;

	k = 0;
	while (set[k])
	{
		if (str[i][j] == set[k])
		{
			data->pos.y = i;
			data->pos.x = j;
		}
		k++;
	}
}
