#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "node.h"

char* toLowerCase(char* word);
int hash(char* word, char keys[26]);
void handleWords(char* word, char keys[26], struct Node* hashtable[26]);
void inorderTraversalWrite(struct Node* root, int file);
int max(struct Node* hashtable[26]);
int maxStrLen(struct Node* root, int max);
int lenInt(int number);
void freeBst(struct Node* root);


int main(int argc, char* argv[]) {
  
	int fdin;
  char buffer[1024];
  char* words = (char*) malloc(sizeof(char) * 1024);
  ssize_t size;

  char keys[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
  struct Node* hashtable[26];
  for( int i = 0; i<26; i++){
    hashtable[i] = NULL;
  }

  
  


	char* wordFreak= getenv("WORD_FREAK");
	if(wordFreak != NULL){
	 if((fdin = open(wordFreak, O_RDONLY)) == -1){
          perror("File not found");
    }
      while ((size = read(fdin, buffer, 1)) > 0) {
       if(isalpha(buffer[0]) != 0 ){
         strncat(words, buffer,1);
       } 
       else{
        if(strcmp(words, "") != 0){
         words = toLowerCase(words);
         handleWords(words, keys, hashtable);
         words[0] = '\0';
        }
       }
    } 
    if(strcmp(words, "") != 0){
      words = toLowerCase(words);
      handleWords(words, keys, hashtable);
      words[0] = '\0';
    } 
    printf("\n");
    words[0] = '\0';
	}
  

  //Getting Argument Variables
	for(int i = 1; i < argc; i++){
    if ((fdin = open(argv[i], O_RDONLY)) == -1) {
      printf("File cannot be opened. \n");
  	}
  else {
    while ((size = read(fdin, buffer, 1)) > 0) {
      if(isalpha(buffer[0]) != 0 ){
         strncat(words, buffer, 1);
       } 
       else{
        if(strcmp(words, "") != 0){
         words = toLowerCase(words);
         handleWords(words, keys, hashtable);
         words[0] = '\0';
        }
       }
    }         
    if ((close(fdin)) == -1) {
       printf("File cannot be closed. \n");
    }
	} 
  if(strcmp(words, "") != 0){
    words = toLowerCase(words);
    handleWords(words, keys, hashtable);
  }
  words[0] = '\0';	
  }
  words[0] = '\0';


  //Getting STDIN INPUT
  while((size = read(STDIN_FILENO, buffer, 1)) > 0){
    if(isalpha(buffer[0]) != 0 ){
         strncat(words, buffer,1);
       } 
       else{
        if(strcmp(words, "") != 0){
         words = toLowerCase(words);
         handleWords(words, keys, hashtable);
         words[0] = '\0';
        }
       }
  }
  if(strcmp(words, "") != 0){
      words = toLowerCase(words);
      handleWords(words, keys, hashtable);
      words[0] = '\0';
    } 
  printf("\n");
  words[0] = '\0';
  
  free(words);  

  int output = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

  for(int i =0; i< 26; i++){
    inorderTraversalWrite(hashtable[i], output);
    freeBst(hashtable[i]);
  }
  

	
  return 0;
}



char* toLowerCase(char* string){
  for(int i = 0; string[i] != '\0'; i++){
    string[i]= tolower(string[i]);
  }
  return string;
}



int hash(char* word, char keys[26]){
  char hashChar = word[0];
  for(int i =0; i < 26; i++){
    if( keys[i] == hashChar){
      return i;
    }
  }
  return -1;
}

void handleWords(char* word, char keys[26], struct Node* hashtable[26]){
  int index = hash(word, keys);
  int wordFound = incrementCount(hashtable[index], word);
  if(wordFound == 0){
    hashtable[index]=insert(hashtable[index], word);
  }
}

int lenInt(int number){
  int length = 0;
  while(number != 0){
    number = number/10;
    length++;
  }
  return length;
}



void inorderTraversalWrite(struct Node* root, int file){
  if(root !=NULL){
    inorderTraversalWrite(root->left, file);
    write(file, root->word, strlen(root->word));   
    write(file, " : ", 3);
    char * buf = (char*) malloc(sizeof(char)*10);
    sprintf(buf, "%i", root->count);
    write(file, buf, lenInt(root->count));
    free(buf);
    write(file, "\n", 1);
    inorderTraversalWrite(root->right, file);
  }
}

void freeBst(struct Node* root){
  if(root == NULL){
   return;
  }
  freeBst(root->left);
  freeBst(root->right);
  free(root->word);
  free(root);
}

