/*Name: Colin Ekedigwe, Student number: 20403046 & Name: Gideon Amaechi, Student number: 20364806*/
/*https://www.youtube.com/watch?v=eVqfNODGT1E&list=PLRJUuMNQoQ9j4Px-gxsrpai1IbwJprVhC&index=4&t=25*/
/*https://www.daniweb.com/programming/software-development/threads/482239/binary-tree-search-phone-book*/
/*https://malikprogrammers.com/2021/08/23/simple-mini-project-phonebook-in-c/*/
/*https://www.studytonight.com/c-projects/phone-book-application-c-language-project*/
/*Parts of the coding used here I got from my previous project last year*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> /*This allows the sleep function to operate - gives time for loading of program*/
/*https://stackoverflow.com/questions/39156743/sleep-warning-implicit-declaration-of-function-sleep*/

struct node{ /*Initialising our variables and assigning them with memory size*/
    char name[40];
    char phone_no[12];
    char address[50];
    struct node*left;
    struct node*right;
};
struct node*head=NULL;
char temp_n[40];
char temp_p[12];
char temp_a[50];

/*Creating a new node*/
struct node* createNode(char *name,char *phone_no,char *address){
    struct node*new_node=(struct node*)malloc(sizeof(struct node));
    strcpy(new_node->name,name);
    strcpy(new_node->phone_no,phone_no);
    strcpy(new_node->address,address);
    new_node->left=new_node->right=NULL;
    return new_node;
}

