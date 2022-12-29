#include <stdio.h>
#include <string.h>

void sort (int A[][3], int N, int t) {
 	int i, j, k;
	int temp;
	
	for(i = 0; i < N; i++) {		
    	for(j = i + 1; j < N; j++) {			
    		if(A[i][t] > A[j][t]) {
				for(k = 0; k < 3; k++) {
					temp = A[i][k];
					A[i][k] = A[j][k];
					A[j][k] = temp;
				}
			}
		}	
	}
}

void fcfs (int y, int input[100][3]) {
	
	int i;
	int l;
	int arrivalTime = 0, burstTime = 0;
	int waitTime = 0;
	float aveWait = 0;
	int startTime = 0, endTime = 0;
	
	sort(input, y, 1);
	
	for(l = 0; l < y; l++) {
		printf("%d %d %d \n", input[l][0], input[l][1], input[l][2]);
	}
	printf("\n");
	
	for(i = 0; i < y; i++) {
		arrivalTime = input[i][1];
		burstTime = input[i][2];
		
		// if there is a gap between the current end time and arrival time of the next process 
		if (arrivalTime > endTime) {
			startTime = arrivalTime;
			endTime = startTime + burstTime; 
		} else {
			startTime = endTime;
			endTime = startTime + burstTime; 
		}
		
		waitTime = startTime - arrivalTime;
		aveWait = aveWait + waitTime;
		printf("P[%d] Start Time: %d End Time: %d | Waiting time: %d\n", input[i][0], startTime, endTime, waitTime);

	}
	aveWait = aveWait / y;
	printf("\nAve Waiting Time: %f ", aveWait);
}

void sjf (int y, int input[100][3]) {	
	int i = 0, n = 0, x = 0, nQueue = 0, nDone = 0;
	int sjf_type = 0; //used to check if all arrival time are the same
	int waitTime = 0, currTime = 0;
	int readyq[100][3], min[3];
	float aveTime = 0;

	//initialization
	for(i = 0; i < y; i++){
		for(n = 0; n < 3; n++){
			readyq[i][n] = 0;
		}
	}
	
	//checks for the arrival time
	for(i = 0; i < y; i++){
		if(input[i][1] != input[i+1][1])
			sjf_type = 1;
	}

	//getting shortest burst time for all with same arrival time
	if(sjf_type == 0){
		for(x = 0; x < y; x++){
			min[2] = 999999;
			for(n = 0; n < y; n++){
				if(input[n][2] < min[2] && input[n][2] != 0){
					min[0] = input[n][0];
					min[1] = input[n][1];
					min[2] = input[n][2];
				}
			}

			printf("P[%d] Start Time: %d ", min[0], currTime);
			waitTime = currTime - min[1];
			currTime += min[2];
			printf("End time: %d | Waiting time: %d\n", currTime, waitTime);	
			aveTime += waitTime;
			
			//removes the processed ID from the list
			for(i = 0; i < y; i++){
				if(input[i][0] == min[0])
					input[i][2] = 0;
			}
		}
	}
	
	else if(sjf_type == 1){
		while(nDone == 0){
			nQueue = 0;
		
			//get ready queue
			for(i = 0; i < y; i++){
				if(input[i][1] <= currTime && input[i][2] != 0){
					readyq[nQueue][0] = input[i][0];
					readyq[nQueue][1] = input[i][1];
					readyq[nQueue][2] = input[i][2];
	
					input[i][2] = 0;
					nQueue++;
				}
			}
			
			//get sj based on  burst time
			for(x = 0; x < nQueue; x++){
				min[2] = 999999;
				
				if(nQueue > 0){
					for(n = 0; n < y; n++){
						if(readyq[n][2] < min[2] && readyq[n][2] != 0){
							min[0] = readyq[n][0];
							min[1] = readyq[n][1];
							min[2] = readyq[n][2];
						}
					}
				}
				else{
					for(n = 0; n < y; n++){
						if(input[n][2] < min[2] && input[n][2] != 0){
							min[0] = input[n][0];
							min[1] = input[n][1];
							min[2] = input[n][2];
						}
					}
				}
	
				printf("P[%d] Start Time: %d ", min[0], currTime);
				waitTime = currTime - min[1];
				currTime += min[2];
				printf("End time: %d | Waiting time: %d\n", currTime, waitTime);	
				aveTime += waitTime;
				
				//removes the processed ID from the list
				for(i = 0; i < nQueue; i++){
					if(readyq[i][0] == min[0])
						readyq[i][2] = 0;
				}
				
				// checks if all processes are done
				nDone = 1;
				for(i = 0; i < y; i++){
					if(readyq[i][2] != 0 || input[i][2] != 0)
						nDone = 0;
				}
			}
		}
	}
	
	aveTime /= y;
	printf("Average waiting time: %f", aveTime);
	
}

