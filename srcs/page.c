#include "malloc.h"

/**
 * @brief The init_page() function initializes a page.
 * @param page_size The size of the page.
 * @param block_size The size of a block.
 * @param block_num The number of blocks.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
*/
t_page_hdr	*init_page(size_t page_size, size_t block_size, size_t block_num)
{
	t_page_hdr		*page;

	page = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (page == MAP_FAILED)
		return (NULL);
	page->next = NULL;
	page->block_size = block_size;
	page->block_num = block_num;
	page->phys_block_num = 0;
	return (page);
}

/**
 * @brief The add_page() function adds a page to a block.
 * @param page The page list to add the page to.
 * @param page_size The size of the page.
 * @param block_size The size of a block.
 * @param block_num The number of blocks.
 * @return On success, a pointer to the memory block allocated by the function. NULL otherwise.
*/
t_page_hdr	*add_page(t_page_hdr **page, size_t page_size, size_t block_size, size_t block_num)
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

/**
 * @brief The get_page() function gets a page from a block.
 * @param page The page list to check.
 * @param block The block to check.
*/
t_page_hdr	*get_page(t_page_hdr *page, void *block)
{
	if (!page || !block)
		return (NULL);
	if (block < (void *) page || block >= ((void *) (page + 1)) + page->block_num * (page->block_size + BLOCK_META_SIZE))
		return (get_page(page->next, block));
	return (page);
}

/**
 * @brief The is_in_page() function checks if a block is in a page.
 * @param page The page to check.
 * @param block The block to check.
 * @return On success, 1 if the block is in the page, 0 otherwise.
*/
int	is_in_page(t_page_hdr *page, void *block)
{
	t_block_hdr	*crt_block_hdr;
	void		*crt_block;

	if (!page || !block)
		return (0);
	crt_block_hdr = (t_block_hdr *) (page + 1);
	for (uint32_t i = 0; i < page->phys_block_num; i++)
	{
		crt_block = (void *) crt_block_hdr + BLOCK_META_SIZE;
		if (crt_block == block)
			return (crt_block_hdr->size != 0);
		crt_block_hdr = crt_block + page->block_size;
	}
	return (0);
}

/**
 * @brief The is_empty_page() function checks if a page is empty.
 * @param page The page to check.
 * @return On success, 1 if the page is empty, 0 otherwise.
*/
int	is_empty_page(t_page_hdr *page)
{
	void		*current_block = page + 1;
	t_block_hdr	*block_hdr;

	if (!page)
		return (0);
	for (uint32_t i = 0; i < page->phys_block_num; i++)
	{
		block_hdr = current_block + page->block_size;
		if (block_hdr->size)
			return (0);
		current_block = block_hdr + 1;
	}
	return (1);
}

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