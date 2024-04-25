#include "malloc.h"

/**
 * @brief The print_blocks() function prints the blocks.
 * @param page The page to check.
*/
void	print_blocks(t_page_hdr *page)
{
	void		*block;
	t_block_hdr	*block_hdr = (t_block_hdr *)(page + 1);

	for (size_t i = 0; i < page->phys_block_num; i++)
	{
		block = block_hdr + 1;
		if (block_hdr->size)
			ft_printf_fd(1, PREFIX"[%u] Block: "C_BLU"%p"C_RESET" - "C_BLU"%p"C_RESET" - size: "C_BLU"%u"C_RESET"\n", i, block, block + block_hdr->size, block_hdr->size);
		block_hdr = block + page->block_size;
	}
}

/**
 * @brief The show_alloc_mem() function displays the memory allocated.
*/
void	show_alloc_mem()
{
	t_page_hdr	*page = g_page;
	ft_printf_fd(1, PREFIX"Alloc Memory:\n");
	int i = 0;
	while (page)
	{
		char *type = "Large";
		if (page->block_size == TINY_BLOCK_SIZE)
			type = "Tiny";
		else if (page->block_size == SMALL_BLOCK_SIZE)
			type = "Small";
		ft_printf_fd(1, PREFIX"[%d] %s Page : "C_BLU"%p\n"C_RESET, i, type, page);
		i++;
		print_blocks(page);
		page = page->next;
		if (page)
			ft_printf_fd(1, "\n");
	}
}