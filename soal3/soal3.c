#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <wait.h>
#include <time.h>
#include <string.h>

void encriptCaesar(char message[], int shift){
  char c;
    for(int i=0; message[i] != '\0'; i++)
    {
      c = message[i];
      if(c >= 'a' && c<= 'z'){
        c = c + shift;

        if(c > 'z'){
          c = c - 'z' + 'a' - 1;
        }
        message[i] = c;
      }
      else if(c >= 'A' && c<= 'Z'){
        c = c + shift;

        if(c > 'Z'){
          c = c - 'Z' + 'A' - 1;
        }
        message[i] = c;
      }
    }
}

void zipDir(char date[]){
  char output[30];
  strcpy(output, date);
  strcat(output, ".zip");
  char *argv[] = {"/usr/bin/zip", "-r", output, date, NULL};
  execv("/usr/bin/zip", argv);
}

void rmDir(char folder[])
{
  char *argv[] = {"rm", "-r", folder, NULL};
    execv("/bin/rm", argv);
}

void makeDir(char date[])
{
  char *argv[] = {"mkdir", "-p",date, NULL};
  execv("/bin/mkdir", argv);
}

void download(char date2[], char link[], char folder[])
{
  strcat(folder,date2);
  char *argv[] = {"/usr/bin/wget", "-bq","-O",folder, link, NULL};
  execv("/usr/bin/wget" ,argv);
}

void makeFile(char folder[])
{
  strcat(folder, "status.txt");
  FILE *outfile = fopen(folder, "w+");
  char message[50] = "Download Success";
  encriptCaesar(message, 5);
  fputs(message, outfile);
  fclose(outfile);
}

void createKiller(const char* c[], int sid){
  FILE *outfile = fopen("Killer.sh", "w+");
  char s[10];
  sprintf(s, "%d",sid);
  fputs("#!/bin/bash\n", outfile);
  if(strcmp(c[1], "-x")==0){
    fputs("kill -15 ", outfile);
    fputs(s, outfile);
  }
  else if(strcmp(c[1], "-z")==0){
    fputs("killall -9 ", outfile);
    fputs(c[0], outfile);
  }
  fclose(outfile);
}

int main(int argc, const char* argv[]) {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/riki/Praktikum2/")) < 0) {
    exit(EXIT_FAILURE);
  }
  createKiller(argv,(int)sid);

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    pid_t child_id;
    child_id=fork();
    if (child_id < 0) {
      exit(EXIT_FAILURE);
    }
    char date[80];
    struct tm * timeinfo;
    time_t t;
    if(child_id==0)
    {
        pid_t child2_id;
        int status;
        child2_id = fork();
        time (&t);
        timeinfo = localtime(&t);
        strftime (date, 80, "%Y-%m-%d_%H:%M:%S", timeinfo);
        if (child2_id < 0) {
          exit(EXIT_FAILURE);
        }
        if(child2_id==0){
          makeDir(date);
        }
        else{
          while((wait(&status))>0);
          int seconds;
          char folder [100] = "/home/riki/Praktikum2/";
          strcat(folder, date);
          strcat(folder, "/");
          for(int i=0; i<10; i++){
            pid_t child4_id = fork();
            seconds = (time_t)(time(NULL)%1000) + 50;
            char link[100] = "https://picsum.photos/";
            char str[10];
            sprintf(str, "%d", seconds);
            strcat(link, str);
            struct tm * dates;
            time_t u;
            time (&u);
            char date2[50];
            dates = localtime(&u);
            strftime (date2, 80, "%Y-%m-%d_%H:%M:%S", dates);
            if(child4_id==0)
              download(date2, link, folder);
            sleep(5);
          }
          makeFile(folder);
          int s;
          pid_t child5_id = fork();
          if(child5_id == 0)
          {
            zipDir(date);
          }
          else{
            while((wait(&s))>0);
            rmDir(date);
          }
        }
    }
  sleep(40);
  }
}
