#include "malloc.h"

void	collector()
{
	if (!g_page)
		return ;
	for (t_page_hdr *crt_page = g_page; crt_page; crt_page = g_page)
		free_page(&g_page, crt_page);
}

void	check_leaks()
{
	void *crt_block; 
	unsigned long long nb_bytes = 0;
	unsigned long long nb_blocs = 0;

	for (t_page_hdr *crt_page = g_page; crt_page; crt_page = crt_page->next)
	{
		t_block_hdr *crt_block_hdr = (void *) (crt_page + 1); 
		for (uint32_t i = 0; i < crt_page->phys_block_num; i++)
		{
			crt_block = (void *) crt_block_hdr + BLOCK_META_SIZE;
			nb_bytes += crt_block_hdr->size;
			if (crt_block_hdr->size)
				nb_blocs++;
			crt_block_hdr = crt_block + crt_page->block_size;
		}
	}
	ft_printf_fd(1, "=== in use at exit: %u bytes in %u blocks ===\n", nb_bytes, nb_blocs);
}