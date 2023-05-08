#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

static struct nlist *hashtab[HASHSIZE];

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

int main()
{
    install("ONE", "1");
    install("TWO", "2");
    install("THREE", "3");

    printf("lookup(ONE): %s\n", lookup("ONE")->defn);
    printf("lookup(TWO): %s\n", lookup("TWO")->defn);
    printf("lookup(THREE): %s\n", lookup("THREE")->defn);

    printf("\nundef(TWO)\n\n");
    undef("TWO");

    printf("lookup(ONE): %s\n", lookup("ONE")->defn);
    printf("lookup(TWO): %s\n", lookup("TWO") ? lookup("TWO")->defn : "NULL");
    printf("lookup(THREE): %s\n", lookup("THREE")->defn);

    return 0;
}

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;

    return NULL;
}

char *_strdup(char *);

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)
    {
        np = (struct nlist *)malloc(sizeof(*np));

        if (np == NULL || (np->name = _strdup(name)) == NULL)
            return NULL;

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *)np->defn);

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}

void undef(char *name)
{
    struct nlist *np, *prev = NULL;
    unsigned hashval = hash(name);

    for (np = hashtab[hashval]; np != NULL; np = np->next)
    {
        if (strcmp(name, np->name) == 0)
            break;
        prev = np;
    }

    if (np == NULL)
        return;

    if (prev == NULL)
        hashtab[hashval] = np->next;
    else
        prev->next = np->next;

    free((void *)np->name);
    free((void *)np->defn);
    free((void *)np);
}

char *_strdup(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);

    return p;
}