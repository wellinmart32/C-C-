/*
 * order_generator.c
 *
 */


#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE_F    10      /* array size */ 
#define SIZE_C    10      /* array size */ 


static int matrix[SIZE_F][SIZE_C]; //cada columna va corresponder a un ingrediente
static int status[SIZE_F]; //0 no enviado, 1 en proceso, 2 finalizado

void print_queue (int matrix[SIZE_F][SIZE_C])
{
    int i, j;
    int first;

    for (i = 0; i < SIZE_F; i++) {
        printf ("[");
        first = 1;
        for (j = 0; j < SIZE_C; j++) {
            if (!first)
                printf (",");
            printf ("%x", matrix[i][j]);
            first = 0;
        }
        printf ("]\n");
    }
        
}

void fill_queue (int matrix[SIZE_F][SIZE_C],int status[SIZE_F])
{
    int i, j;
    int first;
    
    for (i = 0; i < SIZE_F; i++){
      matrix[i][0]= 2;    
      matrix[i][1]= (rand() % (3 - 1)+1) ;    
      matrix[i][2]= (rand() % (3 - 1)+1) ;    
      matrix[i][3]= (rand() % (3 - 1)+1) ;    
    }
	

//Considerar la forma de generar la cantidad de ingredientes para cada orden

      

    for (i = 0; i < SIZE_F; i++)   
        status[i]=0;
}
int pending_items(int matrix[SIZE_F][SIZE_C]){
int sum,i;
sum=0;
	for (i = 0; i < SIZE_F; i++) 
		sum=sum+matrix[i][0];
	return(sum);
}

int next_item (int matrix[SIZE_F][SIZE_C])
{
    int i, j;
    int sum;
    
    for (i = 0; i < SIZE_F; i++) 
	sum=sum+matrix[i][0];
    if (sum<=0)
        return (-1);
    while(pending_items(matrix)>0)
    {
	i=(rand() % (SIZE_F - 1));
	return(i);
	
    }
}

int main (int argc, char *argv[])
{
   int i;
   struct timespec tim, tim2;
   tim.tv_sec = 0;
   tim.tv_nsec = 500000000L; //medio segundo
   char buffer[50]; 
   int sockfd;
   int len, rc ;
   struct sockaddr_in address;
   int result;

    //Create socket for client.
   sockfd = socket(PF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) { 
	perror("Socket create failed.\n") ; 
	return -1 ; 
  } 
	
	//Name the socket as agreed with server.
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(7734);
  len = sizeof(address);
  result = connect(sockfd, (struct sockaddr *)&address, len);
  
  if(result == -1){
		perror("Error has occurred");
		exit(-1);
  }

    fill_queue(matrix,status);
    print_queue (matrix);
    printf("%d",pending_items(matrix));
    while(pending_items(matrix)>0){
	nanosleep(&tim , &tim2); 
	i=next_item(matrix);
        if (status[i]==2) {
	   while(status[i++]!=2); 	

        }
        memset(buffer,0,sizeof(buffer));
	if (status[i]==0) {
		status[i]=1;
		sprintf(buffer,"Orden %d Ingredientes %d-%d-%d-%d",i,matrix[i][0],matrix[i][1],matrix[i][2],matrix[i][3]);
		rc = write(sockfd, &buffer, strlen(buffer));
		continue;		
	}
	if (status[i]==1) {
    for (int j = 0; j < SIZE_C; j++){
      matrix[i][j]=0;
			status[i]=2;
		}
    }    
  }
    return 0;
}
