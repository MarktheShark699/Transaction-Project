#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define buffer 80

/* Author: Mark Corri
   Date: 4/25/2021
   Description: This project keeps tracks of day-to-day rental processes of tools to specific customers. It uses array of structure and is handled by pointers.
*/


struct Tool
{
    bool isAvailable;
    char toolID[6];//for up to 6 characters or letters
    char toolType[50];//up to 50 characters
    double fullDay;
    double halfDay;
}typedef Tool;

struct Customer
{
    char customerID[7];//up to 7 digits
    char firstName[26];//26 characters
    char lastName[26];//26 characters
    char phoneNum[11];//10 digits
    char email[100];//100 characters
}typedef Customer;

struct Transaction
{
    char customerID[7];
    char toolID[6];
    char rentalPer[1];
    float rentalFees;
}typedef Transaction;

//prototypes
int menuSelection();
int custMenu();
int transactionMenu(Tool* pst, Customer* pstr, Transaction* ptr, int stCount, int transCount, int toolCount);
void toolMenu();
void createCust(Customer* pstr, int current);
void dispCust(Customer* pstr, int current);
int searchCust(char* searchID, Customer* pstr, int current);
void toolArrays(Tool* pst);
void createTool(Tool* pst, int toolCount);
int searchTool(Tool* pst, char* psearchTool, int toolCount);
int searchToolID(Transaction* ptr, char* psearchToolID, int transCount);
void dispTool(Tool* pt, int toolCount);
void custIDTrans(Transaction* ptr, Customer* pstr, int transCount, int stCount);
void toolList(Tool* pst);
void displayTransaction(Transaction* ptr, int transCount);
void searchTrans(Transaction* ptr, Customer* pstr, Tool* pst, int custCount, int transCount, int toolCount);
bool validateToolID(char* pInput);
bool isDigit(const char c);
bool isChar(char c);
bool validatePhoneNumber(char* pInput);
bool validateCustID(char* pInput);
bool validateCustName(char* pInput);
bool validateToolType(char* pInput);
bool validateNum(char* pInput);


