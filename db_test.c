#include<stdio.h>
#include<stdlib.h>
#include "header_db.h"

/*@description: This is the main file which tests all the functions for serializing and deserializing a binary search tree and functions to search and
                update student details to a file database.txt declared in header_db.h file.
 *@created on: 27th March 2018
 *@author: Sangeeta Gupta, tinnigupta1998@gmail.com
 */

int main()
{
    int flag=1;
    int count=1;
    int choice;
    int index_key;
    int rollNo_value;

    node* nptr = NULL;
    FILE* fptr_write;

    while(flag)
    {

      student student1;
      fprintf(stdout, "Enter 1 for inserting record\n2 for showing the tree\n3 for commiting changes\n4 for searching a record (id wise)\n");
      fscanf(stdin,"%d",&choice);

      switch(choice)
      {

        case 1:   fprintf(stdout,"\nEnter student first name: \n");
                  fscanf(stdin,"%s",student1.first_name);

                  fprintf(stdout,"\nEnter student last name: \n");
                  fscanf(stdin,"%s",student1.last_name);

                  fprintf(stdout,"\nEnter student cgpa: \n");
                  fscanf(stdin,"%f",&student1.cgpa);

                  fprintf(stdout,"\nEnter student programme: (Enter abbreviation only) \n");
                  fscanf(stdin,"%s",student1.programme);

                  fprintf(stdout,"\nEnter student rollno : \n");
                  fscanf(stdin,"%d",&student1.rollNo);

                  student1.index_value = countNumberOfLines();

                  insertStudentRecord(&student1);

                  if(nptr==NULL)
                    {

                        if(student1.index_value==0)
                        {
                            nptr=insert(nptr,student1.rollNo,student1.index_value);
                        }

                        else
                        {
                            nptr=writeFromIndexFile(nptr);
                         }

                    }
                  else
                  {

                        insert(nptr,student1.rollNo,student1.index_value);

                  }

                  break;


        case 2:  printPreorder(nptr);

                 break;


        case 3:  fptr_write = fopen("index.txt","w");

                 if(fptr_write==NULL)
                 {
                     fprintf(stdout, "Couldn't open file!\n");
                  }
                  else
                  {
                    writeToIndexFile(nptr,fptr_write);
                  }

                  fclose(fptr_write);

                  break;


       case 4:    fprintf(stdout,"\nEnter student rollno to be searched! : \n");
                  fscanf(stdin,"%d",&rollNo_value);

                  nptr=writeFromIndexFile(nptr);
                  index_key=search(nptr,rollNo_value);

                  if(index_key>-1)
                  {

                    FILE* fptr_read_search = fopen ("database.txt","r");
                    if(fptr_read_search==NULL)
                    {
                        fprintf(stdout, "Cannot open file!\n");
                    }

                    else
                    {

                        int ch = 0;

                        while(!feof(fptr_read_search)&& ch<index_key)
                        {

                            if(getc(fptr_read_search)=='\n')
                            {
                              ch=ch+1;
                            }

                        }

                        fscanf(fptr_read_search,"%d %d %s %s %f %s",&student1.index_value,&student1.rollNo,student1.first_name,student1.last_name,&student1.cgpa,student1.programme);
                        fprintf(stdout,"Student name: %s %s Student programme: %s Student cgpa: %f Student rollNo: %d\n",student1.first_name,student1.last_name,student1.programme,student1.cgpa,student1.rollNo);

                        fclose(fptr_read_search);

                      }

                  }
                  else
                  {

                    fprintf(stdout, "Couldn't find record!\n");

                  }

                  break;


        default : fprintf(stdout,"\nWrong choice!");

                  break;

     }

        fprintf(stdout,"Do you want to try again?\nEnter 1 for yes and 0 for no\n");
        fscanf(stdin,"%d",&flag);

   }

    return EXIT_SUCCESS;

}
