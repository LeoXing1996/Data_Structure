#include <stdio.h>
#include <stdlib.h>

#define Succ 1
#define Error 0
#define Fail 0

#define Status int

typedef struct DuLNode{
    int Member;
    struct DuLNode *Prior;
    struct DuLNode *Next;
}DuLNode, *DuLinkList;

void Menu();
int List_to_Ocp(Status);
Status Init_List(DuLinkList, int);
Status Insert_Element(DuLinkList, int, int);
Status Delete_Element(DuLinkList, int, int*);
Status Show_List(DuLinkList);
Status Merge_List(DuLinkList List_a, DuLinkList List_b, DuLinkList List_c);

int main() {
    int num, count;
    Status Merged = 0;  //记录3号表是否由于合并操作生成
    Status res;

    DuLinkList Head_1 = NULL;
    DuLinkList Head_2 = NULL;
    DuLinkList Head_3 = NULL;
    //创建2个双向链表
    for(count = 0; count < 2; ++count){
        printf("Create the %d DuList\n", count);
        printf("Enter the length of the List:");
        scanf("%d", &num);
        switch (count){
            case 0:{res = Init_List(Head_1, num); break;}
            case 1:{res = Init_List(Head_2, num); break;}
            case 2:{res = Init_List(Head_3, num); break;}
            default:break;
        }
        if(!res){
            printf("Failed to Create the %dth DuList\n", count);
            return Fail;
        }
        printf("The %dth DuList is Created Successfully!\n", count);
    }

    //打开功能菜单
    Menu();
    char Enter;
    Enter = (char)getchar();

    while(Enter != 'Q'){
        switch (Enter){
            case 'I':{
                int pos, Mem, List_Num;
                List_Num = List_to_Ocp(Merged);
                //插入位置
                printf("Enter the Position you want to Insert:");
                scanf("%d", &pos);
                //插入元素
                printf("Enter the Element you want to Insert:");
                scanf("%d", &Mem);
                //执行操作
                if(List_Num == 1)
                    res = Insert_Element(Head_1, pos, Mem);
                if(List_Num == 2)
                    res = Insert_Element(Head_2, pos, Mem);
                else res = Insert_Element(Head_3, pos, Mem);

                if (res != 0) printf("Occupation Succeed\n");
                else printf("Insert Failed\n");
                break;
            }
            case 'D':{
                int pos, List_Num;
                int * a;
                List_Num = List_to_Ocp(Merged);
                //操作位置
                printf("Enter the Position you want to Insert:");
                scanf("%d", &pos);
                //执行操作
                if(List_Num == 1)
                    res = Delete_Element(Head_1, pos, a);
                if(List_Num == 2)
                    res = Delete_Element(Head_2, pos, a);
                else res = Delete_Element(Head_3, pos, a);
                //显示执行情况
                if (res != 0) {
                    printf("Occupation Succeed\n");
                    printf("The Element you Deleted is: %d\n", *a);
                }
                else printf("Insert Failed\n");
                break;
            }
            case 'S':{
                int List_Mum;
                List_Mum = List_to_Ocp(Merged);
                printf("Elements in List %d are:", List_Mum);
                switch (List_Mum){
                    case 1: {Show_List(Head_1); break;}
                    case 2: {Show_List(Head_2); break;}
                    case 3: {Show_List(Head_3); break;}
                    default: break;
                }
                break;
            }
            case 'M':{
                printf("Start to Merge List_1 and List_2\n");
                res = Merge_List(Head_1, Head_2, Head_3);
                if(!res){printf("Occupation Failed\n"); }
                else {
                    printf("The New List is shown below:\n");
                    Show_List(Head_3);
                    Merged = 1;
                }
                break;
            }
            default:{
                printf("You Enter a Wrong Letter, Please Enter Again\n");
                break;
            }
        }
        Enter = (char)getchar();
    }
    printf("Bye!");
    return 0;
}

void Menu(){
    printf("Enter I to Insert a new Element\n");
    printf("Enter D to Delete a Element from the List\n");
    printf("Enter S to Show the List\n");
    printf("Enter M to Merge two List\n");
    printf("Enter Q to Quit\n");
}

int List_to_Ocp(Status Merged){
    int List_Num, List_Range;
    printf("Enter which DuList you want Insert:");
    scanf("%d", &List_Num);

    //判定List_3是否已经由于合并操作而生成
    if(Merged == 0) List_Range = 2;
    else List_Range = 3;
    //操作的链表
    while(List_Num<=0 || List_Num > List_Range){
        printf("Please Enter a Number from 1 to %d:\n", List_Range);
        scanf("%d", &List_Num); }
    return List_Num;
}

Status Init_List(DuLinkList Head, int num){

    return Succ;
}