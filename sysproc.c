#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

//New mprotect system call to change the writeable bit of the 
//passed address to 0
int
sys_mprotect(void)
{
  //Declare local instances of arguments
  void *add;
  int len;
  
  //Grab the pointer argument from argv[0], in this
  //it checks if the pointer is in address space
  if(argptr(0, (void*)&add, sizeof(void *)) < 0) 
    return -1;
  //Check if the address is page aligned
  if((uint)add % PGSIZE != 0)
    return -1;
  //Get integer argument from argv[1]
  if(argint(1, &len) < 0)
    return -1;
  //Check if the len is greater than zero
  if(len <= 0)
  	return -1;
  
  return mprotect(add, len);
}

//New munprotect system call to change the writeable bit of the 
//passed address to 1
int
sys_munprotect(void)
{
  //Declare local instances of arguments
  void *add;
  int len;
  
  //Grab the pointer argument from argv[0], in this
  //it checks if the pointer is in address space
  if(argptr(0, (void*)&add, sizeof(void *)) < 0) 
    return -1;
  //Check if the address is page aligned
  if((uint)add % PGSIZE != 0)
    return -1;
  //Get integer argument from argv[1]
  if(argint(1, &len) < 0)
    return -1;
  //Check if the len is greater than zero
  if(len <= 0)
  	return -1;

 
  return munprotect(add, len);
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
