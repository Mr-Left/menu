/**************************************************************************************************/
/* Copyright (C) SA14226202@USTC, 2014-2015                                                       */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  Zuoguoqinng                                                          */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/16                                                           */
/*  DESCRIPTION           :  This is a menu program                                               */
/**************************************************************************************************/

/*
 *	Revision log
 *
 *	Created by Zuoguoqing, 2014/09/16
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_MAX_LEN 16

/*Declaration of some methods*/
int Help();
int Quit();

/*define node of linklist*/
typedef struct LinkNode
{
	struct LinkNode* next;
	char* cmd;
	char* des;
	int  (*handler)();
}LinkNode, *LinkList;

/*Method to creat LinkList*/
LinkList CreatLinkList()
{
	LinkList list = (LinkList)malloc(sizeof(LinkNode));
	list->cmd = NULL;
	list->des = NULL;
	list->next = NULL;
	list->handler = NULL;
	return list;
}

/*Method to add node to linklist*/
void AddLinkNode(LinkList list, LinkNode* node)
{
	LinkNode* tmp = list;
	while(tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = node;
}

/*Method to initialize linklist*/
void InitDate(LinkList* list)
{
	*list = CreatLinkList();
	LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));

	node->cmd = "help";
	node->des = "Menu list: \n";
	node->handler = Help;
	AddLinkNode(*list, node);

	node = (LinkNode*)malloc(sizeof(LinkNode));
	node->cmd = "version";
	node->des = "Version of menu is V1.0\n";
	node->handler = NULL;
	AddLinkNode(*list, node);

	node = (LinkNode*)malloc(sizeof(LinkNode));
	node->cmd = "quit";
	node->des = "Quit from program Menu V1.0\n";
	node->handler = Quit;
	AddLinkNode(*list, node);
}

/*Method to show all cmd list member*/
void ShowCmdList(LinkList list)
{
	LinkNode* tmp = list;
	printf("COMMAND\t\t\tDESCRIPTION\n\n");
	while(tmp->next)
	{
		tmp = tmp->next;
		printf("%s\t\t\t%s", tmp->cmd, tmp->des);
	}
}

/*Method to find weather there is a cmd like input*/
LinkNode* FindCmd(LinkList list, char* cmd)
{
	LinkNode* tmp = list;
	while(tmp->next)
	{
		tmp = tmp->next;
		if(!strcmp(tmp->cmd, cmd))
		{
			return tmp;
		}
	}
	
	return NULL;
}

/*Head node of cmd link list*/
LinkList head = NULL;

int main()
{
	InitDate(&head);

	while(1)
	{
		printf("Please input a cmd> ");
		char cmd[CMD_MAX_LEN];
		scanf("%s", cmd);
		LinkNode* ret = FindCmd(head, cmd);
		if(!ret)
		{
			printf("This is a wrong cmd!Please input again or type 'help' to get some infomation.\n");
			continue;
		}
		printf("%s", ret->des);
		if(ret->handler)
		{
			ret->handler();
		}
	}

	return 0;
}


int Help()
{
	ShowCmdList(head);
	return 0;
}

int Quit()
{
	exit(0);
}


