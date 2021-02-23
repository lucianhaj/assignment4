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
#include <assert.h>








pthread_mutex_t mue1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mue2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mue3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mue4 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t full1 =  PTHREAD_COND_INITIALIZER;
pthread_cond_t full2 =  PTHREAD_COND_INITIALIZER;
pthread_cond_t full3 =  PTHREAD_COND_INITIALIZER;
pthread_cond_t full4 =  PTHREAD_COND_INITIALIZER;


int b1_count = 0;
int b2_count = 0;
int b3_count = 0;
int b4_count = 0;





//Here the functions we are creating the different buffers which will 
// contain 50 character arrays of length 1000 

char  buff1[1024]= {0};
char  buff2[1024] = {0};

char buff3[1024] = {0};

// requires len(replacement_term) <= len(term)
char* replaceTerm(const char *line, const char *term, const char *replacement_term)
{
	// fail if we have any null args
	assert(line);
	assert(term);
	assert(replacement_term);
	
    // note this depends on the target line len <= source line length
    char *buf = calloc(strlen(line)+1, sizeof(char));
    const char *p = NULL;
    const char *rest = line;
    // while we are still finding term 
    while((p = strstr(rest, term)))
    {
        strncat(buf, rest, (size_t)(p - rest));
        strcat(buf, replacement_term);
        rest = p + strlen(term);
    }
   // no more term, so just tack on what's left
    strcat(buf, rest);
    return buf;
}


//char ** buff3[50];



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

	char * tmp_str = (char*) calloc(1024, sizeof(char));
	int stop = 0;


	
	while(!stop){
	 fgets(tmp_str, 1000, stdin);

	pthread_mutex_lock(&mue1);
	 strcpy(buff1, tmp_str); 
	b1_count++;
	
	pthread_cond_signal(&full1);
	pthread_mutex_unlock(&mue1);
	
	
	
	// wait until the print thread has dealt with this line
		pthread_mutex_lock(&mue4);
		while (b4_count == 0) {
			pthread_cond_wait(&full4, &mue4);
		}
		b4_count++;
		pthread_mutex_unlock(&mue4);

	
	if(strncmp(tmp_str, "STOP\n", 5) == 0){
		stop = 1;
	}
	
	} 
		 
	return NULL;
	
 
}

void* line_sep(void* args) {
	int stop = 0;
	char *line = calloc(1000, sizeof(char));
	
	//Tokenizes input based on "\n" and places it into buffer 2 to be seperated by an empty space
	while (! stop) {
		
		// wait for lock then copy data locally
		pthread_mutex_lock(&mue1);
		while (b1_count == 0) {
			pthread_cond_wait(&full1, &mue1);
		}
		
		strcpy(line, buff1);
		b1_count--;
		pthread_mutex_unlock(&mue1);

		// check for STOP before we remove the newline
		if (strncmp(line, "STOP\n", 5) == 0) {
			stop = 1;
		}
		else{
		int len = strlen(line);
			if (line[len - 1] == '\n') {
				line[len - 1] = ' ';
			}
			
		}
		// process the current line replace \n with space

		// lock buffer and copy data for next thread
		pthread_mutex_lock(&mue2);
		strcpy(buff2, line);
		b2_count++;
		pthread_cond_signal(&full2);
		pthread_mutex_unlock(&mue2);
	}

	return NULL;
}

	
void * plus_replace(void * s){
	char * new_line;
	int stop = 0;
	
	char *line = calloc(1000, sizeof(char));

	
	while(!stop){
    pthread_mutex_lock(&mue2);
	while(b2_count == 0){
		pthread_cond_wait(&full2, &mue2);
		}
	strcpy(line, buff2);
	b2_count--;
 
	pthread_mutex_unlock(&mue2); 
	
	if(strncmp(line, "STOP\n", 5) == 0){
		stop = 1;
	new_line = line;
	}
	else{
	new_line = replaceTerm(line, "++", "^");

		
		
	}
	
	
	
	pthread_mutex_lock(&mue3);
	  
	strcpy(buff3, new_line);
	b3_count++;
	pthread_cond_signal(&full3);
	pthread_mutex_unlock(&mue3);   
		
	}
	return NULL; 
	
	
}





void * output_line(void * out){
	char * print_buffer = (char*) malloc(50000 * sizeof(char));
	char *line = calloc(1000, sizeof(char));

	int stop = 0;
	int last_line = 0;
	char output[81] = {0};
	//fputs(buff1[b3_count-1], stdout);
	while(!stop){	
	pthread_mutex_lock(&mue3);	
	while(b3_count == 0){
		pthread_cond_wait(&full3, &mue3);
	}
	strcpy(line, buff3);
	strcat(print_buffer, buff3);
	b3_count--;
	pthread_mutex_unlock(&mue3);
	
	// now that content is in our local storage, print it
		int cur_line_count = (strlen(print_buffer))/80;
		for (int line = last_line; line < cur_line_count; line++) {
			memset(output, 0, 81); // clear the output line
			strncpy(output, print_buffer + (line*80), 80);
				printf("%s\n", output);
			fflush(stdout);
		}
		last_line = cur_line_count;

	
	
	if(strncmp(line, "STOP\n", 5) == 0){
		stop = 1;
	}
	// let the line input thread know we are done with printing
		pthread_mutex_lock(&mue4);
		b4_count--;
		pthread_cond_signal(&full4);
		pthread_mutex_unlock(&mue4);

	}
	


	return NULL; 
 
}

 






int main(int argc, char *argv[]){
FILE * stream; 
int stop = 0;
int target = 0; 

 
	pthread_t rd_line;
	pthread_t sp_line; 
	pthread_t p_r_l;
	pthread_t out_l;
	
	
	pthread_create(&rd_line, NULL, read_line, NULL);
	pthread_create(&sp_line, NULL, line_sep, NULL);
	pthread_create(&p_r_l, NULL, plus_replace, NULL);
	pthread_create(&out_l, NULL, output_line, NULL);
	pthread_join(rd_line, NULL);
	pthread_join(sp_line, NULL);
	
	pthread_join(p_r_l, NULL);
		pthread_join(out_l, NULL);


return 0;
}



	//stream = fopen("./input1-1.txt", "r");
	
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
