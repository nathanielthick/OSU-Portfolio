/*
 * Name: Nathaniel Thickett
 * Email: thicketn@oregonstate.edu
 * PROGRAM 3
 * OS 1
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>

int allowBackground = 1;
int background = 0;
int exitstatus = 0;

/*
 * FUCNTION: cd_func
 * PARAMS: arguments strings array and int total arguments
 * RETURNS: VOID
 * PURPOSE: rund 'cd' function
 */
void cd_func(char * arguments[512], int argtot){
	int flag = 0;
	
	switch(argtot) {
		case 1:
		//if there is only 1 argument, it is just CD
			chdir(getenv("HOME"));
			break;
		default:
			//otherwise, goes to specified directory
			flag = chdir(arguments[1]);
			if (flag == -1) {
				printf("-- Selected Directory Could Not Be Found --\n");
				fflush(stdout);
			}
			break;
		
	}
}

/*
 * FUCNTION: handleSIGTSTP()
 * PARAMS: NONE
 * RETURNS: VOID
 * PURPOSE: SIGTSTP signal handler, toggles allowBackground variable and prints message about current mode
 */
void handleSIGTSTP() {
	char* prompt = ": ";
	char* message; //message string
	int messageSize = -1;	//size of message string
	if(allowBackground == 1) {//if background allowed
		message = "\nEntering foreground-only mode (& is now ignored)\n";
		messageSize = 50;
		allowBackground = 0;
		write(1, message, messageSize);//uses reentrant write() function
	}else if(allowBackground == 0){//if background not allowed
		message = "\nExiting foreground-only mode\n";
		messageSize = 30;
		allowBackground = 1;
		write(1, message, messageSize);//uses reentrant write() function
	}
	//write(1, prompt, 2);
}

/*
 * FUCNTION: parentFor()
 * PARAMS: pid_t childPid
 * RETURNS: VOID
 * PURPOSE: performs function of parent when process is ran
 */
void parentFork(pid_t childPid) {
	//checks if background enabled before executing in background
	if (background == 1 && allowBackground == 1) {
		waitpid(childPid, &exitstatus, WNOHANG);
		printf("Background process PID is: %d\n", childPid);
		fflush(stdout);
	}
	// Otherwise execute in foreground
	else {
		waitpid(childPid, &exitstatus, 0);
	}
}

/*
 * FUCNTION: printStat()
 * PARAMS: exitstatus
 * RETURNS: VOID
 * PURPOSE: prints exit status or signal used
 */
void printStat(int exitstatus){
	if (WIFEXITED(exitstatus)) {
        // If exited by status
        printf("EXITED WITH VALUE: %d\n", WEXITSTATUS(exitstatus));
    } 
	else if (WIFSIGNALED(exitstatus)) {
        // If terminated by signal
        printf("TERMINATED WITH SIGNAL: %d\n", WTERMSIG(exitstatus));
    }
	fflush(stdout);
}


