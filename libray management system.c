#include<stdio.h>
#include<string.h>
/* * * * * * * * * * * * * * * * * * * * * * * *
                  Admin
* * * * * ** * * * * * * * * * * * * * * * * * */
void see_all_issued_books();

struct Book
{
 char book_name[30],book_branch[5],book_author[30];
 int book_id;
 float book_price;
}b;

void get_new_book_data()   /* entering all book data for saving in file */
{
  printf("Enter book Id\n");
  scanf("%d",&b.book_id);
  printf("Enter book name\n");
  scanf("%s",b.book_name);
  printf("Enter branch name\n");
  scanf("%s",b.book_branch);
  printf("Enter author name\n");
  scanf("%s",b.book_author);
  printf("Enter book price");
  scanf("%f",&b.book_price);
}
void add_new_book()  /* saving new book data into file  */
{
 get_new_book_data();
 FILE *fp;
 fp=fopen("Book_data.txt","a");
 fwrite(&b,sizeof(struct Book),1,fp);
 fclose(fp);
}
void print_data(struct Book book)
{
  printf("Book Id: %d\n",book.book_id);
  printf("Book name: %s\n",book.book_name);
  printf("Book Branch: %s\n",book.book_branch);
  printf("Book Price: %f\n",book.book_price);
  printf("Book Author: %s\n",book.book_author);
}
void read_data()   /*  reading all books data */
{
 struct Book obj;
 FILE *fp;
 fp=fopen("Book_data.txt","r");
    printf("\n\n* * * * * * * * * * * * * * * * * * * * * * * *\n");
 while(fread(&obj,sizeof(struct Book),1,fp))
  {
    print_data(obj);
    printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
  }
 printf("\n\n");
 fclose(fp);
}


void search_book(int entered_id)
{
 struct Book obj;
 FILE *fp;
 fp=fopen("Book_data.txt","r");
 while(fread(&obj,sizeof(struct Book),1,fp))
  {
   if(entered_id==obj.book_id)
    {
      print_data(obj);
      break;
    }
  }
 printf("\n\n");
 fclose(fp);
}
void delete_book(int entered_id)   /* deleting book from book.txt   */
{
 struct Book obj;
 FILE *fr,*fw;
 fr=fopen("Book_data.txt","r");
 fw=fopen("temp.txt","a");
 while(fread(&obj,sizeof(struct Book),1,fr))
  {
   if(entered_id!=obj.book_id)
    {
     fwrite(&obj,sizeof(struct Book),1,fw);
    }
  }
 printf("\n\n");
 fclose(fr);
 fclose(fw);
 remove("Book_data.txt");
 rename("temp.txt","Book_data.txt");
 remove("temp.txt");
}
/* * * * * * * * * * Student Info  * *  * * * * * * * */
struct Student
{
 char student_name[30],student_registration_no[10],student_branch[5];
}s;
void get_student_data()
{
  printf("Enter Student Name\n");
  scanf("%s",s.student_name);
  printf("Enter Registration number\n");
  scanf("%s",s.student_registration_no);
  printf("Enter branch\n");
  scanf("%s",s.student_branch);
}

void add_new_student()
{
 get_student_data();
 FILE *fp;
 fp=fopen("Student_data.txt","a");
 fwrite(&s,sizeof(struct Student),1,fp);
 fclose(fp);
}
void print_student_data()
{
 printf("Registration no: %s\n",s.student_registration_no);
 printf("Name: %s\n",s.student_name);
 printf("Branch: %s\n",s.student_branch);
 printf("* * * * * * * * * * * * * * * * * * * * * * * *\n");
}
void read_all_student()
{
 FILE *fp;
 fp=fopen("Student_data.txt","r");
 printf("\n\n* * * * * * * * * * * * * * * * * * * * * * * *\n");
 while(fread(&s,sizeof(struct Student),1,fp))
  print_student_data();
 printf("\n\n");
 fclose(fp);
}
void remove_student_profile()
{
 char reg[10];
 printf("Enter Registration number: ");
 scanf("%s",reg);
 FILE *fp,*fw;
 fp=fopen("Student_data.txt","r");
 fw=fopen("temp_student.txt","a");
 while(fread(&s,sizeof(struct Student),1,fp))
  {
   if(strcmp(reg,s.student_registration_no)!=0)
    fwrite(&s,sizeof(struct Student),1,fw);
  }
 fclose(fp);
 fclose(fw);
 remove("Student_data.txt");
 rename("temp_student.txt","Student_data.txt");
 remove("temp_student.txt");
}
void admin()
{
 int ch,entered_id;
 do
  {
    printf("1. Add Book\n");
    printf("2. Delete Book\n");
    printf("3. view all books\n");
    printf("4. Search book\n");
    printf("5. Add Student\n");
    printf("6. Show all Student\n");
    printf("7. Show all Issued Books\n");
    printf("8. Remove Student Profile\n");
    printf("0. Exit\n");
   scanf("%d",&ch);
   switch(ch)
    {
     case 0:break;
     case 1:add_new_book();
	    break;
     case 2:printf("Enter book id to Delete \n");
	    scanf("%d",&entered_id);
            delete_book(entered_id);
	    break;
     case 3:read_data();
            break;
     case 4:printf("Enter book id to search \n");
	    scanf("%d",&entered_id);
            search_book(entered_id);
	    break;
     case 5:add_new_student();
	    break;
     case 6:read_all_student();
            break;
     case 7:see_all_issued_books();
            break;
     case 8:remove_student_profile();
            break;
     default:printf("Please choose correct option\n");
    }
  }while(ch!=0);
}
// Admin all functions over

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                      Issue Book
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
struct Issued_Books
{
 int bid;
 char reg[10],name[30],book_name[20],author_name[20];
}ib;
int search_for_student(char registration_no[])
{
 int found=0;
 FILE *fp;
 fp=fopen("Student_data.txt","r");
 while(fread(&s,sizeof(struct Student),1,fp))
  {
   if(strcmp(registration_no,s.student_registration_no)==0)
    {
      found=1;
      break;
    }
  }
 fclose(fp);
if(found==1)
 return 1;
else
 return 0;
}
int search_book_id(int entered_id)
{
// printf("search_book_id\n");
 FILE *fp;
 int found=0;
 fp=fopen("Book_data.txt","r");
 while(fread(&b,sizeof(struct Book),1,fp))
 {
  if(b.book_id==entered_id)
   {
     found=1;
     break;
   }
 }
 fclose(fp);
 if(found==1)
  return 1;
 else
  return 0;
}
 void copy_content()
 {
  strcpy(ib.reg,s.student_registration_no);
  strcpy(ib.name,s.student_name);
  strcpy(ib.book_name,b.book_name);
  strcpy(ib.author_name,b.book_author);
  ib.bid=b.book_id;
 }
