#include "ft_malloc.h"

void	print_addresses(t_page_hdr *page)
{
	ft_printf(PREFIX"Page Hdr : "C_BLU"%p\n"C_RESET, page);
}

void	print_blocks(t_page_hdr *page)
{
	void		*block = page + 1;
	t_block_hdr	*block_hdr;

	for (size_t i = 0; i < page->block_num; i++)
	{
		block_hdr = block + page->block_size;
		if (block_hdr->size)
			ft_printf(PREFIX"Block: "C_BLU"%p"C_RESET" - size: "C_BLU"%u"C_RESET"\n", block, block_hdr->size);
		block = block_hdr + 1;
	}
}

void	show_alloc_mem()
{
	t_page_hdr	*page = g_page;
	
	while (page)
	{
		print_addresses(page);
		print_blocks(page);
		if (page->next)
			ft_printf("\n");
		page = page->next;
	}
}