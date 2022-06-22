void RR(FILE * fp, int numProcess, int tSlice)
{
	char proid[numProcess][4];
	char arrival[numProcess][4];
	char burst[numProcess][4];
	int id[numProcess];
	int arr[numProcess];
	int bur[numProcess];
	int ebur[numProcess];
	int fin[numProcess];
	int sliced[numProcess];
	int check = 1;
	int count = 0;
	int done = 0;
	int temp;
	int total = 0;
	float avg = 0.0;
	
	int i = 0;
	int j = 0;
	int k = 0;
	
	//READS EVERY VALUE FOR EVERY PROCESS
	for(i = 0; i < numProcess; i++)
	{
		fscanf(fp, "%s", proid[i]);
		fscanf(fp, "%s", arrival[i]);
		fscanf(fp, "%s", burst[i]);
	}
	
	//CONVERTS ALL CHAR TO INT VALUES
	for(i = 0; i < numProcess; i++)
	{
		id[i] = atoi(proid[i]);
		arr[i] = atoi(arrival[i]);
		bur[i] = atoi(burst[i]);
		ebur[i] = atoi(burst[i]);
		total += bur[i];
		sliced[i] = 0;
	}
	
	printf("Round Robin (RR)\n");
	
	int procs[total];
	int start[numProcess][total];
	int end[numProcess][total];
	
	for(i = 0; i < numProcess; i++) 
	{ 
		for(j = 0; j < total; j++) 
		{
			start[i][j] = -1;
			end[i][j] = -1;
		}
	}
	
	for(i = 0; i < numProcess; i++) 
	{ 
		for(j = i + 1; j < numProcess; j++) 
		{
			if(arr[i] > arr[j]) 	
			{
				temp = id[i]; 
				id[i] = id[j]; 
				id[j] = temp; 
				temp = arr[i]; 
				arr[i] = arr[j]; 
				arr[j] = temp; 
				temp = bur[i]; 
				bur[i] = bur[j]; 
				bur[j] = temp;
			}
		} 
	}
	
	//ASSIGNS PROCESS ID TO SPECIFIC "TIMESTAMPS"
	for(i = 0; i < total; i++) 
	{
		for(j = 0; j < numProcess; j++) 
		{
			if((ebur[j] > 0) && (arr[j] <= i) && (count < tSlice) && !sliced[j]) 
			{
				k = j;
				break;
			}
		}
		
		count++;
		ebur[k]--;
		procs[i] = k;
		
		if(count == tSlice)
		{
			sliced[k] = 1;
			count = 0;
		}
		
		if(ebur[k] == 0)
		{
			sliced[k] = 1;
			count = 0;
		}
		
		for(j = 0; j < numProcess; j++) 
		{
			if(!sliced[j])
			{
				if(arr[j] <= i)
				{
					done = 0;
					break;
				}
			}
			if(sliced[j]) 
			{
				done = 1;
			}
		}
		
		if(done)
		{
			for(j = 0; j < numProcess; j++) 
			{
				if(arr[j] <= i)
				{
					if(ebur[j] > 0)
					{
						sliced[j] = 0;
					}
				}
			}
		}
	}
	
	//GETS FINAL END TIME OF EACH PROCESS
	for(i = 0; i < total; i++) 
	{ 
		for(j = 0; j < numProcess; j++) 
		{ 
			if(procs[i] == j) 
			{ 
				fin[j] = i;
			}
		}
	}
	
	//GETS ALL START AND END TIMES
	for(i = 0; i < numProcess; i++) 
	{
		k = 0;
		check = 1;
		for(j = 0; j <= total; j++) 
		{
			if(procs[j] == i) 
			{ 
				if(check)
				{
					start[i][k] = j;
				}
				check = 0;
			}
			else
			{
				if(!check)
				{
					end[i][k] = j;
					k++;
				}
				check = 1;
			}
		}
	}
	
	for(i = 0; i < numProcess; i++) 
	{
		printf("P[%d]", id[i]);
		for(j = 0; j < total; j++) 
		{
			if(start[i][j] != -1 && end[i][j] != -1)
			{
				printf(" start time: %d\t end time: %d\t |", start[i][j], end[i][j]);
			}
		}
		printf(" Waiting time: %d\n", (((fin[i] - arr[i]) + 1) - bur[i]));
		avg += (((fin[i] - arr[i]) + 1) - bur[i]);
	}
	
    printf("Average waiting time: %f\n", (avg / numProcess));
}