void save_student_data()
{
 FILE *fp;
 int found=0;
 fp=fopen("Issued_Book_data.txt","a");
  copy_content();
 fwrite(&ib,sizeof(struct Issued_Books),1,fp);
 fclose(fp);
 printf("\n\nBook Issued Successfully\n\n");
}
void issue_book()
{
 char reg_no[10];
 int enter_book_id;
 printf("Enter Registration number: ");
 scanf("%s",reg_no);
 int k=search_for_student(reg_no);
 if(k==1)
  {
   printf("Enter Book Id\n");
   scanf("%d",&enter_book_id);
   int rbid=search_book_id(enter_book_id);
    if(rbid==1)
      save_student_data();
    else
     printf("No Book Found\n");
  }
 else
   printf("No student data is Found\n");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                     Deposit Book
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int check_book(char regis[],int book_id)
{
 FILE *fp,*fw;
 int found=0;
 fp=fopen("Issued_Book_data.txt","r");
 fw=fopen("temp_book.txt","a");
 while(fread(&ib,sizeof(struct Issued_Books),1,fp))
  {
    if(ib.bid==book_id && (strcmp(ib.reg,regis)==0))
      found=1;
    else
      fwrite(&ib,sizeof(struct Issued_Books),1,fw);
  }
 fclose(fp);
 fclose(fw);
 if(found==1)
 {
  remove("Issued_Book_data.txt");
  rename("temp_book.txt","Issued_Book_data.txt");
  remove("temp_book.txt");
 return 1;
 }
 else
 return 0;
}
void deposit_book()
{
 char regd_no[10];
 int book_id;
 printf("Enter Student registration number: ");
 scanf("%s",regd_no);
 printf("Enter Book id: ");
 scanf("%d",&book_id);
 int k=check_book(regd_no,book_id);
 if(k==1)
  printf("\n\nBook Returned Successfully\n\n");
 else
 printf("Book Not Found\n");
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                        Main Body Start
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int main()
{
 int choice;
 char c,password[]="shailu",pass[20];
 printf("Welcome to Library Management system\n");
 scanf("%c",&c);                             

 do
 {
   printf("Enter your choice\n");
   printf("0. Enter Admin\n");
   printf("1. Issue Book\n");
   printf("2. Deposit Book\n");
   printf("3. Exit\n");
   scanf("%d",&choice);
    switch(choice)
     {
      case 0:printf("Enter admin password\n");
	     scanf("%s",pass);
	     if(strcmp(password,pass)==0)
	       admin();
	     else
                printf("\n\n Warning! Wrong Password. \n\n");
             break;
      case 1:issue_book();
             break;
      case 2:deposit_book();
             break;
      case 3:break;
     }
 }while(choice!=3);
}                                              // main body over//



void see_all_issued_books()
{
 FILE *fr;
 fr=fopen("Issued_Book_data.txt","r");
  printf("\n");
 while(fread(&ib,sizeof(struct Issued_Books),1,fr))
 {
  printf("Student Id: %s\n",ib.reg);
  printf("Student Name: %s\n",ib.name);
  printf("Book Id: %d\n",ib.bid);
  printf("Book Name: %s\n",ib.book_name);
  printf("Book Author: %s\n",ib.author_name);
  printf("* * * * * * * * * * * * * * * * * * * * * * *\n");
 }
  printf("\n");
fclose(fr);
}
