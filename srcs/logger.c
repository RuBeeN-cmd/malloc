#include "malloc.h"

/**
 * @brief The get_debug_fd() function gets the file descriptor for the debug malloc. If DEBUG_MALLOC
*/
int	get_debug_fd()
{
	static int fd = -1;

	if (fd == -1)
	{
		char *debug_type = getenv("MALLOC_DEBUG");
		if (!debug_type)
			fd = -2;
		else if (ft_strncmp(debug_type, "file", 4) == 0)
		{
			fd = open(getenv("MALLOC_DEBUG_PATH"), O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
				fd = -2;
		}
		else if (ft_strncmp(debug_type, "stdout", 6) == 0)
			fd = STDOUT_FILENO;
		else
			fd = -2;
	}
	return (fd);
}

void	print_malloc(size_t size)
{
	int		fd = 1;
	char	*prefix = "";
	char	*reset = "";

	fd = get_debug_fd();
	if (fd == -2)
		return ;
	if (fd == STDOUT_FILENO)
	{
		prefix = PREFIX C_GRN;
		reset = C_RESET;
	}
	ft_printf_fd(fd, "%smalloc(%u)%s called\n", prefix, size, reset);
}

void	print_free(void *ptr)
{
	int		fd = 1;
	char	*prefix = "";
	char	*reset = "";

	fd = get_debug_fd();
	if (fd == -2)
		return ;
	if (fd == STDOUT_FILENO)
	{
		prefix = PREFIX C_RED;
		reset = C_RESET;
	}
	ft_printf_fd(fd, "%sfree(%p)%s called\n", prefix, ptr, reset);
}

void	print_realloc(void *ptr, size_t size)
{
	int		fd = 1;
	char	*prefix = "";
	char	*reset = "";

	fd = get_debug_fd();
	if (fd == -2)
		return ;
	if (fd == STDOUT_FILENO)
	{
		prefix = PREFIX C_YEL;
		reset = C_RESET;
	}
	ft_printf_fd(fd, "%srealloc(%p, %u)%s called\n", prefix, ptr, size, reset);
}