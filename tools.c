#include "cub3d.h"


void	free_double(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free (ptr);

}

// int is_invalid_rgb(const char *input)
// {
//     int count = 0;
//     char **token;
//     int i;

//     token = ft_split(input, ",");
//     i = 0;

//     while (token[i]) {
//         token[i] = htr_trim(token[i]);

//         int val = 0;
//         int is_valid_number = 1;
//         int k = 0;

//         do {
//             if (!isdigit(token[i][k])) {
//                 is_valid_number = 0;
//                 break;
//             }
//             val = val * 10 + (token[i][k] - '0');
//             k++;
//         } while (token[i][k] != '\0');

//         if (!is_valid_number || val < 0 || val > 255) {
//             free(token);
//             return 1;
//         }

//         count++;
//         i++;
//     }

//     free(token);
//     return count != 3;
// }

