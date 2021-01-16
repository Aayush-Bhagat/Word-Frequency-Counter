#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"



struct Node *createNode(char* word){
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->word = (char*) malloc(sizeof(char)*1024);
  strcpy(newNode->word, word);
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->count=1;
  return newNode;
}

int incrementCount(struct Node *root, char* word){
  char* newWord = (char*) malloc(sizeof(char)*1024);
  strcpy(newWord, word);
  if(root == NULL){
    return 0;
  }
  if(strcmp(newWord, root->word) == 0){
    root->count = root->count +1;
    return 1;
  }
  if(strcmp(newWord, root->word) < 0){
    return incrementCount(root->left, word);
  }
  else if(strcmp(newWord, root->word) > 0){
    return incrementCount(root-> right,word);
  }
  return 0;
}

struct Node* insert (struct Node *root, char* word){
  if( root == NULL) {
    return createNode(word);
  }
  if(strcmp(word, root->word) < 0){
    root->left = insert(root->left, word);
  }
  else if(strcmp(word, root->word) > 0){
    root->right = insert(root->right, word);
  }
  
  return root;

}

