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


int output_buff = 0;

char * read_line(int fd){
	char * nread = malloc(sizeof(char) * 1000);
	
	int len = 0; 
	int count = 0; 
	
	getline(&nread, &len, fd);
	printf("what is the line: %s \n ", nread);
	return nread;
}


char * seperate_line(char * line, int * stop){
	int count = 0;
	char * nread = malloc(sizeof(char) * 1000);
	for(int i = 0; i < 1000; i++){
		nread [i] = 0;
	}
	while(line[count] != 0){
		if(line[count] == '\n'){
			line[count] = ' ';
		}
		if(line[count] == "S" && line[count+1] == "T" && line[count+2] == "O" && line[count+3] == "P"){
			*stop = 1;
			break; 
			
		}
		nread[count] = line[count];
		count++;
	}
		
		printf("what is the line: %s \n", nread);

	return nread; 
	
}
char * plus_replace(char * line){
	int star_count = 1;
	int count = 2;
	int i = 0; 
	for(i = 0; i < strlen(line); i++){
	if(line[i] == 43 && line[i+1] == 43 && line[i-1] == 32){
		//++ and then ++ again
		
		while(line[i+count] == 43){
		count+= 2; 
		star_count += 1;
		
	
		}
		for(int x = 0; x < star_count; x++){
			line[i + x] = 32;
			
			
		}
		for(int z = 0; z < star_count; z++){
			line[i + star_count + z] = 94;
			
		}
		i += count; 
		count = 2;
		star_count = 1;
		//line[i+2] = 94;
	}
	else if(line[i] == 43 && line[i+1] == 43 && line[i-1] != 32){
		
		while(line[i+count] == 43){
		count+= 2; 
		star_count += 1;
	
		}
		for(int x = 0; x < star_count; x++){
			line[i + x] = 94;
			
			
		}
		for(int z = 0; z < star_count; z++){
			line[i + star_count + z] = 32;
			
		}
		i += count; 
		count = 2;
		star_count = 1;
	}
	}
		printf("what is the line: %s \n", line);
	return line;
	
}





char * add_to_output(char * line, char * out){
	for(int i = 0; i < strlen(line); i++){
	out[output_buff] = line[i];
	output_buff++;
	}
	
	return out;
	
	
	
	
}
char * output_line(char * out){

	int i = 0;
	int count = 0;
	
	
		
	if(output_buff >= 80){
	for(i = 0; i< 80; i++){
	fputc(out[i], stdout);
	out[i] = 0;
	output_buff--;
	}
	fputc('\n', stdout);
	i = 0;
	
	}
	return out;


}








int main(int argc, char *argv[]){
FILE * stream; 
int stop = 0;
int target = 0; 

	int result = fopen("./input1-1.txt", "r");

/* char * buf1 = malloc(sizeof(char)*1000);
 char * buf2 = malloc(sizeof(char)*1000);
char * buf3 = malloc(sizeof(char)*1000);  */
char * buf1= NULL;
char * buf2 = NULL;
char * buf3 = NULL;
char * output = malloc(sizeof(char) * 1000);
	for(int i = 0; i < 1000; i++){
		output[i] = 0;
	} 
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
buf1 = read_line(result);


buf2 = seperate_line(buf1, &stop);


buf3 = plus_replace(buf2);

output = add_to_output(buf3, output);

output = output_line(output);




//}
}