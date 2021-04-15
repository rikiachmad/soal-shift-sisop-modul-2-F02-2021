#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

bool is_suffix(char *filename, char *suffix){
  int filename_length = strlen(filename);
  int suffix_length = strlen(suffix);
  if(filename_length < suffix_length) return false;
  int i,j;
  for(i=suffix_length-1, j=1; i>=0; i--, j++){
    if(suffix[i] != filename[filename_length-j])
      return false;
  }
  return true;
}

void createFolder(char *filename, char *current_dir){
  int i, status;
  bool more_than_one = false; //cek apakah ada lebih dari satu pet
  for(i=0;i<strlen(filename);i++)
    if(filename[i] == '_'){
      more_than_one = true;
      break;
    }
  int j;
  char category[100] = "/"; //mengetahui kategori untuk membuat folder
  for(j = 0; j<strlen(filename); j++){
    category[j+1] = filename[j];
    if(filename[j] == ';'){
      category[j+1] = '\0';
       break;
     }
  }
  
  char newFolder[100];
  strcpy(newFolder, current_dir);
  strcat(newFolder, category);  //folder baru

  // printf("%d\n", access(newFolder, F_OK));
  if(access(newFolder, F_OK) == -1){  //folder belum ada
    pid_t child;
    child = fork();
    if(child==0)
    {
      char *arg[] = {"mkdir", newFolder, NULL};  //command buat directory
      execv("/usr/bin/mkdir", arg);  //menjalankan mkdir dari file c
    }
    while ((wait(&status)) > 0);
  }

  if(more_than_one){
    char newName[100];
    i++;j=0;
    for(; i<strlen(filename); i++)
      newName[j++] = filename[i];
    newName[j] = '\0';
    createFolder(newName, current_dir);   //panggil kembali fungsi ini dengan menghilangkan informasi pet depan
    //printf("%s\n", newName);
  }
}

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

  DIR *dp;
  struct dirent *ep;
  // int count = 0;
  dp = opendir(destination);
  if (dp != NULL)
  {
    while ((ep = readdir (dp))) {
      if(is_suffix(ep->d_name,".jpg")){
        createFolder(ep->d_name, destination);
      }
      else if ( !strcmp(ep->d_name, ".") || !strcmp(ep->d_name, "..") );
      else{
        char to_remove[100];
        strcpy(to_remove, destination);
        strcat(to_remove,"/");
        strcat(to_remove, ep->d_name);
        child = fork();
        if(child == 0){
          char *remove[] = {"rm", "-rf", to_remove, NULL};
          execv("/usr/bin/rm", remove);
        }
        while ((wait(&status)) > 0);
        // count++;
      }
    }

    (void) closedir (dp);
  } else perror ("Couldn't open the directory");
  // printf("%d\n",count );
}
