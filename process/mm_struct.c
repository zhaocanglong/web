#include<stdio.h>
#include<unistd.h>
#include<errno.h>

int g_val = 0;

int main(){
  pid_t pid;
  pid = fork();
  if(pid < 0){
    perror("fork error\n");
  }
  else if(pid == 0){
    printf("this is child process...........\n");
    printf("g_val:%d g_val'adress: %p\n",g_val,&g_val);
  }
  else{
    printf("this is parent process..........\n");
    printf("g_val:%d g_val'adress: %p\n",g_val = 100,&g_val);
    sleep(5);
  }

  return 0;
}
