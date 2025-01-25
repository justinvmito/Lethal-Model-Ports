/****************************************
//
//   Name:           Justin Mito
//    
//   HOMEWORK:       Project2
//
//   CLASS:          ICS 212
//
//   INSTRUCTOR:     Ravi Narayan
//
//   DATE:           April 19 2024
//
//   File:           record.h
//
//   DESCRIPTION:    Defines the "record" structure
//                   Defines the following variables:   
//                   int accountno:          The account number
//                   char name[25]:          The account holder's name
//                   char address[45]:       The account holder's address
//                   struct record* next:    The next record in the list
//
*****************************************/

#ifndef RECORDSTRUCT
#define RECORDSTRUCT

struct record
{
    int               accountno;
    char              name[25];
    char              address[45];
    struct record     *next;
};

#endif
