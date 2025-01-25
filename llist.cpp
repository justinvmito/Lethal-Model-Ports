/*****************************************************************
//
//  NAME:        Justin Mito
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 9, 2024
//
//  FILE:        llist.cpp 
//
//  DESCRIPTION:
//   Describe the file
//
****************************************************************/

#include "llist.h"
#ifndef RECORD_H
    #include <iostream>
    #include "record.h"
#endif
#include <fstream>
#include <cstring>


record * start;
char     filename[20];
        
/*******************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads the contents of a file and makes a linked 
//                 list with them.
//
//  Parameters:    None
//
//  Return values: 0:            The file was read from and the linked
//                               list was derived from it.
//
//                 -1:           The file is inaccessible for reading
//
***************************************************************/

int llist::readfile()
{

    #ifdef DEBUG
        std::cout << "Debug mode: called readfile with no parameters" << "\n";
    #endif

    int toReturn = 0;
    struct record * previous = NULL;
    struct record * toAdd = NULL;
    char uname[45];
    char uaddress[45];
    char add[45];
    int uaccountno;
    int exitCondition = 0;
    int condition = 0;
    int firstTime = 0;

    std::ifstream infile((*this).filename, std::ifstream::in);

    if (infile == NULL)
    {
        toReturn = -1;
    }
    else
    {
        infile.ignore(20,'\n');
        while (exitCondition == 0)
        {
            infile >> uaccountno;
            if (infile.eof())
            {
                exitCondition = 1;
            }
            else
            {
                infile.ignore(20,'\n');
                toAdd = new struct record;
                (*toAdd).accountno = uaccountno;
                infile.getline(uname, 45);
                strcpy((*toAdd).name, uname);
                infile.getline(uaddress, 45);

                while (condition == 0)
                {
                    infile.getline(add, 45);

                    if (strlen(add) == 0)
                    {
                        strcpy((*toAdd).address, uaddress);
                        condition = 1;
                    }
                    else
                    {
                        strcat(uaddress, "\n");
                        strcat(uaddress, add);
                    }
                }

                condition = 0;

                if (firstTime == 0)
                {
                    (*this).start = toAdd;
                    previous = (*this).start;
                    firstTime = 1;
                }
                else
                {
                    (*previous).next = toAdd;
                    previous = toAdd;
                    (*previous).next = NULL;
                }
            }
        }
    }
    return toReturn;
}

/***************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Reads the contents of a file and makes a linked
//                 list with them.
//
//  Parameters:    None
//
//  Return values: 0:            The file was read from and the linked
//                               list was derived from it.
//
//                 -1:           The file is inaccessible for reading
//
***************************************************************/

int llist::writefile()
{
    #ifdef DEBUG
        std::cout << "Debug mode: called writefile with no parameters" << "\n";
    #endif
    int toReturn = 0;
    struct record * current = (*this).start;
    std::ofstream outfile((*this).filename);

    if (outfile == NULL)
    {
        toReturn = -1;
    }
    else
    {
        while (current != NULL)
        {
            outfile << "\n" << (*current).accountno << "\n" << (*current).name << "\n";
            outfile << (*current).address << "\n" << std::flush;
            current = (*current).next;
        }
        outfile << "\n";
    }

    return toReturn;
}


/***************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Clears heap space used by the linked list.
//
//  Parameters:    None
//
//  Return values: None
//
****************************************************************/

void llist::cleanup()
{
    #ifdef DEBUG
        std::cout << "Debug mode: called cleanup with no parameters" << "\n";
    #endif
    struct record * current = (*this).start;
    struct record * next;

    (*this).writefile();
    while (current != NULL)
    {
        next = (*current).next;
        delete(current);
        current = next;
    }

    (*this).start = NULL;
}

/***************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record to the linkedlist using the parameters
//                 given.
//
//  Parameters:    int uaccountno:        The record number
//                 char [] uname:         The record holder's name
//                 char [] uaddress:      The record holder's address
//
//  Return values: 0:                     The record was successfully added
//
//                 -1:                    A record with the specified account number
//                                        already exists.
//
***************************************************************/

int llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
    #ifdef DEBUG
        std::cout << "Debug mode: called addRecord with parameters: " << "uaccountno " << uaccountno;
        std::cout <<", uname " << uname << ", uaddress " << uaddress << "\n";
    #endif
    struct record * account = NULL;
    struct record * current = NULL;
    struct record * following = NULL;
    int toReturn = -1;
    int condition = -1;

    account = new struct record;
    (*account).accountno = uaccountno;
    strncpy((*account).name, uname, 25);
    strncpy((*account).address, uaddress, 45);

    if ((*this).start == NULL)
    {
        (*account).next = NULL;
        (*this).start = account;
        toReturn = 0;
    }
    else if ((*this).start != NULL)
    {
        condition = 0;
        current = (*this).start;
        following = (*(*this).start).next;

        if (uaccountno < (*current).accountno)
        {
            (*account).next = (*this).start;
            (*this).start = account;
            toReturn = 0;
            condition = 1;
        }

        while (condition == 0)
        {
            if (following == NULL)
            {
                 if (uaccountno == (*current).accountno)
                 {
                     toReturn = -1;
                     condition = 1;
                 }
                 else
                 {
                    (*account).next = NULL;
                    (*current).next = account;
                    toReturn = 0;
                    condition = 1;
                }
            }
            else if (uaccountno == (*current).accountno)
            {
                toReturn = -1;
                condition = 1;
            }
            else if (uaccountno == (*following).accountno)
            {
                toReturn = -1;
                condition = 1;
            }
            else if (uaccountno < (*following).accountno)
            {
                (*account).next = following;
                (*current).next = account;
                toReturn = 0;
                condition = 1;
            }
            else
            {
            current = following;
            following = (*following).next;
            }
        }
    }
    return toReturn;
}

/***************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructs a "default" llist, calling readfile on
//                 the "default" file.
//
//  Parameters:    none
//
//  Return values: none
//
***************************************************************/

llist::llist()
{
    #ifdef DEBUG
        std::cout << "Debug mode: called llist with no parameters" << "\n";
    #endif

    strncpy((*this).filename, "default.txt", sizeof("default.txt"));
    (*this).start = NULL;
    (*this).readfile();
}

/***************************************************************
//
//  Operator name: =
//
//  DESCRIPTION:   A set-equals method for making the equals operation
//                 usable on llist instances. Creates a copy of the llist.
//
//  Parameters:    const llist& orig:     The llist that will be copied.
//
//  Return values: The llist copy
//
***************************************************************/

llist& llist::operator=(const llist& orig)
{
    llist * newlist = new llist(orig);
    return *newlist;
}

/***************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructs a llist from the file with the name in
//                 the parameter by calling readfile.
//
//  Parameters:    char[] file  :  The name of the text file that will
//                                 be read/written.
//
//  Return values: none
//
***************************************************************/

llist::llist(char file[])
{
    #ifdef DEBUG
       std::cout << "Debug mode: called llist with parameter: file " << file << "\n";
    #endif 

    strncpy((*this).filename, file, (int)sizeof(file));
    (*this).start = NULL;
    (*this).readfile();     
}

/***************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructs a llist by copying the llist in the
//                 parameter.
//
//  Parameters:    llist * orig :  The pointer to the llist to copy
//
//  Return values: none
//
***************************************************************/

llist::llist(const llist & orig)
{
    #ifdef DEBUG
        std::cout << "Debug mode: called llist with parameter: llist " << "\n";
    #endif

    struct record * current = NULL;
    struct record * toAdd = new struct record;
    struct record * first = NULL;

    strcpy((*this).filename, orig.filename);
    current = orig.start;
    (*toAdd).accountno = (*current).accountno;
    strcpy((*toAdd).name, (*current).name);
    strcpy((*toAdd).address, (*current).address);
    (*toAdd).next = new struct record;
    first = toAdd;
    current = (*current).next;
    while (current != NULL)
    {   
        toAdd = (*toAdd).next;
        (*toAdd).accountno = (*current).accountno;
        strcpy((*toAdd).name, (*current).name);
        strcpy((*toAdd).address, (*current).address);
        (*toAdd).next = new struct record;
        current = (*current).next;
    }
    (*toAdd).next = NULL;
    (*this).start = first;
}

