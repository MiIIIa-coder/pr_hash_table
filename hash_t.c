/*!
  @file hash_t.c
  @brief Contains functions of hash-table.
*/

#include "hash_t.h"

unsigned h__a_b__(unsigned n)
{
    return ((A * n + B) % P);
}

unsigned get_hash(const char *pat, const char *end)
{
    unsigned p = 0;
    unsigned r = 1;

    for (; pat != end; ++pat, r *= R)
        p += ((*pat) * r) % P;
    return h__a_b__(p);
}

struct node_t *creat_list()
{
    struct node_t *l = (struct node_t*)malloc(sizeof(struct node_t));
    l->next = NULL;
    l->word = NULL;
    l->count_w = 0u;

    return l;
}

void put_word_in_b(struct node_t *top, const char *text, unsigned start,
                   unsigned len)
{
    unsigned i = 0;
    unsigned j = 0;
    top->word = (char*)calloc(len + 1, sizeof(char));

    for (j = 0, i = start; j < len; ++i, ++j) {
        *(top->word + j) = *(text + i);
    }

    *(top->word + j) = '\0';
}

struct node_t *find_last(struct node_t *top)
{
    struct node_t *ptr = NULL;

    for (ptr = top; ptr->next != NULL; ptr = ptr->next) {
    }

    return ptr;
}

void add_to_list(struct node_t *last, const char *text, unsigned start,
                 unsigned len)
{
    struct node_t *tmp;

    if (last == NULL)
        return;

    tmp = (struct node_t *) malloc(sizeof(struct node_t));
    assert(last->next == NULL);

    put_word_in_b(tmp, text, start, len);
    tmp->count_w = 1u;
    tmp->next = NULL;

    if (last->next == NULL)
        last->next = tmp;
}


void delete_hash_t(struct node_t **hash_t)
{
    unsigned i = 0;
    struct node_t *new_top = NULL;

    for (i = 0; i < M; ++i) {         //M - is a power of hash_t
        while (hash_t[i]->next != NULL) {
            new_top = hash_t[i]->next;
            free(hash_t[i]);
            hash_t[i] = new_top;
        }
    }

    free(hash_t);
}

void create_hash_table(const char *text, unsigned len_text,
                       struct node_t **hash_t)
{
    unsigned i = 0;
    unsigned j = 0;
    unsigned hash = 0;
    unsigned was_found = 0;

    char *word = NULL;

    struct node_t *last = NULL;
    struct node_t *bucket = NULL;

    //in all places of hash-table put pointer of list
    for (i = 0; i < M; ++i) {   //M - is a const
        hash_t[i] = creat_list();
    }

    //in hash-table put finding words with their hashes
    for (i = 0; i < len_text; ) {
        j = i;
        while (!(isspace(*(text + i))) && *(text + i) != '\0') {
            ++i;
        }
        hash = get_hash(text + j, text + i - 1);
        word = get_word(text + j, text + i - 1);

        was_found = 0;
        if (hash_t[hash]->word == NULL) {       //if first in bucket
            ++(hash_t[hash]->count_w);
            put_word_in_b(hash_t[hash], text, j, i - j);
            was_found = 1;
        } else {
            bucket = hash_t[hash];
            while (bucket != NULL) {
                if (strcmp(bucket->word, word) == 0) {
                    ++(bucket->count_w);        //add count of word
                    was_found = 1;
                    break;
                }
                bucket = bucket->next;  //step to next el of list
            }
        }

        if (!(was_found)) {
            last = find_last(hash_t[hash]);
            add_to_list(last, text, j, i - j);
        }

        ++i;                    //miss space
    }

    free(word);

}
