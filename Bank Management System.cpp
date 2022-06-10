#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;
class account
{
	int acno;
        int age;
        char address[50];
        char phone_no[15];
	char name[50];
	int deposit;
	char type;
	static int temp;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;//function to return type of account
	static int generate_account_no()
    {
    	return ++temp;
    }
};  //class ends here
int account::temp=1000;
void account::create_account()
{
	acno=generate_account_no();
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
        cout<<"\nEnter account holder's address : ";
        cin.getline(address,50);
        cout<<"\nEnter account holder's phone no. : ";
        cin.getline(phone_no,15);
        cout<<"\nEnter account holder's age : ";
        cin>>age;
        while(1){
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
        if(type=='c'||type=='s'||type=='S'||type=='C')
        break;
        else
        cout<<"\n\t Wrong input.Please try again\n";
}
type=toupper(type);
while(1){
  	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
        if((type=='S'&&deposit>=500)||(type=='C'&&deposit>=1000))
        break;
        else
        cout<<"\nPlease deposit the minimum required balance.Try again..\n";
}
	cout<<"\n\nAccount Created with account no : "<<acno;
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
        cout<<"\nAddress : ";
        cout<<address;
        cout<<"\nPhone No. : ";
        cout<<phone_no;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
        cin.ignore();
	type=toupper(type);
	cout<<"\nModify phone no. : ";
        cin.getline(phone_no,15);
        cout<<"\nModify address : ";
        cin.getline(address,50);
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(14)<<" "<<name<<setw(14)<<" "<<type<<setw(14)<<deposit<<setw(14)<<" "<<age<<setw(14)<<" "<<phone_no<<endl;
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function
int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\t\tMAIN MENU";
		cout<<"\n\n\t\t01. NEW ACCOUNT";
		cout<<"\n\n\t\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t\t08. EXIT";
		cout<<"\n\n\t\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThank You for using Bank Management System";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}
void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			File.seekp(File.tellp()-sizeof(ac));
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
void delete_account(int n)
{
	account ac;
        int count=0;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
                else{
                     count++;
                    }
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
if(count==0)
cout<<"\n\n\tRecord not found..";
else
cout<<"\n\n\tRecord Deleted of account number : "<<n;
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\t\t\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"========================================================================================================\n";
	cout<<"A/c no.           NAME                     Type        Balance          Age             Phone NO.\n";
	cout<<"========================================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
                        cin.ignore();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to withdraw : ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient balance";
				else
					ac.draw(amt);
		      }
			File.seekp(File.tellp()-sizeof(ac));
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated. ";
                        cout<<" \nBalance is "<<ac.retdeposit();
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
void intro()
{
    cout<<"\n\n\n\t\t\t\t\t\t  WELCOME ";
     cout<<"\n\t\t\t\t\t\t _________ ";
    cout<<"\n\n\t\t\t\t\t\t    TO";
	cout<<"\n\n\t\t\t\t\t  BANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t\t\t  ________________________";
	cout<<"\n\n\n\n\t\t\t\tMADE BY : MEGHA MATHUR";
	cout<<"\n\n\t\t\t\tCOLLEGE : GRAPHIC ERA DEEMED TO BE UNIVERSITY, DEHRADUN";
	cout<<"\n\n\n\t\t\t\t Press any key to proceed.";
	cin.get();
}
