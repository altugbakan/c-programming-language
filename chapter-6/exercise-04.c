#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXNODE 100

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void flattentree(struct tnode *);
void nodesort();

int currnode = 0;
struct tnode *nodes[MAXNODE];

struct tnode
{
    char *word;
    int count;
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

    nodesort();

    printf("Distinct words sorted into decreasing order of frequency:\n");

    for (int i = 0; i < currnode; i++)
        printf("%d %s\n", nodes[i]->count, nodes[i]->word);

    return 0;
}

struct tnode *talloc();
char *_strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL)
    {
        p = talloc();
        p->count = 1;
        p->word = _strdup(w);
        p->left = p->right = NULL;
        nodes[currnode++] = p;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

void nodesort()
{
    int gap, i, j;
    struct tnode *temp;

    for (gap = currnode / 2; gap > 0; gap /= 2)
        for (i = gap; i < currnode; i++)
            for (j = i - gap; j >= 0 && nodes[j]->count < nodes[j + gap]->count; j -= gap)
            {
                temp = nodes[j];
                nodes[j] = nodes[j + gap];
                nodes[j + gap] = temp;
            }
}

struct tnode *talloc()
{
    return (struct tnode *)malloc(sizeof(struct tnode));
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
        ;

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