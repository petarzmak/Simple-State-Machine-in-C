#include <stdio.h>
#include <stdlib.h>

//deals with how the state machine behaves given a specific input
char states(char input, char curState, char state[8][5]){ 
	if (curState == 'A'){
		if (input == '0')
			curState = state[0][1];
		else if (input == '1')
			curState = state[0][2];
	} else if (curState == 'B'){
		if (input == '0')
			curState = state[1][1];
		else if (input == '1')
			curState = state[1][2];
	} else if (curState == 'C'){
		if (input == '0')
			curState = state[2][1];
		else if (input == '1')
			curState = state[2][2];	
	} else if (curState == 'D'){
		if (input == '0')
			curState = state[3][1];
		else if (input == '1')
			curState = state[3][2];	
	} else if (curState == 'E'){
		if (input == '0')
			curState = state[4][1];
		else if (input == '1')
			curState = state[4][2];	
	} else if (curState == 'F'){
		if (input == '0')
			curState = state[5][1];
		else if (input == '1')
			curState = state[5][2];	
	} else if (curState == 'G'){
		if (input == '0')
			curState = state[6][1];
		else if (input == '1')
			curState = state[6][2];
	} else if (curState == 'H'){
		if (input == '0')
			curState = state[7][1];
		else if (input == '1')
			curState = state[7][2];	
	}
		return curState;
}

//changes the specified path for the current state if the destination is valid
void change(char path, char dest, char curState, char state[8][5]){ 
	
	int column = path - '0' + 1; //convert char to int
	int row = curState - 65; //convert char to int
	int end = dest - 65; //convert char to int
	
	if (state[end][4] == 'a' && (dest == 'A' || dest == 'B' || dest == 'C' || dest == 'D' || dest == 'E' || dest == 'F' || dest == 'G' || dest == 'H'))
		state[row][column] = dest;
	else{
		printf("The destination state does not exit"); 
		printf("\n");
	}
	
}

//prints the state machine
void printer(char state[8][5]){ 
	for (int i = 0; i < 8; i++){
		if (state[i][4] == 'a'){
			for (int j = 0; j < 3; j++){
				printf("%c ", state[i][j]);
			}
			printf("\n");
		}
	}
}

//checks for any garbage states
void garb(char state[8][5]){ 
	
	int check = 0; //used to check if a matching state is found
	
	for (int i = 0; i < 8; i++){
		for (int j = 1; j < 3; j++){
			for (int k = 0; k < 8; k++){
				if (state[i][0] == state[k][j] && i != k){
					check = 1;
					break;
				}
			}
		}
		//sets garbage state to g or r depending on if the state is garbage or not
		if(check == 0){
			state[i][3] = 'g';
		}else if(check == 1){
			state[i][3] = 'r';
		}
		check = 0;
	}
}



int main(int argc, char * argv[])
{
	char curState = 'A';
	char input[6];
	char gar[8];
	int m = 0;
	int check = 0;
	printf("Starting State: %c\n\n", curState);
	printf("Valid Commands: \n0 (switch state) \n1 (switch state) \nc path destination (change) \ng (garbage identify) \np (print) \nd (delete all garbage) \nd state (delete specific garbage)\ne (exit)\n");
	
	//hardcoded FSM. Column 0 is the state, 1 and 2 are the destinations, 3 is the garbage identifier, 4 is the deleted identifier
	char state[8][5] = {{'A', 'H', 'C', 'r', 'a'},
					  {'B', 'D', 'A', 'r', 'a'},
					  {'C', 'C', 'F', 'r', 'a'},
					  {'D', 'C', 'B', 'r', 'a'},
					  {'E', 'G', 'D', 'r', 'a'},
					  {'F', 'E', 'G', 'r', 'a'},
					  {'G', 'A', 'H', 'r', 'a'},
					  {'H', 'B', 'E', 'r', 'a'}};		
					  		  
	while(fgets(input,6,stdin)){
		//to navigaet FSM using 1 and 0 input
		if(input[0] == '1' || input[0] == '0'){ 
			
			curState = states(input[0], curState, state);
			printf("Current State: %c\n", curState);
		
		//change command	
		} else if(input[0] == 'c'){ 
			
			change(input[2], input[4], curState, state);
		
		//print command	
		} else if(input[0] == 'p'){ 
			
			printer(state);
		
		//identify garbage command (also prints out garbage states)	
		} else if(input[0] == 'g'){ 
			
			garb(state); //checks for garbage
			
			for (int i = 0; i < 8; i++){
				if (state[i][3] == 'g' && state[i][4] == 'a'){
					gar[m] = state[i][0]; //fills garbage array so that elements can be printed
					check = 1; //used as boolean value to indicate whether garbage has been found
					m++;
				}
			}
			
			//controls print statement for garbage
			if (check == 0)
				printf("No garbage");
			else{
				printf("Garbage: ");
				for (int i = 0; i <= m; i++)
					printf("%c ", gar[i]);
			}
			
			check = 0;
			m = 0;
			printf("\n");
			
		//delete command
		} else if(input[0] == 'd'){ 
			
			//delete command with optional argument
			if (input[2] == 'A' || input[2] == 'B' || input[2] == 'C'|| input[2] == 'D' || input[2] == 'E' || input[2] == 'F' || input[2] == 'G' || input[2] == 'H'){ 
			
				if (state[input[2] - 65][3] == 'g' && state[input[2] - 65][4] == 'a'){ //checks if indicated state is garbage or not
					state[input[2] - 65][4] = 'd';
					printf("Deleted.");
				} else{
					printf("Not deleted.");
				}
			}
			
			//delete command with no argument
			else{ 
				//identifies if there are any garbage states
				for (int i = 0; i < 8; i++){  
					if (state[i][3] == 'g' && state[i][4] == 'a'){
						check = 1;
					}
				}
				
				if (check == 1){
					printf("Deleted: ");
					for (int i = 0; i < 8; i++){
						if (state[i][3] == 'g' && state[i][4] == 'a'){ //checks for any garbage states
							printf("%c ", state[i][0]);
							state[i][4] = 'd'; //sets state to 'deleted'
						}
					}
				}
				else
					printf("No states deleted.");
				check = 0;
			}
			printf("\n");
		
		//additional exit command	
		} else if(input[0] == 'e'){ 
			printf("Exiting...\nBye Bye");
			exit(0);
		}
	}
}
