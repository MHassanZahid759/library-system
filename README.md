# library-system//F2024266761 M.Hassan Zahid

#include<iostream>
#include<string>
using namespace std;

const int MAX_Books=100;



// Abstract class
class libraryEntity{
public:
// pure virtual function
virtual void display()=0;
};

template <typename T>

class Book:public libraryEntity{
    // Data Member
    public:
    string title;
    string author;
    string genre;
    T bookid;
    bool  recommend;
   // Member function
public:
   //Default constructor‹‹
    Book(){
        title="oop";
        author="Hassan";
        genre="fantasy";
       recommend=false;
    }
    //parametraize constructor

    Book(string t,string a,string g ,T i){
     title=t;
     author=a;
     genre=g;
     bookid=i;
    recommend=false;
    }
    
    bool operator==(const Book<T>& other)const {
        return bookid==other.bookid;
    }
// ------display function------

    void display()override{
        cout<<"Book title is :"<<title<<endl;
        cout<<"Book author is :"<<author<<endl;
        cout<<"Book geners is :"<<genre<<endl;
    }
    friend void printbookdetail(const Book<T>& b);
    
};

// --------Friend Function--------
template<typename T>
void printbookdetail(const Book<T>& b){
    cout<<"Book ID :"<<b.bookid<<endl;
    cout<<"Book title :"<<b.title<<endl;
    cout<<"Book Author is :"<<b.author<<endl;

}

class User{
    //---- Data Member----
public:
string username;
string preferredgenre;
 static const int MAX_RECOMMENDED = 10;

//------ Association--------- 
    Book<int>* recommendedBooks[MAX_RECOMMENDED];
    int recommendedCount;
// ----Member function----
    User() {
        recommendedCount = 0;
        for (int i = 0; i < MAX_RECOMMENDED; i++) {
            recommendedBooks[i] = nullptr;
        }
    }
void userinput(){
    cout<<"Enter user name :";
    getline(cin,username);
    cout<<"Enter preferred gener :";
    getline(cin,preferredgenre);
}
// ------function to recommend book to user-----
void recommendedbook(Book<int>* book[],int size){
    cout<<"Recommended for :"<<username<<endl;
    cout<<"preferred Genre :"<<preferredgenre<<endl;
    bool found=false;
    for(int i=0;i<size;i++){
        if(book[i]->genre==preferredgenre){
            book[i]-> display();
            book[i]->recommend=true;
            found=true;

        }
    }
        if(!found){
        cout<<"---No book found in your preffered gener---"<<endl;
        
        }

}
};

int main(){
    
    Book<int>* book[MAX_Books];
    int bookcount=0;
    char choice;

  book[bookcount++]=new Book<int>("Math","Hassan","Algabra",12);
    book[bookcount++]=new Book<int>("Physics","Ali","Numerical",44);


bool running=true;
    while(running){
        string title,author,genre;
        int id;
        cout<<"1.Add Book"<<endl;
        cout<<"2.View all Book"<<endl;
        cout<<"3.Get book Recommed"<<endl;
        cout<<"4.Reset Recommended Book"<<endl;
        cout<<"5.exit"<<endl;
        cout<<"enter your choice";
        cin>>choice;
    
        cin.ignore();

        switch(choice){
        
        case '1':
        cout<<"Title";
        getline(cin,title);
        cout<<"Auther";
        getline(cin,author);
        cout<<"Id";
        cin>>id;
        cin.ignore();
        cout<<"Genre";
        getline(cin,genre);
       
      
        
        if(bookcount<MAX_Books){
                book[bookcount++]= new Book<int>(title,author,genre,id);
                cout<<"Book added successfully"<<endl;
                
        }else{
            cout<<"Book storage Full";
        }
        break;
        
        case '2':
        if(bookcount==0){
            cout<<"No book in the library"<<endl;
        }else{
            cout<<"All book in the library"<<endl;
        
        for(int i=0;i< bookcount;i++){
            if(!book[i]->recommend){
            book[i]->display();
            }
        }
       
        }
            break;
        
        case '3':{
         User u;
        u.userinput();
        u.recommendedbook( book,bookcount);
        }
   break;
        case '4':
        for(int i=0;i<bookcount;i++){
            book[i]->recommend=false;
        }
        cout<<"All book have been reset"<<endl;
        break;
     case '5':
     cout<<"Exist the program";
     for(int i=0;i< bookcount;i++){
        delete book[i];
     }
  running =false;
  break;
   default:
   cout<<"Invalid choice";
   
        }

        }
      
    
}
