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

void	free(void *ptr)
{
	t_page_hdr	*page = get_page(g_page, ptr);
	if (!page)
	{
		// Invalid free
		return ;
	}
	t_block_hdr *block_hdr = ptr + page->block_size;
	ft_bzero(ptr, block_hdr->size + BLOCK_META_SIZE);
}