/**************************************************************************************************/
/* Copyright (C) mc2lab.com, SSE@USTC, 2014-2015                                                  */
/*                                                                                                */
/*  FILE NAME             :  compare.c                                                            */
/*  PRINCIPAL AUTHOR      :  Zhangjunxiang <JG14225004>                                           */
/*  SUBSYSTEM NAME        :  compare                                                              */
/*  MODULE NAME           :  compare                                                              */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/13                                                           */
/*  DESCRIPTION           :  This is a compare program                                            */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by Zhangjunxiang, 2014/09/13
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define CMD_LEN     128
#define DESC_LEN    1024
#define CMD_NUM     10

int Cmd();
int Find();
int Ex();

typedef struct DataNode
{
    char*   cmd;
    char*   desc;
    int     (*handler)();
    struct  DataNode *next;
} tDataNode;


tDataNode* Search(tDataNode * prior, char * cmd)
{
    if(prior == NULL || cmd == NULL)
    {
        return NULL;
    }
    tDataNode *p = prior;
    while(p != NULL)
    {
        if(!strcmp(p->cmd, cmd))
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int ShowCmd(tDataNode * prior)
{
    printf("Menu List:\n");
    tDataNode *p = prior;
    while(p != NULL)
    {
        printf("\t%s\n", p->cmd);
        p = p->next;
    }
    return 0;
}


/* menu program */

static tDataNode element[] =
{
    {"compare", "This is a compare function!", NULL, &element[1]},
    {"description", "How to deal with two figures.", NULL, &element[2]},
    {"help", "Help Documents!", Cmd, &element[3]},
    {"exit", "Exit the program!", Ex, NULL}
};

int i = 0;

main()
{
    printf(" \n***There is a Compare Program.***\n ");
    while(!i)
    {
        char cmd[CMD_LEN];
        printf(" \nInput a command > ");
        scanf("%s", cmd);
        Find(cmd);
    }
}

int Cmd()
{
    ShowCmd(element);
    return 0;
}

int Find(char * cmd)
{
        tDataNode *p = Search(element, cmd);
        if( p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            return 0;
        }
        printf("%s - %s\n", p->cmd, p->desc);
        if(p->handler != NULL)
        {
             p->handler();
        }

}

int Ex(char * cmd)
{
    i = 1;
    return 0;
}
