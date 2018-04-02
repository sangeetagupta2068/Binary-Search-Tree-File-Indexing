#include<stdio.h>
#include<stdlib.h>
#include "header_db.h"

/*@description: This file contains all the functions for serializing and deserializing a binary search tree and functions to search and
                update student details to a file database.txt.
 *@created on: 27th March 2018
 *@author: Sangeeta Gupta, tinnigupta1998@gmail.com
 */

node* createNode(int rollNo,int index_value)
{
   /*
    *@description: for initializing a node each time
    *int,int -> node
    */

    node* newNode = malloc ( sizeof (node) );

    newNode->rollNo = rollNo;
    newNode->index = index_value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;

}


node* insert(node* root, int rollNo, int index)
{
  /*
   *@description: for creating the binary search tree.
   *node,int,int -> node
   */

    if (root == NULL)
        {
            root=createNode(rollNo,index);
            return;
        }

    if (rollNo < root->rollNo)
        root->left  = insert(root->left, rollNo, index);
    else if (rollNo > root->rollNo)
        root->right = insert(root->right, rollNo, index);

    return root;
}


void writeToIndexFile(node *root,FILE* fptr_write)
{
  /*
   *@description: for serializing the binary search tree by writing it to a file.
   *node,FILE pointer-> void
    */

    if (root == NULL)
    {
        return;
    }

    fprintf(fptr_write, "%d %d \n", root->rollNo,root->index);
    writeToIndexFile(root->left,fptr_write);
    writeToIndexFile(root->right,fptr_write);

}


void printPreorder(node* root)
{
  /*
   *@description: for printing the binary tree.
   *node -> void
   */
    if ( root == NULL )
        return;

    fprintf(stdout,"%d ", root->rollNo);
    printPreorder(root->left);
    printPreorder(root->right);

}


node* writeFromIndexFile(node* nptr)
{
  /*
   *@description: for writing the contents from the file to the binary search tree.
   *node -> node
   */

    FILE* fptr_read = fopen("index.txt","r");

    int tempNodeValueInt=0,tempNodeValueIdInt=0;
    char tempNodeValue[50],tempNodeValueId[10];

    while(!feof(fptr_read))
    {

        fscanf(fptr_read,"%s %s",tempNodeValue,tempNodeValueId);
        tempNodeValueInt=atoi(tempNodeValue);
        tempNodeValueIdInt = atoi(tempNodeValueId);

        if(nptr==NULL)
        {
          nptr=insert(nptr,tempNodeValueInt,tempNodeValueIdInt);
        }
        else
        {
          insert(nptr,tempNodeValueInt,tempNodeValueIdInt);
        }

    }

    return nptr;

    fclose(fptr_read);

}


int search(node* root,int key_rollNo)
{
  /*
   *@description: for searching the index key in the binary search tree.
   *node,int->int
   */

    if ( root->rollNo==key_rollNo )
    {

        return root->index;

    }
    else
    {

        if ( key_rollNo > root->rollNo )
            return ( root->right != NULL ) ? search ( root->right ,key_rollNo ) : -1;

        else if(key_rollNo<root->rollNo)
            return ( root->left != NULL )?search ( root->left,key_rollNo ) : -1;

    }

}


int countNumberOfLines()
{
  /*
    *@description: for counting the number of lines in database.txt
   *none -> node
   */

    FILE* fptr_read = fopen ("database.txt","r");

    if(fptr_read==NULL)
    {
      return 0;
    }

    fseek(fptr_read,0,SEEK_SET);

    int count=0;

    while(!feof(fptr_read))
    {
          if(getc(fptr_read)=='\n')
          {

              count=count+1;

          }

    }

    fclose(fptr_read);
    return count;

}


void insertStudentRecord(student* student_ptr)
{
  /*
   *@description: for writing the student details to database.txt
   *student-> void
   */

    FILE* fptr_write;

    fptr_write = fopen("database.txt","a+");

    fprintf(fptr_write, "%d ",student_ptr->index_value);
    fprintf(fptr_write, "%d ",student_ptr->rollNo );
    fprintf(fptr_write,"%s %s %f ",student_ptr->first_name,student_ptr->last_name,student_ptr->cgpa);
    fprintf(fptr_write,"%s \n",student_ptr->programme);

    fclose(fptr_write);

}
