#include "ft_malloc.h"

/**
 * @brief The print_blocks() function prints the blocks.
 * @param page The page to check.
*/
void	print_blocks(t_page_hdr *page)
{
	void		*block = page + 1;
	t_block_hdr	*block_hdr;

	for (size_t i = 0; i < page->block_num; i++)
	{
		block_hdr = block + page->block_size;
		if (block_hdr->size)
			ft_printf(PREFIX"Block: "C_BLU"%p"C_RESET" - Block_hdr: "C_BLU"%p"C_RESET" - size: "C_BLU"%u"C_RESET"\n", block, block_hdr, block_hdr->size);
		block = block_hdr + 1;
	}
}

/**
 * @brief The show_alloc_mem() function displays the memory allocated.
*/
void	show_alloc_mem()
{
	t_page_hdr	*page = g_page;
	
	while (page)
	{
		ft_printf(PREFIX"Page Hdr : "C_BLU"%p\n"C_RESET, page);
		print_blocks(page);
		if (page->next)
			ft_printf("\n");
		page = page->next;
	}
}