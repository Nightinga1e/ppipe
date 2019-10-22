#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
//#include <assert.h>
#include <string.h>

int main(){
	int pipefd[2];
	pid_t cpid;
	char buf;
	char *str[10]={" "};
	
//	assert(argc ==2);

	int check =0;
	check = pipe(pipefd);
	if (check ==-1){
		perror("pipe error");
		return -1;
	}
	cpid = fork();
	if (cpid == -1){
		perror("fork error");
		return -1;
	}
	if (cpid ==0){
		printf("\n CHILD HERE \n");
		close (pipefd[1]);
		while(read(pipefd[0], &buf,1) >0){
			write(STDOUT_FILENO, &buf, 1);
		}
		write(STDOUT_FILENO, "\n",1);
		close(pipefd[0]);
		return 0;
	}else{
		close(pipefd[0]);
		printf("\nPARENT HERE Enter something (10chars)\n");
		scanf("%s", &str);
		write(pipefd[1],str, 10);
		close(pipefd[1]);
		wait(NULL);
		return 0;
	}
}