/*Enables user to input name, address and number*/
void insert(char *name,char *phone_no,char *address){
    struct node*root=head;
    struct node *prev = NULL;
    if(root==NULL){
        struct node*new_node=createNode(name,phone_no,address);
        head=new_node;
        return;
    }
    while(root!=NULL){ /*If the same phone number is entered regardless of name and address an error message comes up*/
        prev = root;
        if(strcmp(root->phone_no,phone_no)==0){
            printf("\nThis phone number already exists!");
            return;
        }
        else if(strcmp(root->name,name)>0){
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    struct node* new = createNode(name,phone_no,address);
    if(strcmp(prev->name,name)>0){
        prev->left = new;
    }
    else{
        prev->right = new;
    }
}

struct node* inorderpre(struct node* node)
{
    while (node->right != NULL)
        node = node->right;
 
    return node;
}
/*https://www.youtube.com/watch?v=RDT0Ebms9Ts&t=1062s*/
/*Enables user to delete a contact from the phone book*/
struct node* deleteNode(struct node* root, char*name)
{
    if (root == NULL)
        return root;
 
    if (strcmp(root->name,name)>0)
        root->left = deleteNode(root->left, name);
 
    else if (strcmp(root->name,name)<0)
        root->right = deleteNode(root->right, name);

    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = inorderpre(root->left);
        strcpy(root->name,temp->name);
        root->left = deleteNode(root->left, temp->name);
    }
    return root;
}

/*Enables user to see information associated with name such as number and address*/
void searchname(struct node*root,char *name){ /*Searches for a node and retrieves data.*/
    if(root!=NULL){
        searchname(root->left,name);
        if(strstr(root->name,name)){
            printf("Name : %-12s , Phone No.: %-10s , Address: %-12s \n",root->name,root->phone_no,root->address);
        }
        searchname(root->right,name);
    }
}

/*Enables user to see information associated with number such as name and address*/
void searchnum(struct node*root,char *phone){ /*Searches for a node and retrieves data.*/
    if(root!=NULL){
        searchnum(root->left,phone);
        if(strstr(root->phone_no,phone)){
            printf("Name : %-12s , Phone No.: %-10s , Address: %-12s \n",root->name,root->phone_no,root->address);
        }
        searchnum(root->right,phone);
    }
}

/*Enables user to see information associated such as name, number and address in ascending order*/
void showcontact(struct node*root){
    if(root!=NULL){
        showcontact(root->left);
        printf("Name : %-12s , Phone No.: %-10s , Address: %-12s \n",root->name,root->phone_no,root->address);
        showcontact(root->right);
    }
}

int main(){ /*Interface of the program, I got this from one of my previous projects last year*/
    sleep(1.5);
    printf("****************************************************************");
    printf("\n\n\n*********COLIN AND GIDEON'S SHELL - 20403046 & 20364806*********");
    printf("\n\n\t---------USE AT YOUR OWN RISK----------");
    printf("\n\n------Unsure of what commands to use? Type '5'------");
    printf("\n\n\n****************************************************************\n");
    sleep(1.2);
    printf("Welcome User to Colin & Gideon's custom C command shell program!\n");
    printf("----------------------------------------------------------------\n");
    sleep(1);
    printf("\n\tLet's begin, here are your options down below!\n");
    menu:
    printf("\n-------------------------------MENU------------------------------\n"); /*Menu options*/
    printf("1. Add Contact\n");
    printf("2. Delete Contact\n");
    printf("3. Search Contact\n");
    printf("4. Show All Contacts\n");
    printf("5. Show 'README' Instructions\n");
    printf("6. Quit Program\n");

    int pick; /*Want input to be an integer, we will get the number than assign it ti the correct function below*/
    printf("\nEnter your pick: ");
    scanf("%d",&pick);

    if(pick==1){ /*User inputs name, phone number and address, information is collect from our insert function*/
        printf("\nEnter name: ");
        while((getchar())!='\n');
        scanf("%[^\n]%*c",temp_n);

        printf("Enter phone number: ");
        scanf("%[^\n]%*c",temp_p);

        printf("Enter address: ");
        scanf("%[^\n]%*c",temp_a);
        insert(temp_n,temp_p,temp_a); /*Get information from user input to display name, number and address*/
    }
    else if(pick==2){ /*If user wants to delete a contact, if no contacts exist they will be returned back to the menu*/
        if(head==NULL){
            printf("No contacts to be deleted!\n");
            goto menu;
        }
        printf("\nEnter the name to be deleted: "); /*Get contact to be deleted via the persons name*/
        while((getchar())!='\n');
        scanf("%[^\n]%*c",temp_n);
        head=deleteNode(head,temp_n);
    }
    /*https://www.includehelp.com/c-programs/else-without-a-previous-if-error-in-c.aspx#:~:text=This%20error%3A%20'else'%20without,these%20statement%20do%20not%20terminate. helped me with executing if and else if to give the option to add numbers to search*/
    else if(pick==3){ /*Allows user to search for a person either via name or number*/
        struct node*root=head;
        if(root==NULL){
            printf("\nNo Contacts to search !\n");
            goto menu;
        }
        /*https://stackoverflow.com/questions/19692139/if-word-then-prints-something Give the user the option to search a name or number*/
        char x[30];
        printf("Would you like to search a 'name' or 'number'?: ");
        scanf("%s", x);
        if (strcmp(x, "name")==0){ /*Once the user types name we instantly prepare to find the name they will insert*/
            printf("\nSearch a name: ");
            while((getchar())!='\n');
            scanf("%[^\n]%*c",temp_n);
            printf("\n");
            searchname(root,temp_n);
            printf("\n");
        }
        else if (strcmp(x, "number")==0){ /*Once the user types number we instantly prepare to find the number they will insert*/
            printf("\nEnter a phone number: ");
            while((getchar())!='\n');
            scanf("%[^\n]%*c",temp_p);
            printf("\n");
            searchnum(root,temp_p);
            printf("\n");
        }
        goto menu;
    }
    else if(pick==4){ /*Shows user all the contacts available and if theres none they will return to the menu*/
        struct node*root=head;
        if(root==NULL){
            printf("\nNo Contacts are there!\n");
            goto menu;
        }
        printf("\nHere are all the contacts in the system!\n"); /*All contacts will be displayed in ascending order*/
        showcontact(root);
        printf("\n");
    }
    else if(pick==5){ /*README SECTION, User manual of the phonebook*/
        struct node*root=head;
        system("more ../src/readme.md"); /*Using system to find the readme insturction manual*/
    }
    else if(pick==6){ /*Exits the program completely*/
        exit(0);
    }
    else{
        printf("Please select a number between 1 - 6, You will return to the menu!\n"); /*If user inserts any key other than 1-6 they will return to the menu*/
        sleep(1.2);
    }
    goto menu;
return 0;
}

/*Author: Colin Ekedigwe - Student Number: 20403046 - I am aware of the Universities regards to breaches of academic
integrity and plagiarism as serious. Any assistance I have gotten by using code to help me has been referenced and
stated with links. I am writing this to acknowledge that a breach of the rules may result in penalties being imposed.*/
