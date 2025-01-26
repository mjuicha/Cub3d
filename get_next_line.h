#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*empty_str(void);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *str, char *buff);
char	*the_line(char *str);
char	*next_line(char *str);
char	*read_line(int fd, char *str);

#endif