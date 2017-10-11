#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREASE 10
#define Error 0
#define Succ 1
#define Fail 0

typedef int Status ;
typedef int Elementype;     //顺序表中基本元素的类型
typedef Status (*Compare)(Elementype a, Elementype b); //定义回调名称
typedef struct{
    Elementype *First;
    int Length;
    int Max;
}SqList;


Status Equal(Elementype, Elementype);
Status Init_List(SqList *List, Elementype a);
int LocateElement(SqList List, Elementype a, 
    Compare Func);      //先只传函数名试一试
Status InsertElement(SqList *List, Elementype a, int num);
Status DeleteElement(SqList *List, int num);
Status ShowList(SqList List);
void Menu(void);

Status Init_List(SqList *List, Elementype a){
    List -> First = (Elementype *)malloc(LIST_INIT_SIZE * sizeof(Elementype));
    if (!List -> First){
        printf("OverFlow\n");
        exit(Fail);
    }
    else{
        *List->First = a;
        List->Length = 1;
        List->Max = LIST_INIT_SIZE;
    }
    return Succ;
}//Init_List 初始化顺序表 并插入第一个元素

int LocateElement(SqList List, Elementype a, Compare Func){
    //先判断是否为空表
    if(!List.Length){
        printf("Empty List\n");
        return Fail;
    }
    else{
        int i = 0;
        Elementype *p = List.First;
        while(i<= List.Length && !Func(a, *p++))
            ++i;
        if(i>List.Length) {return Fail;}
        else {return i;}
    }
}//LocateElement

Status ShowList(SqList List){
    int i = 0;
    if(!List.Length){
        printf("Empty List.\n");
        return Fail;
    }
    else{
        Elementype *p = List.First;
        while(++i <= List.Length){
            printf("%d: %d\n", i, *p);
            p += sizeof(Elementype);
        }

    }
    if(i > List.Length) {return Succ;}
}

Status InsertElement(SqList *List, Elementype a, int num){
    //判断插入位置的合法性
    if(num <1 || num > List->Length + 1){
        printf("Invalid position\n");
        return Fail;
    }
    if(List->Length == List->Max){
        Elementype *NewBase;
        NewBase = (Elementype *)realloc(List->First, (List->Max + LISTINCREASE) * sizeof(SqList));
        if(!NewBase){
            printf("Stack Flow\n");
            return Fail;
        }
        else{
            List->First = NewBase;
            List->Max += LISTINCREASE;
        }
    }
    Elementype *p = List->First + (List->Length - 1) * sizeof(Elementype);  //找到最终元素的指针
    Elementype *Insert = List->First + (num - 1) * sizeof(Elementype); 
    while(p >= Insert){
        *(p+1) = *p;
        --p;
    }
    *Insert = a;
    ++List->Length;
    return Succ;
}

Status DeleteElement(SqList *List, int num){
    if(num<0 || num >List->Length) {printf("Invalid Position.\n"); return Error;}
    int i;
    Elementype *p = List->First + (num - 1) * sizeof(Elementype);
    for(i = num; i < List->Length; ++i){
        *p = *(p + sizeof(Elementype));
    }
    free(List->First + (num - 1) * sizeof(Elementype));
    return Succ;
}//DeleteElement

Status Equal(Elementype a, Elementype b){
    if(a==b){return Succ;}
    else {return Fail;}
}//Compare 比较元素是否相同


int main(void){
    SqList List;
    Elementype Mem;
    int pos;
    char Enter;
    printf("Initial the List\n");
    printf("================================\n");    
    printf("Enter the first member of the List:");
    scanf("%d", &Mem);
    Init_List(&List, Mem);

    Enter = (char) getchar();
    while(Enter != 'Q'){
        Menu();
        Enter = (char) getchar();
        switch(Enter){
            case 'Q':{printf("Bye!\n"); break;}
            case 'I':{printf("The member you want to insert is: "); scanf("%d", &Mem);
                        printf("The position you want to insert is: "); scanf("%d", &pos);
                        InsertElement(&List, Mem, pos); break;}
            case 'D':{printf("Enter the position of the member you want to delete:\n"); scanf("%d", &pos);
                        DeleteElement(&List, pos); break;}
            case 'F':{printf("Enter the element you want to locate:\n"); scanf("%d", &Mem);
                        pos = LocateElement(List, Mem, Equal); printf("Element %d is at the location %d", Mem,pos); break;}
            case 'S':{printf("The elements of the list are:\n");ShowList(List);
                        break;}
            default:{printf("You enter a wrong letter, try again\n"); break;}
                
        }
    }
    return 0;
}

void Menu(void){
    printf("Enter 'I' to insert a new member\n");
    printf("Enter 'D' to delete a member\n");
    printf("Enter 'S' to show the list\n");
    printf("Enter 'F' to Find the member\n");
    printf("Enter 'Q' to Exit\n");
    printf("================================\n");
    printf("Now, enter a letter:\n");
}