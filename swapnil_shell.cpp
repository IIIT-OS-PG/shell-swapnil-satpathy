#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include  <stdio.h>
#include  <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;





void  separate(char *line, char **argv)
{
     while (*line != '\0') {      
          while (*line == ' ')
               *line++ = '\0';    
          *argv++ = line;
         
          while (*line != '\0' && *line != ' ')
               line++;            
     }
     *argv = '\0';                
}




void redirectionforone(char **argv, int l){
    int status2;
    pid_t pid2;
    char *argv2[64];
    int k=0;
    int j=0;
    for(;argv[j]!='\0';j++){
            if(strcmp(argv[j],">")==0)
                break;
            else{
            argv2[k]=argv[j];
            k++;
            }
        }
        
argv2[k]='\0';
   
    pid2=fork();
    if(pid2<0){
        cout<<"Error while doing fork() operation"<<endl;
        exit(1);
    }
    else if(pid2==0){
        
        int fdout=open(argv[j+1], O_WRONLY | O_CREAT, 0664);
        dup2(fdout, STDOUT_FILENO);
        close(fdout);
        
        if(execvp(*argv2,argv2)<0){
            cout<<"Error while doing exec() in redirection"<<endl;
        
    }
    else{
        while(wait(&status2)!=pid2);
        close(fdout);
    }
    }
    
    return;
    
}



void redirectionfortwo(char **argv, int l){
    int status2;
    pid_t pid3;
    char *argv3[64];
    int k=0;
    int j=0;
    for(;argv[j]!='\0';j++){
        if(strcmp(argv[j],">>")==0)
            break;
        else{
            argv3[k]=argv[j];
            k++;
        }
    }
    
    argv3[k]='\0';
    
    pid3=fork();
    if(pid3<0){
        cout<<"Error while doing fork() operation"<<endl;
        exit(1);
    }
    else if(pid3==0){
        
        int fdout=open(argv[j+1], O_WRONLY | O_APPEND, 0664);
        dup2(fdout, STDOUT_FILENO);
        close(fdout);
        
        if(execvp(*argv3,argv3)<0){
            cout<<"Error while doing exec() in redirection"<<endl;
            
        }
        else{
            while(wait(&status2)!=pid3);
            close(fdout);
        }
    }
    
    return;
    
}














int  main(void)
{
     char  line[1024];             
     char  *argv[64];
     pid_t pid;
     int status; 
     int argc=0;             
     
     while (1) {                  
          printf("$");     
          gets(line);             
          printf("\n");
          separate(line, argv);
          if (strcmp(argv[0], "exit") == 0)  
               break; 
         

         if(strcmp(argv[0],"cd")==0){
                
                chdir(argv[1]);
                continue; 
            }
         
        
         
         
         int flag=0;
         
         for(int i=0;argv[i]!='\0';i++){
             if(strcmp(argv[i],">")==0){
                 redirectionforone(argv,i);
                 flag=1;
                 
             }
         }
         if(flag==1)
             continue;
         
         
         int flag_2=0;
         
         for(int i=0;argv[i]!='\0';i++){
             if(strcmp(argv[i],">>")==0){
                 redirectionfortwo(argv,i);
                 flag_2=1;
                 
             }
         }
         if(flag_2==1)
             continue;
         
         
        
                 
         
          pid=fork();
          if(pid<0){
            cout<<"Error while doing fork() operation"<<endl;
            exit(1);
            }
          else if(pid==0){
            if(execvp(*argv,argv)<0)
                {
                cout<<"Error while doing exec() operation.Kindly check the command"<<endl;
                exit(1);
                }
          }
             
          else{
            while(wait(&status)!=pid);
           }
    
         
     }
     return 0;
}

                
