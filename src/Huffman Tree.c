#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char data;
    int frequency;
    struct node *left,*right,*next;
}List;

void another_node(List **head, char new_data)  // listeye yeni bir node ekleyen fonksiyon
{
    List *temporary; List *new_node; // temporary listeyi gezmek icin kullanilmistir
    temporary = (*head);
    new_node = (List*)malloc(sizeof(List));

    new_node->data = new_data;
    new_node->frequency = 1;

    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    if((*head) == NULL)
    {
        (*head) = new_node;
        return;
    }
    while(temporary->next != NULL)
    {
        temporary = temporary->next;
    }

    temporary->next = new_node;

}

int does_exist(List *head, char data)  //  String'ten okunmus olan harf daha once linkli listede mevcut ise
{                                      //  1 mevcut degil ise 0 donduran fonksiyon
    List *temporary = head;

    while(temporary != NULL)
    {
        if(temporary->data == data)
        {
            temporary->frequency++;
            return 1;
        }
        temporary = temporary->next;
    }
    return 0;
}

void create_list(List **head, char entry[])   //  String'i "does_exist" ve "another_node" fonksiyonunu kullanarak
{                                             //  linkli listeye ceviren fonksiyon
    int i=0;
    while(entry[i] != '\0')
    {
        if( !does_exist((*head),entry[i]) )  // does_exist harf once listede mevcut ise 1 dondurur
        {
            another_node(head,entry[i]);
        }
        i++;
    }
}

void print_list(List *head)    //  linkli listeyi ekrana yazdiran fonksiyon
{
    List *temporary = head;

    while(temporary != NULL)
    {
        printf("%d%c ->",temporary->frequency,temporary->data);
        temporary = temporary->next;
    }
}

void insert(List **head, List *adding_node)   //  herhangi bir nodu sirali bir sekilde linkli listeye ekleyen fonksiyon
{

    List *current;
    if (*head == NULL || ((*head)->frequency >= adding_node->frequency))
    {
        adding_node->next = *head;
        *head = adding_node;
    }
    else
    {
        current = *head;
        while (current->next!=NULL && current->next->frequency <= adding_node->frequency)
        {
            current = current->next;
        }
        adding_node->next = current->next;
        current->next = adding_node;
    }
}

void sort(List **head, List **bos)    //  insertion sortu gerceklestirmek icin bu fonksiyonun icinde "insert" fonksiyonu kullanilmistir
{
    List *temporary = (*head);
    while ( temporary != NULL )
    {
        List *next = temporary->next;
        insert(bos , temporary);
        temporary = next;
    }
    *head = *bos;
}


List* create_tree(List *current, List *current_next)  // iki tane nodu bir tree sekline ceviren fonksiyon
{
    List *bos = (List*)malloc(sizeof(List));
    bos->data = ' ';
    bos->frequency = (current->frequency) + (current_next->frequency);
    bos->left = current;
    bos->right = current_next;
    bos->next = NULL;
    return bos;
}

void complete_tree(List **head)    //  linkli listeyi tree'ye ceviren fonksiyon
{
    List *bos;
    List *current = *head;

    while(current->next != NULL )
    {
        bos = create_tree(current,current->next);
        insert(head,bos);
        current = current->next->next;
    }
    (*head) = bos;

}

int calculate_height(List *head)   //  tree'nin yuksekliginim hesaplayan fonksiyon
{
   if (head == NULL)
       return 0;
   else
   {
       int Left_height = calculate_height(head->left);
       int Right_height = calculate_height(head->right);

       if (Left_height > Right_height)
           return(Left_height+1);
       else return(Right_height+1);
   }
}

void print_level(List *head, int height)   //  tree'nin herhangi bir seviyesini yazdiran fonksiyon
{
    if (head == NULL){
        printf(" ");
        return;
    }
    if (height == 1)
    {
        if(head->data == ' ' && head->left == NULL)
        {
            printf("%dSpace  ",head->frequency);
        }
        else{
            printf("%d%c   ", head->frequency,head->data);
        }
    }
    else if (height > 1)
    {
        print_level(head->left, height-1);
        print_level(head->right, height-1);
    }
}

void print_tree(List *head)          //  tree'yi yazdiran fonksiyon
{
    int h = calculate_height(head);
    int i;
    for (i=1; i<=h; i++)
    {
        print_level(head, i);
        printf("\n");
    }
}


int main()
{
    List *head = NULL;
    List *bos = NULL;

    char entry[100];
    printf("Enter your String\n");
    scanf("%[^\n]",entry);

    create_list(&head,entry);
    sort(&head,&bos);
    printf("Linked List Form:\n\n");
    print_list(head);
    printf("\n\n");
    complete_tree(&head);

    printf("Tree Form:\n\n");
    print_tree(head);



    return 0;
}
