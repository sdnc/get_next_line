#include "get_next_line.h"

static char *append(int fd, char *buf, char *remainder)
{
    int     bytes_read;
    char    *temp;

    bytes_read = 1;
    while (bytes_read != 0)
    {
        bytes_read = read(1, buf, BUFFER_SIZE);
        if (bytes_read == -1) // This means that there's an error
            return (NULL);
        else if (bytes_read == 0) // This means EOF
            break ;
        buf[bytes_read] = '\0';
        if (!remainder)
            return (ft_strdup(""));
        temp = remainder;
        remainder = ft_strjoin(temp, buf);
        free(temp);
        if (ft_strchr (buf, '\n'))
            break ;
    }
    return (remainder);
}

static char *extract(char *line)
{
    size_t  i;
    char    *remainder;

    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
        i++;
    if (line[i] == '\0' || line[1] == '\0')
        return (0);
    remainder = ft_substr(line, i + 1, ft_strlen(line) - 1);
    if (!remainder)
    {
        free(remainder);
        remainder = NULL;
    }
    line[i + 1] = '\0';
    return (remainder);
}

char	*get_next_line(int fd)
{
    static char *remainder;
    char        *buf;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
    return (NULL);
    line = append(fd, buf, remainder);
    free(buf);
    if (!line)
        return (NULL);
    remainder = extract(line);
    return (line);
}
