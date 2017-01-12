#include <unistd.h>
#include <string.h>

static const int PATH_MAX = 1024;

void pwd(char* argv[])
{
	char buff[PATH_MAX];
	getcwd( buff, sizeof(buff) );
	/* TODO: Finish this command */
	write(1, buff, strlen(buff));
	write(1, "\n", 1);
}
