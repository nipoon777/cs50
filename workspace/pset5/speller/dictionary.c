// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

//implement a linked list

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


//define a hashtable array

node* hashtable[HASHTABLE_SIZE];

unsigned int word_count = 0;

bool loaded = false;


//CREATE A HASHFUNCTION

int hash_it(char* needs_hashing)
{
    unsigned int hash =0;
    for(int i=0, n = strlen(needs_hashing);i<n;i++)
        hash = (hash << 2)^needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}



// Returns true if word is in dictionary else false
bool check(const char* word)
{
    // check whether the text file words are correctly spelled
    int len = strlen(word);
    char word_copy [len + 1];

    for(int i = 0 ;i < len;i++)
    {
        word_copy[i]= tolower(word[i]);

    }
    //to end the word character
    word_copy[len] = '\0';

    //get the copy of the word
    int h = hash_it(word_copy);
    //assign the cursor to the bucket

    node* pointer = hashtable[h];

    while(pointer != NULL)
    {
        if(strcmp(pointer->word,word_copy) == 0)
        {
            return true;
            //spelled correctly

        }
        else
        {
            pointer = pointer->next;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char* dictionary)
{
    // EMPTY the hashtable fully
    for(int i = 0 ;i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;

    }
    //open the dictionary file
    FILE* file = fopen(dictionary,"r");

    if(file == NULL)
    {
        printf("Couldn't open the dictionary \n");
        return false;

    }
    //it will run through the entire file
    while(true)
    {

        node* new_node = malloc(sizeof(node));
        if (new_node==NULL)
        {
            printf("Could not malloc the node");
            return false;

        }
        //scan each word of the file to reach end of file
        fscanf(file,"%s",new_node->word);
        new_node->next = NULL;

        if(feof(file))
        {
            free(new_node);
            break;

        }
        //increment the word count
        word_count++;
        //find the unique position in the hash table
        int h = hash_it(new_node->word);
        //assume it to be the first element in the table
        node* head = hashtable[h];
        //if first element
        if(head==NULL)
        {
            hashtable[h]= new_node;

        }
        // add at the first of the link list
        else
        {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
        }

    }
    //close dictionary
    fclose(file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(loaded)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i =0 ;i< HASHTABLE_SIZE;i++)
    {
        node* pointer = hashtable[i];
        while(pointer != NULL)
        {
            //keep connected to the link
            node*temp = pointer;
            pointer = pointer-> next;
            free(temp);
        }

    }
    loaded=false;
    return true;
}
