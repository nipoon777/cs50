 /**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */

 /*
 to create a hashtable and a linked list
 */
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node *hashtable[50];

unsigned int count =0;

bool loaded=false;

int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}
/** Check whether the entered word is spelled correctly,return true if successful else false.
 **/


bool check(const char *word)
{
    int len = strlen(word);
    char word_copy[len+1];

    for(int i =0 ;i<len;i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    word_copy[len]='\0';
    //find the location in the bucket

    int h = hash_it(word_copy);
    //make the search node point at the start of the bucket and keep looking for the matched word

    node*cursor= hashtable[h];

    while(cursor!=NULL)
    {
        if (strcmp(cursor->word,word_copy)==0)
        {
            //word matched and in the dictionary
            return true;
        }
        else
        {
            cursor=cursor->next;

        }

    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // make the hash table empty to add new elements to the hash table
    for(int i =0;i<HASHTABLE_SIZE;i++)
    {
        hashtable[i] = NULL;

    }
    //OPEN THE DICTIONARY
    FILE *fp = fopen(dictionary,"r");
    if(fp==NULL)
    {
        printf("Could not open the dictionary. \n");

        return false;

    }
    while(true)
    {
        node* new_node = malloc(sizeof(node));
        if(new_node==NULL)
        {
            printf("could not allocate a new node.\n");
        }

        //read the word from the file and store in the node
        fscanf(fp,"%s",new_node->word);
        new_node->next=NULL;



        if(feof(fp))
        {
            free(new_node);
            break;
        }



        count++;

        int h = hash_it(new_node->word);
        node* head = hashtable[h];


        // if it is the first element in the hash table we need to first declare the head
        if(head==NULL)
        {
            hashtable[h]= new_node;
        }
        // make the node pointer to point to the new element added

        else
        {

            new_node->next = hashtable[h];
            hashtable[h]=new_node;

        }
    }
    fclose(fp);
    loaded= true;
    return true;


}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (loaded)
    {
        return(count);

    }
    else
    {
        return 0;
    }

}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for(int i =0 ; i<HASHTABLE_SIZE;i++)
    {
        node* cursor = hashtable[i];

        while(cursor!=NULL)
        {
            // to not loose the link we need a temporary variable;

            node *temp = cursor;
            cursor=cursor->next;
            free(temp);
        }


    }
    loaded = false;
    return true;
}