void srtf (int y, int input[100][3]) {
	int i, j;
	int min = 999999;
	int done = 0, time = 0;
	int shortest = 0;
	int check = 0;
	int startTime, endTime;
	int prev = -1, ctr = 1;
	int first = 1;
	float aveWait = 0;
	int remainingTime[100];
	int waitingTime[100];
	int unfinished[100];
	
	// initialization
	for(i = 0; i < y; i++) {
		// copy burst times of all processes
		remainingTime[i] = input[i][2];
		
		// initialize unfinished array
		unfinished[i] = 0;
	}
	
	while(done != y) {
		// find the process with shortest remaining time that is currently in ready queue
		for(j = 0; j < y; j++) {
			if(remainingTime[j] > 0 && remainingTime[j] < min && input[j][1] <= time) {
				min = remainingTime[j];
				shortest = j;	
				check = 1;
			} 
		}
		
		if(first == 1) {
			startTime = time;
			printf("\nP[%d] Start time: %d ", input[shortest][0], startTime);
			first = 0;
		} else {
			if(shortest != prev) {
				endTime = startTime + ctr;
				ctr = 1;
				
				// if process has remaining time left
				if(unfinished[prev] != 0) {
					waitingTime[shortest] = startTime - unfinished[prev];
				} 				
				// if process is finished
				else {
					waitingTime[shortest] = startTime - input[prev][1];
				}
				
				// if process is unfinished, save value
				if(remainingTime[prev] != 0) {
					unfinished[prev] = endTime;
				}
						
				aveWait = aveWait + waitingTime[shortest];
				printf(" End time: %d | Waiting time: %d\n", endTime, waitingTime[shortest]);
				
				startTime = time;
				printf("P[%d] Start time: %d ", input[shortest][0], startTime);
			} else if(prev == -1) {
				break;
			} else {
				ctr++;
			}
		}

		if(check == 0) {
			time++;
			continue;
		}
		
		// decrement remaining time and update minimum
		remainingTime[shortest]--;
		min = remainingTime[shortest];
		
		// if a process is finished
		if(remainingTime[shortest] == 0) {
			done++;
			check = 0;
			
			endTime = time + 1;
			
			if(waitingTime[shortest] < 0) {
				waitingTime[shortest] = 0;
			}
		}
		
		if(min == 0) {
			min = 999999;
		}
		
		time++;
		prev = shortest;
	}
	
	endTime = startTime + ctr;
	
	waitingTime[shortest] = startTime - input[shortest][1];
	aveWait = aveWait + waitingTime[shortest];
	printf("End time: %d | Waiting time: %d", endTime, waitingTime[shortest]);
	
	aveWait = aveWait / y;
	printf("\nAverage waiting time: %f", aveWait);
}

void round_robin (int y, int z, int input[100][3]) {
	int i = 0, x = 0, nDone = 0;
	int waitTime = 0, currTime = 0;
	float aveTime = 0;
	
	while(nDone == 0){
		if(input[x][2] != 0){
			printf("P[%d] Start Time: %d ", input[x][0], currTime);
			waitTime = currTime - input[x][1];
			
			if(input[x][2] < z){
				currTime += input[x][2];
				input[x][2] = 0;
			}
			else{
				currTime += 3;
				input[x][2] -= z;
			}
			
			input[x][1] = currTime; // updates the arrival time
			printf("End time: %d | Waiting time: %d\n", currTime, waitTime);
			aveTime += waitTime;
		}
		
		// checks if all processes are done
		nDone = 1;
		for(i = 0; i < y; i++){
			if(input[i][2] != 0)
				nDone = 0;	
		}
		
		x++;
		if(x == y)
			x = 0;
	}
	
	aveTime /= y;
	printf("Average waiting time: %f", aveTime);
}

int main(void) {

	FILE* fp;
	int x = 0, y = 0, z = 0;
	int input[100][3];
	int n = 0, i = 0;
	char filename[15]; 

	// get filename
	printf("Input filename: ");
	scanf("%s", filename);
	strcat(filename, ".txt");
	
	// initialize input
	for(i = 0; i < 100; i++){
		for(n = 0; n < 3; n++){
			input[i][n] = 0;
		}
	}

	// read file
	fp = fopen(filename, "r");

	if(fp != NULL) {
		fscanf(fp, "%d %d %d", &x, &y, &z);

		for(i = 0; i < y; i++){
			for(n = 0; n < 3; n++){
				fscanf(fp, "%d", &input[i][n]);
			}
		}
              
        fclose(fp);  // don't forget to close this file   
	}
	else{
		fprintf(stderr, "ERROR: File %s not found! Exiting...\n", filename);
        return 0;
	}

	switch(x) {
		case 0: fcfs(y, input); break;
		case 1: sjf(y, input); break;
		case 2: srtf(y, input); break;
		case 3: round_robin(y, z, input); break;
	}	

	return 0;
}
