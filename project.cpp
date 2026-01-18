#include<iostream>
#include<string>
using namespace std;
class transaction{
	public:
	int transid;
	double amount;
	int borrowid;
	int lenderid;
	string borrowday;
	int allowdays;
	bool returned;
	float percentage;
	transaction* next;
	transaction (int id,double am,int bid,int lid,string bd,int ad,float p){
		transid=id;
		amount=am;
		borrowid=bid;
		lenderid=lid;
		borrowday=bd;
		allowdays=ad;
		returned=false;
		percentage=p;
		next=NULL;
		
	}
};
class user{
	public:
		int id;
		string name;
		bool isActive;
		transaction* loan;
		transaction* payment;
		user* left;
		user* right;
		user(int i,string na){
			id=i;
			name=na;
			isActive=true;
			loan=NULL;
			payment=NULL;
			left=NULL;
			right=NULL;
		}
		void addlon(transaction* t){
			t->next=loan;
			loan=t;
		}
		void addpayment(transaction* t){
			t->next=payment;
			payment=t;
		}
};
 user* createuser(int id,string name){
 user* u=new user(id,name);
	return u;
}
user*insert(user*root,int id,string name){
	if(!root){
		return createuser(id,name);
	}
	if(id<root->id){
		root->left=insert(root->left,id,name);
	}
	if(id>root->id){
		root->right=insert(root->right,id,name);
	}
	return root;
}
user* search(user* root,int id){
	if(!root){
		return  NULL;
		
	}
	if(root->id==id){
		return root;
	}
	if(id<root->id){
		return search(root->left,id);
	}
	return search(root->right,id);
}
void updateuser(user* root){
	int id;
	string newname;

	cout<<"Enter user id : ";
	cin>>id;

	user* u=search(root,id);
	if(!u){
		cout<<"user not found"<<endl;
		return;
	}
	if(u->isActive){
		cout<<"Enter new name : ";
		cin>>newname;
		u->name=newname;
		cout<<"user updated succesfully"<<endl;
	}else
	cout<<"user is in active"<<endl;

}
void deleteuser(user* root,int deleteid){
user * u=search(root,deleteid);

if(!u){
	cout<<"user not found "<<endl;
	return;
}
if(u->isActive){
	cout<<"user is found"<<endl;
	u->isActive=false;
	cout<<"user is deleted"<<endl;
}else
cout<<"user not found"<<endl;
}
void userlist(user* root){
 if(!root){
	return;
 }
 userlist(root->left);
 if(root->isActive){
	cout<<"user id :"<<root->id<<endl<<"User name :"<<root->name<<endl;
 }
 userlist(root->right);
}

void borrowmoney(user* root){
int tid,borrowerid,lenderid,allowday;
string borrowday;
float percent;
double Amount;
user *borrower;
user* lender;

cout<<"Enter transaction id :";
cin>>tid;

cout<<"Enter borrower Id :";
cin>>borrowerid;

cout<<"Enter lender id :";
cin>>lenderid;

cout<<"Enter a day from which loan send : ";
cin>>borrowday;

cout<<"Enter allowed day for return loan : ";
cin>>allowday;

cout<<"Enter amount: ";
cin>>Amount;
cout<<"Enter fine percentage : ";
cin>>percent;
borrower=search(root,borrowerid);
lender=search(root,lenderid);

if(!borrower||!lender){
	cout<<"borrower or lender not found"<<endl;
	return;
}
if(!borrower->isActive||!lender->isActive){
cout<<"borrower or lender is inactive"<<endl;
return;
}
transaction* t=new transaction(tid,Amount,borrowerid,lenderid,borrowday,allowday,percent);
borrower->addlon(t);
lender->addpayment(t);

cout<<"recoad updated successfully"<<endl;

}

void returnmoney(user* root){
int tranid,borrowerid,lenderid;
user* borrower;
int return_day;
int returnedamount;
  
  cout<<"Enter borrower id: ";
  cin>>borrowerid;
borrower=search(root,borrowerid);
  if(!borrower|| !borrower->isActive){
	cout<<"borrower not fount id in active "<<endl;
	return;
  }
  cout<<"Enter transaction id : ";
  cin>>tranid;

  transaction* t=borrower->loan;
 bool found=false;
 while(t){
	if(t->transid==tranid){
		found=true;
		break;
	}
	t=t->next;	
}
if(!found){
	cout<<"transaction id not found "<<endl;
return;
}
if(t->returned){
	cout<<"Transaction already marked as returned"<<endl;
	return;
}
cout<<"Enter number of days when amount is returned";
cin>>return_day;
cout<<"Enter amount you returned ";
cin>>returnedamount;

cout<<"Enter lender id :";
cin>>lenderid;
user*lender=search(root,lenderid);

if(!lender||!lender->isActive){
	cout<<"lender not found and is inactive"<<endl;
	return;
}

if(return_day>t->allowdays){
	double fine=t->amount*t->percentage/100;

	cout<<"late! fine applied : "<<fine<<endl;
	cout<<"Total amount to pay with fine : "<<(t->amount+fine)<<endl;

}else{
	cout<<"no fine is applied "<<endl;
	cout<< "Total amount to pay is : "<<t->amount<<endl;
}
t->returned=true;
cout<<"Tracsaction marked as returned"<<endl;
}
void checkaccount(user* root){
	int id;
	
	cout<<"user id";
	cin>>id;
	user* u=search(root,id);
	if(!u){
		cout<<"users not found"<<endl;
		return;
	}
	cout<<"Loan to pay"<<endl;
	transaction* t=u->loan;
	while(t){
		cout<<"TID"<<t->transid<<endl
		    <<"Amount"<<t->amount<<endl
			<<"returend"<<(t->returned ?"yes":"No")<<endl;
			t=t->next;
	}
	cout<<"\n payment received"<<endl;
	t=u->payment;
	while(t){
		cout<<"ID"<<t->transid
			<<"Amount"<<t->amount<<endl;
			t=t->next;
	}

}
int main(){
	user* root=nullptr;
	int id;
	string name;
	char choice;
	do{
		cout<<"------Loan system menue----";
		cout<<"\n1.insert user"<<endl;
		cout<<"2.search user"<<endl;
		cout<<"3.update user"<<endl;
		cout<<"4.delete user"<<endl;
		cout<<"5.borrew Money"<<endl;
		cout<<"6.user list"<<endl;
		cout<<"7.Returned Money"<<endl;
		cout<<"8. check account"<<endl;
		cout<<"0.Exit"<<endl;
		cout<<"Enter you choice :"<<endl;
		cin>>choice;

	switch(choice){
case '1':
	
	cout<<"Enter id ";
	cin>>id;
	cout<<"ENTER NAME :";
	cin>>name;
root=insert(root,id ,name);
break;
case '2':{

int searchid;
cout<<"Enter user id :"<<endl;
cin>>searchid;
user* u=search(root,searchid);
if(u){
	cout<<"user found: ";
	cout<<"\n user id : "<<u->id<<endl;
	cout<<"user name :"<<u->name<<endl;
	cout<<"user status: "<<(u->isActive ? "yes":"  No")<<endl;
}else{
	cout<<"user not found";
}

break;
}

case '3':
updateuser(root);
break;
case '4':
int deleteid;
cout<<"Enter id to delte :";
cin>>deleteid;
deleteuser(root,deleteid);

break;

case '5':
borrowmoney(root);

break;

case '6':
userlist(root);
break;
case '7':
returnmoney(root);

break;
case '8':
checkaccount(root);
break;

}
	
	}while(choice!='0');
	return 0;

}