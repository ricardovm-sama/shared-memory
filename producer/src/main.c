#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <sys/shm.h> 
#include <sys/mman.h> 
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <semaphore.h>
  
int new_producer(char *name, int size, int waiting_time) 
{ 
  
    // mensaje a producir/escribir en memoria compartida 
    //char* message = generate_message(); 
  
    // file descriptor de memoria compartida 
    int shm_fd; 
  
    // puntero a objeto en memoria compartida 
    void* ptr; 
  
    // crear el objeto de memoria compartida 
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 
  
    // configurar el tamaño del objeto en memoria compartida 
    ftruncate(shm_fd, size); 
  
    // mapear memoria de objeto en memoria compartida 
    ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0); 

    //Escribir al objeto en memoria compartida
    ptr += sizeof(char[100][20]) + sizeof(sem_t); // Aumenta la cantidad de productores activos

    //strcpy(ptr[100], message); // Depositar mensaje en el buffer

    return 1;
}

int main(int argc, char* argv[])
{
    char buffer_name[30]; // Nombre del buffer en memoria compartida (dirección) 

    printf("Program Name Is: %s",argv[0]); 
    if(argc==1) { 
       printf("\nNo Extra Command Line Argument Passed Other Than Program Name. Closing program..."); 
       return 0; 
    }
    if(argc>=2) 
    { 
        printf("\nNumber Of Arguments Passed: %d",argc); 
        printf("\n----Following Are The Command Line Arguments Passed----"); 
        for(int counter=0;counter<argc;counter++) {
            printf("\nargv[%d]: %s",counter,argv[counter]); 
        }

        int valid_arg2 = 1; // Indica si el argumento 2 es válido
        int valid_arg3 = 1; // Indica si el argumento 3 es válido
        size_t large;
        int cont = 1;
        int count2;
        char* pstring;
        while(cont < 3) { // Chequea que el segundo argumento sea string, y que el tercero sea un número
            large = strlen(argv[cont]);
            printf("\nLength %zu : %s",large,argv[cont]);
            count2 = 0;
            pstring = argv[cont];
            while(count2<large) {
                printf("\nChar %c",pstring[count2]);
                if (cont == 1) { // Verificar que los caracteres del segundo argumento sean letras
                   if (!isalpha(pstring[count2])) {
                      valid_arg2 = 0;
                      break;
                   }
                } else {
                   if (!isdigit(pstring[count2])) { // Verificar que los caracteres del tercer argumento sean números
                      valid_arg3 = 0;
                      break;
                   }
                }
                count2 = count2 + 1; 
            }       
            cont = cont + 1;
        }
  
        if (argc!=3) {
           printf("\nWrong number of arguments. Closing program..."); 
           return 0;
        }
        if (!valid_arg2) {
           printf("\nargv[2] is invalid (only letters are allowed). Closing program..."); 
           return 0;
        }
        if (!valid_arg3) {
           printf("\nargv[3] is invalid (only numbers are allowed). Closing program..."); 
           return 0;
        }

      printf("\n<<");
      printf("getpid(): %d", getpid()); // Obtener e imprimir el id del proceso
      printf(">>\n");        
    } 

    return 0;
}
