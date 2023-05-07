#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define AMOUNT 6

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

int amount = AMOUNT;
char *last = NULL;
int lastprinted = 0;

struct tnode
{
    char *word;
    struct tnode *left;
    struct tnode *right;
};

int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];

    if (argc == 2 && (*++argv)[0] == '-')
        amount = atoi(++argv[0]);

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    printf("Words that are identical in the first %d characters:\n", amount);
    treeprint(root);

    return 0;
}

struct tnode *talloc(void);
char *_strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (strlen(w) < amount)
        return p;

    if (p == NULL)
    {
        p = talloc();
        p->word = _strdup(w);
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) <= 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);

        if (last == NULL)
        {
            last = p->word;
        }
        else if (strncmp(last, p->word, amount) == 0)
        {
            if (!lastprinted)
            {
                printf("%s\n", last);
                lastprinted = 1;
            }
            printf("%s\n", p->word);
        }
        else
        {
            last = p->word;

            if (lastprinted)
                printf("\n");

            lastprinted = 0;
        }

        treeprint(p->right);
    }
}

struct tnode *talloc(void)
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
    else
        return c;

    if (isalpha(c) || c == '_' || c == '#' || c == '\'' || c == '"')
    {
        for (; --lim > 0; w++)
            if (!isalnum(*w = getch()) && *w != '_' && *w != '#' && *w != '\'' && *w != '"')
            {
                ungetch(*w);
                break;
            }
    }
    else if (c == '/')
    {
        if ((c = getch()) == '*')
        {
            for (; --lim > 0;)
            {
                if ((c = getch()) == '*')
                {
                    if ((c = getch()) == '/')
                    {
                        w--;
                        break;
                    }
                    else
                        ungetch(c);
                }
            }
        }
        else
            ungetch(c);
    }
    else if (c == '"' || c == '\'')
    {
        for (; --lim > 0; w++)
        {
            if (*w == c)
            {
                w++;
                break;
            }
            else if (*w == EOF)
                break;
        }
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