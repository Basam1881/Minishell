#include <dirent.h>
#include <stdio.h>

int main(int ac, char **av)
{
	
	DIR *d;
	struct dirent *dir_struct;

	d = opendir(".");
	if (!d)
		return (1);
	while(1)
	{
		dir_struct = readdir(d);
		if(!dir_struct)
			break;
		printf("%s\n", dir_struct->d_name);
	}
	closedir(d);
}

int	check_name(char *name, char *wild_card)
{
	int i = 0;
	int j = 0;
	int k = 0;
	/* 
		 c = "moatasem.c"
		 c2= "mohammed.c"
		wc = "mo*ta*.c" 
	 */
}