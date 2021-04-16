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
#define maxSize 100

/*
  fungsi untuk cek apakah punya suffix yang sama
*/
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

/*
  Fungsi untuk membuat folder baru dan memindahkan sesuai dengan soal.
  Dengan 3 parameter yaitu nama file asli, nama file jika lebih dari
  satu foto hewan dengan menghilangkan spesifikasi hewan yang sudah 
  dikelompokkan dan direktori tujuan semua file.
*/
void createFolder(char *filename, char *newName, char *current_dir){
  pid_t child;
  int i, status;
  bool more_than_one = false; //cek apakah ada lebih dari satu pet
  for(i=0;i<strlen(newName);i++)
    if(newName[i] == '_'){
      more_than_one = true;
      break;
    }
  int j;
  
  /*
    Spesifikasi dari foto yang ada (kategori, nama dan umur)
    Kategori dimulai dari "/" agar langsung digabung dengan direktori
  */
  char category[maxSize] = "/";
  char name[maxSize];
  char umur[5];
  
  /*
  Mengetahui kategori hewan dari nama
  */
  for(j = 0; j<strlen(newName); j++){
    category[j+1] = newName[j];
    if(newName[j] == ';'){
      category[j+1] = '\0';
       break;
     }
  }
  
  /*
    Mendapatkan nama dari hewan yang dimaksud
  */
  int counter = 0;j++;
  for(;j<strlen(newName)-4; j++){
    if(newName[j] == ';'){
      name[counter] = '\0';
      break;
    }
    name[counter++] = newName[j];
  }
  
  /*
    Mendapatkan umur dari binatang peliharaan.
  */
  counter = 0; j++;
  for(;j<strlen(newName)-4;j++){
    if(newName[j] == '_'){
      break;
    }
    umur[counter++] = newName[j];
  }
  umur[counter] = '\0';
  
  /*
    Folder baru untuk karegori tiap binatang dengan menggabungkan 
    direktori saat ini dengan nama kategori
  */
  char newFolder[maxSize];
  strcpy(newFolder, current_dir);
  strcat(newFolder, category);  //folder baru

  /*
    Membuat file txt berisi keterangan yang dimasukkan pada folder tiap kategori,
    yaitu newFolder.
  */
  char keterangan[maxSize];
  strcpy(keterangan, newFolder);
  strcat(keterangan, "/keterangan.txt");
  // printf("%d\n", access(newFolder, F_OK));

  /*
    Path dari nama file untuk melakukan copy
  */
  char copy_file[maxSize];
  strcpy(copy_file, current_dir);
  strcat(copy_file, "/");
  strcat(copy_file, filename);

  /*
    Path tujuan dari copy dengan langsung mengubah namanya menjadi
    [nama].jpg
  */
  char newPath[maxSize];
  strcpy(newPath, newFolder);
  strcat(newPath, "/");
  strcat(newPath, name);
  strcat(newPath, ".jpg");

  /*
    Membuat folder baru untuk kategori dengan memeriksa apakah folder
    sudah ada atau belum
  */
  if(access(newFolder, F_OK) == -1){  //folder belum ada
    child = fork();
    if(child==0)
    {
      char *arg[] = {"mkdir", newFolder, NULL};  //command buat directory
      execv("/usr/bin/mkdir", arg);  //menjalankan mkdir dari file c
    }
    while ((wait(&status)) > 0);
  }

  /*
    Copy file dari path file sumber ke path rujuan
  */
  child = fork();
  if(child == 0){
    char *argv[] = {"cp", copy_file, newPath};
    execlp("cp", argv[0], argv[1], argv[2], NULL);
  }
  while ((wait(&status)) > 0);

  /*
    Mengisi nama dan umur di keterangan.txt tiap folder
  */
  FILE *fptr = fopen(keterangan, "a");
  fprintf(fptr, "nama : %s\numur : %s tahun\n\n", name, umur);
  fclose(fptr);

  /*
    Jika lebih dari satu pet, lakukan rekursi karena tidak pasti
    berapa jumlah pet dalam satu foto.
  */
  if(more_than_one){
    char newName[maxSize];
    i++;j=0;
    for(; i<strlen(filename); i++, j++)
      newName[j] = filename[i];
    newName[j] = '\0';
    createFolder(filename, newName, current_dir);   //panggil kembali fungsi ini dengan menghilangkan informasi pet depan
    //printf("%s\n", newName);
  }
  
  /*
    Jika sudah copy semua file, hapus.
    Dari awal tidak menggunakan move karena ada yang lebih dari satu pet
  */
  else{
    child = fork();
    if(child == 0){
      char *remove[] = {"rm", copy_file, NULL};
      execv("/usr/bin/rm", remove);
    }
    while ((wait(&status)) > 0);
  }
}

int main(int argc, char *argv[])
{
  pid_t child1, child;
  int status;
  char *username = getenv("USER");  //mendapatkan username dalam format string
  char destination[maxSize] = "/home/", sourceZip[maxSize];

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

      /*
        Jika berakhiran jpg, artinya file yang ditunjuk merupakan file gambar/foto
      */
      if(is_suffix(ep->d_name,".jpg")){
        createFolder(ep->d_name, ep->d_name, destination);
      }
      
      else if ( !strcmp(ep->d_name, ".") || !strcmp(ep->d_name, "..") );  //Folder sekarang atau folder parent, jadi biarkan saja
      
      else{
        /*
          hapus folder yang tidak digunakan
        */
        char to_remove[maxSize];
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
