#include "hash_t.h"

char *get_word(const char *beg, const char *end)
{
    unsigned i = 0;
    unsigned len = 0;
    char *word;

    len = (end - beg) + 1;

    word = (char*)calloc(len + 1, sizeof(char));

    for (i = 0; i < len; ++i)
        *(word + i) = *(beg + i);

    word[len] = '\0';

    return word;

}

unsigned count_f_w(const char *find_word, unsigned len,
                   struct node_t **hash_t)
{
    unsigned hash = 0;

    struct node_t *f_bucket = NULL;

    hash = get_hash(find_word, find_word + len - 1);

    if (hash_t[hash]->word != NULL) {   //if ->word != NULL, then ->next != NULL
        f_bucket = hash_t[hash];
        do {
            if (strcmp(f_bucket->word, find_word) == 0) {
                return f_bucket->count_w;
            } else {
                f_bucket = f_bucket->next;
            }
        } while (f_bucket != NULL);
    }

    return 0u;
}



int main()
{
    unsigned i = 0;
    unsigned j = 0;
    int res = 0;
    unsigned c_ans = 0;         //count  of answers
    unsigned len_text = 0;      //length of text
    unsigned len_f_w = 0;       //length of finding words

    struct node_t **hash_t;

    char unused;
    char *text, *f_words, *find_word;

    res = scanf("%d\n", &c_ans);
    assert(res == 1);
    res = scanf("%d\n", &len_text);
    assert(res == 1);

    unused = ' ';
    while (isspace(unused))
        scanf("%c", &unused);

    text = (char*)calloc(len_text + 1, sizeof(char));
    assert(text != NULL);

    text[0] = unused;

    for (i = 1; i < len_text; ++i)
        scanf("%c", text + i);
    text[len_text] = '\0';

    res = scanf("%d\n", &len_f_w);
    assert(res == 1);

    unused = ' ';
    while (isspace(unused))
        scanf("%c", &unused);

    f_words = (char*)calloc(len_f_w + 1, sizeof(char));
    assert(f_words != NULL);

    f_words[0] = unused;

    for (i = 1; i < len_f_w; ++i)
        scanf("%c", f_words + i);
    f_words[len_f_w] = '\0';

    ///////////////////

    hash_t = (struct node_t **)calloc(M, sizeof(struct node_t *));
    create_hash_table(text, len_text, hash_t);

    for (i = 0; i < len_f_w; ) {
        j = i;
        while (!(isspace(*(f_words + i))) && *(f_words + i) != '\0') {
            ++i;
        }

        find_word = (char*)calloc(i-j + 1, sizeof(char));
        find_word = get_word(f_words + j, f_words + i - 1);
        printf("%u ", count_f_w(find_word, i - j, hash_t));

        ++i;                    //miss space
        free(find_word);
    }

    free(text);
    free(f_words);

    delete_hash_t(hash_t);
}
