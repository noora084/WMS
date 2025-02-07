#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std :: chrono ;
using namespace std ; 
struct Item{
    string name ; 
    int count ; 
    int price ; 
};
void readrow(string line , Item &aItem){
    stringstream ss(line);
    ss >> aItem.name >> aItem.count >> aItem.price ; 
}
int load(Item *items , int maxsize){
    fstream myfile("anbar.txt" , ios::in) ; 
    string row ; 
    int i = 0 ; 
    while(getline(myfile , row) &&i<maxsize){
        readrow(row, items[i]) ; 
        i++ ; 
    } 
    myfile.close() ; 
    return i ; 
}
void update(Item items[] , int size){
    ofstream myfile("anbar.txt" , ios::out) ;
    for(int i = 0 ; i<size ; i++){
        myfile<<items[i].name << " " << items[i].count << " " << items[i].price<<"T" <<endl ; 
    }
    myfile.close() ;
}
string to_lower(string s){        
    for(char &c : s)
        c = tolower(c);
    return s;
}
void addNEWITEM(string&itemname , int price){
    fstream myfile("anbar.txt" , ios::app) ;
    myfile<<itemname << " " << 1 << " " << price << "T" << endl ; 
    myfile.close() ; 
}
void adding(string &itemname , int&price){
    bool found = false ; 
    const int maxsize = 100 ;
    Item *items= new Item[maxsize];
    int itemcount= load(items , maxsize);
    for(int i = 0 ; i<itemcount ; i++){
        if(to_lower(items[i].name) == to_lower(itemname)){
            items[i].count++;
            found = true ; 
            break ; }
    }
    if(found){
        update(items , itemcount) ; 
        cout<< "added successfully!" << endl ; 
    }
    else{
        addNEWITEM(itemname , price) ; 
        cout<< "added successfully!" << endl ; 
    } 
}
void buying(string &itemname, int &userwallet){
    bool found = false ; 
    const int maxsize = 100 ;
    Item *items= new Item[maxsize];
    int itemcount= load(items , maxsize);
    for(int i = 0 ; i<itemcount ; i++){
        if(to_lower(items[i].name) == to_lower(itemname)){
            found = true ; 
            if(userwallet<items[i].price){
                cout<< "you dont have enough money!"; 
                break ; 
            }if(items[i].count == 0){
                cout<< "we dont have that anymore." ; 
                break ; 
            }if(userwallet>=items[i].price){
                items[i].count-- ; 
                userwallet-=items[i].price ; 
                update(items , itemcount) ; 
                cout<< "done! remaining money: " <<userwallet ; 
                break ; 
            }
        }
    }
    if(!found)
        cout<< "item not found!" ; 
}
void remove(string &itemname){
    bool found = false ; 
    const int maxsize = 100 ;
    Item *items= new Item[maxsize];
    int itemcount= load(items , maxsize); 
    for(int i = 0 ; i<itemcount ; i++){
        if(to_lower(items[i].name) == to_lower(itemname)){
            found = true ; 
            items[i].count-- ;  
            update(items , itemcount) ; 
            cout<< "done!" << items[i].name << " removed." ; 
            break ; 
        }
    }
    if(!found)
        cout<< "item not found!" ; 
}
void rename(string &itemname, string &newItemname){
    bool found = false ; 
    const int maxsize = 100 ;
    Item *items= new Item[maxsize];
    int itemcount= load(items , maxsize); 
    for(int i = 0 ; i<itemcount ; i++){
        if(to_lower(items[i].name) == to_lower(itemname)){
            found = true ; 
            string name = items[i].name ; 
            items[i].name = newItemname ;  
            update(items , itemcount) ; 
            cout<< "done!" << name << " renamed." ; 
            break ; 
        }
    }
    if(!found)
        cout<< "item not found!" ; 
}
void changePrice(string &itemname, int newItemPrice){
    bool found = false ; 
    const int maxsize = 100 ;
    Item *items= new Item[maxsize];
    int itemcount= load(items , maxsize); 
    for(int i = 0 ; i<itemcount ; i++){
        if(to_lower(items[i].name) == to_lower(itemname)){
            found = true ; 
            items[i].price = newItemPrice ;  
            update(items , itemcount) ; 
            cout<< "done!" << items[i].name << " has changed." ; 
            break ; 
        }
    }
    if(!found)
        cout<< "item not found!" ; 
}
void show(string &itemname){
    bool found = false ; 
    const int maxsize = 100 ;
    Item *items= new Item[maxsize];
    int itemcount= load(items , maxsize); 
    for(int i = 0 ; i<itemcount ; i++){
        if(to_lower(items[i].name) == to_lower(itemname)){
            found = true ;  
            cout << items[i].name << " " << items[i].count << " " << items[i].price << "T";
            break;
        }
    }
    if(!found)
        cout<< "item not found!" ; 
}
void timing(auto&start, auto&end, string&mission){
    fstream myfile("logging.txt" , ios:: app) ; 
    chrono::duration<float> duration = end - start ;
    myfile << duration.count() << "s " << "for " << mission << "ing."<< endl  ; 
    myfile.close() ; 
}
int main(){
    string nonAdmin1 = "sara" ; 
    string nonAdmin3 = "zahra" ; 

    int userwallet1 = 200 ; 
    int userwallet3 = 0 ; 
    
    string Admin1 = "noora"; 
    string Admin2 = "roza";

    cout<< "Hello! welcome to our shop!" << endl ; 
    string username ; 
    cout<< "Enter your username: " ; 
    cin >> username ; 

    int userPassword ; 
    cout<< "Enter your password: " ; 
    cin >> userPassword ;
    //admin
    if((username == "noora" && userPassword== 100) || username == "roza" && userPassword==101){
        cout<<"welcome " << username << ", " << "what do you want to do? " ;
        while(true){
            string mission; 
            cin>> mission;
            if(mission == "0"){
                cout<< "hope you visit us soon! bye." ; 
                exit(0) ; 
            }
            for(int i = 0 ; i<mission.length() ; i++)
                mission[i] = tolower(mission[i]) ; 
            if(mission == "add"){
            auto start = chrono:: high_resolution_clock:: now() ;
            string item  ; int price ; 
            cin>> item >> price ; 
            cout<< "[$]add ITEM PRICE..." ; 
            adding(item , price) ;
            auto end = chrono:: high_resolution_clock:: now() ;
            timing(start , end , mission) ;
            cout << "what else do you want to do?(0 to exit) " ;  
            }     
            else if(mission == "remove"){
                auto start = chrono:: high_resolution_clock:: now() ;
                string itemname ; 
                cin >> itemname ;
                cout<< "[$]remove ITEM..." ;  
                remove(itemname) ; 
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ; 
                cout << endl <<"what else do you want to do?(0 to exit) " ;  
            }
            else if(mission == "price"){
                auto start = chrono:: high_resolution_clock:: now() ;
                string newitemname; int newprice ; 
                cin >> newitemname >> newprice ; 
                cout<< "[$]price ITEM NEWPRICE..." ; 
                changePrice(newitemname , newprice) ; 
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ; 
                cout << endl <<"what else do you want to do?(0 to exit) " ;  
            }
            else if(mission== "rename"){
                auto start = chrono:: high_resolution_clock:: now() ;
                string newitem , item ; 
                cin >> item >>newitem ; 
                cout<< "[$]rename ITEM NEWITEM..." ; 
                rename( item , newitem ) ; 
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ;
                cout << endl <<"what else do you want to do?(0 to exit) " ;  
 
            }
            else if(mission == "credit"){
                string user ; int amount ; 
                cin >> user >> amount ;
                auto start = chrono:: high_resolution_clock:: now() ;
                for(int i = 0 ; i<user.length() ; i++)
                    user[i] = tolower(user[i]) ;
                cout<< "[$]credit USER AMOUNT..."<<endl ; 
                if(user=="sara"){
                    userwallet1+= amount ; 
                    cout<< "done!" << endl ;
                }
                else if(user=="zahra"){
                    userwallet3+= amount ; 
                    cout<< "done!" << endl ;
                }else
                cout << "user not found!" << endl ;
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ; 
                cout <<"what else do you want to do?(0 to exit) " ;  
            }
            else
                cout<< "you dont have access to use that.what else do you want to do?(0 to exit) " ; 
        }
    }
    //non admin
    else if((username == "sara" && userPassword== 123) || (username == "zahra"&& userPassword==566)){
        cout<< "welcome " << username << "," << "what do you want to do?(0 to exit) " ;
        while(true){
            string mission ;
            cin>> mission ;
            if(mission == "0"){
                cout<< "hope you visit us soon! bye." ; 
                exit(0) ; 
            }
            for(int i = 0 ; i<mission.length() ; i++)
                mission[i] = tolower(mission[i]) ;
            if(mission== "balance"){
                auto start = chrono:: high_resolution_clock:: now() ;
                cout << "[#]balance..."  ;  
                if(username=="sara")
                cout<< "you have " << userwallet1 << "T" ; 
                if(username=="zahra")
                cout<< "you have " << userwallet3 << "T" ; 
                cout << endl <<"what else do you want to do?(0 to exit) " ; 
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ;
            }
            else if(mission=="show"){
                auto start = chrono:: high_resolution_clock:: now() ;
                string name ;
                cout << "[#]show ITEM..."  ;  
                cin>> name ; 
                show(name);
                cout << endl <<"what else do you want to do?(0 to exit) " ; 
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ; 
            }
            else if(mission=="buy"){
                auto start = chrono:: high_resolution_clock:: now() ;
                string itemName;
                cin >> itemName;
                cout << "[#]buy ITEM..."  ; 
                if(username=="zahra"){
                    buying(itemName, userwallet3);
                } else if (username=="sara") {
                    buying(itemName, userwallet1);
                }
                cout << endl <<"what else do you want to do?(0 to exit) " ; 
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ; 
            } 
            else if(mission=="help"){
                auto start = chrono:: high_resolution_clock:: now() ;
                string command ; 
                cout<< "[#]help..." ; 
                cin >> command ;
                for(int i = 0 ; i<command.length() ; i++)
                    command[i] = tolower(command[i]) ; 
                if(command=="show")
                    cout<< "you can see all the products we have by using *show* " ; 
                else if(command=="buy")
                    cout<< "you can buy anything we have by using *buy* " ; 
                else if(command=="balance")
                    cout<< "you can see your wallet by using *balance* " ;
                else
                    cout<< "you are not allowed to." ; 

                cout << endl <<"what else do you want to do?(0 to exit) " ; 
                auto end = chrono:: high_resolution_clock:: now() ;
                timing(start , end , mission) ; 
            }
            else
            cout<< "you dont have access to use that.what else do you want to do?(0 to exit) " ;          
        }
        
    }
    else
        cout << "username and password do not match! run the program again." ;  
}