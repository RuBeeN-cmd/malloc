#include "malloc.h"

t_page_hdr	*g_page = NULL;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief The find_free_block() function finds a free block of memory.
 * @param page The page to search in.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
*/
void	*find_free_block(t_page_hdr *page)
{
	t_block_hdr	*block_hdr;
	void		*block;

	if (!page || page->phys_block_num >= page->block_num)
		return (NULL);
	block_hdr = (t_block_hdr *)(page + 1);
	block = block_hdr + 1;
	for (uint32_t i = 0; i < page->phys_block_num; i++)
	{
		if (!block_hdr->size)
			return (block);
		block_hdr = block + page->block_size;
		block = block_hdr + 1;
	}
	page->phys_block_num++;
	return (block);
}

/**
 * @brief The find_block() function finds a block of memory.
 * @param page The page to search in.
 * @param block_size The size of a block.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
*/
void	*find_block(t_page_hdr *page, uint32_t block_size)
{
	if (!page)
		return (NULL);
	if (page->block_size == block_size && page->phys_block_num < page->block_num)
	{
		void *block = find_free_block(page);
		if (block)
			return (block);
	}
	return (find_block(page->next, block_size));
}

/**
 * @brief The define_block() function defines a block of memory, and create a page if necessary.
 * @param size The size of the memory that needs to be allocated.
 * @param page_size The size of the page.
 * @param block_size The size of a block.
 * @param block_num The number of blocks.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
*/
void	*define_block(size_t size, size_t page_size, size_t block_size, size_t block_num)
{
	t_block_hdr	*block_hdr;
	void		*block = NULL;
	t_page_hdr	*page = g_page;
	
	if (block_num != 1)
		block = find_block(g_page, block_size);
	if (!block)
	{
		page = add_page(&g_page, page_size, block_size, block_num);
		if (!page)
			return (NULL);
		block = (void *) (page + 1) + BLOCK_META_SIZE;
		page->phys_block_num++;
	}
	block_hdr = block - BLOCK_META_SIZE;
	block_hdr->size = size;
	return (block);
}

/**
 * @brief The pre_allocate() function pre-allocate memory for TINY and SMALL pages.
*/
void	pre_allocate()
{
	if (g_page)
		return ;
	add_page(&g_page, TINY_PAGE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCK_NUM);
	add_page(&g_page, SMALL_PAGE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCK_NUM);
}

/**
 * @brief The enable_garbage_collector() function enable the garbage collector if the env variable "MALLOC_COLLECTOR" equal to "atexit"
*/
void	enable_garbage_collector()
{
	char *garbage_collector = getenv("MALLOC_COLLECTOR");
	if (garbage_collector && !ft_strncmp(garbage_collector, "atexit", 6))
		atexit(collector);
}

/**
 * @brief The malloc() function allocates size bytes and returns a pointer to the allocated memory.
 * If size is 0, then malloc() returns either NULL.
 * @param size The size of the memory that needs to be allocated.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
 */
void	*malloc(size_t size)
{
	pthread_mutex_lock(&g_mutex);
	void	*block = NULL;

	print_malloc(size);
	if (!g_page)
	{
		enable_garbage_collector();
		pre_allocate();
	}
	if (!size)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	if (size <= TINY_BLOCK_SIZE)
		block = define_block(size, TINY_PAGE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCK_NUM);
	else if (size <= SMALL_BLOCK_SIZE)
		block = define_block(size, SMALL_PAGE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCK_NUM);
	else
	{
		size_t	page_size = ((size + PAGE_META_SIZE + BLOCK_META_SIZE) + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE;
		size_t	block_size = page_size - PAGE_META_SIZE - BLOCK_META_SIZE;
		block = define_block(size, page_size, block_size, 1);
	}
	pthread_mutex_unlock(&g_mutex);
	return (block);
}