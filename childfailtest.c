/*
* This test case protects the address then writes to it in the child process 
* then unprotects he memory and writes to it in both processes.
* 
* This test case throws a trap error in the child when the process reaches line 24
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
		p[0] = 's';
	}
	else
	{
		wait();
	}
	if(munprotect((void*)p, 1) < 0)
		exit();
	p[0] = 'R';
	exit();
}
