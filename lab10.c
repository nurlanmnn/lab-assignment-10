#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie *children[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTree = (struct Trie*)malloc(sizeof(struct Trie));
    
        myTree->count = 0;

        int i;
        for (i=0; i<26; i++)
            myTree->children[i] = NULL;

    return myTree;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *curr = pTrie;
    for (int i = 0; i < strlen(word); i++) 
    {
        int index = word[i] - 'a';
        if (!curr->children[index]) 
        {
            curr->children[index] = createTrie();
        }
        curr = curr->children[index];
    }

    curr->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *curr = pTrie;
    for(int i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if(curr->children[index] == NULL){
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i = 0; i < 26; i++){
        if(pTrie->children[i] != NULL)
            deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return 0;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* ifp = fopen("dictionary.txt", "r");
    int n;
    fscanf(ifp, "%d", &n);
    char word[120];
    for(int i = 0; i < n; i++){
        fscanf(ifp, "%s", word);
        pInWords[i] = (char*)malloc(strlen(word)*sizeof(char));
        strcpy( pInWords[i], word);
    }

    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}