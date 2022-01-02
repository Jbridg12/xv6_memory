/*
* This test case protects the address then unprotects it in the child process 
* then tries to write to the memory in the parent which is still protected
* 
* This test case throws a trap error in the parent when the process reaches line 32
*/

#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[]) {
	char *p = malloc(sizeof(char)*4096);
	p[0] = 'Q';
	int pid;
	if(mprotect((void*)p, 1) < 0)
		exit();
	if((pid = fork()) == -1)
		exit();
	  
	if(pid == 0)
	{
		if(munprotect((void*)p, 1) < 0)
			exit();
		p[0] = 's';
	}
	else
	{
		wait();
	}
	p[0] = 's';
	exit();
}
