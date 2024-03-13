#include "ft_malloc.h"

t_page_hdr	*g_page = NULL;

void	free(void *ptr)
{
	(void) ptr;
}

void	*get_block(t_page_hdr *page)
{
	return (page + 1);
}

void	*get_block_header(t_page_hdr *page)
{
	return (((void *) page + 1) + page->block_size);
}

t_page_hdr	*init_page_hdr(size_t page_size, uint16_t block_size, uint16_t block_num)
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
	ft_printf(PREFIX C_YEL"New Page:"C_BLU" %p\n"C_RESET, page);
	ft_printf(PREFIX C_YEL"Block Hdr:"C_BLU" %p\n"C_RESET, get_block_header(page));
	ft_printf(PREFIX C_YEL"Block:"C_BLU" %p\n"C_RESET, get_block(page));
	ft_printf(PREFIX C_YEL"Block Size:"C_BLU" %u\n"C_RESET, block_size);
	ft_printf(PREFIX C_YEL"Block Num:"C_BLU" %u\n"C_RESET, block_num);
	ft_printf(PREFIX C_YEL"Block Hdr Size:"C_BLU" %u\n"C_RESET, sizeof(t_block_hdr));
	return (page);
}

void	add_page(t_page_hdr **page, int type)
{
	t_page_hdr	*current = *page;
	if (!page)
		return ;
	if (!current)
	{
		if (type == PT_TINY)
			*page = init_page_hdr(TINY_PAGE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCK_NUM);
		else if (type == PT_SMALL)
			*page = init_page_hdr(SMALL_PAGE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCK_NUM);
		return ;
	}
	while (current && current->next)
		current = current->next;
	if (type == PT_TINY)
		current->next = init_page_hdr(TINY_PAGE_SIZE, TINY_BLOCK_SIZE, TINY_BLOCK_NUM);
	else if (type == PT_SMALL)
		current->next = init_page_hdr(SMALL_PAGE_SIZE, SMALL_BLOCK_SIZE, SMALL_BLOCK_NUM);
}

void	pre_allocate()
{
	if (g_page)
		return ;
	ft_printf(PREFIX C_YEL"Pre-allocating Tiny Page\n"C_RESET);
	add_page(&g_page, PT_TINY);
	ft_printf("\n"PREFIX C_YEL"Pre-allocating Small Page\n"C_RESET);
	add_page(&g_page, PT_SMALL);
}

void	print_allocated()
{
	t_page_hdr		*page = g_page;
	t_block_hdr	*block;
	int		block_num;
	int		i = 0;
	while (page)
	{
		block_num = page->block_num;
		ft_printf(C_GRN"Page %d:"C_RESET"\n", i++);
		block = get_block(page);
		while (block_num--)
		{
			if (block->size)
				ft_printf("Block: %p\n", block);
			block++;
		}
		page = page->next;
	}
}

void	*malloc(size_t size)
{
	if (!g_page)
		pre_allocate();
	ft_printf(PREFIX C_GRN"Size: %u ", size);
	if (size <= TINY_BLOCK_SIZE)
	{
		ft_printf(", Tiny Block Asked\n"C_RESET);
	}
	else if (size <= SMALL_BLOCK_SIZE)
	{
		ft_printf(", Small Block Asked\n"C_RESET);
	}
	else
	{
		ft_printf(", Large Block Asked\n"C_RESET);
	}
	return (NULL);
}

