/**
 *
 * unlink() testing
 *
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	FILE *fp1;
    FILE *fp2;
    int y,w;
    fp1=fopen("check_unlink.txt","w+");
    if(fp1==NULL)
    	printf("fopen1 failed\n");
    else{
    	fclose(fp1);
    }
	// remove file
	y = unlink("check_unlink.txt");
	if(y==-1){
		printf("unlink 1 failed err no. %d\n",errno);
	}
	fp2=fopen("check_unlink_2.txt","w+");
    if(fp1==NULL)
    	printf("fopen1 failed\n");
    else{
    	fclose(fp2);
    }
	// remove file
	w = unlink("check_unlink_2.txt");
	if(w==-1){
		printf("unlink 2 failed err no. %d\n",errno);
	}
	return 0;
}