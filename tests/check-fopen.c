#include <stdio.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    FILE *fp1;
    FILE *fp2;
    int y,w;
    fp1=fopen("foo.txt","w+");
    if(fp1==NULL)
    	printf("fopen1 failed\n");
    else{
	    fprintf(fp1,"hello world");
    	y = fclose(fp1);
    }
    if(y==EOF)
    	printf("fclose1 failed\n");
    
    fp2=fopen("foo2.txt","w+");
    if(fp2==NULL)
    	printf("fopen2 failed\n");
    else{
    	fprintf(fp2,"bye world");
    	w = fclose(fp2);
    }
    	
    if(w==EOF)
    	printf("fclose2 failed\n");
    return 0;
}
