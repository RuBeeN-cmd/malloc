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