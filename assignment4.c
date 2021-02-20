#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>








pthread_mutex_t mue1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mue2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mue3 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full1 =  PTHREAD_COND_INITIALIZER;
pthread_cond_t full2 =  PTHREAD_COND_INITIALIZER;
pthread_cond_t full3 =  PTHREAD_COND_INITIALIZER;


int b1_count = 0;
int b2_count = 0;
int b3_count = 0;






//Here the functions we are creating the different buffers which will 
// contain 50 character arrays of length 1000 
char ** create_buff(){
	char ** buff[50];

for(int i = 0; i < 50; i++){
	buff[i] = (char*) malloc(1000 * sizeof(char));
}
	return buff;
}

char ** buff1[50];
char ** buff2[50];
char ** buff3[50];




/* 

char * read_line(FILE * stream){
	buff1[b1_count] = (char*) malloc(80 * sizeof(char));
	size_t len = 80; 
	char * nread;
	//getline(&buff1[b1_cont], &len, stream);
	fgets(buff1[b1_count],80, stream);

	//printf("nread %s \n", nread);
/* 	fseek(stream, 0, SEEK_SET);
	fgets(&buff1[b1_count], 90, stream);
	b1_count++;
	  */
/* 	
	printf("what is the line: %s \n ", buff1[b1_count]);  
	return buff1[b1_count]; 
}
  */

void *read_line(void * stream){
	// while !STOP loop here
		
		//{
	char * tmp_str = (char*)malloc(1000 * sizeof(char));

	int count = 0;
	//FILE * stream = *((FILE
	
	
	
	//while(strcmp(tmp_str, "STOP") != 0){
	 fgets(tmp_str, 80, (FILE *)stream);
		printf("what is the line %s \n", tmp_str);

	pthread_mutex_lock(&mue1);
	 buff1[b1_count] =(char*)malloc(1000 * sizeof(char));
	 strcpy(buff1[b1_count], tmp_str); 
	b1_count++;
	
	pthread_cond_signal(&full1);
	pthread_mutex_unlock(&mue1);
	//printf("what is the line %s \n", buff1[b1_count-1]);
		// } 
	//free(tmp_str); 
	return NULL;
		//}
	
} 
void * seperate_line(void * parameter){
	int count = 0;
			/* pthread_mutex_lock(&mue1);
		while(b1_count == 0){
		pthread_cond_wait(&full1, &mue1);
		
		}	
	if(strcmp(buff1[b1_count], "STOP") == 0){
	
			return NULL;
		}
		pthread_mutex_unlock(&mue1); */
			
	 
	pthread_mutex_lock(&mue1);
		while(b1_count == 0){
		pthread_cond_wait(&full1, &mue1);
		}
		 
		pthread_mutex_lock(&mue2); 
		 buff2[b2_count] = (char *)malloc(1000 * sizeof(char));
		strcpy(buff2[b2_count], buff1[b1_count-1]); 
		buff2[b2_count] = buff1[b1_count-1];

		b2_count++;
		pthread_cond_signal(&full2);

		pthread_mutex_unlock(&mue2);
	while(count < 1000){
		
		  if(buff1[b1_count-1][count] == '\n'){
		
			buff1[b1_count-1][count] = ' ';
		}
		  
		

				count++;

		}
		b1_count--;

		pthread_mutex_unlock(&mue1);
		 

	
		 
		 
		
		
		printf("buff2 at %d contains %s:", b2_count-1, buff2[b2_count-1]); 
		return NULL;
		
		
		
		
		
		
		//printf("buff1 contains: %s \n", buff1[b1_count+1]);
	
	
	
}

// char * seperate_line(int * stop){
	// int count = 0;
	
	// while(count < 1000){
		// if(buff1[b1_count][count] == '\n'){
			// buff1[b1_count][count] = ' ';
		// }

		// if(strcmp(buff1[b1_count], "STOP") == 0){
			// *stop = 1;
			// break; 
		// }
				// count++;

		// }
	// buff2[b2_count] = (char *)malloc(1000 * sizeof(char));
		// strcpy(buff2[b2_count], buff1[b1_count]);
		
		// printf("buff1 contains: %s \n", buff2[b1_count]);
	
	
	
// }
void place_in_buffer(char ** buffer){
	
	
	
	
	
	
	
	
}
		
	
	
