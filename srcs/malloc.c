#include "ft_malloc.h"

t_page_hdr	*g_page = NULL;

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
	void		*block;
	t_page_hdr	*page = g_page;
	
	if (block_num != 1)
	{
		block = find_block(g_page, block_size);
		if (!block)
		{
			page = add_page(&g_page, page_size, block_size, block_num);
			block = page + 1;
		}
	}
	else
	{
		page = add_page(&g_page, page_size, block_size, block_num);
		block = page + 1;
	}
	block_hdr = block + block_size;
	block_hdr->size = size;
	return (block);
}

void	pre_allocate()
{
	if (g_page)
		return ;
	add_page(&g_page, TINY_PAGE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCK_NUM);
	add_page(&g_page, SMALL_PAGE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCK_NUM);
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
		block = define_block(size, ((size + PAGE_META_SIZE + BLOCK_META_SIZE) + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE, size, 1);
	show_alloc_mem();
	return (block);
}

