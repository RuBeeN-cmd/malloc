#include "malloc.h"

/**
 * @brief The get_block_hdr() function gets a block header from a block.
 * @param page The page to check.
 * @param block The block to check.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
 */
t_block_hdr	*get_block_hdr(t_page_hdr *page, void *block)
{
	void		*crt_block;
	t_block_hdr	*crt_block_hdr;

	if (!page || !block)
		return (NULL);
	crt_block_hdr = (t_block_hdr *) (page + 1);
	for (uint32_t i = 0; i < page->phys_block_num; i++)
	{
		crt_block = (void *) crt_block_hdr + BLOCK_META_SIZE;
		if (crt_block == block)
			return (crt_block_hdr);
		crt_block_hdr = crt_block + page->block_size;
	}
	return (NULL);
}

/**
 * @brief The realloc_block() function reallocates a block of memory.
 * @param ptr The pointer to the memory block that needs to be reallocated.
 * @param size The new size of the memory block.
 * @param block_hdr The block header.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
*/
void	*realloc_block(void *ptr, size_t size, t_block_hdr *block_hdr)
{
	void	*new_ptr = malloc(size);
	if (!new_ptr)
	{
		// Malloc failed
		return (NULL);
	}
	pthread_mutex_lock(&g_mutex);
	size_t	copy_size = block_hdr->size < size ? block_hdr->size : size;
	ft_memcpy(new_ptr, ptr, copy_size);
	pthread_mutex_unlock(&g_mutex);
	free(ptr);
	return (new_ptr);
}

/**
 * @brief The realloc() function changes the size of the memory block pointed to by ptr to size bytes.
 * @param ptr The pointer to the memory block that needs to be reallocated.
 * @param size The new size of the memory block.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
 */
void	*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&g_mutex);
	print_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_mutex);
	t_page_hdr	*page = get_page(g_page, ptr);
	if (!page || !is_in_page(page, ptr))
	{
		// Invalid pointer
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	t_block_hdr	*block_hdr = get_block_hdr(page, ptr);
	if (size <= page->block_size)
	{
		// No need to reallocate
		block_hdr->size = size;
		pthread_mutex_unlock(&g_mutex);
		return (ptr);
	}
	pthread_mutex_unlock(&g_mutex);
	void	*new_ptr = realloc_block(ptr, size, block_hdr);
	return (new_ptr);
}