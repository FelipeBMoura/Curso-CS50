// Get the code from here: https://stackoverflow.com/questions/71313784/cs50-pset5-speller-optimisation

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#if _USE_ZPRT_
#define dbgprt(_fmt...)             printf(_fmt)
#else
#define dbgprt(_fmt...)             do { } while (0)
#endif

#ifndef NODEHASH
#define NODEHASH    1
#endif

#ifndef FASTNODE
#define FASTNODE    1
#endif

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1 + 1];
    struct node *next;
#if NODEHASH
    unsigned int hash;
#endif
} node;

//Prototypes
unsigned int hash(const char *word);

// TODO: Choose number of buckets in hash table
// odd prime number bigger than word count, because math
#ifndef N
#define N 187751
#endif

// Hash table
node *table[N];                         // may need to use calloc

// word count
int word_count = 0;

// 31 because math
// modulus only really needed to clip hash to table index
// so do it _once_ by caller of hash/hash2
#if 0
#define HASH \
    hash = (31 * hash + chr) % N
#else
#define HASH \
    hash = (31 * hash) + chr
#endif

// Hashes word to a number and copies lowercase chars to output buffer
unsigned int
hash2(char *dest,const char *word)
{
    unsigned int hash = 0;

    for (int chr = *word++;  chr != 0;  chr = *word++) {
        chr = tolower((unsigned char) chr);
        HASH;
        *dest++ = chr;
    }

    *dest = 0;

    return hash;
}

// Returns true if word is in dictionary, else false
bool
check(const char *word)
{
    char tmp[LENGTH + 10];

    unsigned int hval = hash2(tmp,word);
    unsigned int hidx = hval % N;

    // iterate through bucket
    for (node *cur = table[hidx];  cur != NULL;  cur = cur->next) {
        // check hash value first -- limits number of str*cmp calls
#if NODEHASH
        if (cur->hash != hval)
            continue;
#endif

        if (strcmp(cur->word, tmp) == 0)
            return true;
    }

    return false;
}

// Hashes word to a number
unsigned int
hash(const char *word)
{
    unsigned int hash = 0;

    for (int chr = *word++;  chr != 0;  chr = *word++)
        HASH;

    return hash;
}

// adjust this value to suit
#ifndef ARENASIZE
#define ARENASIZE       1000
#endif

typedef struct seg seg_t;
struct seg {
    seg_t *seg_next;                // next segment
    int seg_count;                  // number of used nodes in this segment
    node seg_node[ARENASIZE];       // nodes in this segment
};

node *nodelist;                     // list of freed nodes
seg_t *seglist;                     // head of linked list of segments

// newnode -- allocate from pool
node *
newnode(void)
{
    seg_t *seg;
    node *cur;

    while (1) {
        // get node from free node cache
        // use the cached node if possible
        // this only happens if freenode were called [which it isn't]
        cur = nodelist;
        if (cur != NULL) {
            nodelist = cur->next;
            break;
        }

        // try to allocate from current segment
        seg = seglist;
        if (seg != NULL) {
            if (seg->seg_count < ARENASIZE) {
                cur = &seg->seg_node[seg->seg_count++];
                break;
            }
        }

        // allocate a new segment
        seg = malloc(sizeof(*seg));

        // out of memory
        if (seg == NULL)
            break;

        // mark segment as completely unused
        seg->seg_count = 0;

        // attach to segment list
        seg->seg_next = seglist;
        seglist = seg;
    }

    return cur;
}

// freenode -- free a node
void
freenode(node *cur)
{

#if FASTNODE
    cur->next = nodelist;
    nodelist = cur;
#else
    free(cur);
#endif
}

// segunload -- release all segments
void
segunload(void)
{
    seg_t *seg;
    seg_t *next;

    seg = seglist;
    seglist = NULL;

    for (;  seg != NULL;  seg = next) {
        next = seg->seg_next;
        free(seg);
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool
unload(void)
{
    node *cur;

    // remove all nodes from the table
    for (int i = 0;  i < N;  ++i) {
        cur = table[i];

        // put all nodes in hash table back on [cached] free list
        // NOTE: not really necessary
#if FASTNODE
        word_count = 0;
        cur = NULL;
#else
        node *next;
        for (;  cur != NULL;  cur = next, --word_count) {
            next = cur->next;
            freenode(cur);
        }
#endif

        table[i] = cur;
    }

    segunload();

    return true;
}

// Loads dictionary into memory, returning true if successful, else false
bool
load(const char *dictionary)
{

    // open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
        return false;

    // read words from dictionary and write to hash table
    while (1) {
#if FASTNODE
        node *n = newnode();
#else
        node *n = malloc(sizeof(*n));
#endif
        if (n == NULL)
            return false;

        char *word = n->word;

        if (fgets(word,sizeof(n->word),dict) == NULL) {
            freenode(n);
            break;
        }

        // strip newline
#if 0
        word += strlen(word);
        if (--word >= n->word) {
            if (*word == '\n');
                *word = 0;
        }
#else
        word = strchr(word,'\n');
        if (word != NULL)
            *word = 0;
#endif

        // run hash to find the bucket in table
        unsigned int pos = hash(n->word);

#if NODEHASH
        n->hash = pos;
#endif

        // put node in hash table
        pos %= N;
        n->next = table[pos];
        table[pos] = n;

        word_count++;
    }

    fclose(dict);

    // DEBUG: show the bucket counts
#if _USE_ZPRT_
    node *cur;
    int mincount = 0;
    int maxcount = 0;
    int buckcount = 0;
    int totcount = 0;

    for (int i = 0;  i < N;  ++i) {
        cur = table[i];
        if (cur == NULL)
            continue;

        int count = 0;
        for (;  cur != NULL;  cur = cur->next)
            ++count;

        printf("load: BUCKET/%d count=%d\n",i,count);

        if (i == 0) {
            mincount = count;
            maxcount = count;
        }

        if (count < mincount)
            mincount = count;
        if (count > maxcount)
            maxcount = count;
        totcount += count;

        ++buckcount;
    }

    printf("load: TOTAL buckcnt=%d/%d mincount=%d maxcount=%d avgcount=%d/%d\n",
        buckcount,N,mincount,maxcount,totcount / buckcount,totcount / N);
#endif

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int
size(void)
{
    return word_count;
}