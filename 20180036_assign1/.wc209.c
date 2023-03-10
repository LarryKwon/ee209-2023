#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * DFA State Enum
*/
enum DFAState
{
    Out, // Out : it means outside words
    In, // In : it means inside words
    PreComment_In, // PreComment_In: when  user types '/' from the state 'In'
    PreComment_Out, // PreComment_Out: when user types '/' from the state 'Out'
    Comment, // when user types '*' from the state PreComment_In and PreComment_Out
    C99_Comment, // when user type one more '/' from the state PreComment_In and PreComment_Out
    PreOut // when user type '*' from the state Comment
};

/**
 * types of wordCount, which contains below
 * nw: number of word
 * nc: number of character
 * nl: number of line
 * state: state
 * comment_line: where the comment line starts
*/
typedef struct _wordCount
{
    int nw;
    int nc;
    int nl;
    enum DFAState state;
    int comment_line;
} wordCount;

/**
 * like constructor, set the values in wordCount
*/
void constructor(int nw, int nc, int nl, enum DFAState state, int comment_line, wordCount *ptr)
{
    ptr->nc = nc;
    ptr->nw = nw;
    ptr->nl = nl;
    ptr->state = state;
    ptr->comment_line = comment_line;
}
/**
 * out state
 * when the input is Space, remain out state
 * else it can go to PreComment_out or In state whether the character is '/' or not
 * when the input is '/' it goes PreComment_Out state
 * else it goes In state
*/
wordCount out(const wordCount *ptr, char c)
{
    wordCount temp;
    wordCount *ptr_temp;
    ptr_temp = &temp;
    constructor(ptr->nw, ptr->nc, ptr->nl, ptr->state, ptr->comment_line, ptr_temp);
    if (isspace(c) != 0)
    {
        if (c == '\n')
        {
            ptr_temp->nl += 1;
        }
        ptr_temp->nc += 1;
        ptr_temp->state = Out;
    }
    else
    {
        if (c == '/')
        {
            ptr_temp->nc += 1;
            ptr_temp->state = PreComment_Out;
        }
        else
        {
            ptr_temp->nc += 1;
            ptr_temp->state = In;
            ptr_temp->nw += 1;
            // printf("%d in->out\n", ptr_temp->nw);
        }
    }
    return temp;
}

/**
 * In state
 * when the input is Space, go to out state
 * else it can go to PreComment_In or remains in In state whether input is '/' or not
 * if the input is '/', it should go PreComment_In because it means that if the next character is '/' or '*', it should go Comment or C99_Comment
 * else it remains in In state
*/
wordCount in(const wordCount *ptr, char c)
{
    wordCount temp;
    wordCount *ptr_temp;
    ptr_temp = &temp;
    constructor(ptr->nw, ptr->nc, ptr->nl, ptr->state, ptr->comment_line, ptr_temp);
    if (isspace(c) != 0)
    {
        if (c == '\n')
        {
            ptr_temp->nl += 1;
        }
        ptr_temp->nc += 1;
        ptr_temp->state = Out;
    }
    else
    {
        if (c == '/')
        {
            ptr_temp->nc += 1;
            ptr_temp->state = PreComment_In;
        }
        else
        {
            ptr_temp->nc += 1;
            ptr_temp->state = In;
        }
    }
    return temp;
}

/**
 * PreComment_In
 * when the input is space it should go Out state
 * else it should go to Comment, C99_Comment or In 
 * if the input is '*', it should go into Comment state
 * if the input is '/', it should go into C99_Comment state because it means '//' is entered
 * if the input is other character, it should go into In state because it means the inputs are just like '/a' 
*/

wordCount precomment_in(const wordCount *ptr, char c)
{
    wordCount temp;
    wordCount *ptr_temp;
    ptr_temp = &temp;
    constructor(ptr->nw, ptr->nc, ptr->nl, ptr->state, ptr->comment_line, ptr_temp);
    if (isspace(c) != 0)
    {
        if (c == '\n')
        {
            ptr_temp->nl += 1;
        }
        ptr_temp->nc += 1;
        ptr_temp->state = Out;
    }
    else
    {
        if (c == '*')
        {
            //ptr_temp->nw += 1;
            ptr_temp->state = Comment;
            ptr_temp->comment_line = ptr->nl + 1;
        }
        else if (c == '/')
        {
            ptr_temp->nc -= 1;
            ptr_temp->state = C99_Comment;
        }
        else
        {
            ptr_temp->nc += 1;
            ptr_temp->state = In;
        }
    }
    return temp;
}

/**
 * PreComment_Out
 * it is almost same with PreComment_In, but the only difference is that the start point.
 * PreComment_In is from In state and PreComment_Out is from Out State
 * when the start point is Out state when the input character is not space which is not '/' or '*', it means the new word starts
 * But when the start point is In state, there's no need to consider above conditions because a word already starts
 * 
 * when the input is space it should go Out state
 * else it should go to Comment, C99_Comment or In 
 * if the input is '*', it should go into Comment state
 * if the input is '/', it should go into C99_Comment state because it means '//' is entered
 * if the input is other character, it should go into In state because it means the inputs are just like '/a' 
*/

