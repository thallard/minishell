#include "libft.h"

int	ft_free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (-1);
}

