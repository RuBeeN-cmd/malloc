#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <libft.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>

#define PT_TINY		0
#define PT_SMALL	1
#define PT_LARGE	2
#define PT_NUM		3

typedef struct s_page	t_page;

struct s_page
{
	uint8_t	type;
	t_page	*next;
};

void	*malloc(size_t size);
void	free(void *ptr);

#endif