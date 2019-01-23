#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <unistd.h>

static const int PATH_MAX = 1024;

void ls(char* argv[])
{
	char buf[PATH_MAX];
	char dir[PATH_MAX];
	getcwd( dir, sizeof(dir) );
	DIR *mydir = opendir(dir);
	struct dirent *myfile = NULL;
	while((myfile = readdir(mydir)) != NULL)
	{
		sprintf(buf, "%s/%s", dir, myfile->d_name);
		write(1, buf, strlen(buf));
		write(1, "\n", 1);
	}
    closedir(mydir);
}
