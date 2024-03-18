#include "ft_malloc.h"

t_page_hdr	*g_page = NULL;

// t_page_hdr	*get_page(t_page_hdr *page, void *block)
// {
// 	if (!page)
// 		return (NULL);
// 	if (block < page || block >= ((void *) (page + 1)) + page->block_num * (page->block_size + BLOCK_META_SIZE))
// 		return (get_page(page->next, block));
// 	return (page);
// }

void	free(void *ptr)
{
	(void) ptr;
	// t_page_hdr	*page = get_page(g_page, ptr);
	// if (!page)
	// 	return ;
	// t_block_hdr *block_hdr = ptr + page->block_size;
}

void	*get_block(t_page_hdr *page)
{
	return (page + 1);
}

void	*get_block_header(t_page_hdr *page)
{
	return (((void *) page + 1) + page->block_size);
}

t_page_hdr	*init_page_hdr(size_t page_size, uint16_t block_size, uint16_t block_num)
{
	t_page_hdr	*page;

	page = mmap(NULL, page_size, PROT_READ | PROT_WRITE, 0x20 | MAP_PRIVATE, -1, 0); // 0x20 = MAP_ANONYMOUS
	if (page == MAP_FAILED)
	{
		ft_printf("mmap failed\n");
		return (NULL);
	}
	page->next = NULL;
	page->block_size = block_size;
	page->block_num = block_num;
	return (page);
}

t_page_hdr	*add_page(t_page_hdr **page, size_t page_size, uint16_t block_size, uint16_t block_num)
{
	t_page_hdr	*current = *page;
	if (!page)
		return (NULL);
	if (!current)
	{
		*page = init_page_hdr(page_size, block_size, block_num);
		return (*page);
	}
	while (current && current->next)
		current = current->next;
	current->next = init_page_hdr(page_size, block_size, block_num);
	return (current->next);
}

void	pre_allocate()
{
	if (g_page)
		return ;
	add_page(&g_page, TINY_PAGE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCK_NUM);
	add_page(&g_page, SMALL_PAGE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCK_NUM);
}

void	*find_free_block(t_page_hdr *page)
{
	t_block_hdr	*block_hdr;
	void		*block;

	if (!page)
		return (NULL);
	block = page + 1;
	for (uint32_t i = 0; i < page->block_num; i++)
	{
		block_hdr = block + page->block_size;
		if (!block_hdr->size)
			return (block);
		block = block_hdr + 1;
	}
	return (NULL);
}

void	*find_block(t_page_hdr *page, uint32_t block_size)
{
	if (!page)
		return (NULL);
	if (page->block_size == block_size)
	{
		void *block = find_free_block(page);
		if (block)
			return (block);
	}
	return (find_block(page->next, block_size));
}

void	*define_block(uint64_t size, size_t page_size, uint16_t block_size, uint16_t block_num)
{
	t_block_hdr	*block_hdr;
	t_page_hdr	*page = g_page;
	void		*block = find_block(g_page, block_size);
	if (!block)
	{
		page = add_page(&g_page, page_size, block_size, block_num);
		block = page + 1;
	}
	block_hdr = block + block_size;
	block_hdr->size = size;
	return (block);
}

void	*define_large_block(uint64_t size, size_t page_size, uint16_t block_size, uint16_t block_num)
{
	t_block_hdr	*block_hdr;
	void		*block;
	t_page_hdr	*page;

	page = add_page(&g_page, page_size, block_size, block_num);
	block = page + 1;
	block_hdr = block + page->block_size;
	block_hdr->size = size;
	return (block);
}

void	*malloc(size_t size)
{
	void	*block = NULL;
	if (!g_page)
		pre_allocate();
	if (size <= TINY_BLOCK_SIZE)
		block = define_block(size, TINY_PAGE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCK_NUM);
	else if (size <= SMALL_BLOCK_SIZE)
		block = define_block(size, SMALL_PAGE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCK_NUM);
	else
		block = define_large_block(size, ((size + PAGE_META_SIZE + BLOCK_META_SIZE) + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE, size, 1);
	if (size == 16000)
		print_pages(g_page);
	return (block);
}

