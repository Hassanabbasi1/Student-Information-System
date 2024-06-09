#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio>

using namespace std;

struct student
{
	string name;
	string reg_no;
	string class_name;
	string cgpa;
	//int total_marks;
	//int marks[5];
	student* next;
	student(string, string, string, string, student*);
};

student::student(string tempname, string tempclass_name,
 string tempcgpa, string tempreg_no, student* tempNext)
:name(tempname), class_name(tempclass_name), cgpa(tempcgpa), reg_no(tempreg_no), next(tempNext)
{}

typedef student* studentPtr;

void readFile(studentPtr &root);
void insert (studentPtr &root);
void delname(studentPtr &root);
studentPtr locateNode(studentPtr temp, string tit);
void delreg_no(studentPtr &root);
studentPtr locateNodereg_no(studentPtr temp, string isb);
void searchreg_no(studentPtr temp);
void printList(studentPtr temp);
void printclass_name(studentPtr temp);
void saveFile(studentPtr temp);
int countNodes(studentPtr temp);

void getline(istream &stream, string &str, char delimiter)
{	char temp[500];
	stream.get(temp, 500, delimiter);
	stream.ignore(500, delimiter);
	str = temp;
}

void getline(istream &stream, int &num, char delimiter)
{	int temp;
	stream >> temp;
	stream.ignore(500, delimiter);
	num= temp;
}



int main()
{
	int choice;
	studentPtr root = NULL;
	readFile(root);

textcolor(3);
textbackground(3);
	do
	{ clrscr();
  gotoxy(15,2); cout<<""
        "    ÛÛÛÛÛ ÛÛÛÛÛ  ÛÛÛÛÛ  ÛÛÛÛÛ  ÛÛÛÛÛÛÛÛÛÛÛÛÛ   "<<endl; gotoxy(15,3);
  cout<<"     ÛÛÛ   ÛÛÛ    ÛÛÛ    ÛÛÛ       ÛÛÛÛÛ       "<<endl; gotoxy(15,4);
  cout<<"     ÛÛÛ   ÛÛÛ    ÛÛÛ    ÛÛÛ        ÛÛÛ        "<<endl; gotoxy(15,5);
  cout<<"     ÛÛÛ   ÛÛÛ    ÛÛÛ    ÛÛÛ        ÛÛÛ        "<<endl; gotoxy(15,6);
  cout<<"     ÛÛÛ   ÛÛÛ    ÛÛÛ    ÛÛÛ        ÛÛÛ        "<<endl; gotoxy(15,7);
  cout<<"     ÛÛÛ   ÛÛÛ    ÛÛÛ    ÛÛÛ        ÛÛÛ        "<<endl; gotoxy(15,8);
  cout<<"      ÛÛÛÛÛÛÛ    ÛÛÛÛÛ  ÛÛÛÛÛ      ÛÛÛÛÛ       "<<endl<<endl; gotoxy(6,9);
  cout<<"-----------------------------------------------------------------"<<endl; gotoxy(6,10);
  cout<<"                    STUDENT MANAGEMENT SYSTEM                    "<<endl; gotoxy(6,11);
  cout<<"-----------------------------------------------------------------"<<endl; gotoxy(15,12);
		cout<<"(1) Add a student to the list\n"; gotoxy(15,13);
		cout<<"(2) Delete a student based on name\n";    gotoxy(15,14);
		cout<<"(3) Delete a student based on Arid No\n"; gotoxy(15,15);
		cout<<"(4) Search for a student by Arid No.\n"; gotoxy(15,16);
		cout<<"(5) List all students.\n";       gotoxy(15,17);
		cout<<"(6) List all students by same class.\n"; gotoxy(15,18);
		cout<<"(7) Quit.\n\n";  gotoxy(15,19);
		cout<<"Enter your choice ---> ";
		cin >> choice;

		if (1 <= choice && choice <= 6)
		{
			switch (choice)
			{
			case 1:
            {clrscr();
				insert(root);
				break;}
			case 2:
            {clrscr();
            textcolor(6);
				textbackground(6);
				delname(root);
				break;}
			case 3:
            {clrscr();
            textcolor(4);
				textbackground(4);
				delreg_no(root);
				break;}
			case 4:
           {clrscr();
            textcolor(4);
				textbackground(4);
				searchreg_no(root);
				break; }
			case 5:
           {clrscr();
            textcolor(4);
				textbackground(4);
				printList(root);
				break;}
			case 6:
           {clrscr();
            textcolor(4);
				textbackground(4);
				printclass_name(root);
				break;}
			default:
				{cout << "Invalid choice.  Enter again.\n\n";
            clrscr();
			   break;}
			}
		}	
	}
	while (choice != 7);
	saveFile(root);
	return 0;
   getch();
}

void readFile(studentPtr &root)
{
	int numstudents;
	string tit, aut, pub, isb;
	ifstream infile ("students.txt", ios::in);
	infile >> numstudents;
	infile.ignore(500,'\n');
	for (int count = 0; count < numstudents; count++)
	{
		getline(infile, tit, '\n');
		getline(infile, aut, '\n');
      getline(infile, isb, '\n');
		getline(infile,pub, '\n');

		root = new student (tit, aut, pub, isb, root);
	}
}

