#include "malloc.h"

/**
 * @brief The get_page_index() function gets the index of a page.
 * @param page The page to check.
 * @return On success, the index of the page. -1 otherwise.
*/
int	get_page_index(t_page_hdr *page)
{
	t_page_hdr	*current_page = g_page;
	int			index = 0;

	while (current_page)
	{
		if (current_page == page)
			return (index);
		index++;
		current_page = current_page->next;
	}
	return (-1);
}


/**
 * @brief The free() function frees the memory space pointed to by ptr.
 * @param ptr The pointer to the memory that needs to be freed.
*/
void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	t_page_hdr	*page = get_page(g_page, ptr);
	if (!page || !is_in_page(page, ptr))
	{
		// Invalid free
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	ft_bzero(ptr - BLOCK_META_SIZE, BLOCK_META_SIZE);
	if (get_page_index(page) > 1 && is_empty_page(page))
		free_page(&g_page, page);
	pthread_mutex_unlock(&g_mutex);
}