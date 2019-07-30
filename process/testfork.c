#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

int main()
{
  pid_t pid = fork();
  if(pid < 0){
    perror("fork error \n");
    exit(1);
  }
  else if(pid == 0){
    pid_t cid = fork();
    if(cid < 0){
      perror("cid fork error \n");
      exit(2);
    }
    else if(cid == 0){
      printf("this is child's child process :%d\n",getpid());
      sleep(5);
    }
    else{
      printf("this is child's parent process :%d\n",getpid());
      sleep(5);
    }
  }
  else{
    printf("this is parent process :%d\n",getpid());
  }
  return 0;
}
