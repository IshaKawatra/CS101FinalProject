#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct Books{ 
  string	title;
	string authorlast;
	string authorfirst;
	string ISBN;
	double price;
	int availability;
} ;

bool Open_File(ifstream &Fin);
char Menu();
void Details(Books list[], int size);
void Return (Books list[], int size, Books booksale[]);
void Purchase ( Books list[], int size, Books booksale[]);
void Replace ( Books list[], int size, Books booksale[]);
void ByAuthor( Books list[], int size);
void DisplayBooks( Books list[], int size);
void Alphabetical( Books list[], int size);
void ExitPrint( Books list[], Books booksale[], int size);

int main() {

   Books list[100];
   Books booksale[100];
   cout << "Welcome to Isha's Bookstore!" << endl;

   ifstream	fin ;
   bool isopen = Open_File(fin); 
   int size=0;
	while(!fin.eof())
	{	
		getline(fin, list[size].title);
		getline(fin, list[size].authorlast, ',');
		getline(fin, list[size].authorfirst);
		fin>>list[size].ISBN;
		fin>>list[size].price;
		fin>>list[size].availability;
		fin.ignore(10, '\n');
		size++;
		
	}

	for(int k=0; k<=size; k++)
	{
		booksale[k].title = list[k].title;
		booksale[k].authorlast = list[k].authorlast;
		booksale[k].authorfirst = list[k].authorfirst;
		booksale[k].ISBN = list[k].ISBN;
		booksale[k].price = list[k].price;
		booksale[k].availability = 0;
	}
   bool flag = true;
	do {
	if(isopen)
   {
	   char c = Menu();
	   switch (c)
	   {
			case 'A': Purchase (list, size, booksale);
				break;
			case 'B': Return (list, size, booksale);
				break;
			case 'C': Replace (list, size, booksale);
				break;
			case 'D': DisplayBooks (list, size);
				break;
			case 'E': Alphabetical (list, size);
				break;
			case 'F': Details(list, size);
				break;
			case 'G': ByAuthor(list, size);
				break;
			case 'H': ExitPrint(list, booksale, size);
				flag = false;
				break;
			default:
				cout << "Invalid entry. Program terminated.";
	   }
   }

   else 
   {
	   cout << "Invalid data. Program terminated." << endl;
	   flag = false;
   }
   }
   while(flag);
   return 0 ;
}

char Menu() {
	char choice;
	cout << endl;
	cout << "Please choose from the following options. \n";
	cout << "'A' = purchase a book\n";
	cout << "'B' = return a book\n"; 
	cout << "'C' = replace a book\n"; 
	cout << "'D' = view all available books\n";
	cout << "'E' = print a sorted list of all books\n";
	cout << "'F' = view the details of a specific book\n";
	cout << "'G' = view all books by a specific author\n";
	cout << "'H' = exit program\n" << endl << endl;
	cin >> choice;
	return choice;
}

bool Open_File(ifstream &Fin)
{
	string File_Name ;
	cout << endl << "Please enter file name: " ;
	getline(cin, File_Name);
	Fin.open(File_Name.c_str());
	if(Fin.fail()) {
		return false;
	}
	else {
		return true ;
	}
}

void Replace (Books list[], int size, Books booksale[])
{
	string enterreturn;
	cout << endl << "What book would you like to return? " << endl;
	cin.ignore('10', '\n');
	getline(cin, enterreturn);
	bool flag = true;
	for (int i = 0; i < size; i++){
		if (enterreturn == list[i].title){
			cout << endl << "Is this book damaged? (Y/N) " << endl;
			char yn;
			cin >> yn;
			if (yn == 'N')
			{
				list[i].availability++;
				booksale[i].availability--;
			}
			else if (yn == 'Y'){
				cout << "Book disposed." << endl;
				booksale[i].availability--;
			}
			flag = false;
		}
	}
	if (flag)
	{cout << endl << "This book cannot be returned." << endl;}
	else if (!flag){
	cout << endl << "Would you like to replace it with the same book? (Y/N)" << endl;
	char yn1;
	cin >> yn1;
	if (yn1 == 'Y'){
		for (int i = 0; i < size; i++) {
			if (enterreturn == list[i].title){
				list[i].availability--;
				cout << endl << "You have successfully replaced the same book. " << endl;
			}
		}
	}
	else if (yn1 == 'N'){
		
		cout << endl << "What book would you like to purchase instead? " << endl;
		string buyinstead;
		cin.ignore('10', '\n');
		getline(cin, buyinstead);
		for (int i = 0; i < size; i++){
			if (buyinstead == list[i].title){
				list[i].availability--;
				booksale[i].availability++;
				cout << endl << "You have successfully purchased " << list[i].title << "." << endl;
			}
		}
	}
		
	}			
}
void ByAuthor( Books list[], int size) {	
    string enterlastname;
	cout << endl << "Please enter the last name of the author you wish to view. " << endl;
	cin.ignore('10', '\n');
	getline(cin, enterlastname);
	bool flag = true;
	for (int i = 0; i < size; i++)
	{
		if (enterlastname == list[i].authorlast)
		{
			for (int c = i; c < i+1; c ++)
			{
				cout << "Title: " << list[c].title << endl;
				cout << "Author: " << list[c].authorlast << endl;
				cout << "Quantity: " << list[c].availability << endl;
				cout << "ISBN: " << list[c].ISBN << endl;
				cout << "Price: " << list[c].price << endl << endl;
				flag = false;
			}
		}
	}
	if(flag)
	{cout<<"No author by that name was found in our inventory." << endl;}
}


