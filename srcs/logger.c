#include "malloc.h"

int	get_debug_fd()
{
	static int fd = -1;

	if (fd == -1)
		fd = open("debug.log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd);
}