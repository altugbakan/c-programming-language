#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
struct lnode *addline(struct lnode *, int);
void treeprint(struct tnode *);
int wordsearch(char *);

char *ignorewords[] = {
    "a", "an", "and", "are", "as", "at", "be", "but", "by", "for", "if", "in", "is", "it", "of", "on", "that", "the", "to", "was", "were", "with"};
int currentline = 1;

struct lnode
{
    int line;
    struct lnode *next;
};

struct tnode
{
    char *word;
    struct lnode *lines;
    struct tnode *left;
    struct tnode *right;
};

int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    printf("All words in the document and their line numbers:\n");
    treeprint(root);

    return 0;
}

int wordsearch(char *word)
{
    int high = sizeof ignorewords / sizeof(char *), mid, cond, low = 0;

    while (low < high)
    {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, ignorewords[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

struct tnode *talloc(void);
struct lnode *lalloc(void);
char *_strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (wordsearch(w) != -1)
        return p;

    if (p == NULL)
    {
        p = talloc();
        p->word = _strdup(w);
        p->left = p->right = NULL;
        p->lines = addline(p->lines, currentline);
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->lines = addline(p->lines, currentline);
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

struct lnode *addline(struct lnode *p, int line)
{
    if (p == NULL)
    {
        p = lalloc();
        p->line = line;
        p->next = NULL;
    }
    else if (p->line != line)
        p->next = addline(p->next, line);

    return p;
}

void treeprint(struct tnode *p)
{
    struct lnode *lines;

    if (p != NULL)
    {
        treeprint(p->left);
        printf("%s: ", p->word);
        for (lines = p->lines; lines != NULL; lines = lines->next)
            printf("%d ", lines->line);
        printf("\n");
        treeprint(p->right);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

struct lnode *lalloc(void)
{
    return (struct lnode *)malloc(sizeof(struct lnode));
}

char *_strdup(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);

    return p;
}

int getch();
void ungetch(int);

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n')
            currentline++;

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }

    *w = '\0';

    return word[0];
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