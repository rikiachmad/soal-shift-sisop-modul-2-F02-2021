# soal-shift-sisop-modul-2-F02-2021

# Soal 3
## Sub Soal-a
Pada Sub soal a, diminta untuk membuat sebuah direktori tiap 40 detik dengan nama sesuai dengan timestamp [YYYY-mm-dd_HH:ii:ss].
Disini kita dapat menggunakan library time.h untuk mendapatkan format waktu sebagai nama direktori.
``` C
char date[80];
struct tm * timeinfo;
time_t t;
time (&t);
timeinfo = localtime(&t);
strftime (date, 80, "%Y-%m-%d_%H:%M:%S", timeinfo);
```
source code diatas berfungsi untuk menamai direktori sesuai dengan format yang diminta oleh soal.
Lalu untuk dapat memebuat direktori setiap 40 detik, maka dapat digunakan template daemon sesuai dengan modul dengan sleep(40),dan untuk membuat direktori nya sendiri dapat menggunakan fungsi execv, perlu diingat bahwa execv akan menggantikan proses yang berjalan saat ini, sehingga agar program tidak berhenti setelah menggunakan execv, maka perlu dilakukan fork() untuk spawn child process yang nantinya akan menjalankan command exxecv ini.
``` C
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
```
fungsi makedir():
``` C
void makeDir(char date[])
{
  char *argv[] = {"mkdir", "-p",date, NULL};
  execv("/bin/mkdir", argv);
}
```
![image](https://user-images.githubusercontent.com/74702068/115959634-5737ef80-a537-11eb-9b04-db14a7a118ae.png)

## Sub Soal-b
Pada sub soal-b, setelah membuat direktori sesuai dengan permintaan sub-soal a, direktori yang telah dibuat tersebut diisi dengan 10 file gambar yang di download tiap 5 detik dengan link yang tertera dan format penamaan file yang sama seperti sub-soal a.
Gambar yang di download harus berukuran (n%1000)+50 pixel dimana n merupakan detik Epoch linux. Kita dapat melakukan hal ini dengan looping sebanyak 10 kali dan tiap-tiap loop nya akan melakukan spawn child process untuk download gambar sesuai permintaan soal dan di akhir loop diberikan sleep selama 5 detik.
Berikut Source Code nya.
``` C
while((wait(&status))>0);
int seconds;
char folder [100] = "/home/riki/Praktikum2/";
strcat(folder, date);
strcat(folder, "/");
for(int i=0; i<10; i++){
  //spawn child process agar tidak menterminate program saat pemanggilan execv
  pid_t child4_id = fork();
  //detik Epoch
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
    //download gambar
    download(date2, link, folder);
  sleep(5);
}
```
Fungsi download :
``` C
void download(char date2[], char link[], char folder[])
{
  strcat(folder,date2);
  char *argv[] = {"/usr/bin/wget", "-bq","-O",folder, link, NULL};
  execv("/usr/bin/wget" ,argv);
}
```
![image](https://user-images.githubusercontent.com/74702068/115959641-6323b180-a537-11eb-8ff0-eda54eb8642e.png)


## Sub Soal-c
Setelah direktori terisi dengan 10 gambar, Program diharuskan membuat sebuah file status.txt yang berisi "Download Success" yang dienkripsi dengan teknik caesar cypher dengan shift 5.
Setelah file tersebut dibuat, direktori akan di zip dan direktori akan dihapuse sehingga hanya menyisakan file zip.
Untuk membuat file status.txt dapat menggunakan standart input output dari C dan untuk teknik encripsi caesar dapat dilakukan dengan menggeser angka ASCII dari tiap-tiap karakter.
fungsi makeFile():
``` C
void makeFile(char folder[])
{
  strcat(folder, "status.txt");
  FILE *outfile = fopen(folder, "w+");
  char message[50] = "Download Success";
  encriptCaesar(message, 5);
  fputs(message, outfile);
  fclose(outfile);
}
```
fungsi encriptCaesar():
``` C
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
```
fungsi zipDir() dan rmDir():
```C
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
```
![image](https://user-images.githubusercontent.com/74702068/115959647-6f0f7380-a537-11eb-9958-237555c487e6.png)

## Sub soal-d dan soal-e
untuk sub soal-d dan e, saya mengerjakannya sekaligus karena sub soal e merupakan lanjutan dari sub soal d.
Pada sub soal d, diminta untuk membuat program killer berupa bash dimana apabila program tersebut dijalankan, maka akan menterminate program C yang sedang berjalan dan akan menghapus dirinya sendiri.
Dan untuk sub-soal e, program killer yang dibuat memiliki dua mode yaitu pada saat program utama dipanggil dengan argumen -z dan -x. 
Saat program utama dipanggil dengan argumen -z, maka pada saat program killer dijalankan akan menterminate semua proses yang sedang berlangsung, sedangkan untuk argumen -x apabila program bash dijalankan makan akan menunggu hingga direktori beserta isinya dibuat lalu di zip dan process akan berhenti.
Untuk menyelesaikan sub-problem d dan e, saya membuat fungsi createKiller yang mengambil argumen berupa constant argv dari parameter main dan sid. Hal ini digunakan untuk menyimpan argumen pada saat program dipanggil dengan sebuah argumen dan untuk menyimpan pid dari process tersebut.
Lalu untuk di dalam fungsi tersebut akan melakukan pengecekan apakah argumen merupakan "-z" ataukan "-x".
Apabila argumen merupakan "-z" maka program bash yang akan dibuat akan berisi command 
``` Bash
killall -9 [nama file] 
rm Killer.sh
```
dan apabila argumen merupakan "-x", maka program bash akan berisi
```Bash
kill -15 [pid]
rm Killer.sh
```
Source Code:
``` C
void createKiller(const char* c[], int sid){
  FILE *outfile = fopen("Killer.sh", "w+");
  char s[10];
  sprintf(s, "%d",sid);
  fputs("#!/bin/bash\n", outfile);
  if(strcmp(c[1], "-x")==0){
    fputs("kill -15 ", outfile);
    fputs(s, outfile);
    fputs("\nrm Killer.sh ", outfile);
  }
  else if(strcmp(c[1], "-z")==0){
    fputs("killall -9 ", outfile);
    fputs(c[0], outfile);
    fputs("\nrm Killer.sh ", outfile);
  }
  fclose(outfile);
}
```
![image](https://user-images.githubusercontent.com/74702068/115959653-7a629f00-a537-11eb-9f95-cb6a7f1c44e4.png)
