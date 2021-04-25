# soal-shift-sisop-modul-2-F02-2021
# Nomor 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar, namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya. Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop demi menarik perhatian Stevany. 
Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi. (a) Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg (b) untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :). (c) Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta (d) memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan). (e) Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany). (f) Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).
## Sub soal a Membuat direktori Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg
Untuk membuat direktorinya kami menggunakan fungsi berikut:
```
void makefolder(char *array){
	pid_t child_id;
	int status;
	child_id = fork();
	
	if(child_id < 0){
		exit(EXIT_FAILURE);
	}
	if(child_id == 0){
		char *argv[]={"mkdir",array,NULL};
		execv("/bin/mkdir",argv);
	}else{
		wait(&status);
		return;
	}
}
```
Fungsi makefolder memiliki 1 parameter dan kami deklarasikan char pointer argv untuk meletakkan command sebelum dieksekusi dengan execv. Kemudian dieksekusi dengan perintah execute("/bin/mkdir",argv). 
### Output
<img width="196" alt="6" src="https://user-images.githubusercontent.com/67305615/115980689-dd484a80-a5b8-11eb-872b-55d83d0c03d5.PNG">
## Sub soal b
## Sub soal b Mengunduh musik, film, dan foto
Untuk mengunduh file tersebut kami menggunakan fungsi berikut:
```
void download(char *array, char *rename){
	pid_t child_id;
        int status;
        child_id = fork();

        if(child_id < 0){
                exit(EXIT_FAILURE);
        }
        if(child_id == 0){
                char *argv[]={"wget","-q",array,"-O",rename,NULL};
	        execv("/bin/wget",argv);

        }else{
                wait(&status);
                return;
        }
}
```
### Output
<img width="228" alt="7" src="https://user-images.githubusercontent.com/67305615/115980846-ff8e9800-a5b9-11eb-9ac6-94c6a9d4ada3.PNG">
## Sub soal c Mengekstrak zip yang telah didownload
Untuk mengekstrak zipnya kami menggunakan fungsi unzip, adapun fungsinya sebagai berikut:
```
void unzip(char *array){
	pid_t child_id;
        int status;
        child_id = fork();

        if(child_id < 0){
                exit(EXIT_FAILURE);
        }
        if(child_id == 0){
                char *argv[]={"unzip","-q",array,NULL};
	        execv("/bin/unzip",argv);


        }else{
                wait(&status);
                return;
        }
}
```

### Output
<img width="315" alt="8" src="https://user-images.githubusercontent.com/67305615/115980962-b25ef600-a5ba-11eb-919e-b8ee562ccd20.PNG">
## Sub soal d Memindahkan hasil ekstrak file ke direktori yang sudah dibuat pada soal 1a
Untuk memindahkan file ekstraknya kami menggunakan fungsi pindah, adapun fungsinya sebagai berikut:
```
void pindah(char *source, char *target){
	char arr[999] = "/home/fika/Praktikum2/";
	strcat(arr,source);	
	strcat(arr,"/.");

	pid_t child_id;
        int status;
        child_id = fork();

        if(child_id < 0){
                exit(EXIT_FAILURE);
        }
        if(child_id == 0){
                char *argv[]={"cp","-r",arr,target,NULL};
	        execv("/bin/cp",argv);
        }else{
                wait(&status);
                return;
        }
}
```
Karena file yang ingin dipindah hanya isi foldernya saja, maka kita tambahkan "/." pada parameter arraynya, dapat dilihat pada line 81.
### Output
<img width="315" alt="8" src="https://user-images.githubusercontent.com/67305615/115981747-4d0e0380-a5c0-11eb-9015-ad08d61835b5.JPG">
<img width="315" alt="8" src="https://user-images.githubusercontent.com/67305615/115981753-51d2b780-a5c0-11eb-97a4-c9d22ef608c9.JPG">
<img width="315" alt="8" src="https://user-images.githubusercontent.com/67305615/115981775-79298480-a5c0-11eb-9f3b-ee4e9c370a74.JPG">

# Nomor 2
 Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.<br/><br/>
(a) Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.<br/><br/>
(b) Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.<br/><br/>
(c) Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”. <br/><br/>
(d) Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.<br/><br/>
(e) Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
```C
nama : joni
umur  : 3 tahun

nama : miko
umur  : 2 tahun

```

## Sub soal a
Untuk mengekstrak file zip diperlukan untuk mengetahui letak awal dan tujuan dari file.
```C
char *username = getenv("USER");  //mendapatkan username dalam format string
char destination[maxSize] = "/home/", sourceZip[maxSize];

strcat(destination,username);
strcpy(sourceZip,destination);
strcat(sourceZip,"/Downloads/pets.zip"); //directory pets.zip
strcat(destination,"/modul2");
```
String `username` digunakan untuk mengganti [user], sehingga akan otomatis mengetahui user sekarang. String `destination` adalah tempat untuk meletakkan file zip, sedangkan `sourceZip` adalah letak dari file zip. Karena tujuan letak file hasil ekstrak ada di "/home/[user]/modul2/petshop", maka perlu menginisialisasi awal menjadi "/home/" yang kemudian ditambah dengan username dan "/modul2". Begitu juga sumber file, hanya saja letakkan sesuai sumbernya.<br/><br/>

