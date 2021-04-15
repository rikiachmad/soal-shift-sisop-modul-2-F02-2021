#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  pid_t child1, child;
  int status;
  char *username = getenv("USER");  //mendapatkan username dalam format string
  char destination[100] = "/home/", sourceZip[100];

  strcat(destination,username);
  strcpy(sourceZip,destination);

  strcat(sourceZip,"/Downloads/pets.zip"); //directory pets.zip
  strcat(destination,"/modul2");

  child1 = fork();
  if(child1==0)
  {
    char *mkdirModul[] = {"mkdir", destination, NULL};  //command buat directory
    execv("/usr/bin/mkdir", mkdirModul);  //menjalankan mkdir dari file c
  }
  while ((wait(&status)) > 0);

  strcat(destination, "/petshop");  //directory untuk isi pets.zip

  child = fork();
  if(child == 0)
  {
      char *argv[] = {"unzip" , sourceZip, "-d", destination, NULL};  //command unzip pets.zip ke directory tujuan
      execv("/usr/bin/unzip", argv);  //menjalankan unzip dari file c
  }
  while ((wait(&status)) > 0);
}
