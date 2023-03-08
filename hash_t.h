/*!
  @file hash_t.h
  @brief Interface of hash-table.
*/

#ifndef HASH_T_H_INCLUDED
#define HASH_T_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

const unsigned A = 257u;
const unsigned B = 519u;
const unsigned P = 19739u;
const unsigned M = 11919u;   //Power of hash-table
const unsigned R = 119u;

struct node_t {
    struct node_t *next;
    char *word;
    unsigned count_w;
};

/*!
  @brief function finds hash for unsigned.
*/
unsigned h__a_b__(unsigned n);

/*!
  @brief function finds hash for char.
*/
unsigned get_hash(const char *pat, const char *end);

/*!
  @brief function return word
*/
char *get_word(const char *beg, const char *end);

/*!
  @brief function creates beginning of new bucket in hash-table.
*/
struct node_t *creat_list();

/*!
  @brief function puts word in bucket of hash-table.
*/
void put_word_in_b(struct node_t *top, const char *text, unsigned start,
                   unsigned len);

/*!
  @brief function finds last elem in bucket.
*/
struct node_t *find_last(struct node_t *top);

/*!
  @brief function adds new elem to list.
*/
void add_to_list(struct node_t *last, const char *text, unsigned start,
                 unsigned len);

/*!
  @brief function deletes hash-table.
*/
void delete_hash_t(struct node_t **hash_t);

/*!
  @brief function creates hash-table.
*/
void create_hash_table(const char *text, unsigned len_text,
                       struct node_t **hash_t);




#endif // HASH_T_H_INCLUDED
