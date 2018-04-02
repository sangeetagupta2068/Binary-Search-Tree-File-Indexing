/*@description: This is the header file which contains the function declarations and structure definitions for implementing
                the search,deserialization and serialization of a binary search tree and storing student details in database.txt
 *@created on: 27th March 2018
 *@author: Sangeeta Gupta, tinnigupta1998@gmail.com
 */

#ifndef HEADER_H

    #define HEADER_H 1

    //structure definitions
    typedef struct
    {

        char first_name[40];
        char last_name[40];
        float cgpa;
        char programme[100];
        int rollNo;
        int index_value;

    } student;

    typedef struct node node;

    struct node
    {

        int rollNo;
        int index;
        node* left;
        node* right;

    };

    //function prototypes
    node* createNode(int ,int );
    node* insert(node* , int ,int );
    void writeToIndexFile(node*,FILE* fptr_write);
    node* writeFromIndexFile(node*);
    void insertStudentRecord(student* );
    int countNumberOfLines();
    void printPreorder(node* );
    int search(node*,int);

#endif
