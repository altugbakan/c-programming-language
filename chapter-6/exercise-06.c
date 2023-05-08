#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define HASHSIZE 101

int getword(char *, int);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);

static struct nlist *hashtab[HASHSIZE];

struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
};

int main()
{
    struct nlist *n;
    char word[MAXWORD], defn[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
    {
        if (strcmp("#define", word) == 0)
        {
            getword(word, MAXWORD);
            getword(defn, MAXWORD);

            install(word, defn);
        }
        else
        {
            if ((n = lookup(word)) != NULL)
            {
                printf("%s: %s\n", word, n->defn);
            }
            else
            {
                printf("%s\n", word);
            }
        }
    }

    return 0;
}

int getch();
void ungetch(int);

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;
    if (!isalnum(c) && c != '#')
    {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '#')
        {
            ungetch(*w);
            break;
        }

    *w = '\0';

    return word[0];
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

char *_strdup(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);

    return p;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}