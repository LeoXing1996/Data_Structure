#include<stdio.h>
#include<stdlib.h>

#define Fail 0
#define Error 0
#define Succ 1

typedef int Elementype;
typedef int Status;
typedef struct LNode{
    Elementype Member;
    struct LNode * Next;
}LNode, *NodeLink;

void Menu();
Status InsertElement(NodeLink, int, Elementype);
Status DeleteElement(NodeLink, int, Elementype *);
Status CreateList_Head_Mode(NodeLink, int);
Status CreateList_Rear_Mode(NodeLink, int);
Status ShowList(NodeLink);
Status PurgeList(NodeLink);


Status InsertElement(NodeLink Head, int pos, Elementype a){
    int i = 0;
    NodeLink p = Head;
    //查找插入位点，找到pos的前驱
    while(!p && i < pos - 1){
        ++i;
        p = p->Next;
    }
    if(!p || i > pos-1) {printf("Invalid position\n"); return Error;}     //!p检验i大于表长+1; j>i-1检验i小于等于0
    NodeLink tar;
    tar = (NodeLink)malloc(sizeof(LNode));
    tar->Next = p->Next;
    tar->Member = a;
    p->Next = tar;
    return Succ;
}//InsertElement

Status DeleteElement(NodeLink Head, int pos, Elementype *Deleted){
    int i = 0;
    NodeLink p = Head;
    //开始遍历，寻找前驱结点
    while(i < pos - 1 && !(p->Next)){
        ++i;
        p = p->Next;
    }
    if(i > pos - 1 || !(p->Next)) {printf("Invalid position!\n"); return Error;}
    NodeLink temp;
    temp = p->Next;
    *Deleted = temp->Member;
    p->Next = temp->Next;
    free(temp);
    return Succ;
}//DeleteElement

Status CreateList_Head_Mode(NodeLink Head, int num){
    int i = 1;
    Elementype Enter;
    Head = (NodeLink)malloc(sizeof(LNode));
    if(!Head){printf("Stake Flow\n"); return Error;}

    Head->Next = NULL;
    for(i = num; i>0; --i){
        NodeLink p;
        p = (NodeLink)malloc(sizeof(LNode));
        if(!p){printf("Stake Flow!\n"); return Error;}

        printf("Please Enter the %dth Element", num - i + 1);
        scanf("%d", &Enter);
        p->Next = Head->Next;
        p->Member = Enter;
        Head->Next = p;
    }
    printf("Link List has already created!\n");
    return Succ;
}//CreateList_Head_Mode

Status CreateList_Rear_Mode(NodeLink Head, int num){
    int i;
    NodeLink Rear;

    Head = (NodeLink)malloc(sizeof(LNode));
    if(!Head){printf("Stake Flow!\n"); return Error;}
    Head->Next = NULL;
    Rear = Head;
    for(i = num; i>0; --i){
        NodeLink p;
        p = (NodeLink)malloc(sizeof(LNode));
        if (!p){printf("Stake Flow!\n"); return Error;}
        Elementype  Enter;

        printf("Enter the %dth Element:",num - i + 1);
        scanf("%d", &Enter);
        p->Member = Enter;
        Rear->Next = p;
        Rear = p->Next;
    }
    Rear->Next = NULL;
    printf("Already Created the LinkList\n");
    return Succ;
}//CreateList_Rear_Mode

Status ShowList(NodeLink Head){
    NodeLink p = Head->Next;
    if(!p)
        printf("Empty List\n");
    while(!p){
        printf("%d\n", p->Member);
        p = p->Next;
    }
    return Succ;
}//ShowList

Status PurgeList(NodeLink Head){
    NodeLink p;    //p为待检验节点的前驱结点
    p = Head;
    Head->Next = NULL;
    while(p->Next){
        NodeLink q, succ;
        succ = p->Next->Next;
        q = Head->Next;
        //比较元素是否相同，相同则free
        while(q != p->Next && p->Next->Member != q->Member)
            q = q->Next;
        if(p->Next != q){
            free(p->Next);
            p->Next = succ;
        }
        p = p->Next;
    }
    printf("LinkList has purged!\n");
    return Succ;
}//PurgeList

int main(void){
    NodeLink Head = NULL;
    int num;
    char Enter;
    Status res = 0;
    printf("Choose the type mode to create the list\n");
    printf("Enter R to use Rear_Mode(which we recommend),"
                   " Enter H to use Head_Mode\n");
    Enter = (char)getchar();
    if (Enter != 'R') {
        while (Enter != 'H') {
            Enter = (char) getchar();
            printf("Please Enter a correct Letter\n");
            printf("Enter R to use Rear_Mode(which we recommend),"
                           " Enter H to use Head_Mode\n");
        }
    }
    switch (Enter){
        case 'H':{
            printf("Head_Mode\n");
            printf("Enter the length of the LinkList: ");
            scanf("%d", &num);
            res = CreateList_Rear_Mode(Head, num);
            break;
        }
        case 'R':{
            printf("Rear_Mode\n");
            printf("Enter the length of the LinkList: ");
            scanf("%d", &num);
            res = CreateList_Rear_Mode(Head, num);
            break;
        }
        default:break;
    }

    if(!res){
        printf("Can't create a new list\n");
        return Fail;
    }
    else printf("LinkList Created successfully\n");

    Menu();
    Enter = (char) getchar();
    while(Enter != 'Q'){
        switch (Enter){
            case 'I':{
                int pos;
                Elementype a;
                printf("Enter the position you want to insert:");
                scanf("%d", &pos);
                printf("Enter the Element you want insert:");
                scanf("%d", &a);
                InsertElement(Head,pos,a);
                printf("Insert Finished\n");
                break;
            }
            case 'D':{
                int pos;
                Elementype *a = NULL;
                printf("Enter the position you want Delete:\n");
                scanf("%d", &pos);
                res = DeleteElement(Head, pos, a);
                if(res){
                    printf("The Element you deleted is %d", *a);
                    printf("Delete Finished\n");
                    break;
                }
            }
            case 'S':{
                printf("The Elements in the list are:\n");
                ShowList(Head);
                break;
            }
            case 'P':{
                printf("Begin to purge the list, please wait.....\n");
                PurgeList(Head);
                printf("Purge finished\n");
                printf("The new List is:\n");
                ShowList(Head);
            }
            default:{
                printf("You Enter a Wrong Letter, try again\n");
                break;
            }
        }
        printf("===================\n");
        Menu();
        Enter = (char)getchar();
    }
    printf("Bye\n");
    return 0;
}

void Menu(){
    printf("Enter\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}