int main()
{
    int answer = 0;//Allows the user to choose to start program
    int reply = 0;//Variable that gets input from menu selections
    int location = -1;//helps for searching customer
    int toolLocation = -1; //helps for searching tools
    int toolCount = 0; // Keep track of tool current index
    int custCount = 0; // Keep track of customer current index
    int transCount = 0;// Keep track of customer current index


    char input[buffer] = {' '};
    char* pInput = NULL;
    Tool* pst = malloc(100 * sizeof(Tool));
    Customer* pstr = malloc(100 * sizeof(Customer));
    Transaction* ptr = malloc(100 * sizeof(Transaction));

//create do loop to decide whether to end the program or continue
    do{
       toolList(pst);
        while(answer != 4)
        {
            answer = menuSelection();
                switch(answer)
                {
                    case 1: printf("\n************CUSTOMER MENU************ \n");
                            printf("Enter 1 to Create a Customer \n");
                            printf("Enter 2 to Search a Customer \n");
                            printf("Enter 3 to go back to Main Menu \n");
                            printf("Enter Selection: ");
                            scanf("%d", &reply);
                            if(reply == 1){
                                createCust(pstr, custCount);
                                custCount++;
                            }else
                            if(reply == 2)
                            {
                            fflush(stdin);
                            printf("Enter Customer ID to search: ");
                            pInput = fgets(input, buffer, stdin);
                            strtok(pInput, "\n");
                            location = searchCust(pInput, pstr, custCount);
                            if(location < 0)
                            {
                                printf("Wrong ID, enter another....\n");
                            }else{
                                    dispCust(pstr, location);
                                    printf("click any button to continue.... \n");
                                    getch();
                                    break;
                                }//end if(location < 0)
                            }else
                            if(reply == 3)
                            {
                                printf("hit any key to continue...");
                                getch();
                                menuSelection();
                            }
                            break;
                    case 2: printf("\n************TOOL MENU************ \n");
                            printf("Enter 1 to Add a Tool \n");
                            printf("Enter 2 to Search for a Tool \n");
                            printf("Enter 3 to go back to Main Menu \n");
                            printf("Enter Selection: ");
                            scanf("%d", &reply);
                            if(reply == 1)
                            {
                                createTool(pst, toolCount);
                                toolCount++;
                            }else
                            if(reply == 2)
                            {
                            rewind(stdin);
                            printf("Enter Tool ID to search: ");
                            pInput = fgets(input, buffer, stdin);
                            strtok(pInput, "\n");
                            toolLocation = searchTool(pst, pInput, toolCount);
                            if(toolLocation < 0)
                            {
                                printf("Wrong ID, enter another....\n");
                            }else{
                                    dispTool(pst, toolLocation);
                                    printf("click any button to continue.... \n");
                                    getch();
                                    break;
                                }//end if(toolLocation < 0)
                            }else
                            if(reply == 3)
                            {
                                printf("hit any key to continue...");
                                getch();
                                menuSelection();
                            }
                            break;
                    case 3: printf("\n************TRANSACTION MENU************ \n");
                            printf("Enter 1 to Start a Transaction \n");
                            printf("Enter 2 to Search for a Transaction \n");
                            printf("Enter 3 to Display all Transactions \n");
                            printf("Enter 4 to go back to Main Menu \n");
                            printf("Enter Selection: ");
                            scanf("%d", &reply);
                            if(reply == 1)
                            {
                              transactionMenu(pst, pstr, ptr, custCount, transCount, toolCount);
                              transCount++;
                            }
                            if(reply == 2)
                            {
                                searchTrans(ptr, pstr, pst, custCount, transCount, toolCount);
                            }
                            if(reply == 3)
                            {
                                for(int i = 0; i < transCount; i++)
                                {
                                    displayTransaction(ptr, i);
                                }

                            }
                            break;
                    case 4: printf("hit any key to continue...");
                                getch();
                                menuSelection();
                            break;

                }//end switch
        }//end while
            printf("Enter 0 to quit program, 1 to continue program.\n");
        scanf("%d", &answer);
        system("cls");
       }while (answer == 1);
            printf("********************** \n");
            printf("Thank you. Goodbye. ");

    return 0;
}//end main

int menuSelection()
{
    int answer = 0;
    printf("\n************MENU************ \n");
    printf("Enter 1 for Customer Menu \n");
    printf("Enter 2 for Tool Menu \n");
    printf("Enter 3 for Transaction Menu \n");
    printf("Enter 4 to Quit Program \n");
    printf("Enter Selection: ");
    scanf("%d", &answer);
    return answer;
}//end menu selection


