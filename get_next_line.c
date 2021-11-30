/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdzamari <dza.sara@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:18:19 by sdzamari          #+#    #+#             */
/*   Updated: 2021/11/03 14:11:35 by sdzamari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include <stdio.h> //for testing with main
// #include <fcntl.h> //for testing

/*

bytes_read is assigned value by calling the <unistd.h> 
read function with the fd, buffer and macro-set BUFFER_SIZE.
If read returns -1 it means there's an error, while 0 means EOF (end of file).

If remainder has no value, it is assigned the value of an empty string.
Temp is assigned the value of remainder to protect the value for the next step.

Remainder is then assigned a new value by calling ft_strjoin, attaching buffer to the end of temp.
Temp is then freed.

If a new-line character is found in buffer, the loop is broken.
Finally, the function returns the static char *remainder.

*/
static char	*read_and_append(int fd, char *buffer, char *remainder)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		temp = remainder;
		remainder = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (remainder);
}

/*

Idx is set to 0 and then incremented while the value at the
current index of the line is not a new-line character NOR a null-terminator.
After incrementation, if the value of line at the current index or index place 1
is a null-terminator, the function returns 0.

Remainder is assigned a new value by creating a sub-string from line with the
starting point of the idx value + 1, and a total length of length of line - the idx value.
If there is no value in remainder, it is freed and assigned a NULL value.

*/
static char	*update_next_line(char *line)
{
	size_t	idx;
	char	*remainder;

	idx = 0;
	while (line[idx] != '\n' && line[idx] != '\0')
		idx++;
	if (line[idx] == '\0' || line[1] == '\0')
		return (0);
	remainder = ft_substr(line, idx + 1, ft_strlen(line) - idx);
	if (*remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	line[idx + 1] = '\0';
	return (remainder);
}

/*

line is the string to return. Remainder is a static char as it holds on the
leftovers of line during program run-time. Returns 0 in case of undefined input values.

This function is concerned with assigning values to the different variables,
allocating space in memory for the buffer and then freeing it after usage.

*/

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = read_and_append(fd, buffer, remainder);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remainder = update_next_line(line);
	return (line);
}

/*
int	main(void)
{
	int	fd;
	char *str;

	fd = open("test", O_RDWR);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	return 0;
}
*/