#include "ft_str.h"
#include "ft_mem.h"

int			ft_strmatch_opt(const char *str, const char *match, int option)
{
	int		ret;
	char	*tmp;
	t_mchi	*head;

	if (!str || !match || !(head = ft_getmchi(match)))
		return (0);
	tmp = (char *)str;
	if ((option & RGX_BKSLSH) && (tmp = ft_strdupli(str)))
		tmp = (tmp ? tmp : (char *)str);
	ret = ft_strtks(tmp, head, option);
	ft_delmchi(head);
	if ((option & RGX_BKSLSH) && tmp != str)
	{
		if (ret && (ret = -1))
			while (++ret < g_iread)
				if (str[ret] == '\\' && ++g_iread)
					if (str[++ret])
						++g_iread;
		free(tmp);
	}
	return (ret ? 1 : 0);
}

static void	end_match(char	**tmp1, const char *match, int n, int option)
{
	if (!match)
		return ;
	if (option == -1)
		ft_memdel((void **)tmp1);
	else if ((option & RGX_N))
		if (n < (int)ft_strlen(match))
			*tmp1 = ft_strndup(match, n);
}

int			ft_strnmatch_opt(const char *str, const char *match, int n,
						int option)
{
	int		ret;
	char	*tmp[2];
	t_mchi	*head;

	tmp[1] = NULL;
	end_match(&tmp[1], match, n, option);
	if (!str || !match || !(head = ft_getmchi(tmp[1] ? tmp[1] : match)))
		return (0);
	end_match(&tmp[1], match, n, (option & RGX_N ? -1 : 0));
	tmp[0] = (char *)str;
	if ((option & RGX_BKSLSH) && (tmp[0] = ft_strdupli(str)))
		tmp[0] = (tmp[0] ? tmp[0] : (char *)str);
	ret = ((option & RGX_N) ? ft_strtks(tmp[0], head, option)
			: ft_strntks(tmp[0], head, n, option));
	ft_delmchi(head);
	if ((option & RGX_BKSLSH) && tmp[0] != str)
	{
		if (ret && (ret = -1))
			while (++ret < g_iread)
				if (str[ret] == '\\' && ++g_iread)
					if (str[++ret])
						++g_iread;
		free(tmp[0]);
	}
	return (ret ? 1 : 0);
}
