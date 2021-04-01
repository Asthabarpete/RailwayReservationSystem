#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    int choice,ticket_no,result;
    Passenger *ptr;
    char *pmob_no;
    int *pticket_no;
    char *ptrain_no;

    add_trains();
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
            exit(0);
        switch(choice)
        {
            case 1:
                    view_trains();
                    getch();
                    clrscr();
                    break;
            case 2:
                    ptr=get_passenger_details();
                    clrscr();
                    if(ptr!=NULL)
                   {
                    ticket_no=book_ticket(*ptr);
                    if(ticket_no==-1)
                    {
                    textcolor(LIGHTRED);
                    printf("Booking Failed!");

                    }
                   else
                   {
                    textcolor(LIGHTGREEN);
                    printf("Ticket Successfully Booked\nYour ticket no is %d",ticket_no);
                   }
                   textcolor(LIGHTBLUE);
                  printf("\nPress any key to go back to the main screen.........");
                  getch();
                  clrscr();
                  }
                 break;


            case 3:
                    clrscr();
                    ticket_no= accept_ticket_no();
                    if(ticket_no!=0)
                    {
                        view_ticket(ticket_no);
                    }

                    getch();
                    clrscr();
                    break;
            case 4:
                    clrscr();
                    pmob_no=accept_mob_no();
                    if(pmob_no!=NULL)
                     {
                       pticket_no=get_ticket_no(pmob_no);
                       view_all_tickets(pmob_no,pticket_no);
                     }
                    clrscr();
                    break;
            case 5:
                    clrscr();
                    view_all_bookings();
                    getch();
                    clrscr();
                    break;
            case 6:
                    clrscr();
                    ptrain_no=accept_train_no();
                    clrscr();
                    if(ptrain_no!=NULL)
                      view_bookings(ptrain_no);
                    clrscr();
                    break;
            case 7:
                    clrscr();
                    ticket_no=accept_ticket_no();
                    clrscr();
                    if(ticket_no!=0)
                    {
                        result=cancel_ticket(ticket_no);
                        if(result==0)
                        {
                            textcolor(LIGHTRED);
                            printf("no Booking against %d Ticket number",ticket_no);
                        }
                        else if(result==1)
                        {
                            textcolor(LIGHTGREEN);
                            printf("Ticket number %d Successfully cancelled",ticket_no);
                        }
                        else if(result==2)
                        {
                            textcolor(RED);
                            printf("sorry! Error in cancellation  Try again... ");
                        }
                        textcolor(WHITE);
                        printf("\n\n press any key to go back to the main menu........");
                    }
                    getch();
                    clrscr();
                    break;
            case 8:
                    clrscr();
                    int password;
                    printf("enter password to cancel train:-");
                    scanf("%d",&password);
                    if(password==947997)
                {
                    ptrain_no=accept_train_no();
                    clrscr();
                    if(ptrain_no!=NULL)
                    {
                        result=cancel_train(ptrain_no);
                        if(result==0)
                        {
                            textcolor(LIGHTRED);
                            printf("no booking on  %s Train number present",ptrain_no);
                        }
                        else if(result==1)
                        {
                            textcolor(LIGHTGREEN);
                            printf("Train number %s Successfully cancelled",ptrain_no);
                        }
                        else if(result==2)
                        {
                            textcolor(RED);
                            printf("sorry! Error in cancellation  Try again... ");
                        }
                        textcolor(WHITE);
                        printf("\n\n press any key to go back to the main menu........");
                    }
                }
                else
                {
                    textcolor(RED);
                    printf("\n\n\nwrong passcode.........");
                    textcolor(YELLOW);
                }
                    getch();
                    clrscr();
                    break;
           default:
                  textcolor(LIGHTRED);
                  printf("\nWrong Choice! Try Again");
                  getch();
                  clrscr();
                  break;

        }
    }

    return 0;
}

