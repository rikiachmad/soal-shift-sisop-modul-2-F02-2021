#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>

int main() {
 
  pid_t child_id;
  int status;

  child_id = fork();
  
  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
    
    char *argv[] = {"mkdir", "-p", "Fylm", "Musyik", "Pyoto", NULL};
    execv("/bin/mkdir", argv);
  } 
}