int main(){
	//setup signal handler
	struct sigaction SIGTSTP_action;
	SIGTSTP_action.sa_handler = handleSIGTSTP;
    sigfillset(&SIGTSTP_action.sa_mask);
    SIGTSTP_action.sa_flags = 0;
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);

	int pid = getpid();//get pid for later
	int exited = 0;//set while loop exit cond to 0
	char* arguments[512];//max arguments = 512
	int argtot;//total arguments
	char clap[2048];//used as temp string
	int max = 2048;
	char inputFile[256] = "";//string for inputfile name
	char outputFile[256] = "";//string for outputfile name
	int i, j;//for for loops
	int outF, inF;//for files
	int haveIn = 0, haveOut = 0;//for files
	char input[2048];//used to store input
	char *token;

	

	while(!exited){
		pid = getpid();
		
		//prints prompt
		printf(": ");
		fflush(stdout);

		//gets input of size max 2048 from stdin
	   	fgets(input, 2048, stdin);

		//total args reset to 0
		argtot = 0;


		int flag = 0;
		//sets enter character to string null terminator
		for (i=0; flag == 0 && i<2048; i++) {
			if (input[i] == '\n') {
				input[i] = '\0';
				flag = 1;
			}
		}

		flag = strcmp(input, "");
		if (flag == 0) {
			arguments[0] = "";
			continue;
		}

		token = strtok(input, " ");

		while(i < 512 && token){//while token and arguments < 512
			if (strcmp(token, "<") == 0) {//checks for input
				token = strtok(NULL, " ");//next token
				strcpy(inputFile, token);//sets inputfile name to token
				haveIn = 1;//sets input file flag to 1
			}
			else if (strcmp(token, ">") == 0) {
				token = strtok(NULL, " ");//next token
				strcpy(outputFile, token);//sets outputfile name to token
				haveOut = 1;//sets output file flag to 1
			}
			else{
				arguments[argtot] = token;//sets argument to token
				for(int l = 0; l < strlen(arguments[argtot]) -1; l++) {//loop to check for '$$'
					if(arguments[argtot][l] == '$' && arguments[argtot][l+1] == '$') {
						arguments[argtot][l] = '\0';
						arguments[argtot][l+1] = '\0';//sets $$ to NULL character
						snprintf(clap, max, "%s%d", arguments[argtot], pid);//fills temp string clap with argument followed by pid
						arguments[argtot] = clap;//sets arguemnt to temp string
					}
				}
				argtot++;//increments total arg counter
			}
			token = strtok(NULL, " ");//next tok
			i++;

		}

		if (strcmp(arguments[argtot -1], "&") == 0) {
			background = 1;
			arguments[argtot-1] = NULL;
		}


		if (arguments[0][0] == '#'){ //ignores comments or blank lines
			continue;
		}

		if(arguments[0][0] == '\0') { //ignores comments or blank lines
			continue;
		}
		
		//exit function
		else if (strcmp(arguments[0], "exit") == 0) {
			exited = 1;
		}
	
		//call CD function
		else if (strcmp(arguments[0], "cd") == 0) {
			// Change to the directory specified
			cd_func(arguments, argtot);
		}

		//calls print status function
		else if (strcmp(arguments[0], "status") == 0) {
			printStat(exitstatus);
		}
		

		//any other function
		else{

			pid_t spawnPid = fork();//forkbomb time :)

			switch (spawnPid) {
				case 0:	;
					if (haveIn){
						// open input file
						if ((inF = open(inputFile, O_RDONLY)) < 0) { 
            				fprintf(stderr, "cannot open file: \"%s\" for input\n", inputFile);
            				fflush(stdout); 
            				exit(1); 
						}
						// dup2 assign input file
						dup2(inF, 0);
						close(inF);
					}

					if (haveOut){
						// open output file
						if((outF = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0){
							fprintf(stderr, "cannot open file: \"%s\" for output\n", outputFile);
							fflush(stdout); 
							exit(1);
						}
						
						// dup2 assign it
						dup2(outF, 1);
						close(outF);
					}
					
					// execute arguments
					if (execvp(arguments[0], arguments) == -1) {
						perror(arguments[0]);
						exit(2);
					}
					fflush(stdout);
					break;
				
				default:	
					parentFork(spawnPid);//runs parent fork function

				//checks for terminated background ps
				while ((spawnPid = waitpid(-1, &exitstatus, WNOHANG)) > 0) {
					printf("Child with PID: \"%d\" was terminated\n", spawnPid);
					printStat(exitstatus);
					fflush(stdout);
				}
			}
		}
		//resets input
		for (i=0; input[i]; i++) {
			input[i] = '\0';
		}
		//resets other vars and file strings
		background = 0;
		inputFile[0] = '\0';
		outputFile[0] = '\0';
		//resets arguments
		for (i=0; i<512; i++) {
			arguments[i] = NULL;
		}

		haveIn = 0, haveOut = 0;
		
	}
    
}