void insert (studentPtr &root)
{
	string tit, aut, pub, isb;

   gotoxy(20,8);
	cout <<" -- RECORD INSERION FORM -- ";

   gotoxy(15,12);
	cout << "name:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, tit, '\n'); gotoxy(15,13);
	cout << "class_name:\t\t";
	getline(cin, aut, '\n'); gotoxy(15,14);
   cout << "Arid No:\t\t\t";
	getline(cin, isb, '\n'); gotoxy(15,15);
	cout << "cgpa:\t\t\t";
	getline(cin,pub, '\n');

	root = new student (tit, aut, pub, isb, root);
   	cout << "\n\t Insetion done successfully!\n\t press any key to go back to menu! ";
      getch();
}

void delname(studentPtr &root)
{
	string tit;

      gotoxy(20,8);
	cout <<" -- RECORD DELETION FORM (Through name) -- ";


	gotoxy(15,12);
	cout << "Enter student name to be deleted from record :\t";
	cin.ignore(500,'\n');
	getline(cin, tit, '\n');

	studentPtr p = locateNode(root, tit);

	if (p == NULL)
	  { gotoxy(15,14);	cout << "\nRECORD NOT FOUND!\n Deletion cannot be done.\n\n";  }
	else if (root == p)
		root = p->next;
	else
	{
		studentPtr q = root;
		while (q->next != p)
			q = q->next;
		q->next = p->next;
	}
	delete p;
      getch();
}

studentPtr locateNode(studentPtr temp, string tit)
{
	while (temp != NULL)
	{
		if (temp->name == tit)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void delreg_no(studentPtr &root)
{
	string isb;


         gotoxy(20,8);
	cout <<" -- RECORD DELETION FORM (Through Arid NO) -- ";

  gotoxy(15,12);
	cout << "Enter student Arid no. to be deleted :\t";
	cin.ignore(500,'\n');
	getline(cin, isb, '\n');

	studentPtr p = locateNodereg_no(root, isb);

	if (p == NULL)
	  { gotoxy(15,14);	cout << "\nDeletion cannot be done.\n\n";  }
	else if (root == p)
		root = p->next;
	else
	{
		studentPtr q = root;
		while (q->next != p)
			q = q->next;
		q->next = p->next;
	}
	delete p;
      getch();
}

studentPtr locateNodereg_no(studentPtr temp, string isb)
{
	while (temp != NULL)
	{
		if (temp->reg_no == isb)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

void searchreg_no(studentPtr temp)
{
	string isb;


   
         gotoxy(20,8);
	cout <<" -- RECORD SEARCHING FORM (Through Arid NO) -- ";

    gotoxy(15,12);
	cout << "Enter student Arid No:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, isb, '\n');
	
	while (temp != NULL)
	{
		if (isb == temp->reg_no)
		{  gotoxy(15,14);
			cout << temp->name << "\n"; gotoxy(15,15);
			cout << temp->class_name << "\n"; gotoxy(15,16);
         cout << temp->reg_no << "\n\n"; gotoxy(15,17);
			cout << temp->cgpa << "\n"; gotoxy(15,18);

		}
		temp = temp->next;
	}
	cout << "\n";
      getch();
}

void printList(studentPtr temp)
{
	cout << "\n";
   
         gotoxy(25,1);
	cout <<" -- RECORDS DISPLAY -- ";

      gotoxy(6,3);
       cout<<"------------------------------------------------------------"<<endl;  gotoxy(6,4);
       cout<<setw(15)<<"Name"<<setw(18)<<"ClassName"<<setw(15)<<
                   "Arid No"<<setw(12)<<"CGPA  \n"<<endl; gotoxy(6,5);
       cout<<"------------------------------------------------------------\n\n";  //gotoxy(12,15);

	while (temp != NULL)
	{
		cout<<"\t   "<<temp->name;
		cout<<"\t     "<<temp->class_name;
      cout<<"\t     "<<temp->reg_no;
		cout<<"     "<<temp->cgpa<<"\n";

		temp = temp->next;
	}
	cout << "\n";
          cout<<"\n\n All records searched!\n Press any key to go back to menu! "<<endl;
   getch();
}

void printclass_name(studentPtr temp)
{
	string aut;


            gotoxy(20,8);
	cout <<" -- RECORD DISPLAY (Through same class name) -- ";

      gotoxy(6,3);
	cout << "Enter class name to search:\t\t\t";
	cin.ignore(500,'\n');
	getline(cin, aut, '\n');
	
	while (temp != NULL)
	{
		if (temp->class_name == aut)
		{       gotoxy(6,5);
			cout << temp->name << "\t";
			cout << temp->class_name << "\t";
         cout << temp->reg_no << "\t";
			cout << temp->cgpa << "\n";

		}
		temp = temp->next;
	}
	cout << "\n";
      getch();
}

void saveFile(studentPtr temp)
{
	int count = countNodes(temp);
	ofstream outFile("saved.txt",ios::out);
	
	outFile << count << "\n";
	while (temp != NULL)
	{
		outFile << temp->name << "\n";
		outFile << temp->class_name << "\n";
      outFile << temp->reg_no << "\n";
		outFile << temp->cgpa << "\n";
		temp = temp->next;
	}
	cout << "\n";

}

int countNodes(studentPtr temp)
{
	int countB = 0;
	while (temp != NULL)
	{
		countB++;
		temp = temp->next;
	}
	return countB;
}

