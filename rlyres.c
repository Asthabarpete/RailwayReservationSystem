#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include "conio2.h"
#include "rlyres.h"
int enterchoice()//to display all item in our program
{

    int choice,i;
    textcolor(GREEN);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    textcolor(BLUE);
    printf("\t\t********************************************************\n");
    textcolor(GREEN);
    printf("\nSelect an option");
    printf("\n1-View Trains");
    printf("\n2-Book Ticket");
    printf("\n3-View Ticket");
    printf("\n4-Search Ticket No");
    printf("\n5-View All Bookings");
    printf("\n6-View Train Bookings");
    printf("\n7-Cancel Ticket");
    printf("\n8-Cancel Train");
    printf("\n9-Quit");
    printf("\n\nEnter choice:");
    scanf("%d",&choice);
    textcolor(YELLOW);
    return choice;

}
void add_trains()//adding train in file
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
    FILE *fp=fopen("E:\\project of c\\alltrains.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("E:\\project of c\\alltrains.dat","wb");//writting train in file if no present in file
        fwrite(alltrains,4*sizeof(Train),1,fp);
        gotoxy(1,25);
        printf("File created and saved!\n\n");

    }
    else
        {
          gotoxy(1,25);
          printf("File already present\n\n");
        }
    fclose(fp);

}
void view_trains()//display train list present in file
{
    clrscr();
    int i;
    textcolor(YELLOW);

    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
     for(i=1;i<=80;i++)
        printf("-");
    FILE *fp=fopen("E:\\project of c\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);

    }
    printf("\n\n\n\n");
    printf("press any key to continue..........");
    fclose(fp);
}
int check_train_no(char *trainno)//checking of train number present in file or not
{
    FILE *fp=fopen("E:\\project of c\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          if(strcmp(tr.train_no,trainno)==0)
          {
                  fclose(fp);
                  return 1;
          }

    }
fclose(fp);
return 0;
}
int check_mob_no(char* mobileno)//checking valid mobile number
{
    if(strlen(mobileno)!=10)
        return 0;
    while(*mobileno!='\0')
    {
        if(isdigit(*mobileno)==0)
            return 0;
        mobileno++;
    }
    return 1;
}

