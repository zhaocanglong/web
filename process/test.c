//#include<stdio.h>
//#include<unistd.h>
//#include<errno.h>
//#include<stdlib.h>
//int main()
//{
//  pid_t pid = fork();
//  if(pid < 0){
//    perror("fork() error\n");
//    return -1;
//  }
//  else if(pid == 0){
//    printf("this is child process : %d\n",getpid());
//    sleep(30);
//    exit(1);
//  }
//  else{
//    int st,ret;
//    printf("this is parent process: %d\n",getpid());
//    ret = waitpid(-1,&st,0);
//    if(ret > 0 && (st & 0x7F) == 0){
//      printf("child exit code: %d\n",(st>>8)&0xFF);
//    }
//    else if(ret > 0){
//      printf("segment exit code:%d\n",st&0xFF);
//    }
//  }
//  return 0;
//.autorelabel
//}
//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <sys/wait.h>
//int main()
//{
//  pid_t pid;
//  pid = fork();
//  if(pid < 0){
//    printf("%s fork error\n",__FUNCTION__);
//    return 1;
//
//  }else if( pid == 0  ){ //child
//  printf("child is run, pid is : %d\n",getpid());
//  sleep(5);
//  exit(1);
//  } else{
//    int status = 0;
//    pid_t ret = 0;
//   // do
//   // {
//      ret = waitpid(-1, &status, WNOHANG);//非阻塞式等待
//      if( ret == 0  ){
//        printf("child is running\n");
//
//      }
//     //  sleep(1);
//
//   // }while(ret == 0);
//    if( WIFEXITED(status) && ret == pid  ){
//      printf("wait child 5s success, child return code is :%d.\n",WEXITSTATUS(status));
//
//    }else{
//      printf("wait child failed, return.\n");
//      return 1;
//
//    }
//
//  }
//  return 0;

//}

