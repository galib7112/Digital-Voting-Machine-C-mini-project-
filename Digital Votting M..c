#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<ctype.h>
struct voter_info
{
    char name[30];
    char nid_no[20];
    char sex[10];
    char date_of_birth[15];
    char father_name[30];
    char mother_name[30];
    char password[10];
}voter,del;
struct candidate_info
{
    char name[30];
    char nid_no[20];
    char symbol[20];
    long long int VOTE;
    struct candidate_info *next;
}candidate,Del,*can=NULL;
struct voted_list
{
    char nid_no[20];
    struct voted_list *next;
}*voted=NULL;

FILE *fp;
FILE *fpc;
COORD coord= {0,0};
long long int vote[11]={0},total_vote=0,total_voter=0;

void gotoxy(x,y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void delay(unsigned int mseconds)
{
    clock_t n = mseconds + clock();
    while (n > clock());
}
void welcome()
{
    gotoxy(30,4);
	printf("Welcome to digital voting system");
	gotoxy(35,6);
	printf("---------------------");
}

void admin()
{
    char n;
    system("cls");
	welcome();
	label1:

    gotoxy(22,15);
	printf("Enter the corresponding no");

	gotoxy(22,19);
	printf("1. Voter Registration");
	gotoxy(22,21);
	printf("2. Candidate Registration");
	gotoxy(22,23);
	printf("3. Delete from Voter List");
	gotoxy(22,25);
	printf("4. Delete from Candidate List");
	gotoxy(22,27);
	printf("5. Return to main menu");

	gotoxy(22,29);
	fflush(stdin);
	n=getch();
	switch(n)
	{

    case '1':
        {
            voter_reg();
            break;
        }

    case '2':
        {
           candedate_reg();
           break;
        }

    case '3':
        {
           delet_voter();
           break;
        }

    case '4':
        {
            delet_candidate();
            break;
        }

    case '5':
        {
           return;
        }

    default:
        {
            system("cls");
            welcome();
            gotoxy(22,11);
            printf("Wrong choice");
            gotoxy(22,13);
            printf("Retype choice");
            goto label1;
        }

	}
	system("cls");
	welcome();
	goto label1;
}

//SUMI
void voter_reg()
{
    char again;
    label1:
    system("cls");
    welcome();

    gotoxy(15,14);
    printf("Enter the Information of Voter:");
	gotoxy(15,16);
	printf("Name:");

	gotoxy(15,18);
	printf("NID No:");

	gotoxy(15,20);
	printf("Sex:");

	gotoxy(15,22);
	printf("Date of Birth:");

	gotoxy(15,24);
	printf("Father Name:");

	gotoxy(15,26);
	printf("Mother Name:");

	gotoxy(15,28);
	printf("Password:");

	fflush(stdin);
	gotoxy(30,16);
	gets(voter.name);
	strupr(voter.name);

	fflush(stdin);
	gotoxy(30,18);
	gets(voter.nid_no);


	gotoxy(30,20);
	fflush(stdin);
	gets(voter.sex);
	strupr(voter.sex);

	fflush(stdin);
	gotoxy(30,22);
	gets(voter.date_of_birth);


	gotoxy(30,24);
	fflush(stdin);
	gets(voter.father_name);
	strupr(voter.father_name);

	fflush(stdin);
	gotoxy(30,26);
	gets(voter.mother_name);
	strupr(voter.mother_name);

	fflush(stdin);
	gotoxy(30,28);
	gets(voter.password);
	if((fp=fopen("Voter","ab+"))==NULL)
    {
       printf(":: Cannot open the file.... ::");
       getch();
       exit(1);
    }
    fprintf(fp,"%s %s %s %s %s %s %s\n",voter.name,voter.nid_no,voter.sex,voter.date_of_birth,voter.father_name,voter.mother_name,voter.password);
    fclose(fp);
    gotoxy(15,31);
	printf("Enter '1' for next record(y/n):");
	again=getch();
	if(again=='1')
	{
		goto label1;
	}
	else
        return;
}//end of voter registration

void delet_voter()
{
    FILE *old,*newrec;
    int test=0;
    lebel1:
	system("cls");
	welcome();

    old=fopen("Voter","r+");
    newrec=fopen("new","ab+");
    gotoxy(22,15);
    printf("Enter the NID No. of the voter to delete: ");
    gets(del.nid_no);
    while(fscanf(old,"%s %s %s %s %s %s %s",&voter.name,&voter.nid_no,&voter.sex,&voter.date_of_birth,&voter.father_name,&voter.mother_name,&voter.password)!=EOF)
    {
        if(strcmp(voter.nid_no,del.nid_no)==0)
        {
            test++;
            gotoxy(27,20);
            printf(":: Record deleted successfully! ::");
        }
        else
            fprintf(newrec,"%s %s %s %s %s %s %s\n",voter.name,voter.nid_no,voter.sex,voter.date_of_birth,voter.father_name,voter.mother_name,voter.password);

   }
   fclose(old);
   fclose(newrec);
   remove("Voter");
   rename("new","Voter");

   if(test==0)
    {
        gotoxy(27,20);
        printf("::No Records Available::");
        gotoxy(22,23);
        printf("Enter '1' to try again : ");
        char n;
        n=getch();
        if(n=='1')
        {
            goto lebel1;
        }
        else
            return;
    }

    gotoxy(22,23);
    printf("Enter '1' to try again : ");
    char i=getch();
    if(i=='1')
    {
        goto lebel1;
    }
    else
        return;
}//end of delete

//REAFAT
void candedate_reg()
{
    char again;
    label1:
    system("cls");
    welcome();

    gotoxy(15,14);
    printf("Enter the Information of Candidate:");
    gotoxy(15,16);
	printf("NID No:");

	gotoxy(15,18);
	printf("Name:");

	gotoxy(15,20);
	printf("Symbol:");


	fflush(stdin);
	gotoxy(25,16);
	gets(candidate.nid_no);

	fflush(stdin);
    gotoxy(25,18);
    gets(candidate.name);
    strupr(candidate.name);

    gotoxy(25,20);
    fflush(stdin);
    gets(candidate.symbol);
    strupr(candidate.symbol);
    if((fpc=fopen("Candidate","ab+"))==NULL)
    {
        printf("Cannot open the file....");
        getch();
        exit(1);
    }
    fprintf(fpc,"%s %s %s\n",candidate.nid_no,candidate.name,candidate.symbol);
    fclose(fpc);
    gotoxy(15,23);
    printf("Enter '1' for next record(y/n):");
    again=getch();
    if(again=='1')
    {
        goto label1;
    }
    else
        return;
}
void delet_candidate()
{
    FILE *old,*newrec;
    int test=0;
    lebel1:
	system("cls");
	welcome();

    old=fopen("Candidate","r+");
    newrec=fopen("new","ab+");
    gotoxy(22,15);
    printf("Enter the NID No. of the candidate to delete: ");
    gets(Del.nid_no);
    while(fscanf(old,"%s %s %s",&candidate.nid_no,&candidate.name,&candidate.symbol)!=EOF)
    {
        if(strcmp(candidate.nid_no,Del.nid_no)==0)
        {
            test++;
            gotoxy(27,20);
            printf(":: Record deleted successfully! ::");
        }
        else
    fprintf(newrec,"%s %s %s\n",candidate.nid_no,candidate.name,candidate.symbol);

   }
   fclose(old);
   fclose(newrec);
   remove("Candidate");
   rename("new","Candidate");

   if(test==0)
    {
        gotoxy(27,20);
        printf("::No Records Available::");
        gotoxy(22,23);
        printf("Enter '1' to try again : ");
        char n;
        n=getch();
        if(n=='1')
        {
            goto lebel1;
        }
        else
            return;
    }

    gotoxy(22,23);
    printf("Enter '1' to try again : ");
    char i=getch();
    if(i=='1')
    {
        goto lebel1;
    }
    else
        return;
}//end of delete

//UZZAL
void voter_list()
{
    int i;
    long long int x=1;
    fp=fopen("Voter","r");
    int test=0;
    system("cls");
    gotoxy(3,5);
    printf("No.");
    gotoxy(9,5);
	printf("NID No");

	gotoxy(31,5);
	printf("Name");

	gotoxy(61,5);
	printf("Sex");

	gotoxy(73,5);
	printf("Date of Birth");

	gotoxy(95,5);
	printf("Father Name");

	gotoxy(122,5);
	printf("Mother Name");
	int n=7;
    while(fscanf(fp,"%s %s %s %s %s %s %s",&voter.name,&voter.nid_no,&voter.sex,&voter.date_of_birth,&voter.father_name,&voter.mother_name,&voter.password)!=EOF)
       {
           gotoxy(3,n);
           printf("%lld",x);
           gotoxy(9,n);
           puts(voter.nid_no);
           gotoxy(31,n);
           puts(voter.name);
           gotoxy(61,n);
           puts(voter.sex);
           gotoxy(73,n);
           puts(voter.date_of_birth);
           gotoxy(95,n);
           puts(voter.father_name);
           gotoxy(122,n);
           puts(voter.mother_name);

           n=n+2;
           x++;
           test++;
       }

    fclose(fp);
    if (test==0)
        {   system("cls");
            printf("\nNO RECORDS!!\n");
        }

        label1:
        printf("\n\n\nEnter 1 to back : ");
        i=getch();
        switch(i)
        {
        case '1':
            {
                return;
                break;
            }
        default:
            {
                printf("\nInvalid!");
                goto label1;
            }
        }
}
void candidate_list()
{
    int i;
    candidate_print();
    label1:
    printf("\n\n\n\t\tEnter 1 to back : ");
    i=getch();
    switch(i)
    {
    case '1':
        {
            return;
            break;
        }
    default:
        {
            printf("\nInvalid!");
            goto label1;
        }
    }
}//end of candidate_list.

void candidate_print()
{
    int x=1;
    fpc=fopen("Candidate","r");
    int test=0;
    system("cls");
    gotoxy(15,5);
    printf("No.");
    gotoxy(21,5);
	printf("Name");

	gotoxy(41,5);
	printf("Symbol");

	int n=7;
    while(fscanf(fpc,"%s %s %s",&candidate.nid_no,&candidate.name,&candidate.symbol)!=EOF)
    {
        gotoxy(15,n);
        printf("%d",x);
        gotoxy(21,n);
        puts(candidate.name);
        gotoxy(41,n);
        puts(candidate.symbol);
        n=n+2;
        x++;
        test++;
    }

    fclose(fpc);
    if(test==0)
    {
        system("cls");
        welcome();
        gotoxy(25,25);
        printf("::No Records Available::");

    }
}

void info_print(char nid[20])
{
    int test=0;
    if((fp=fopen("Voter","rb+"))==NULL)
        {
            system("cls");
            printf("\n Cannot open the record file!!");
            getch();
            exit(1);
        }
        system("cls");
        welcome();
        gotoxy(15,14);
        printf("Your Information:");
        gotoxy(15,16);
        printf("Name:");

        gotoxy(15,18);
        printf("NID No:");

        gotoxy(15,20);
        printf("Sex:");

        gotoxy(15,22);
        printf("Date of Birth:");

        gotoxy(15,24);
        printf("Father Name:");

        gotoxy(15,26);
        printf("Mother Name:");

        while(fscanf(fp,"%s %s %s %s %s %s %s",&voter.name,&voter.nid_no,&voter.sex,&voter.date_of_birth,&voter.father_name,&voter.mother_name,&voter.password)!=EOF)
        {
            if(strcmp(voter.nid_no,nid)==0)
            {
                gotoxy(30,16);
                puts(voter.name);
                gotoxy(30,18);
                puts(voter.nid_no);
                gotoxy(30,20);
                puts(voter.sex);
                gotoxy(30,22);
                puts(voter.date_of_birth);
                gotoxy(30,24);
                puts(voter.father_name);
                gotoxy(30,26);
                puts(voter.mother_name);


                test++;
            }
        }
        if(test==0)
        {
            system("cls");
            welcome();
            gotoxy(25,25);
            printf("::No Records Available::");
        }
        fclose(fp);
}
void voter_info()
{
    char n;
    char Name[30];
    int test=0,x=1;

    lebel1:
	system("cls");
	welcome();

	lebel2:
	gotoxy(22,15);
	printf("Enter the corresponding no");
	gotoxy(22,19);
	printf("1.Search by 'NAME'");
	gotoxy(22,21);
	printf("2.Search by 'NID NO.'");
	gotoxy(22,23);
	printf("3.Return to main menu");
	gotoxy(22,25);
	n=getch();
	switch(n)
	{
    case '1':
        {
            system("cls");
            welcome();
            gotoxy(15,15);

            printf("Enter the Name of Voter: ");
            fflush(stdin);
            gets(Name);
            puts(Name);
            strupr(Name);
            if((fp=fopen("Voter","rb+"))==NULL)
            {
                system("cls");
                printf("\n Cannot open the record file!!");
                getch();
                exit(1);
            }
            system("cls");
            gotoxy(3,5);
            printf("No.");
            gotoxy(9,5);
            printf("NID No");

            gotoxy(31,5);
            printf("Name");

            gotoxy(61,5);
            printf("Sex");

            gotoxy(73,5);
            printf("Date of Birth");

            gotoxy(95,5);
            printf("Father Name");

            gotoxy(122,5);
            printf("Mother Name");
            int n=7;
            while(fscanf(fp,"%s %s %s %s %s %s %s",&voter.name,&voter.nid_no,&voter.sex,&voter.date_of_birth,&voter.father_name,&voter.mother_name,&voter.password)!=EOF)
            {
                if(strcmp(voter.name,Name)==0)
                {
                    gotoxy(3,n);
                    printf("%d",x);
                    gotoxy(9,n);
                    puts(voter.nid_no);
                    gotoxy(31,n);
                    puts(voter.name);
                    gotoxy(61,n);
                    puts(voter.sex);
                    gotoxy(73,n);
                    puts(voter.date_of_birth);
                    gotoxy(95,n);
                    puts(voter.father_name);
                    gotoxy(122,n);
                    puts(voter.mother_name);

                    n=n+2;
                    x++;
                    test++;
                }
            }
            if(test==0)
            {
                system("cls");
                welcome();
                gotoxy(25,25);
                printf("::No Records Available::");

            }
            fclose(fp);
            label3:
            printf("\n\n\n\t\tEnter 1 to back : ");
            char i=getch();
            switch(i)
            {
            case '1':
                {
                    return;
                    break;
                }
            default:
                {
                    printf("\nInvalid!");
                    goto label3;
                }
        }
            break;
        }
    case '2':
        {
            system("cls");
            welcome();
            gotoxy(15,15);
            char nidno[20];
            printf("Enter the NID No. of Voter: ");
            fflush(stdin);
            gets(nidno);
            puts(nidno);
            info_print(nidno);
            label4:
            printf("\n\n\n\tEnter 1 to back : ");
            char i=getch();
            switch(i)
            {
            case '1':
                {
                    return;
                    break;
                }
            default:
                {
                    printf("\nInvalid!");
                    goto label4;
                }
        }
            break;
        }
    case '3':
        {
           return;
        }

    default:
        {
            system("cls");
            welcome();
            gotoxy(22,11);
            printf("Wrong choice");
            gotoxy(22,13);
            printf("Retype choice");
            goto lebel2;
        }
	}
	 goto lebel1;
}//end of voter_info.

void voting()
{
    char n,nid[20];
    int m =0;
	lebel1:
	system("cls");
	welcome();
	gotoxy(22,15);
	printf("Enter your NID No : ");
	fflush(stdin);
	gets(nid);
	m=cheaching(nid);
	if(m==1)
    {
        gotoxy(22,18);
        printf("You already voted.\n");
        gotoxy(22,20);
        printf("Enter '1' to try again : ");
        char i=getch();
        if(i=='1')
        {
            goto lebel1;
        }
        else
            return;
    }
    else
    {
        char pass[20];
        info_print(nid);
        gotoxy(15,28);
        printf("Enter your password for voting: ");

        fflush(stdin);
        gets(pass);
        int test=0;
        if((fp=fopen("Voter","rb+"))==NULL)
        {
            system("cls");
            printf("\n Cannot open the record file!!");
            getch();
            exit(1);
        }

        while(fscanf(fp,"%s %s %s %s %s %s %s",&voter.name,&voter.nid_no,&voter.sex,&voter.date_of_birth,&voter.father_name,&voter.mother_name,&voter.password)!=EOF)
        {
            if(strcmp(voter.nid_no,nid)==0)
            {
               if(strcmp(voter.password,pass)==0)
               {
                   voting_menu(voter.nid_no);
               }
               else
               {
                   gotoxy(30,31);
                   printf("!!Wrong Password!!");
               }
            }
        }
        fclose(fp);
        getch();
    }
}

void voting_menu(char nid[20])
{
    system("cls");
	welcome();
    candidate_print();
    label4:
    printf("\n\n\n\tEnter your vote : ");
    int i;
    scanf("%d",&i);
    switch(i)
    {
    case 1:
        {
            vote[1]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 2:
        {
            vote[2]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 3:
        {
            vote[3]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 4:
        {
            vote[4]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 5:
        {
            vote[5]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 6:
        {
            vote[6]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 7:
        {
            vote[7]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 8:
        {
            vote[8]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 9:
        {
            vote[9]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    case 10:
        {
            vote[10]++;
            total_vote++;
            Insert(nid);
            printf("\n\tYour vote is complete successfully (: ");
            break;
        }
    default:
        {
            printf("\n\n\tWrong choice");
            printf("\n\n\tRetype choice");
            goto label4;
        }
    }
}
void Insert(char nid[20])
{
    struct voted_list *p=NULL;
    struct voted_list *temp=(struct voted_list*)malloc(sizeof(struct voted_list));
    strcpy(temp->nid_no,nid);
    temp->next=NULL;
    if(voted==NULL)
    {
        voted=temp;
    }
    else
    {
        p=voted;
        while(p->next!=NULL)
            p=p->next;
        p->next=temp;
    }
}
int cheaching(char nid[20])
{
    struct voted_list *temp = voted;
    while(temp!=NULL)
    {
        if(strcmp((temp->nid_no),nid)==0)
        {
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

//MYSHA
void result()
{
    candedates();
    voter_count();
    system("cls");
    welcome();
    gotoxy(20,10);
    printf("Total Voter : %lld",total_voter);
    gotoxy(45,10);
    printf("Total Vote : %lld",total_vote);
    gotoxy(30,13);
    printf("Present winner : ");
    gotoxy(47,13);
    puts(can->name);
    gotoxy(15,16);
    printf("No.");
    gotoxy(21,16);
	printf("Name");
	gotoxy(41,16);
	printf("Symbol");
	gotoxy(61,16);
	printf("Vote");
	int x=1,n=18;
    struct candidate_info *temp = can;
    while(temp!=NULL)
    {
        gotoxy(15,n);
        printf("%d",x);
        gotoxy(21,n);
        puts(temp->name);
        gotoxy(41,n);
        puts(temp->symbol);
        gotoxy(61,n);
        printf("%lld",temp->VOTE);
        temp=temp->next;
        x++;
        n+=2;
    }
    gotoxy(30,n);
    getch();
}

void candedates()
{
    can=NULL;
    fpc=fopen("Candidate","r");
    int test=0;
    long long int i=1;
    while(fscanf(fpc,"%s %s %s",&candidate.nid_no,&candidate.name,&candidate.symbol)!=EOF)
    {
        struct candidate_info *temp=(struct candidate_info*)malloc(sizeof(struct candidate_info));
        strcpy(temp->name,candidate.name);
        strcpy(temp->symbol,candidate.symbol);
        strcpy(temp->nid_no,candidate.nid_no);
        temp->VOTE= vote[i];
        temp->next=NULL;
        if(can==NULL)
        can=temp;
        else
        {
            struct candidate_info *temp1=can;
            while(temp1->next!=NULL)
                temp1=temp1->next;
            temp1->next=temp;
        }
        i++;
    }
    bubbleSort();
}

void bubbleSort()
{
    int swapped, i;
    struct candidate_info *ptr1;
    struct candidate_info *lptr = NULL;

    if (can == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = can;

        while (ptr1->next != lptr)
        {
            if (ptr1->VOTE < ptr1->next->VOTE)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}

void swap(struct candidate_info *a, struct candidate_info *b)
{
    long long int temp = a->VOTE;
    a->VOTE = b->VOTE;
    b->VOTE = temp;

    char temp1[30];
    strcpy(temp1,a->name);
    strcpy(a->name,b->name);
    strcpy(b->name,temp1);

    char temp2[20];
    strcpy(temp2,a->nid_no);
    strcpy(a->nid_no,b->nid_no);
    strcpy(b->nid_no,temp2);

    char temp3[20];
    strcpy(temp3,a->symbol);
    strcpy(a->symbol,b->symbol);
    strcpy(b->symbol,temp3);
}

void voter_count()
{
    total_voter=0;
    fp=fopen("Voter","r");
    while(fscanf(fp,"%s %s %s %s %s %s %s",&voter.name,&voter.nid_no,&voter.sex,&voter.date_of_birth,&voter.father_name,&voter.mother_name,&voter.password)!=EOF)
    {
        total_voter++;
    }

}
void explor()
{
	char n;
	label3:
	system("cls");
	welcome();
	label4:
	gotoxy(22,15);
	printf("Enter the corresponding no");
	gotoxy(22,19);
	printf("1. Voter Information");
	gotoxy(22,21);
	printf("2. Voter List");
	gotoxy(22,23);
	printf("3. Candidate List");
	gotoxy(22,25);
	printf("4. Return to main menu");
	gotoxy(22,27);
	fflush(stdin);
	n=getch();
	switch(n)
	{

        case '1':
            {
                voter_info();
                break;
            }
        case '2':
            {
                voter_list();
                break;
            }
        case '3':
            {
                candidate_list();
                break;
            }
        case '4':
            {
                return;
            }

		default:
            {
                system("cls");
				welcome();
				gotoxy(22,11);
				printf("Wrong choice");
				gotoxy(22,13);
                printf("Retype choice");
				goto label4;
            }
	}
	goto label3;
}


void security_cheack()
{
    char pass[10],password[15]="unbeatable";
    int i=0;
    system("cls");
	welcome();
	label1:
    gotoxy(22,11);
    printf("Enter the password to login: ");
    gotoxy(51,11);
    scanf("%s",pass);
	if (strcmp(pass,password)==0)
        {
            gotoxy(22,14);
            printf("Password Match!");
            gotoxy(22,15);
            printf("LODING");
            for(i=0;i<=6;i++)
            {
                delay(100);
                printf(".");
            }
            system("cls");
            welcome();
            admin();
        }
    else
        {
            printf("\n\nWrong password!!\a\a\a");
            printf("\nEnter 1 to try again and 0 to exit:");
            scanf("%d",&i);
            if (i==1)
                {
                    system("cls");
                    security_cheack();
                }

            else if (i==0)
                {
                  return;
                }
            else
                {
                    printf("\nInvalid!");
                    delay(100);
                    system("cls");
                    welcome();
                    goto label1;
                }
        }
}
int main()
{
    int i;
    char n;
    system("cls");
    fflush(stdin);
	welcome();
	label1:

    gotoxy(22,15);
	printf("Enter the corresponding no");

	gotoxy(22,19);
	printf("1. Admin");
	gotoxy(22,21);
	printf("2. Explore");
	gotoxy(22,23);
	printf("3. Voting");
	gotoxy(22,25);
	printf("4. Result");
	gotoxy(22,27);
	printf("5. Quit");

	gotoxy(22,29);
	fflush(stdin);
	gotoxy(22,29);
	n=getch();
	switch(n)
	{

    case '1':
        {
            security_cheack();
            break;
        }

    case '2':
        {
           explor();
           break;
        }

   case '3':
        {
           voting();
           break;
        }

   case '4':
        {
            result();
            break;
        }

    case '5':
        {
            system("cls");
            welcome();
            gotoxy(30,24);
            printf("THANK U");
            gotoxy(30,26);
            printf("BYE");
            for(i=0;i<=6;i++)
            {
                delay(100);
                printf(".");
            }
            printf("\n");
            getch();
            exit(1);
            break;
        }

    default:
        {
            system("cls");
            welcome();
            gotoxy(22,11);
            printf("Wrong choice\a\a\a");
            gotoxy(22,13);
            printf("Retype choice");
            goto label1;
        }

	}
	system("cls");
	welcome();
	goto label1;
	return 0;
}

