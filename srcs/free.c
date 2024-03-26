#include "ft_malloc.h"

t_page_hdr	*get_page(t_page_hdr *page, void *block)
{
	if (!page)
		return (NULL);
	if (block < (void *) page || block >= ((void *) (page + 1)) + page->block_num * (page->block_size + BLOCK_META_SIZE))
		return (get_page(page->next, block));
	return (page);
}

int	is_alloc(t_page_hdr *page, void *block)
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
			return (!block_hdr->size);
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

void	free_page(t_page_hdr **page, t_page_hdr *page_to_free)
{
	t_page_hdr	*current_page = *page;
	t_page_hdr	*prev_page = NULL;

	while (current_page)
	{
		if (current_page == page_to_free)
		{
			if (prev_page)
				prev_page->next = current_page->next;
			else
				*page = current_page->next;
			munmap(current_page, current_page->block_num * (current_page->block_size + BLOCK_META_SIZE) + PAGE_META_SIZE);
			return ;
		}
		prev_page = current_page;
		current_page = current_page->next;
	}
}

void	free(void *ptr)
{
	if (!ptr)
		return ;
	t_page_hdr	*page = get_page(g_page, ptr);
	if (!page || !is_alloc(page, ptr))
	{
		// Invalid free
		return ;
	}
	t_block_hdr *block_hdr = ptr + page->block_size;
	ft_bzero(ptr, block_hdr->size + BLOCK_META_SIZE);
	if (is_empty_page(page))
		free_page(&g_page, page);
}