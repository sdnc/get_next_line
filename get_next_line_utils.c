#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strdup(char *str)
{
    int i;
    char    *copy;

    i = 0;
    copy = malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!copy)
        return (NULL);
    while (str[i])
    {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *megastr;

    i = 0;
    j = 0;
    megastr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
    if (!megastr)
        return (NULL);
    while (s1[i])
    {
        megastr[i] = s1[i];
        i++;
    }
    while (s2[j])
        megastr[i++] = s2[j++];
    megastr[i] = '\0';
    return (megastr);
}

char    *ft_strchr(char *str, int i)
{
    if (!i)
        return (str);
    while (*str)
    {
        if (*str == i)
            return (str);
        str++;
    }
    return (NULL);
}

char    *ft_substr(char *str, int start, int end)
{
    char *substr;
    int i;

    i = 0;
    substr = malloc(sizeof(char) * (ft_strlen(str) - start - end));
    while (i < start)
        i++;
    while (i <= end)
    {
        *substr = str[i];
        substr++;
        i++;
    }
    *substr = '\0';
    return (substr);
}