#include <iostream>
#include <map>
#include <string>
#include <fstream>
#define MIN_BALANCE 500
class insufficientfunds{};
using namespace std;
class Account{
	private:
		long accountnumber;
			string firstname;
			string lastname;
			float balance;
			static long Nextaccountnumber;
	public:
		Account();
		Account(string fname,string lname,float balance);
		long getaccno(){
			return accountnumber;
		}
		string getfirstname(){
			return firstname;
		}
		string getlastname(){
			return lastname;
		}
		float getbalance(){
			return balance;
		}
		
		void Deposit(float amount);
		void withdrawel(float amount);
		
		static void setlastaccno(long accountnumber);
		static long getlastaccno();
		
		friend ofstream &operator<<(ofstream &ofs,Account &acc);
		friend ifstream &operator>>(ifstream &ifs,Account &acc);
		friend ostream &operator<<(ostream &os,Account &acc);
};
long Account::Nextaccountnumber=0;
Account::Account(){
    accountnumber = 0;
    firstname = "";
    lastname = "";
    balance = 0;
}
class Bank{
	private:
		map<long,Account> accounts;
		public:
			Bank();
			Account Openaccount(string fname,string lname,float balance );
			Account BalanceEnquiry(long accountnumber);	
			Account Deposit(long accountnumber,float amount);
			Account withdrawel(long accountnumber,float amount);
			void closeaccount(long accountnumber);
			void showallaccounts();
			~Bank();
};
int main(){
	Bank b;
	Account acc;
	int choice;
	string fname,lname;
	long accountnumber;
	float  balance;
	float amount;
	do{
		
	
	cout<<"***Banking System***"<<endl;
	cout<<"Select one option"<<endl;
		cout<<"1. Open an account"<<endl;
			cout<<"2. Balance Enquiry"<<endl;
				cout<<"3. Deposit"<<endl;
					cout<<"4. Withdrawel"<<endl;
						cout<<"5. Close an Account"<<endl;
							cout<<"6. Show all Accounts"<<endl;
								cout<<"7. Quit"<<endl;
								cout<<"Enter choice ";
								cin>>choice;
		switch(choice){
			case 1:
				cout<<"Enter firstname ";
				cin>>fname;
				cout<<"Enter lastname ";
				cin>>lname;
				cout<<"Enter initial balance ";
				cin>>balance;
				acc=b.Openaccount(fname,lname,balance);
				cout<<endl<<"Congratulations account is created"<<endl;
				cout<<acc;
				break;
					case 2://balance enquiry
				cout<<"Enter accountnumber ";
				cin>>accountnumber;
				cout<<"Enter balance ";
				cin>>amount;
				acc=b.BalanceEnquiry( accountnumber);
				cout<<"Your account details"<<endl;
				cout<<acc;
				break;
					case 3://deposit
				cout<<"Enter accountnumber ";
				cin>>accountnumber;
				cout<<"Enter balance ";
				cin>>amount;
				acc=b.Deposit( accountnumber,amount);
				cout<<"Amount is deposited"<<endl;
				cout<<acc;
				break;
					case 4://withdrawel
				cout<<"Enter accountnumber ";
				cin>>accountnumber;
				cout<<"Enter balance ";
				cin>>amount;
				acc=b.withdrawel( accountnumber,amount);
				cout<<"Amount withdrawel"<<endl;
				cout<<acc;
				break;
					case 5://close account
				cout<<"Enter accountnumber ";
				cin>>accountnumber;
		
				b.closeaccount( accountnumber);
				cout<<"Account is closed"<<endl;
				cout<<acc;
				break;
					case 6://show all account
				b.showallaccounts();
				break;
				case 7:
					break;
					default:
						cout<<"enter correct choice";
						exit(0);
					}
				}while(choice!=7);
				
		}
		Account :: Account(string fname,string lname,float balance){
			Nextaccountnumber++;
			accountnumber=Nextaccountnumber;
			firstname=fname;
			lastname=lname;
			this -> balance=balance;
			
		}	
		void Account:: Deposit(float amount){
			balance+=amount;
			
		}	
		void Account:: withdrawel(float amount){
		if(balance - amount<MIN_BALANCE)
		throw insufficientfunds();
		balance-=amount;
			
		}			
						void Account::setlastaccno(long accountnumber){
							Nextaccountnumber=accountnumber;
						}		
		
	long Account::getlastaccno(){
							return Nextaccountnumber;
						}		
		ofstream &operator<<(ofstream &ofs,Account &acc)	{
			ofs<<acc.accountnumber<<endl;
			ofs<<acc.firstname<<endl;
			ofs<<acc.lastname<<endl;
			ofs<<acc.balance<<endl;
			return ofs;
		}				
ifstream &operator>>(ifstream &ifs,Account &acc)	{
			ifs>>acc.accountnumber;
			ifs>>acc.firstname;
			ifs>>acc.lastname;
			ifs>>acc.balance;
			return ifs;
		}
		ostream &operator<<(ostream &os,Account &acc)	{
		os<<"First Name "<<acc.getfirstname()<<endl;
		os<<"last Name "<<acc.getlastname()<<endl;
		os<<"accountnumber "<<acc.getaccno()<<endl;
		os<<"balance "<<acc.getbalance()<<endl;
			return os;
		}
	Bank::Bank(){
		Account account;
		ifstream infile;
		infile.open("bank.data");
		
		if(!infile){
			cout<<"error in opening file!file not found"<<endl;
			
		}
		while (!infile.eof()){
			infile>>account;
			accounts.insert(pair<long,Account>(account.getaccno(),account));
		}
		
	
	Account::setlastaccno(account.getaccno());
		infile.close();
	
	
	}
	Account Bank::Openaccount(string fname,string lname,float balance){
		ofstream outfile;
		Account account(fname,lname,balance);
		accounts.insert(pair<long,Account>(account.getaccno(),account));
		outfile.open("bank.data",ios::trunc);
		
		map<long,Account>::iterator itr;
		for(itr=accounts.begin();itr!=accounts.end();itr++){
			outfile<<itr->second;
		}
		outfile.close();
		return account;
			}
			Account Bank::BalanceEnquiry(long accountnumber){
				map<long,Account>::iterator itr;
			 itr = accounts.find(accountnumber); 
				return itr->second;
			}
				Account Bank::Deposit(long accountnumber,float amount){
				map<long,Account>::iterator itr;
				 itr = accounts.find(accountnumber); 
				itr->second.Deposit(amount);
				return itr->second;
			}
				Account Bank::withdrawel(long accountnumber,float amount){
				map<long,Account>::iterator itr;
				 itr = accounts.find(accountnumber); 
				itr->second.withdrawel(amount);
				return itr->second;
			}
			void Bank::closeaccount(long accountnumber){
					map<long,Account>::iterator itr;
					cout<<"account deleted"<<endl;
					accounts.erase(accountnumber);
			}
			void Bank::showallaccounts(){
				map<long,Account>::iterator itr;
		for(itr=accounts.begin();itr!=accounts.end();itr++){
		cout<<"Account"<<itr->first<<endl<<itr->second;
		}
			}
Bank::~Bank(){
	ofstream outfile;
	outfile.open("bank.data",ios::trunc);
			map<long,Account>::iterator itr;
		for(itr=accounts.begin();itr!=accounts.end();itr++){
		outfile<<itr->second;
		}
		outfile.close();
}			