wordCount precomment_out(const wordCount *ptr, char c)
{
    wordCount temp;
    wordCount *ptr_temp;
    ptr_temp = &temp;
    constructor(ptr->nw, ptr->nc, ptr->nl, ptr->state, ptr->comment_line, ptr_temp);
    if (isspace(c) != 0)
    {
        if (c == '\n')
        {
            ptr_temp->nl += 1;
        }
        ptr_temp->nc += 1;
        ptr_temp->nw += 1;
        // printf("%d precomment_out -> out\n", ptr_temp->nw);
        ptr_temp->state = Out;
    }
    else
    {
        if (c == '/')
        {
            ptr_temp->nc -= 1;
            // ptr_temp->nw += 1;
            // printf("%d precomment_out -> precomment_in\n", ptr_temp->nw);

            ptr_temp->state = C99_Comment;
        }
        else if (c == '*')
        {
            ptr_temp->state = Comment;
            ptr_temp->comment_line = ptr->nl+1;
        }
        else
        {
            ptr_temp->nc += 1;
            ptr_temp->nw += 1;
            ptr_temp->state = In;
        }
    }
    return temp;
}

/**
 * C99_Comment
 * C99_Comment is the comment starts with '//' and end with '\n'
 * therefore, when the input is '\n' it should go Out state
 * any other characters comes, the state remains as same
*/
wordCount c99_comment(const wordCount *ptr, char c){
    wordCount temp;
    wordCount *ptr_temp;
    ptr_temp = &temp;
    constructor(ptr->nw, ptr->nc, ptr->nl, ptr->state, ptr->comment_line, ptr_temp);

    if(c == '\n')
    {
        ptr_temp->nl += 1;
        ptr_temp->nc += 1;
        ptr_temp->state = Out;
    }else{
        ptr_temp->state = C99_Comment;
    }
    return temp;

}

/**
 * Comment
 * when the input is '*', is should go to PreOut state
 * else the state remains as same
 */
 
wordCount comment(const wordCount *ptr, char c)
{
    wordCount temp;
    wordCount *ptr_temp;
    ptr_temp = &temp;
    constructor(ptr->nw, ptr->nc, ptr->nl, ptr->state, ptr->comment_line, ptr_temp);
    if (c == '*')
    {
        ptr_temp->state = PreOut;
    }
    else if (c == '\n')
    {
        ptr_temp->nl += 1;
        ptr_temp->nc += 1;
    }
    else
    {
        ptr_temp->state = Comment;
    }
    return temp;
}

/**
 * Pre_Out is the state that the comment already starts and the '*' comes
 * Therefore the input is '/', it should go to Out state
 * when the '*' comes, the the state remains
 * or it should remains in Comment
*/
wordCount pre_out(const wordCount *ptr, char c)
{
    wordCount temp;
    wordCount *ptr_temp;
    ptr_temp = &temp;
    constructor(ptr->nw, ptr->nc, ptr->nl, ptr->state, ptr->comment_line, ptr_temp);
    if (c == '*')
    {
        ptr_temp->state = PreOut;
    }
    else if (c == '/')
    {
        ptr_temp->state = Out;
        // printf("pre_out -> out");
    }
    else
    {
        if (c == '\n')
        {
            ptr_temp->nl += 1;
            ptr_temp->nc += 1;
        }
        ptr_temp->state = Comment;
    }
    return temp;
}

/**
 * main switch case, to controll state
*/

int main()
{
    wordCount wc;
    wc.nc = 0;
    wc.nw = 0;
    wc.nl = 0;
    wc.comment_line = 0;
    wc.state = Out;
    char c;
    const wordCount *ptr = &wc;

    while ((c = getchar()) != EOF)
    {
        switch (wc.state)
        {
        case Out:
            wc = out(ptr, c);
            ptr = &wc;
            break;

        case In:
            wc = in(ptr, c);
            ptr = &wc;
            break;

        case PreComment_In:
            wc = precomment_in(ptr, c);
            ptr = &wc;
            break;

        case PreComment_Out:
            wc = precomment_out(ptr, c);
            ptr = &wc;
            break;

        case C99_Comment:
            wc = c99_comment(ptr,c);
            ptr = &wc;
            break;

        case Comment:
            wc = comment(ptr, c);
            ptr = &wc;
            break;

        case PreOut:
            wc = pre_out(ptr, c);
            ptr = &wc;
            break;
        }
    }
    if (wc.nc == 0)
    {
        wc.nw = 0;
        wc.nl = 0;
    }
    else if (wc.state == Comment || wc.state == PreOut)
    {
        printf("Error: line %d: unterminated comment\n", wc.comment_line);
        exit(1);
    }
    printf("%d %d %d\n", wc.nl, wc.nw, wc.nc);
}