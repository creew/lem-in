
#include "libft.h"

char	*ft_trim_spaces(char *str)
{
	size_t	len;
	char	*r;

	r = str;
	while (ft_isspace(*str))
		str++;
	len = ft_strlen(str);
	while (ft_isspace(str[len - 1]))
		str[--len] = '\0';
	ft_memmove(r, str, len + 1);
	return (r);
}