/***************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   Destructs the linked list that it is called from.
//
//  Parameters:    none
//
//  Return values: none
//
***************************************************************/

llist::~llist()
{
    #ifdef DEBUG
        std::cout << "Debug mode: called ~llist with no parameters" << "\n";
    #endif

    /*  This is my test for the extra credit. Uncomment it to run it. Make sure
        that there is a list to copy/print.
    llist * templist = new llist(*this);

    llist * templist2 = new llist();
    templist2 = this;
    std::cout << *templist;
    std::cout << *templist2;
    (*templist).cleanup();
    (*templist2).cleanup();*/

    (*this).cleanup();
}

/***************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Prints the contents of the record with the accountno
//                 in the parameter.
//
//  Parameters:    int uaccountno : The account number of the record whose
//                                  contents will be printed.
//
//  Return values: 0  : The record was found and its contents were printed.
//
//                 -1 : The record does not exist.
//
***************************************************************/

int llist::findRecord(int uaccountno)
{
    #ifdef DEBUG
        std::cout << "Debug mode: calle findRecord with parameter: uaccountno " << uaccountno << "\n";
    #endif
    int condition = 0;
    int toReturn  = 0;
    struct record * current = (*this).start;

    while (condition == 0)
    {
        if (current == NULL)
        {
        toReturn = -1;
        condition = 1;
        }
        else if ((*current).accountno == uaccountno)
        {
            std::cout << "Account#: " << (*current).accountno << "\nName: ";
            std::cout << (*current).name << "\n";
            std::cout << "Address: " << (*current).address << "\n";
            condition = 1;
        }
        else
        {
            current = (*current).next;
        }
    }
    return toReturn;
}

/***************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints the contents of all records in the linked
//                 list
//
//  Parameters:    none
//
//  Return values: none
//
***************************************************************/

void llist::printAllRecords()
{
    #ifdef DEBUG
        std::cout << "Debug mode: Called printAllRecords with no parameters"  << "\n";
    #endif
    struct record * current = (*this).start;

    while (current != NULL)
    {
        std::cout << "Account#: " << (*current).accountno << "\nName: " << (*current).name;
        std::cout << "\nAddress: " << (*current).address << "\n\n";
        current = (*current).next;
    }
}


/***************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes the record with the specified account
//                 number
//
//  Parameters:    int uaccountno : The account number of the record
//                                  to be deleted
//
//  Return values:  0             : The account was deleted
//                 -1             : The account does not exist
//
***************************************************************/

        int llist::deleteRecord(int uaccountno)
        {
            #ifdef DEBUG
                std::cout <<"Debug mode: Called deleteRecord with parameter uaccountno " << uaccountno << "\n";
            #endif
            struct record * previous = NULL;
            struct record * current = (*this).start;
            struct record * temp = NULL;
            int toReturn = 1;

            while (toReturn == 1)
            {
                if (current == NULL)
                {
                    toReturn = -1;
                }
                else if ((*current).accountno > uaccountno)
                {
                    toReturn = -1;
                }
                else if ((*current).accountno == uaccountno)
                {
                    if (previous == NULL)
                    {
                        start = (*current).next;
                    }
                    else
                    {
                        temp = (*current).next;
                        (*previous).next = temp;
                    }

                    delete(current);
                    current = NULL;
                    toReturn = 0;
                }
                else
                {
                    previous = current;
                    current = (*current).next;
                }
            }
            return toReturn;
        }

/***************************************************************
//
//  Operator name: <<
//
//  DESCRIPTION:   Replacement for printAllRecords with the same functionality.
//
//  Parameters:    ostream& output   : The stream that will be printed to.
//                 const llist& list : The llist to be printed
//
//  Return values: The ostream reference
//
***************************************************************/

std::ostream& operator<<(std::ostream& output, const llist& list)
{
    #ifdef DEBUG
        std::cout << "Debug mode: Called printAllRecords with no parameters"  << "\n";
    #endif
    struct record * current;
    if (list.start != NULL)
    {
        current = list.start;
    }

    while (current != NULL)
    {
        std::cout << "Account#: " << (*current).accountno << "\nName: " << (*current).name;
        std::cout << "\nAddress: " << (*current).address << "\n\n";
        current = (*current).next;
    }
    return output;
}
