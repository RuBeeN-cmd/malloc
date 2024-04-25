#ifndef MALLOC_H
#define MALLOC_H

#include <libft.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/resource.h>
#include <fcntl.h>

#define C_RED		"\x1b[31m"
#define C_GRN		"\x1b[32m"
#define C_YEL		"\x1b[33m"
#define C_BLU		"\x1b[34m"
#define C_MAG		"\x1b[35m"
#define C_CYN		"\x1b[36m"
#define C_WHT		"\x1b[37m"
#define C_RESET		"\x1b[0m"

#define PREFIX		C_CYN"[malloc] "C_RESET

#define PAGE_SIZE				((size_t) getpagesize())
#define TINY_BLOCK_SIZE			((size_t) 128 + 16 - BLOCK_META_SIZE)
#define SMALL_BLOCK_SIZE		((size_t) 1024 + 16 - BLOCK_META_SIZE)
#define MIN_BLOCK_PER_PAGE		((size_t) 100)

#define BLOCK_META_SIZE			sizeof(t_block_hdr)
#define PAGE_META_SIZE			sizeof(t_page_hdr)

#define USED_SMALL_PAGE_SIZE	(MIN_BLOCK_PER_PAGE * (SMALL_BLOCK_SIZE + BLOCK_META_SIZE) + PAGE_META_SIZE)
#define SMALL_PADDING_SIZE		(PAGE_SIZE - (USED_SMALL_PAGE_SIZE % PAGE_SIZE))
#define SMALL_PAGE_SIZE			(USED_SMALL_PAGE_SIZE + SMALL_PADDING_SIZE)
#define SMALL_BLOCK_NUM			((SMALL_PAGE_SIZE - PAGE_META_SIZE) / (SMALL_BLOCK_SIZE + BLOCK_META_SIZE))

#define USED_TINY_PAGE_SIZE		(MIN_BLOCK_PER_PAGE * (TINY_BLOCK_SIZE + BLOCK_META_SIZE) + PAGE_META_SIZE)
#define TINY_PADDING_SIZE		(USED_TINY_PAGE_SIZE % PAGE_SIZE)
#define TINY_PAGE_SIZE			(USED_TINY_PAGE_SIZE + PAGE_SIZE - TINY_PADDING_SIZE)
#define TINY_BLOCK_NUM			((TINY_PAGE_SIZE - PAGE_META_SIZE) / (TINY_BLOCK_SIZE + BLOCK_META_SIZE))

typedef struct s_page_hdr	t_page_hdr;
typedef struct s_block_hdr	t_block_hdr;

struct s_block_hdr
{
	uint64_t	size;
};

struct __attribute__((packed)) s_page_hdr
{
	uint64_t	block_size;
	uint32_t	block_num;
	uint32_t	phys_block_num;
	t_page_hdr	*next;
};

extern t_page_hdr		*g_page;
extern pthread_mutex_t	g_mutex;

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem();
void	show_alloc_mem_hex();


t_page_hdr	*add_page(t_page_hdr **page, size_t page_size, size_t block_size, size_t block_num);
t_page_hdr	*init_page(size_t page_size, size_t block_size, size_t block_num);
t_page_hdr	*get_page(t_page_hdr *page, void *block);
int			is_in_page(t_page_hdr *page, void *block);
int			is_empty_page(t_page_hdr *page);
void		free_page(t_page_hdr **page, t_page_hdr *page_to_free);

void		collector();

int			get_debug_fd();
void		print_malloc(size_t size);
void		print_free(void *ptr);
void		print_realloc(void *ptr, size_t size);

#endif