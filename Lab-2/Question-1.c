// Write a program using file handling functions to copy a file (Input1.txt). 
// Write a program which converts entire file (obtained after copying) from lower case to upper case and vice versa.

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


int main(){
    
    FILE *ifp, *ofp;
    char ch;
    
    ifp = fopen("Input1.txt", "r");
    ofp = fopen("Output1.txt", "w");
    
    if(ifp == NULL){
        printf("File not found - Error!\n");
    }
    else{
        while((ch=fgetc(ifp))!=EOF){
            if(isalpha(ch)){
                if(isupper(ch)){
                    ch = tolower(ch);
                }
                else{
                    ch = toupper(ch);
                }
            }
            printf("%c",ch);
            fputc(ch, ofp);
        }
        fclose(ifp);
        fclose(ofp);
    }
    
    return(0);
}