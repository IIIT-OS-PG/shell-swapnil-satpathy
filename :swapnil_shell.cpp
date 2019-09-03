#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include  <stdio.h>
#include  <sys/types.h>










void  parse(char *line, char **argv)
{
     while (*line != '\0') {      
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';    
          *argv++ = line;         
          while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
               line++;            
     }
     *argv = '\0';                
}





     
int  main(void)
{
     char  line[1024];             
     char  *argv[64];
     pid_t pid;
     int status;              
     
     while (1) {                  
          printf("#");     
          gets(line);             
          printf("\n");
          parse(line, argv);      
          if (strcmp(argv[0], "exit") == 0)  
               break; 
          
          if(strcmp(argv[0],"cd")==0){
                
                chdir(argv[1]);
                continue; 
} 
          

          
            
                          
          
          pid=fork();
          if(pid<0){
            printf("Error while doing fork() operation\n");
            exit(1);
            }
          else if(pid==0){
            if(execvp(*argv,argv)<0)
                {
                printf("Error while doing exec() operation\n");
                exit(1);
                }
             }
          else{
            while(wait(&status)!=pid);
            }
            /*if(strcmp(argv[1],">")==0){
            freopen(argv[2], "w", stdout);
                
                }

            if(strcmp(argv[1],">>")==0){
            freopen(argv[2], "a+", stdout);
                
                }*/
    
          
     }
     return 0;
}

                