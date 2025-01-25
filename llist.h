/*****************************************************************
//
//  NAME:        Justin Mito
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 4, 2024
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   Provides the prototype for the llist class.
//
****************************************************************/


#define RECORD_H
#include <iostream>
#include "record.h"


class llist
{
    private:
        record *    start;
        char        filename[20];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        llist(const llist &);
        ~llist();
        llist& operator=(const llist&);
        friend std::ostream& operator<<(std::ostream&, const llist&);
        int addRecord(int, char [], char[]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};
