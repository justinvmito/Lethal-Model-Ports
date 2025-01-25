/*****************************************************************
//
//  NAME:        Justin Mito
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 15, 2024
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION: Implements the user interface for the bank database.
//
****************************************************************/
#include "llist.h"
#ifndef RECORD_H
    #define RECORD_H
    #include <iostream>
    #include "record.h"
#endif
#include <iomanip>
#include <string>
#include <cstring>

void getaddress(char [], int);
void getAccountNum(int &);  

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The base of the user interface. It starts up the
//                 interface and interprets user input to decide what 
//                 they want to do. It then calls functions to carry out
//                 the user's will.
//
//  Parameters:    argc (int) : The number of elements in argv
//
//                 argv (char*[]) : An array of arguments passed
//                                  to the program. The second index 
//                                  will decide whether the program 
//                                  is launched in "debug mode" or not.
//
//  Return values:  0 : The program terminated.
//
****************************************************************/

int main(int argc, char* argv[])
{
    int exit = 0;
    int toReturn = 0;
    int accountNo;
    int chosen = -1;
    int condition = 0;
    char input[20];
    std::string inputstring;
    char name[25];
    std::string namestring;
    char address[45];
    llist * mylist = new llist();

    #ifdef DEBUG
        std::cout << "Debug Mode enabled\n";
    #endif

    while (exit == 0)
    {
        accountNo = -1;
        std::cout << "Entered User Interface. Welcome.\n\n";
        std::cout << "Choose an action by typing its name or shorthand.\n";
        std::cout << "add: Add a new record to the database.\n";
        std::cout << "printall: Prints all records in the database.\n";
        std::cout << "find: Finds the record with the specified account number.\n";
        std::cout << "delete: Deletes a record with the specified account number.\n";
        std::cout << "quit: Quit the program.\n";

        while (condition == 0)
        {
            std::cin >> input;
            std::cout << "\n";
            if (std::strncmp(input, "add", strlen(input)) == 0)
            {
                chosen = 0;
            }
            else if (std::strncmp(input, "printall", strlen(input)) == 0)
            {
                chosen = 1;
            }
            else if (std::strncmp(input, "find", strlen(input)) == 0)
            {
                chosen = 2;
            }
            else if (std::strncmp(input, "delete", strlen(input)) == 0)
            {
                chosen = 3;
            }
            else if (std::strncmp(input, "quit", strlen(input)) == 0)
            {
                chosen = 4;
            }
            else
            {
                chosen = -1;
            }
            std::cout << "\n";

            if (chosen == 0)
            {
                while (condition == 0)
                {
                    getAccountNum(accountNo);
                    
                    if (accountNo == -1)
                    {
                        std::cout << "Invalid input recieved, input integer that is greater than 0\n";
                    }
                    else
                    {
                        std::cout << std::flush << "Enter account holder's name ";
                        std::cin.getline (name, 256);                        
                        getaddress(address, 45);

                        if ((*mylist).addRecord(accountNo, name, address) == -1)
                        {
                            std::cout << "Record has identical account number to existing record\n";
                        }
                        else
                        {
                            std::cout << "Record added\n";
                        }

                        condition = 1;
                    }
                }
            }
            else if (chosen == 1)
            {
                (*mylist).printAllRecords();
                condition = 1;
            }
            else if (chosen == 2)
            {
                getAccountNum(accountNo);
                if (accountNo == -1)
                {
                    std::cout << "Invalid input recieved, input integer that is greater than 0\n";
                }
                else
                {
                    if ((*mylist).findRecord(accountNo) == -1)
                    {
                        std::cout << "Record does not exist\n";
                    }
                    condition = 1;
                }
                condition = 1;
            }
            else if (chosen == 3)
            {
                while (condition == 0)
                {
                    getAccountNum(accountNo);
                    if (accountNo == -1)
                    {
                        std::cout << "Invalid input recieved, input integer that is greater than 0\n";
                    }
                    else
                    {
                        if ((*mylist).deleteRecord(accountNo) == -1)
                        {
                            std::cout << "Record does not exist\n";
                        }
                        else
                        {
                            std::cout << "Record with account #" << accountNo << " removed\n";
                        }
                        condition = 1;
                    }
                }
                condition = 1;
            }
            else if (chosen == 4)
            {
                delete mylist;
                exit = 1;
                condition = 1;
            }
            else if (chosen == -1)
            {
                std::cout << "Invalid input received. Enter a valid input: ";
            }
        }
        condition = 0;
    }
    return toReturn;
}

/*****************************************************************
//
//  Function name:  getaddress
//
//  DESCRIPTION:    Obtains address information from user input
//                  and stores that address into the parameter.
//                  
//  Parameters:     char address[] : A pointer to an array which 
//                                   will store the owner's address.
//
//                  int limit      : Maximum size of the char array.
//
//                  FILE * file    : The name of the file to read input
//                                   from. Generally should be std::cin
//
//  Return values:  None
//                  
//
****************************************************************/

void getaddress(char address[], int limit)
{
    #ifdef DEBUG
        std::cout << "Debug mode: Called getaddress with parameters: char address[] " << address;
        std::cout << ", int limit " << limit << "\n";
    #endif
    int exit = 0;
    std::string stringrawInput;
    char rawInput[45];
    std::string stringinput; 
    char input[45];

    std::cout << "Enter address. Press enter twice to finish:\n";
    std::getline(std::cin, stringinput);
    std::strncpy(input, stringinput.c_str(), 45);

    while (exit == 0)
    {
        std::getline(std::cin, stringrawInput);
        std::strncpy(rawInput, stringrawInput.c_str(), 45);
        if (strlen(rawInput) == 0)
        {
            strncpy(address, input, limit);

            exit = 1;
        }
        else
        {
            strcat(input, "\n");
            strcat(input, rawInput);
        }
    }
}

/****************************************************************
//
//  Function name:  getAccountNum
//
//  DESCRIPTION:    Obtains account# information from user input
//                  and stores that address into the parameter.
//
//  Parameters:     int * : A pointer to an integer that will
//                          store the account number.
//
//  Return values:  None
//
//
****************************************************************/

void getAccountNum(int & accountNum)
{
    int uaccountno;

    #ifdef DEBUG
       std::cout << "Debug mode: Called getAccountNum with parameter: accountNum " << accountNum << "\n";
    #endif

    std::cout << "Enter account number: ";
    if ((std::cin >> uaccountno).fail())
    {
        std::cin.clear();
        std::cin.ignore(20,'\n');
    }
    if (uaccountno <= 0)
    {
        accountNum = -1;
    }
    else
    {
        accountNum = uaccountno;
        std::cin.ignore(20,'\n');
    }
}