void createCust(Customer* pstr, int current)
{
    //variable declerations
    char input[buffer] = {' '};
    char* pInput = NULL;
    bool goodPhoneNum = false;
    bool goodCustID = false;
    bool goodFirstName = false;
    bool goodLastName = false;
    //bool goodEmail = false;
    //input of all customer info below
    fflush(stdin);
    printf("Enter Customer ID: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    strcpy((pstr + current)->customerID, pInput);
    goodCustID = validateCustID(pInput);
    //validation
    while(!goodCustID)
    {
        printf("Invalid!..re-enter proper Customer ID:\n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodCustID = validateCustID(pInput);
    }
    printf("Enter Customer First Name: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    strcpy((pstr + current)->firstName, pInput);
    goodFirstName = validateCustName(pInput);
    //validation
    while(!goodFirstName)
    {
        printf("Invalid!..re-enter First Name:\n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodFirstName = validateCustName(pInput);
    }
    printf("Enter Customer Last Name: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    strcpy((pstr + current)->lastName, pInput);
    goodLastName = validateCustName(pInput);
    //validation
    while(!goodLastName)
    {
        printf("Invalid!..re-enter Last Name:\n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodLastName = validateCustName(pInput);
    }
    printf("Enter customer phone number: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    strcpy((pstr + current)->phoneNum, pInput);
    goodPhoneNum = validatePhoneNumber(pInput);
    //validation
    while(!goodPhoneNum)
    {
        printf("Invalid!..re-enter Phone Number\n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodPhoneNum = validatePhoneNumber(pInput);
    }//end while
    printf("Enter customer Email: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    strcpy((pstr + current)->email, pInput);
    /*goodEmail = validateEmailID(pInput);
    while(!goodEmail)
    {
        printf("Invalid!..re-enter Email Address: \n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodEmail = validateEmailID(pInput);
    }*/
}//end createCust
//====================================================================================
void createTool(Tool* pst, int toolCount)
{
    //declerations
    char input[buffer] = {' '};
    char* pInput = NULL;
    bool goodToolID = false;
    bool goodToolType = false;
    bool goodFullDay = false;
    bool goodHalfDay = false;
    //input of tool info
    fflush(stdin);
    printf("Enter Tool ID: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    strcpy((pst + toolCount)->toolID, pInput);
    goodToolID = validateToolID(pInput);
    //validation
    while(!goodToolID)
    {
        printf("Invalid!..re-enter Tool ID:\n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodToolID = validateToolID(pInput);
    }
    strcpy((pst + toolCount)->toolID, pInput);
    printf("Enter Tool Type: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    strcpy((pst + toolCount)->toolType, pInput);
    goodToolType = validateToolType(pInput);
    //validation
    while(!goodToolType)
    {
        printf("Invalid!..re-enter Tool Type:\n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodToolType = validateToolType(pInput);
    }
    strcpy((pst + toolCount)->toolType, pInput);
    printf("Enter tools First full day number: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    goodFullDay = validateNum(pInput);
    //validation
    while(!goodFullDay)
    {
        printf("Invalid!...re-enter Full Day: \n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodFullDay = validateNum(pInput);
    }
    (pst + toolCount)->fullDay = atof(pInput);
    printf("Enter tool half day: ");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
    goodHalfDay = validateNum(pInput);
    //validation
    while(!goodHalfDay)
    {
        printf("Invalid!..re-enter Half Day: \n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        goodHalfDay = validateNum(pInput);
    }
    (pst + toolCount)->halfDay = atof(pInput);
    (pst + toolCount)->isAvailable = true;
     fflush(stdin);
}
//=======================================================================================
bool validateCustID(char* pInput)
{
    if(strlen(pInput) != 6)
    {
        return false;
    } // end if
    for(int i = 0; i < strlen(pInput); i++)
    {
        if(!isdigit(*(pInput + i)))
        {
            return 0;
        }// end if
    }//end for i
    return 1;
} // end validateCustID
//=================================================================================
bool validateCustName(char *pInput)
{
    for(int i = 0; i < strlen(pInput); i++)
    {
        //only accepts alphabet/char
         if(!isalpha(pInput[i]))
         {
              return 0;
         }//end if
    }//end for
        return 1;
}//end validateCustName
//==============================================================================
bool validatePhoneNumber(char* pInput)
{
    if(strlen(pInput) != 10)
    {
        return false;
    } // end if
     for (int i = 0; i < strlen(pInput); i++)
    {
        if (!isdigit(*(pInput + i)))
        {
            return 0;
        }// end if
    }// end for
    return 1;
}// end validatePhoneNumber
//=======================================================================
bool validateToolID(char* pInput)
{
    if(strlen(pInput) == 5)
    {
        return true;
    } // end if
    else{
        return false;
    }//end else
    return true;
}//end validateToolID
//=====================================================================================
bool validateToolType(char* pInput)
{
    for (int i = 0; i < strlen(pInput); i++)
    {
        if (!isalpha(*(pInput + i)) && !isspace(*(pInput + i)))
        {
            return false;
        }// end if
    }// end for
    return true;
}// end validateToolType
//============================================================================
bool validateNum(char* pInput)
{
    // Validate FirstName
   for (int i = 0; i < strlen(pInput); i++)
    {
        if (!isdigit(*(pInput + i)))
        {
            return false;
        }// end if
    }// end for
    return true;
}// end validateNum
//================================================================================
//bool validateEmailID
//================================================================================
void toolList(Tool* pst)
{
    strcpy((pst + 0)->toolID, "CS012\n");
    strcpy((pst + 0)->toolType, "chain saw\n");
    (pst + 0)->fullDay = 56.00;
    (pst + 0)->halfDay = 45.00;
    (pst + 0)->isAvailable = true;
    //------------------------------------
    strcpy((pst + 1)->toolID, "CC007\n");
    strcpy((pst + 1)->toolType, "concrete cutter\n");
    (pst + 1)->fullDay = 125.00;
    (pst + 1)->halfDay = 95.00;
    (pst + 1)->isAvailable = true;
    //------------------------------------
    strcpy((pst + 2)->toolID, "AC004\n");
    strcpy((pst + 2)->toolType, "air compressor\n");
    (pst + 2)->fullDay = 39.00;
    (pst + 2)->halfDay = 29.00;
    (pst + 2)->isAvailable = true;
    //------------------------------------
    strcpy((pst + 3)->toolID, "FS008\n");
    strcpy((pst + 3)->toolType, "floor sander\n");
    (pst + 3)->fullDay = 75.00;
    (pst + 3)->halfDay = 55.00;
    (pst + 3)->isAvailable = true;
    //------------------------------------
    strcpy((pst + 4)->toolID, "CM002\n");
    strcpy((pst + 4)->toolType, "cement mixer\n");
    (pst + 4)->fullDay = 45.00;
    (pst + 4)->halfDay = 39.00;
    (pst + 4)->isAvailable = true;
}//end populateDest

void dispCust(Customer* pstr, int current)
{
       printf("Customer ID       : %s\n"
            "        First Name  : %s\n"
            "        Last Name   : %s\n"
            "        Phone Number: %s\n"
            "        Email       : %s\n", (pstr + current)->customerID, (pstr + current)->firstName, (pstr + current)->lastName, (pstr + current)->phoneNum, (pstr + current)->email);
    printf("Any key to continue...\n"); getch();
    system("cls");
}//end dispCust
//==========================================================================================================
void dispTool(Tool* pst, int toolCount)
{
   printf("         Tool ID    : %s\n"
            "        Tool Type  : %s\n"
            "        Full Day   : %2.2f\n"
            "        Half Day   : %2.2f\n", (pst + toolCount)->toolID, (pst + toolCount)->toolType, (pst + toolCount)->fullDay, (pst + toolCount)->halfDay);
    printf("Any key to continue...\n"); getch();
    system("cls");
}// End DisplayTool
//=========================================================================================================
void displayTransaction(Transaction* ptr, int transCount)
{
    printf("Customer ID  :%s\n"
           "Tool ID      :%s\n"
           "Rental Period:%s\n"
           "Rental Fees  :%2.2f\n", (ptr + transCount)->customerID, (ptr + transCount)->toolID, (ptr + transCount)->rentalPer, (ptr + transCount)->rentalFees);
           printf("Any key to continue...\n"); getch();
        system("cls");
}//end displayTransaction
//===========================================================================================================
int searchTool(Tool* pst, char* psearchTool, int toolCount)
{
    for(int i = 0; i < toolCount; i++)
    {
            if(stricmp(psearchTool, (pst + i)->toolID) == 0)
            {
                return i;
            }//end if
    }//end for
    return -1;
}// End SearchTool
//===========================================================================================================
int searchCust(char* searchID, Customer* pstr, int custCount)
{
      for(int i = 0; i < custCount; i++)
    {
        if(strcmp(searchID, (pstr + i)->customerID) == 0)
        return i;
    }//end for
    return -1;
}//end searchCust
//============================================================================================================
void searchTrans(Transaction* ptr, Customer* pstr, Tool* pst, int custCount, int transCount, int toolCount)
{
    //declerations
    char input[buffer] = {' '};
    char* pInput = NULL;
    int location = -1;
    int answer = 0;
    fflush(stdin);
    //output that allows user to search for customer ID or Tool ID
    printf("Enter 0 to search for Customer ID....1 to search for Tool ID...\n");
    scanf("%d", &answer);
    if(answer == 0)
    {
        rewind(stdin);
        //gets customer ID
        printf("Enter customer ID...\n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        for(int i = 0; i < transCount; i++)
        {
            location = searchCust(pInput, pstr, custCount);

            if(location < 0)
            {
                printf("Customer not found...press any key to continue \n"); getch();
            } // end if
            else
            {
                displayTransaction(ptr, i);
            }//end else
        }//end for
    }//end if answer
    if(answer == 1)
    {
        rewind(stdin);
        printf("Enter Tool ID: \n");
        pInput = fgets(input, buffer, stdin);
        strtok(pInput, "\n");
        for(int i = 0; i < transCount; i++)
        {
            location = searchTool(pst, pInput, toolCount);
            if(location < 0)
            {
                printf("Tool ID not found...press any key to continue...\n"); getch();
            }//end if
            else
            {
                displayTransaction(ptr, i);
            }//end else
        }//end for
    }//end if answer
    //validates if user inputs digit other than 0 or 1
    while(answer != 0 && answer != 1)
    {
        printf("INVALID ANSWER - Please re-enter 1 for yes or 0 for no:  \n");
        scanf("%d", &answer);
    } // end while loop
}//end searchTrans
int transactionMenu(Tool* pst, Customer* pstr, Transaction* ptr, int stCount, int transCount, int toolCount)
{
    //declerations
    char input[buffer] = {' '};
    char* pInput = NULL;
    int answer = 0;
    int location = -1;//variable to start searching for customerID
    fflush(stdin);
    //gets customer ID
    printf("\nEnter Customer ID: \n");
    pInput = fgets(input, buffer, stdin);
    strtok(pInput, "\n");
     location = searchCust(pInput, pstr, stCount);
        if(location < 0)
            {
                printf("ID not found!...Please create a customer ID to continue...\n");
            }else{
                    strcpy((ptr + transCount)->customerID, pInput);
                    rewind(stdin);
                    for(int i = 0; i < toolCount; i++)
                     {
                        dispTool(pst, i);
                     }//end for
                     printf("\nEnter Tool ID: \n");
                     pInput = fgets(input, buffer, stdin);
                     strtok(pInput, "\n");
                     strcpy((ptr + transCount)->toolID, pInput);
                     //validate toolID
                     location = searchTool(pst, pInput, toolCount);
                     if(!((pst + location)->isAvailable))
                     {
                        printf("Tool not available.\n");
                     }// end if
                     else
                        {
                            strcpy((ptr + transCount)->toolID, pInput);
                            printf("Enter 0 for Full Day's Rental.... 1 for Half Day's Rental... \n");
                            scanf("%d", &answer);
                            printf("\n");
                            if(answer == 0)
                                {
                                    strtok(pInput, "\n");
                                    strcpy((ptr + transCount)->rentalPer, "F");
                                    (ptr + transCount)->rentalFees = 75.00;
                                }//end if
                                if(answer == 1)
                                {
                                    strtok(pInput, "\n");
                                    strcpy((ptr + transCount)->rentalPer, "H");
                                    (ptr + transCount)->rentalFees = 55.00;
                                }//end if
                                while(answer != 0 && answer != 1)
                                {
                                    printf("INVALID ANSWER - Please re-enter 1 for yes or 0 for no:  \n");
                                    scanf("%d", &answer);
                                } // end while loop
                                return 1;
                        }//end else
            }//end else
        return 0;
}//end transactionMenu







