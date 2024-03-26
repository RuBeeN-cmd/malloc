#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <libft.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define C_RED		"\x1b[31m"
#define C_GRN		"\x1b[32m"
#define C_YEL		"\x1b[33m"
#define C_BLU		"\x1b[34m"
#define C_MAG		"\x1b[35m"
#define C_CYN		"\x1b[36m"
#define C_WHT		"\x1b[37m"
#define C_RESET		"\x1b[0m"

#define PREFIX		C_CYN"[ft_malloc] "C_RESET

#define PT_TINY		0
#define PT_SMALL	1
#define PT_LARGE	2
#define PT_NUM		3

#define PAGE_SIZE				getpagesize()
#define TINY_BLOCK_SIZE			128 - BLOCK_META_SIZE
#define SMALL_BLOCK_SIZE		1024 - BLOCK_META_SIZE
#define MIN_BLOCK_PER_PAGE		100
#define BLOCK_META_SIZE			(int) sizeof(t_block_hdr)
#define PAGE_META_SIZE			(int) sizeof(t_page_hdr)
#define TINY_PAGE_NUM			(((TINY_BLOCK_SIZE + BLOCK_META_SIZE) * MIN_BLOCK_PER_PAGE + PAGE_META_SIZE + PAGE_SIZE - 1) / PAGE_SIZE)
#define SMALL_PAGE_NUM			(((SMALL_BLOCK_SIZE + BLOCK_META_SIZE) * MIN_BLOCK_PER_PAGE + PAGE_META_SIZE + PAGE_SIZE - 1) / PAGE_SIZE)
#define TINY_BLOCK_NUM			(TINY_PAGE_NUM * PAGE_SIZE - PAGE_META_SIZE) / (TINY_BLOCK_SIZE + BLOCK_META_SIZE)
#define SMALL_BLOCK_NUM			(SMALL_PAGE_NUM * PAGE_SIZE - PAGE_META_SIZE) / (SMALL_BLOCK_SIZE + BLOCK_META_SIZE)
#define TINY_PAGE_SIZE			TINY_BLOCK_NUM * PAGE_SIZE
#define SMALL_PAGE_SIZE			SMALL_BLOCK_NUM * PAGE_SIZE

typedef struct s_page_hdr	t_page_hdr;
typedef struct s_block_hdr	t_block_hdr;

struct s_block_hdr
{
	uint64_t	size;
};

struct __attribute__((packed)) s_page_hdr
{
	uint32_t	block_size;
	uint32_t	block_num;
	t_page_hdr	*next;
};

extern t_page_hdr	*g_page;

void	*malloc(size_t size);
void	free(void *ptr);

void	show_alloc_mem();

t_page_hdr	*add_page(t_page_hdr **page, size_t page_size, uint16_t block_size, uint16_t block_num);
t_page_hdr	*init_page(size_t page_size, uint16_t block_size, uint16_t block_num);

#endif