Passenger* get_passenger_details()//TAKING DETAIL OF PASSENGER
{
    clrscr();
    gotoxy(55,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter passenger name:");
    static Passenger psn;//static because it must be present at the of program and we to pass its address
    fflush(stdin);//buffer cline
    fgets(psn.p_name,20,stdin);//taking input
    char *pos;
    pos=strchr(psn.p_name,'\n');//to store null and replace \n at the eng of input
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)//to quit the funtion
    {
      textcolor(LIGHTRED);
      gotoxy(1,25);
      printf("Reservation Cancelled!press any key to continue.....");
      getch();
      textcolor(YELLOW);
      return NULL;
    }
    int valid;
    printf("Enter gender(M/F):");
    do
    {
      valid=1;
      fflush(stdin);
      scanf("%c",&psn.gender);
      if(psn.gender=='0')
       {
         textcolor(LIGHTRED);
         gotoxy(1,25);
         printf("\t\t\t\t\t\t\t");//it clear the error msg
         gotoxy(1,25);
         printf("Reservation Cancelled!press any key to continue.....");
         getch();
         textcolor(YELLOW);
         return NULL;
       }
      if(psn.gender!='M' && psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Gender should be M or F (in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf("\t\t\t\t\t\t\t");//clear the entry pass by user which is wrong and take another entry
            gotoxy(19,2);
            textcolor(YELLOW);
        }
     }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,3);
    printf("Enter train number:");
    do
      {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!press any key to continue.....");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
        valid=check_train_no(psn.train_no);
        if(valid==0)
          {
            textcolor(LIGHTRED);
            gotoxy(1,25);

            printf("Error! Invalid Train No");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t\t");
            gotoxy(20,3);
            textcolor(YELLOW);
          }
        }while(valid==0);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,4);
        printf("Enter travelling class(First AC-F,Second AC-S):");
        do
         {
           valid=1;
           fflush(stdin);
           scanf("%c",&psn.p_class);
           if(psn.p_class=='0')
            {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("\t\t\t\t\t\t\t");
              gotoxy(1,25);
              printf("Reservation Cancelled!press any key to continue.....");
              getch();
              textcolor(YELLOW);
              return NULL;
            }
            if(psn.p_class!='F' && psn.p_class!='S')
            {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error! Travelling class should be F or S (in uppercase)");
              valid=0;
              getch();
              gotoxy(48,4);
              printf("\t\t\t\t\t\t\t");
              gotoxy(48,4);
              textcolor(YELLOW);
            }
        }while(valid==0);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,5);
        printf("Enter address:");
        fflush(stdin);
        fgets(psn.address,30,stdin);
        pos=strchr(psn.address,'\n');
        *pos='\0';
        if(strcmp(psn.address,"0")==0)
        {
         textcolor(LIGHTRED);
         gotoxy(1,25);
         printf("Reservation Cancelled!press any key to continue.....");
         getch();
         textcolor(YELLOW);
         return NULL;
       }
       gotoxy(1,6);
       printf("Enter age:");
       do
       {
           valid=1;
           fflush(stdin);
           scanf("%d",&psn.age);
           if(psn.age==0)
           {
               textcolor(LIGHTRED);
               gotoxy(1,25);
               printf("Reservation Cancelled!press any key to continue.....");
               getch();
               textcolor(YELLOW);
               return NULL;
           }
           if(psn.age<0 || psn.age>150)
           {
             textcolor(LIGHTRED);
             gotoxy(1,25);
             printf("Error! Age should be positive and valid");
             valid=0;
             getch();
             gotoxy(11,6);
             printf("\t\t\t\t\t\t\t");
             gotoxy(11,6);
             textcolor(YELLOW);
           }
       }while(valid==0);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t");
        gotoxy(1,7);
        printf("enter mobile number:");
        do
        {
            fflush(stdin);
            fgets(psn.mob_no,12,stdin);
            psn.mob_no[(strlen(psn.mob_no)-1)]='\0';
            if(strcmp(psn.mob_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!press any key to continue.....");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            valid=check_mob_no(psn.mob_no);
            if (valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error!Invalid mobile number");
                getch();
                gotoxy(21,7);
                printf("\t\t\t\t\t\t\t\t");
                gotoxy(21,7);
                textcolor(YELLOW);
            }

        }while(valid==0);

 return &psn;
}
int get_booked_ticket_count(char*train_no,char coach)//counting of ticket on particular train
{
  FILE *fp;
  fp=fopen("E:\\project of c\\allbookings.dat","rb");
  if (fp==NULL)
    return 0;
  Passenger pr;
  int count=0;
  while(fread(&pr,sizeof(pr),1,fp)==1)
  {
      if (strcmp(pr.train_no,train_no)==0 && pr.p_class==coach)
        ++count;
  }
  fclose(fp);
  return count;
}

int last_ticket_no()//finding last ticket number
{
  FILE *fp;
  fp=fopen("E:\\project of c\\allbookings.dat","rb");
  if (fp==NULL)
    return 0;
  Passenger pr;
  fseek(fp,-1L*sizeof(pr),SEEK_END);
  fread(&pr,sizeof(pr),1,fp);
  fclose(fp);
  return pr.ticketno;
}
int book_ticket(Passenger p)//booking ticket
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no %s in %c class!\n",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE * fp=fopen("E:\\project of c\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;

}
int accept_ticket_no()//accepting ticket number
{
    clrscr();

    int ticket_num,valid=0;
    printf("Enter ticket number:");
    do
    {
        gotoxy(55,1);
        textcolor(LIGHTGREEN);
        printf("Press 0 to exit");
        gotoxy(1,1);
        textcolor(YELLOW);
        valid=1;
        fflush(stdin);
        gotoxy(21,1);
        scanf("%d",&ticket_num);
        if (ticket_num==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling input!press any key to continue.....");
               // getch();
                //clrscr();
                textcolor(YELLOW);
                return 0;
            }
        if (ticket_num<0)
        {
            valid=0;
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Ticket number should  be positive");
            getch();
            gotoxy(21,1);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(21,1);

            textcolor(YELLOW);
        }

    }while(valid==0);
    return ticket_num;
}
void view_ticket(int ticket_no)//printing info of particular ticket number
{
    FILE *fp;
    int valid=0;
    Passenger pr;
    fp=fopen("E:\\project of c\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTCYAN);
        printf("\nNo booking done yet");
        return;
    }
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
          if(pr.ticketno==ticket_no)
          {
            textcolor(LIGHTMAGENTA);
            valid=1;
            printf("\nTicket no.:%d\nName:%s\nGender:%c\nTrain no.:%s\nClass:%c\nAddress:%s\nAge:%d\nMobile no.:%s",pr.ticketno,pr.p_name,pr.gender,
                   pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no);
            textcolor(WHITE);
            printf("\n\nEnter any key to continue....");
            fclose(fp);
            break;
          }
    }
    if(!valid)
    {
        fclose(fp);
        textcolor(LIGHTGRAY);
        printf("\nNo Detail of the Ticket Found! press any Key to move back.......");
    }


}
char* accept_mob_no()//taking mobile number
{
    clrscr();

    static char mob_no[12];
    int valid;
    printf("Enter mobile number:");
    do
    {
        gotoxy(55,1);
        textcolor(LIGHTGREEN);
        printf("Press 0 to exit");
        gotoxy(1,1);
        textcolor(YELLOW);
        fflush(stdin);
        gotoxy(21,1);
        fgets(mob_no,12,stdin);
        mob_no[(strlen(mob_no)-1)]='\0';
        if(strcmp(mob_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling input!\npress any key to continue............");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
        valid=check_mob_no(mob_no);
        if (valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error!Invalid mobile number");
                getch();
                gotoxy(21,1);
                printf("\t\t\t\t\t\t\t\t");
                gotoxy(21,1);
                textcolor(YELLOW);
            }

    }while(valid==0);
clrscr();
return mob_no;
}
int* get_ticket_no(char* p_mob_no)//finding ticket number booked at particular number
{
    int count=0;
    Passenger pr;
    FILE *fp=fopen("E:\\project of c\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTCYAN);
        printf("\nNo booking done yet");
        return NULL;
    }
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
      {
          *(p+i)=pr.ticketno;
            i++;
      }
    }
*(p+i)=-1;
fclose(fp);
return p;
}
void view_all_tickets(char *pmob_no,int *pticket_no)//printing ticket number booked at particular number
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("------------------------------------------------------------------------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
textcolor(WHITE);
printf("\n\nPress any key to go back to the main screen..........");
textcolor(YELLOW);
getch();
free(pticket_no);
}
char* accept_train_no()
{
    clrscr();
    static char t_no[10];
    int valid;
    textcolor(YELLOW);
    printf("Enter Train number:");
    do
    {
        gotoxy(55,1);
        textcolor(LIGHTGREEN);
        printf("Press 0 to exit");
        gotoxy(1,1);
        textcolor(YELLOW);
        fflush(stdin);
        gotoxy(20,1);
        fgets(t_no,10,stdin);
        t_no[(strlen(t_no)-1)]='\0';
        if(strcmp(t_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling input!\n");
                textcolor(WHITE);
                printf("\npress any key to continue........");
                printf("\t\t\t\t\t\t\t");
                getch();
                textcolor(YELLOW);
                return NULL;
            }
            valid=check_train_no(t_no);
        if (valid==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Error!Invalid train number");
                getch();
                gotoxy(20,1);
                printf("\t\t\t\t\t\t\t\t");
                gotoxy(20,1);
                textcolor(YELLOW);
            }

    }while(valid==0);
return t_no;

}
void view_bookings(char* t_no)//PRINTING ALL BOOKED TICKET OF PARTICULAR TRAIN
{
    FILE *fp=fopen("E:\\project of c\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTCYAN);
        printf("\nNo booking done yet");
        return ;
    }
    Passenger pr;
    int found=0;
    textcolor(LIGHTBLUE);
    int row=6;
    gotoxy(26,2);
    printf("Booking in train number %s",t_no);
    printf("\n------------------------------------------------------------------------");
    textcolor(LIGHTMAGENTA);
    printf("\nTICKET NO.  TRAIN NO  CLASS   NAME\t   GENDER   AGE   MOBILE NO.");
    printf("\n----------------------------------------------------------------------------");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
          if(strcmp(pr.train_no,t_no)==0)
          {
            found=1;
            printf("\n%d\t     %s\t%c    %s",pr.ticketno,pr.train_no,pr.p_class,pr.p_name);
            gotoxy(46,row);
            printf("%c     %d     %s",pr.gender,pr.age,pr.mob_no);
            row++;
          }
    }
    if(!found)
    {
        clrscr();
        textcolor(LIGHTGREEN);
        printf("\nNo. Ticket Found of %s Train number",t_no);
    }
    printf("\n-------------------------------------------------------------------------------");
    fclose(fp);
    textcolor(WHITE);
    printf("\n\nEnter any key to continue....");
    getch();
}
int cancel_ticket(int ticket_no)
{
    FILE *fp1=fopen("E:\\project of c\\allbookings.dat","rb");
    if (fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo booking done yet");
        return -1;
    }
    FILE *fp2=fopen("E:\\project of c\\temp.dat","wb");
    Passenger pr;
    int found=0;
    int result;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("E:\\project of c\\temp.dat");
    }
    else
    {
        result=remove("E:\\project of c\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("E:\\project of c\\temp.dat","E:\\project of c\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}
int cancel_train(char *train_no)
{
  FILE *fp1=fopen("E:\\project of c\\allbookings.dat","rb");
    if (fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo booking done yet");
        return -1;
    }
    FILE *fp2=fopen("E:\\project of c\\temp1.dat","wb");
    Passenger pr;
    int found=0;
    int result;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("E:\\project of c\\temp1.dat");
    }
    else
    {
        result=remove("E:\\project of c\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("E:\\project of c\\temp1.dat","E:\\project of c\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}
void view_all_bookings()
{
  FILE *fp=fopen("E:\\project of c\\allbookings.dat","rb");
  if (fp==NULL)
    {
        textcolor(LIGHTCYAN);
        printf("\nNo booking done yet");
        return ;
    }
    Passenger pr;
    textcolor(GREEN);
    int row=6;
    gotoxy(26,2);
    printf("ALL BOOKING OF TRAINS");
    printf("\n________________________________________________________________________");
    textcolor(YELLOW);
    printf("\nTICKET NO.  TRAIN NO  CLASS   NAME\t   GENDER   AGE   MOBILE NO.");
    printf("\n_________________________________________________________________________");
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
            printf("\n%d\t     %s\t%c    %s",pr.ticketno,pr.train_no,pr.p_class,pr.p_name);
            gotoxy(46,row);
            printf("%c       %d     %s",pr.gender,pr.age,pr.mob_no);
            row++;

    }
    printf("\n___________________________________________________________________________");
    textcolor(WHITE);
    printf("\n\n\n press any key to go back to main screen..........");
    fclose(fp);
    return;
}







