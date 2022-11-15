#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int dev = open("/dev/dev_nr2", 0);
	if(dev == -1){
		printf("Opening was not possible!\n");
		return -1;
	}
	printf("opening was successfull!\n");
	close(dev);
	return 0;
}
