#include <stdio.h>
#include <dirent.h>
#include "cbfi.h"

int main () {
    struct dirent *pDirent;
    struct dirent *qDirent;
    DIR *pDir, *qDir;

    pDir = opendir ("testdir");
    if (pDir == NULL) {
        printf ("opendir 1 failed for directory testdir\n");
    }
    else{
    	printf("files in directory testdir\n");
    	while ((pDirent = readdir(pDir)) != NULL) {
        	printf ("[%s]\n", pDirent->d_name);
    	}
    	printf("end of files\n");
    	closedir (pDir);	
    }

    qDir = opendir ("testdir");
    if (qDir == NULL) {
        printf ("opendir 2 failed for directory testdir\n");
    }
    else{
    	printf("files in directory testdir\n");
    	while ((qDirent = readdir(qDir)) != NULL) {
        	printf ("[%s]\n", qDirent->d_name);
    	}
    	printf("end of files\n");
    	closedir (qDir);	
    }
    return 0;
}