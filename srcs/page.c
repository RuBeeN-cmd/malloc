#include "ft_malloc.h"

t_page_hdr	*init_page(size_t page_size, uint16_t block_size, uint16_t block_num)
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
	t_page_hdr	*new_page;
	t_page_hdr	*current;
	
	current = *page;
	if (!page)
		return (NULL);
	new_page = init_page(page_size, block_size, block_num);
	if (!new_page)
		return (NULL);
	if (!current)
	{
		*page = new_page;
		return (*page);
	}
	while (current && current->next)
		current = current->next;
	current->next = new_page;
	return (current->next);
}

t_page_hdr	*get_page(t_page_hdr *page, void *block)
{
	if (!page)
		return (NULL);
	if (block < (void *) page || block >= ((void *) (page + 1)) + page->block_num * (page->block_size + BLOCK_META_SIZE))
		return (get_page(page->next, block));
	return (page);
}

int	is_in_page(t_page_hdr *page, void *block)
{
	t_block_hdr	*block_hdr;
	void		*current_block;

	if (!page || !block)
		return (0);
	current_block = page + 1;
	for (uint32_t i = 0; i < page->block_num; i++)
	{
		block_hdr = current_block + page->block_size;
		if (current_block == block)
			return (block_hdr->size != 0);
		current_block = block_hdr + 1;
	}
	return (0);
}

int	is_empty_page(t_page_hdr *page)
{
	void		*current_block = page + 1;
	t_block_hdr	*block_hdr;

	for (uint32_t i = 0; i < page->block_num; i++)
	{
		block_hdr = current_block + page->block_size;
		if (block_hdr->size)
			return (0);
		current_block = block_hdr + 1;
	}
	return (1);
}