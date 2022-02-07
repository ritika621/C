/* Name : Ritika Sabharwal
   TerpConnect ID: rsabharw
   University ID: 117272918
   Discussion Section: 0107

I pledge on my honor that I have not given or received any unauthorized
assistance on this assignment.*/

#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_student(Student *const student, const char first_name[], 
		  const char last_name[])
{
  if( student != NULL && first_name != NULL && last_name != NULL)
    {
 
  student -> first_name = calloc(strlen(first_name) + 1, sizeof(char));
  student-> last_name = calloc(strlen(last_name) +1, sizeof(char));
  strcpy(student -> first_name , first_name);
  strcpy(student -> last_name, last_name);
  
  }
}

Student *create_student(const char first_name[], const char last_name[])
{
  if(first_name == NULL || last_name == NULL)
    return NULL;
else
{
Student *new_student = malloc(sizeof(Student));
    init_student(new_student, first_name, last_name);
    return new_student;
  }
}

  void print_student(Student student)
  {
    if(student.first_name != NULL && student.last_name !=  NULL)
    {
      if(student.last_name != NULL)
       printf("%s, ", student.last_name);
       
    if(student.first_name != NULL)
      printf("%s", student.first_name);
      }
  }

unsigned int change_first_name(Student *const student, const char new_name[])
{
  if(student == NULL || new_name == NULL)
    return 0;
  else {
    student -> first_name = realloc(student -> first_name,( strlen(new_name)+1) * sizeof(char));
    strcpy(student -> first_name, new_name);
    return 1;
  }
}

unsigned int change_last_name(Student *const student, const char new_name[])
{
  
  if(student == NULL || new_name == NULL)
    return 0;
  else {
    student -> last_name = realloc(student -> last_name, (strlen(new_name) +1) * sizeof(char));
    strcpy(student -> last_name, new_name);
    return 1;
  }
}

unsigned int add_nickname (Student *const student, const char nickname[])
{
  if(student == NULL || nickname == NULL || strstr(student -> first_name, "(") 
     != NULL)
    return 0;
  else
    {
      student -> first_name = realloc(student -> first_name, 
			     (strlen(student -> first_name)+ strlen(nickname) + 4) * sizeof(char));
      
      strcat(student -> first_name, " (");
      strcat(student -> first_name, nickname);
      strcat(student -> first_name, ")");
      return 1;
    }
}

int compare(Student student1, Student student2)
{
   if (student1.last_name == student2.last_name && student1. first_name == student2. first_name)
    return 0;

  else if(strcmp(student1.last_name, student2.last_name) == 0) 
    { if(  strcmp(student1.first_name, student2.first_name) == 0)
    return 0;
      else
	return strcmp(student1.first_name, student2.last_name);
    }
  else 

    return strcmp(student1.last_name, student2.last_name);
}

unsigned int reset_student(Student *const student)
{
  if(student == NULL)
    return 0;
  else{
  free(student -> first_name);
  free(student -> last_name);
  (student -> first_name) = NULL;
  (student -> last_name) = NULL;
  return 1;
  }
}

unsigned int free_student(Student **const student)
{if(student == NULL || *student == NULL)
    return 0;
  else {
    free((*student) -> first_name);
    free((*student) -> last_name);
    ( *student) -> first_name = NULL;
    ( *student) -> last_name = NULL;
  free(*student);
  ( *student) = NULL;
  
  return 1;
  }
}


      