void * plus_replace(char ** buff2){
	 /* char ** line; 
	line = (char**)parameter;  */
	int star_count = 1;
	int count = 2;
	int i = 0; 
	 printf("what is replace %s \n:", buff2[b2_count-1]);
 	for(i = 0; i < 80; i++){
		printf("iter \n");
		 if(buff2[b2_count-1][i+1] == NULL){
			
			break;
		} 

	if(buff2[b2_count-1][i] == 43 && buff2[b2_count-1][i+1] == 43 && buff2[b2_count-1][i-1] == 32){
		//++ and then ++ again
		
		
		//add in a bunch of if(buff2[i+count] != NULL)
		if(buff2[b2_count-1][i+count] != NULL){
		while(buff2[b2_count-1][i+count] == 43){
		count+= 2; 
		star_count += 1;
		
	
		}
		}
		//remove spaces
		for(int x = 0; x < star_count; x++){
			if(buff2[b2_count-1][i + x] != NULL){
			buff2[b2_count-1][i + x] = 17;
			}
			
		}
		for(int z = 0; z < star_count; z++){
			if(buff2[b2_count-1][i+count] != NULL){
			buff2[b2_count-1][i + star_count + z] = 94;
			}
			
		}
		i += count; 
		count = 2;
		star_count = 1;
		//buff2[i+2] = 94;
	}
	else if(buff2[b2_count-1][i] == 43 && buff2[b2_count-1][i+1] == 43 && buff2[b2_count-1][i-1] != 32){
		if(buff2[b2_count-1][i+count] != NULL){
		while(buff2[b2_count-1][i+count] == 43){
		count+= 2; 
		star_count += 1;
	
		}
		}
		for(int x = 0; x < star_count; x++){
			if(buff2[b2_count-1][i + x] != NULL){
			buff2[b2_count-1][i + x] = 94;
			}
			
		}
		for(int z = 0; z < star_count; z++){
			if(buff2[b2_count-1][i + star_count + z] != NULL){
			buff2[b2_count-1][i + star_count + z] = 17;
			}
		}
		i += count; 
		count = 2;
		star_count = 1;
	}
	else if(buff2[b2_count-1][i] == 43 && buff2[b2_count-1][i+1] == 43 && buff2[b2_count-1][i+2] != 32){
		
		
		buff2[b2_count-1][i] = 94;
		buff2[b2_count-1][i+1] = 32;
	}
	}
	
	
		printf("what is the buff2: %s \n", buff2[b2_count-1]);
	return NULL; 
	
	
}





char * output_line(char * out){

	int i = 0;
	int count = 0;
	b3_count = strlen(buff1[b1_count]);
	
		

/* 	if(out[i] == 17){
	} */
	fputs(buff1[b1_count], stdout);
	b3_count--;
	
	count = i;
	fputc('\n', stdout);
	
	

	return out;


}








int main(int argc, char *argv[]){
FILE * stream; 
int stop = 0;
int target = 0; 

	stream = fopen("./input1-1.txt", "r");

char ** buf1;
char ** buf2;
char ** buf3;
/* char * buf1 = malloc(sizeof(char)*1000);
 char * buf2 = malloc(sizeof(char)*1000);
char * buf3 = malloc(sizeof(char)*1000);  */

char * output = malloc(sizeof(char) * 1000);
	for(int i = 0; i < 1000; i++){
		output[i] = 0;
	} 
	pthread_t rd_line;
	pthread_t sp_line; 
	pthread_t p_r_l;
	pthread_t output_line;
	
	
	pthread_create(&rd_line, NULL, read_line, (void *) stream);
	pthread_create(&sp_line, NULL, seperate_line, NULL);
	pthread_create(&p_r_l, NULL, plus_replace, buff2);
	pthread_join(rd_line, NULL);
	pthread_join(sp_line, NULL);
	
	pthread_join(p_r_l, NULL);

/* 
if(argv[1] == "<" && argv[3] == NULL){
	result = fopen(argv[2], O_RDONLY);
	dup2(result, 0);
}
else{
	result = fopen(argv[2], O_RDONLY);
	target = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(result, 0);
	dup2(target, 1);
}
 */
 
 //result = fopen(argv[2], "r");




//while(stop != 1){
/* 	buf1 = create_buff();
	//buf2 = create_buff();
	//buf3 = create_buff();
read_line(stream);


seperate_line(&stop);


plus_replace(buff1);

output = output_line(buff1);
   */
 

//}
}