#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxSize 4096

typedef struct _listNode
{
        char* string;
        struct listNode* next;
}listNode;


int main()
{
        listNode* head = NULL;
        listNode** placeToPutNode = &head;
        char* string = malloc(maxSize * sizeof(char));
	if (string == NULL)
                {
                        printf("memory mistake\n");
                        return -1;
                }
        while (1)
        {
                fgets(string, maxSize, stdin);
                if ((strlen(string) == 2) && (string[0] == '.'))
                {
                        break;
                }
                int length = strlen(string);
		++length;
                char* stringImage = malloc(length * sizeof(char));
                if (stringImage == NULL) {
                        printf("memory mistake\n");
                        break;
                }
                memcpy(stringImage, string, length * sizeof(char));
                //stringImage[length] = '\0';
                *placeToPutNode = malloc(sizeof(listNode));
                if (placeToPutNode == NULL)
                {
                        printf("memory mistake\n");
			free(stringImage);
                        break;
                }
                (*placeToPutNode)->next = NULL;
                (*placeToPutNode)->string = stringImage;
                placeToPutNode = &((*placeToPutNode)->next);
        }
	free(string);
        while(head != NULL)
        {
                printf("%s", head->string);
                listNode* nodeToDestroy = head;
                head = head->next;
                free(nodeToDestroy->string);
                free(nodeToDestroy);
        }
return 0;
}

