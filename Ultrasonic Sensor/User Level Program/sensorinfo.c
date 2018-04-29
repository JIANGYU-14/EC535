#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int pFile;
int main(int argc, char **argv)
{
	int interval;
	char line[128];
	FILE *ofpt; 
	
	if (argc == 3)
	{
		
		interval = atoi(argv[1]);

//		if (pFile < 0)
//		{
//		fprintf (stderr, "Module isn't loaded\n");
//		return 0;
//		}
		
		

//		if (ofpt==NULL)
//		{
//			fprintf (stderr, "File cannot be opened\n");
//		}
//		else
//		{
		while(1)
		{
			pFile = open("/dev/sensor", O_RDWR);	
			ofpt = fopen(argv[2],"w");			
			read(pFile, line, 128);			
			//printf("%s\n", line);
			fprintf (ofpt, "%s\n", line);			
			strcpy(line,"");
			fclose(ofpt);
			close(pFile);
			sleep(interval);
		}
//		}
		
		
	}
	else
		printf("Enter The Correct Number Of Arguments\n");
	return 0;
}

