#include "malloc.h"

void	collector()
{
	for (t_page_hdr *crt_page = g_page; crt_page; crt_page = crt_page->next)
		free_page(&g_page, crt_page);
}