Setelah itu buat direktori dari modul2 dengan execv yang mana sekarang `destination` telah masuk lebih dalam ke "/petshop". Perlu menggunakan `child` karena ada proses baru yang dilakukan yang jika tidak menggunakan `child`, maka program berhenti.
```C
  child1 = fork();
  if(child1==0)
  {
    char *mkdirModul[] = {"mkdir", destination, NULL};
    execv("/usr/bin/mkdir", mkdirModul);
  }
  while ((wait(&status)) > 0);

  strcat(destination, "/petshop");
```
Kemudian ekstrak file zip ke tujuan.
```C
child = fork();
  if(child == 0)
  {
      char *argv[] = {"unzip" , sourceZip, "-d", destination, NULL};
      execv("/usr/bin/unzip", argv);
  }
  while ((wait(&status)) > 0);
```
Dari sini pasti terdapat folder yang tidak diinginkan, jadi harus memeriksanya di dalam direktori tujuan. Caranya adalah dengan melihat ekstensi dari file/folder yang ditunjuk. Jika '.jpg', maka itu adalah file yang ingin dikelompokkan, jika '.' atau '..' berarti merupakan folder sekarang atau folder parent. Selain itu bisa dihapus
```C
DIR *dp;
struct dirent *ep;
dp = opendir(destination);
if (dp != NULL)
{
  while ((ep = readdir (dp))) {
    if(is_suffix(ep->d_name,".jpg")){
      createFolder(ep->d_name, ep->d_name, destination);
    }

    else if ( !strcmp(ep->d_name, ".") || !strcmp(ep->d_name, "..") );

    else{
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
    }
  }

  (void) closedir (dp);
}
```
## Sub soal b
Prosedur `createFolder` melakukan passing direktori sekarang sehingga tidak perlu mengulang dari awal. Untuk mengetahui kategori setiap hewan adalah dengan memeriksa nama file sampai bertemu ';' pertama.
```C
for(j = 0; j<strlen(newName); j++){
  category[j+1] = newName[j];
  if(newName[j] == ';'){
    category[j+1] = '\0';
     break;
   }
}
```
Untuk membuat folder tiap kategori cukup hanya dengan menggabungkan direktori sekarang dengan nama kategori dan buat foldernya.
```C
char newFolder[maxSize];
strcpy(newFolder, current_dir);
strcat(newFolder, category);

if(access(newFolder, F_OK) == -1){  //folder belum ada
  child = fork();
  if(child==0)
  {
    char *arg[] = {"mkdir", newFolder, NULL};  //command buat directory
    execv("/usr/bin/mkdir", arg);  //menjalankan mkdir dari file c
  }
  while ((wait(&status)) > 0);
}
```
## Sub soal c
Jika ingin menamai file yang dipindah dengan nama hewan, kita dapat membuatnya dengan mengetahui namanya terlebih dahulu dengan mengetahui string di antara ';' pertama dan kedua (melanjutkan yang tadi).
```C
int counter = 0;j++;
for(;j<strlen(newName)-4; j++){
  if(newName[j] == ';'){
    name[counter] = '\0';
    break;
  }
  name[counter++] = newName[j];
}
```
Untuk sesuai dengan spesifikasi yang diinginkan, copy filename menjadi nama yang baru di folder baru juga.
```C
char copy_file[maxSize];
strcpy(copy_file, current_dir);
strcat(copy_file, "/");
strcat(copy_file, filename);


char newPath[maxSize];
strcpy(newPath, newFolder);
strcat(newPath, "/");
strcat(newPath, name);
strcat(newPath, ".jpg");


child = fork();
if(child == 0){
  char *argv[] = {"cp", copy_file, newPath};
  execlp("cp", argv[0], argv[1], argv[2], NULL);
}
while ((wait(&status)) > 0);
```
## Sub soal d
Karena bisa terdapat lebih dari satu hewan peliharaan, maka perlu untuk menghilangkan nama yang sudah diperiksa. Namun untuk menyalin file diperlukan nama file yang asli. Itulah kenapa filename tetap, sementara ada nama baru untuk mengetahui informasi hewan berikutnya.
```C
void createFolder(char *filename, char *newName, char *current_dir){
  
  bool more_than_one = false;
  for(i=0;i<strlen(newName);i++)
    if(newName[i] == '_'){
      more_than_one = true;
      break;
    }
```
Sisanya sama seperti langkah atas.
## Sub soal e
File keterangan.txt diperlukan setiap folder, oleh karena itu perlu untuk membuat file lewat nama folder ditambah "/keterangan.txt".
```C
char keterangan[maxSize];
strcpy(keterangan, newFolder);
strcat(keterangan, "/keterangan.txt");
```
dan masukkan informasi yang diketahui ke file tersebut menggunakan 'a' karena informasi baru akan dimasukkan di bawahnya, bukan menggantikannya.
```C
FILE *fptr = fopen(keterangan, "a");
fprintf(fptr, "nama : %s\numur : %s tahun\n\n", name, umur);
fclose(fptr);
```
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
