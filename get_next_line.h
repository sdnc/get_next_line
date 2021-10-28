#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 1042

int     ft_strlen(char *str);
char    *ft_strdup(char *str);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_strchr(char *str, int i);
char    *ft_substr(char *str, int start, int end);
char    *get_next_line(int fd);

#endif
