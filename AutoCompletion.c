#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define MAX_SIZE 10000
#define MAX_WORD_SIZE 50

struct TrieNode {
    bool isEndOfWord; //indicating the string from root to node is a string or not
    struct TrieNode* children[26]; // Assuming only lower case alphabetical characters
};

char *words[MAX_SIZE];
void readFromFile();
// Initialize a new Trie node

struct TrieNode* getNode() {
    struct TrieNode* node = malloc(sizeof(struct TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Insert a word into the Trie
void insert(struct TrieNode* root, char* word) {
    struct TrieNode* node = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!node->children[index]) {
            node->children[index] = getNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

// void insert(struct TrieNode* root, char* word) {
//     struct TrieNode* node = root;
//     for (int i = 0; i < strlen(word); i++) {
//         int index = word[i] - 'a';
//         if (!node->children[index]) {
//             node->children[index] = getNode();
//         }
//         node = node->children[index];
//     }
//     node->isEndOfWord = true;
// }

void printWords(struct TrieNode* node, char* prefix) {
    if (node->isEndOfWord) {
        printf("%s\n", prefix);
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            char c = 'a' + i;
            char* newPrefix = malloc(strlen(prefix) + 2);
            strcpy(newPrefix, prefix);
            strncat(newPrefix, &c, 1);
            printWords(node->children[i], newPrefix);
            free(newPrefix);
        }
    }
}

// Find all words in the Trie that start with a given prefix
void search(struct TrieNode* root, char* prefix) {
    struct TrieNode* node = root;
    for (int i = 0; i < strlen(prefix); i++) {
        int index = prefix[i] - 'a';
        if (!node->children[index]) {
            printf("No suggestions found for '%s'\n", prefix);
            return;
        }
        node = node->children[index];
    }
    printWords(node, prefix);
}

int store(struct TrieNode *root, char* s){
    FILE *fp;
    int l = strlen(s) + 1;
    char s1[l];
    strcpy(s1, s); 
   fp = fopen("file.txt", "a");

   fprintf(fp,"\n");
   fprintf(fp,s1,"\n");
   insert(root,s);
   fclose(fp); 
   return 1;
}

//    // Example usage
//     struct TrieNode* root = getNode();
//     FILE *fp;
//     char buff[255];
//     int ch;
//     // char* words[] = {"apple", "banana", "cherry", "grape", "kiwi", "orange", "peach", "pear", "ajinkya"};
//     // int n = sizeof(words) / sizeof(words[0]);
    
//     //getting from file and putting in trie node
//     fp = fopen("words_alpha.txt", "r");
//     if (fp == NULL)
//         printf("File does not exists \n");
//     while (fscanf(fp, "%s", buff) != EOF)
//         insert(root, buff);







int main() {
    // Example usage
    struct TrieNode* root = getNode();
    FILE *fp;
    char buff[255];
    int ch;
    // char* words[] = {"apple", "banana", "cherry", "grape", "kiwi", "orange", "peach", "pear", "ajinkya"};
    // int n = sizeof(words) / sizeof(words[0]);
    
    //getting from file and putting in trie node
    fp = fopen("words_alpha.txt", "r");
    if (fp == NULL)
        printf("File does not exists \n");
    while (fscanf(fp, "%s", buff) != EOF)
        insert(root, buff);

    fclose(fp);


    // for (int i = 0; i < n; i++) {
    //     insert(root, words[i]);
    // }
    char prefix[50];
    printf("Enter a prefix: ");
    scanf("%s", prefix);
    search(root, prefix);

     do
    {
       printf("\n1. Search the word\n");
       printf("2. To insert the word\n");
       printf("3. Exit \n");
       printf("\n\nEnter your choice: ");
       scanf("%d", &ch);
        switch (ch)
        {
        case 1:
           printf("\nEnter the word to search : ");
            scanf("%s", prefix);
            search(root, prefix);
            break;
        case 2: 
                printf("\nEnter the word to insert : \n");
                scanf("%s", prefix);
                store(root,prefix);
            break;
        default:
            break;
        }
    } while (ch!=3);
    
    return 0;
}