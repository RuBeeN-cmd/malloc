#include "malloc.h"

/**
 * @brief The print_byte() function prints a byte in hexadecimal.
 * @param byte The byte to print.
*/
void	print_byte(uint8_t byte)
{
	char hex[2];

	hex[0] = "0123456789ABCDEF"[byte / 16];
	hex[1] = "0123456789ABCDEF"[byte % 16];
	ft_printf("%c%c", hex[0], hex[1]);
}

/**
 * @brief The print_blocks() function prints the blocks.
 * @param page The page to check.
*/
void	print_blocks_hex(t_page_hdr *page)
{
	void		*block;
	t_block_hdr	*block_hdr = (t_block_hdr *)(page + 1);

	for (size_t i = 0; i < page->phys_block_num; i++)
	{
		block = block_hdr + 1;
		if (block_hdr->size)
		{
			for (size_t i = 0; i < BLOCK_META_SIZE; i++)
			{
				if (!(i % 8))
					ft_printf("%p  "C_GRN, (uint8_t *)block_hdr + i);
				print_byte(*((uint8_t *)block_hdr + i));
				if (i % 8 == 7)
					ft_printf("\n"C_RESET);
				else
					ft_printf(" ");
			}
			for (size_t i = 0; i < page->block_size; i++)
			{
				if (!(i % 8))
					ft_printf("%p  "C_BLU, block + i);
				print_byte(*((uint8_t *)block + i));
				if (i % 8 == 7)
					ft_printf("\n"C_RESET);
				else
					ft_printf(" ");
			}
		}
		block_hdr = block + page->block_size;
	}
}

/*
 * @brief The show_alloc_mem_hox() function displays the memory allocated in hexadecimal.
 */
void	show_alloc_mem_hex()
{
	t_page_hdr	*page = g_page;
	while (page)
	{
		for (size_t i = 0; i < PAGE_META_SIZE; i++)
		{
			if (!(i % 8))
				ft_printf("%p  "C_RED, (uint8_t *)page + i);
			print_byte(*((uint8_t *)page + i));
			if (i % 8 == 7)
				ft_printf("\n"C_RESET);
			else
				ft_printf(" ");
		}
		print_blocks_hex(page);
		page = page->next;
		if (page)
			ft_printf("---------------------------------------\n");
	}
}