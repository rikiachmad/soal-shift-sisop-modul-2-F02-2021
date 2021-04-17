#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <string.h>

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

void zip(char *dok1,char *dok2,char *dok3){
        pid_t child_id;
        int status;
        child_id = fork();

        if(child_id < 0){
                exit(EXIT_FAILURE);
        }
        if(child_id == 0){
                char *argv[]={"zip","-rm","Lopyu_Stevany",dok1,dok2,dok3,NULL};
                execv("/bin/zip",argv);


        }else{
                wait(&status);
                return;
        }
}

void hapus(char *array){
	char arr[999] = "/home/fika/Praktikum2/";
        strcat(arr,array);    
	strcat(arr,"/");        

	pid_t child_id;
        int status;
        child_id = fork();

        if(child_id < 0){
                exit(EXIT_FAILURE);
        }
        if(child_id == 0){
                char *argv[]={"rm","-rf",arr,NULL};
                execv("/bin/rm",argv);
        }else{
                wait(&status);
                return;
        }
}

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/fika/Praktikum2/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
    	char task1[]="09-Apr 16:22";
    	char task2[]="09-Apr 22:22";
    	
    	time_t waktu =time(NULL);
    	char ultah[99];
    	struct tm *now = localtime(&waktu);
    	strftime(ultah, sizeof(ultah), "%d-%b %H:%M", now);
    	
    	pid_t child_id;
        int status;
        child_id = fork();

        if(child_id < 0){
                exit(EXIT_FAILURE);
        }
        if(child_id == 0){
        	char *linkfoto="drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download";
		char *linkmusik="drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download";
		char *linkfilm="drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download";
	
		char *Foto="Foto_for_Stevany";
		char *Film="Film_for_Stevany";
		char *Musik="Musik_for_Stevany";

		char *foto="Pyoto";
		char *musik="Musyik";
		char *film="Fylm";

		char *FOTO="FOTO";
		char *MUSIK="MUSIK";
		char *FILM="FILM";

        	if(strcmp(ultah,task1) == 0){
    		
			makefolder(foto);
			makefolder(musik);
			makefolder(film);

			download(linkfoto,Foto);
			download(linkmusik,Film);
			download(linkfilm,Musik);

			unzip("foto");
			unzip("musik");
			unzip("film");

			pindah(FOTO, foto);
			pindah(MUSIK, musik);
			pindah(FILM, film);
		}
		
		if(strcmp(ultah,task2) == 0){
		
			zip(foto,musik,film);

			hapus(FOTO);
			hapus(MUSIK);
			hapus(FILM);
		}

        }else{
                sleep(30);
                continue;
        }    	
  }
}


