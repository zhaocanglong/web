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
    printf("this is child1 process: %d\n",getpid());
    sleep(5);
    exit(3);
//    pid_t cid = fork();
//    if(cid < 0){
//      perror("cid fork error \n");
//      exit(2);
//    }
//    else if(cid == 0){
//      printf("this is child's child process :%d\n",getpid());
//      sleep(5);
//    }
//    else{
//      printf("this is child's parent process :%d\n",getpid());
//      sleep(5);
//    }
  }
  else{
    pid_t cid = fork();
    printf("start this is parent process\n");
    if(cid < 0){
      perror("cid fork error\n");
      exit(2);
    }
    else if(cid == 0){
      printf("this is child2 process: %d\n",getpid());
      sleep(5);
      exit(4);
    }
    else{  
      int st;
      pid_t ret;
      printf("this is parent process :%d\n",getpid());
      ret = waitpid(-1,&st,0);
      if(WIFEXITED(st) && ret == cid){
        printf("wait child process:%d\n",WEXITSTATUS(st));
      }
      else{
        perror("error");
      }
    }
  }
  return 0;
}
