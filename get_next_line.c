/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprevota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:59:53 by jprevota          #+#    #+#             */
/*   Updated: 2017/04/17 17:19:46 by jprevota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"
#include "./libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		get_next_line(const int fd, char **line)
{
	static char	*buff_end;
	int			i;
	int			eof;

	i = 0;
	if (fd < 0 || !line)
		return (-1);
	if (buff_end == NULL &&
			!(buff_end = (char *)malloc(BUFF_SIZE + 1 * sizeof(char))))
		return (-1);
	ft_strclr(*line);
	if (check_nl(buff_end) == 1)
	{
		while (buff_end[i] != '\n')
			i++;
		*line = ft_strncpy(*line, buff_end, i);
		eof = 1;
	}
	else
		eof = read_till_nl(fd, buff_end, line);
	if (ft_strlen(buff_end) > 0 && check_nl(buff_end) == 1)
		buff_end = ft_strchr(buff_end, '\n') + 1;
	if (eof == 0 || (check_nl(buff_end) == 0))
		return (0);
	return (1);
}

int		read_till_nl(int fd, char *buff_end, char **line)
{
	int		i;
	int		ret;
	char	*tmp;

	tmp = ft_strnew((size_t)(BUFF_SIZE + 1));
	while (check_nl(buff_end) != 1 && ret > 0)
	{
		*line = ft_strjoin(*line, buff_end);
		ret = read(fd, buff_end, BUFF_SIZE);
		buff_end[ret] = '\0';
	}
	i = 0;
	while (buff_end[i] != '\n' && buff_end[i] != '\0')
	{
		tmp[i] = buff_end[i];
		i++;
	}
	tmp[i] = '\0';
	*line = ft_strjoin(*line, tmp);
	return (ret);
}

int		check_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int			fd;
	char		**line;
	int			gnl;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (-1);
		if (!(line = (char **)malloc(1 * sizeof(char *))))
			return (-1);
		*line = ft_strnew((size_t)(BUFF_SIZE + 1));
		while ((gnl = get_next_line(fd, line)) != 0)
		{
			ft_putnbr(gnl);
			ft_putendl(" // Line :");
			ft_putstr(*line);
			ft_putchar('\n');
		}
		ft_putnbr(gnl);
		ft_putendl(" // Line :");
		ft_putstr(*line);
	}
	else
		ft_putendl("File missing");
	return (0);
}
