#include "ft_malloc.h"

/**
 * @brief The free_page() function frees a page.
 * @param page The page list to free.
 * @param page_to_free The page to free.
*/
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

/**
 * @brief The free() function frees the memory space pointed to by ptr.
 * @param ptr The pointer to the memory that needs to be freed.
*/
void	free(void *ptr)
{
	if (!ptr)
	{
		// Invalid free
		return ;
	}
	t_page_hdr	*page = get_page(g_page, ptr);
	if (!page || !is_in_page(page, ptr))
	{
		// Invalid free
		return ;
	}
	ft_bzero(ptr, page->block_size + BLOCK_META_SIZE);
	if (is_empty_page(page))
		free_page(&g_page, page);
}