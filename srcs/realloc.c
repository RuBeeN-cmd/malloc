#include "ft_malloc.h"

t_block_hdr	*get_block_hdr(t_page_hdr *page, void *block)
{
	t_block_hdr	*block_hdr;
	void		*current_block;

	if (!page || !block)
		return (NULL);
	current_block = page + 1;
	for (uint32_t i = 0; i < page->block_num; i++)
	{
		block_hdr = current_block + page->block_size;
		if (current_block == block)
			return (block_hdr);
		current_block = block_hdr + 1;
	}
	return (NULL);
}

void	*realloc_block(void *ptr, size_t size, t_block_hdr *block_hdr)
{
	void	*new_ptr = malloc(size);
	if (!new_ptr)
	{
		// Malloc failed
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, block_hdr->size);
	free(ptr);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	t_page_hdr	*page = get_page(g_page, ptr);
	if (!page || !is_in_page(page, ptr))
	{
		// Invalid pointer
		return (NULL);
	}
	t_block_hdr	*block_hdr = get_block_hdr(page, ptr);
	if (size <= page->block_size)
	{
		// No need to reallocate
		block_hdr->size = size;
		return (ptr);
	}
	return (realloc_block(ptr, size, block_hdr));
}