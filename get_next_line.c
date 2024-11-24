/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakoukou <fakoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:44:57 by fakoukou          #+#    #+#             */
/*   Updated: 2024/11/24 14:10:38 by fakoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_newline(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_remaining_buffer(char *str)
{
	int		i;
	int		j;
	char	*buffer_remaining;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	buffer_remaining = malloc(ft_strlen(str) - i);
	if (!buffer_remaining)
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i])
		buffer_remaining[j++] = str[i++];
	buffer_remaining[j] = '\0';
	free(str);
	return (buffer_remaining);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_until_newline(fd, str);
	if (!str)
		return (NULL);
	line = extract_line(str);
	str = get_remaining_buffer(str);
	return (line);
}

/*int	main(void)
{
    // Test 2: Small BUFFER_SIZE (< 8, and 1)
    printf("\n--- Test with Small BUFFER_SIZE (< 8, and 1) ---\n");
    #define SMALL_BUFFER_SIZE 1  // Adjust as needed
    int small_fd = open("test_large.txt", O_RDONLY);
    if (small_fd < 0)
    {
        perror("Failed to open test_small.txt");
        return 1;
    }
    char *t;

    while((t = get_next_line(small_fd))!= NULL)
    {
        printf("%s" , t);
        free(t);
    }
    close(small_fd);

}*/