void Details(Books list[], int size) {	
    string entertitle;
	cout << endl << "What book would you like to view? " << endl;
	cin.ignore('10', '\n');
	getline(cin, entertitle);
	bool flag = true;
	for (int i = 0; i < size; i++) {
		if (entertitle == list[i].title){
			for (int b = i; b < i+1; b ++)
			{
				cout << "Title: " << list[b].title << endl;
				cout << "Author: " << list[b].authorlast << endl;
				cout << "Quantity: " << list[b].availability << endl;
				cout << "ISBN: " << list[b].ISBN << endl;
				cout << "Price: " << list[b].price << endl << endl;
				flag = false;
			}
		}
	}
	if(flag)
	{cout<<"No book by that title was found in our inventory" << endl << endl;}
}

void Purchase ( Books  list[], int size, Books booksale[]) {	 
   string entertitle;
	cout << endl <<"Please enter the title of the book you wish to purchase: ";
	cin.ignore('10', '\n');
   getline(cin, entertitle);
   bool flag = true;
   for (int i = 0; i < size; i++){
	   if (entertitle == list[i].title) {
		   if (list[i].availability > 0) {
			   cout << endl << "The price of this book is $" << list[i].price << ". Would you still like to continue? (Y/N)" << endl;
			   char yn;
			   cin >> yn;
			   if (yn == 'Y'){
				list[i].availability--;
				booksale[i].availability++;
				flag = false;
				cout << "You have successfully purchased " << entertitle << "!" << endl << endl;
			   }
			   else if (yn == 'N'){
				   flag = false;
			   }
		   }
		   else {
			   cout << "Out of stock." << endl;
			   flag = false;
		   }
	   }
   }
   if(flag)
	{cout<<"No book by that title was found in our inventory";}

}

void Return ( Books  list[], int size, Books booksale[]) {	 
   string entertitle;
	cout << "Please enter the title of the book you wish to return: ";
	cin.ignore('10', '\n');
   getline(cin, entertitle);
   bool flag = true;
   for (int i = 0; i <= size; i++)
   {
	   if (entertitle == list[i].title && booksale[i].availability> 0){
		   list[i].availability++;
		   booksale[i].availability--;
		   cout << endl << "You have successfully returned " << entertitle << "!" << endl;
		   flag = false;
	   }
   }
   if(flag)
	{cout<<"You cannot return this book." << endl << endl;}
}

void DisplayBooks( Books list[], int size) {
	cout << setw(25) << left << "TITLE" << setw(15) << left << "AUTHOR" << setw(20) << left<< "QUANTITY" << endl;
	cout << "====================================================================" << endl;
	bool flag = true;
   for (int i = 0 ; i < size ; i++){
		if (list[i].availability > 0) {
			cout << setw(25) << left << list[i].title << setw(15) << left << list[i].authorlast << setw(20) << left << list[i].availability << endl;
			flag = false;
		}
   }
   if(flag)
	{cout<<"No books available.";}

}
 

void Alphabetical( Books list[], int size) {
   cout << endl << endl;
int j, i;
Books temp;

for(i = 0; i < size - 1; ++i)
{
	for(j = i + 1; j < size; ++j)
	{
		if(list[i].title >list[j].title)
		{
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
}

cout << setw(25) << left << "TITLE" << setw(15) << left << "AUTHOR" << setw(20) << left<< "QUANTITY" << endl;
	cout << "====================================================================" << endl;
	bool flag = true;
   for (int i = 0 ; i < size ; i++){
			cout << setw(25) << left << list[i].title << setw(15) << left << list[i].authorlast << setw(20) << left << list[i].availability << endl;
			flag = false;
   }
   if(flag)
	{cout<<"No books available.";}

}

void ExitPrint( Books list[], Books booksale[], int size) {
	double totalsales = 0;
	for (int i = 0 ; i < size ; i++){
		if (booksale[i].availability > 0){
			totalsales += booksale[i].availability*list[i].price;
		}
		else if (booksale[i].availability < 0) {
			totalsales -= booksale[i].availability*list[i].price*(-1);
		}
	}
   cout << setw(20) << left << "Title Sold" << setw(20) << left << "Price" << setw(20)<< left << "Quantity" << setw(20) << endl;
   cout << "========================================================================" << endl << endl;
	bool flag = true;
   for (int i = 0 ; i < size ; i++)
	{
		if (booksale[i].availability > 0){
			cout << setw(20) << left << booksale[i].title << setw(20) << left << booksale[i].price << setw(20) << left << booksale[i].availability << endl;
		flag = false;
		}
		else if (booksale[i].availability < 0){
			cout << setw(20) << left << "N/A" << setw(20) << left << "N/A" << setw(20) << left << "N/A" << endl;
			flag = false;
		}
	
	}
	if(flag)
	{cout<<"No sales made." << endl;}
	else 
	{cout << endl << "TOTAL SALES: $" << setprecision(2) << fixed << totalsales << endl << endl << "Thank you for shopping at Isha's Bookstore!" << endl << endl;}
}
