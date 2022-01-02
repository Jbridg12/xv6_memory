/*
* This test case protects the address then unprotects it in the child process 
* then again once to ensure the parent is also unprotected before it writes to it again
* 
* This test case runs to completion without any errors
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
	if(munprotect((void*)p, 1) < 0)
		exit();
	p[0] = 's';
	exit();
}
