#include<iostream>
#include<fstream>
#include<string.h>
#include <stdio.h>
#include<iomanip>
#include<vector>
#include "header.h"
using namespace std;
/////////////////////////////////////////////////////USER STRUCT DECLARATION////////////////////////////////////////////////////////
struct customer{
    string firstName;
    string lastName;
    string telephone;
    char ic_number[15]="000000-00-0000"; // primary key

    };

struct room{
    int id=-1; //primary key
    char type[20];
    double price;
    bool reserved =false;
    };

    
struct reservation{
    int id;//primary key 
    char customer_ic[15];
    int room_id;
    string check_in;
    string check_out;
    double charged_price;
    double deposit;
    };
struct date{

    int day;
    int month;
    int year;
};

//////////////////////////////////////////////////////GLOBAL VARIABLE///////////////////////////////////////////////////////////////
vector<room> arrRoom;
vector<reservation> arrReservation;
vector<customer> arrCustomer;

const char separator=' ';
/////////////////////////////////////////////////////FUNCTION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////DATE IMPLEMENTATION////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int check_leap_year(int year)
{
    if( year%4==0 && year%100!=0 || year%400==0 )   //if year is a leap year
    return 1;
    
    else
    return 0;
}
int no_of_days_in_month(int month, int year)
{
    // jan, march, may, july, aug, oct, dec contains 31 days
    if( month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12 )
        return 31;
        
    // april, jun, sept, nov contains 30 days
    if( month==4 || month==6 || month==9 || month==11 )
        return 30;
    
    if( month==2 )
    {
        int n=check_leap_year(year);
        if(n==1)    // if year is a leap year then Feb will contain 29 days, otherwise it contains 28 days
        return 29;
        
        else
        return 28;
    }
}

long long int difference_of_days(int day1,int month1, int year1, int day2, int month2, int year2)
{
    if(year1==year2)
    {
        if(month1==month2)
        {
            if(day1==day2)      //for same dates
                return 0;
            else
                return abs(day1-day2);  //for same year, same month but diff days
        }
        else if(month1<month2)
        {
            int result=0;
            for(int i=month1; i<month2; i++)
            result=result+no_of_days_in_month(i,year1);
                
            if(day1==day2)      //for same year, same day but diff month 
                return result;
            else if(day1<day2)
            {
                result=result+(day2-day1);
                return result;
            }
            else
            {
                result=result-(day1-day2);
                return result;
            }
        }
        else
        {
            int result=0;
            for(int i=month2; i<month1; i++)
            result=result+no_of_days_in_month(i,year1);
                
            if(day1==day2)
                return result;
            else if(day2<day1)
            {
                result=result+(day1-day2);
                return result;
            }
            else
            {
                result=result-(day2-day1);
                return result;
            }
        }
    }
    else if(year1<year2)
    {
        int temp=0;
        for(int i=year1; i<year2; i++)
        {
            if(check_leap_year(i))
                temp=temp+366;
            else
                temp=temp+365;
        }
        
        if(month1==month2)      
        {
            if(day1==day2)      //for same month, same day but diff year
                return temp;
            else if(day1<day2)
                return temp+(day2-day1);
            else
                return temp-(day1-day2);
        }
        else if(month1<month2)
        {
            int result=0;
            for(int i=month1; i<month2; i++)
            result=result+no_of_days_in_month(i,year2);
                
            if(day1==day2)      // for same day, diff year and diff month
                return temp+result;
            else if(day1<day2)
            {
                result=result+(day2-day1);
                return temp+result;
            }
            else
            {
                result=result-(day1-day2);
                return temp+result;
            }
        }
        else
        {
            int result=0;
            for(int i=month2; i<month1; i++)
            result=result+no_of_days_in_month(i,year2);
                
            if(day1==day2)
                return temp-result;
            else if(day2<day1)
            {
                result=result+(day1-day2);
                return temp-result;
            }
            else
            {
                result=result-(day2-day1);
                return temp-result;
            }
        }
    }
    else
    {
        int temp=0;
        for(int i=year2; i<year1; i++)
        {
            if(check_leap_year(i))
                temp=temp+366;
            else
                temp=temp+365;
        }
        
        if(month1==month2)
        {
            if(day1==day2)      // for same day, same month but diff year
                return temp;
            else if(day2<day1)
                return temp+(day1-day2);
            else
                return temp-(day2-day1);
        }
        else if(month2<month1)
        {
            int result=0;
            for(int i=month2; i<month1; i++)
            result=result+no_of_days_in_month(i,year1);
                
            if(day1==day2)
                return temp+result;
            else if(day2<day1)
            {
                result=result+(day1-day2);
                return temp+result;
            }
            else
            {
                result=result-(day2-day1);
                return temp+result;
            }
        }
        else
        {
            int result=0;
            for(int i=month1; i<month2; i++)
            result=result+no_of_days_in_month(i,year1);
                
            if(day1==day2)      // for same day, diff year and diff month
                return temp-result;
            else if(day1<day2)
            {
                result=result+(day2-day1);
                return temp-result;
            }
            else
            {
                result=result-(day1-day2);
                return temp-result;
            }
        }
    }
}
bool validDate(int day, int month, int year, int n){
      if(day<1 || day>n || month<1 || month >12 || year <1)
    {
        
        return false;
    }
    return true;
}



date getDate(){
    int day,month,year;
    int n;

     
    cout<<"Day :";
    cin>>day;
    cout<<"Month (ex: for january write '1') :";
    cin>>month;
    cout<<"Year :";
    cin>>year;
    n=no_of_days_in_month(month,year);

    if(!validDate(day,month,year,n)){
        cout<<"Date is not valid. Please re-enter: "<<endl;
            cout<<"Day :";
            cin>>day;
            cout<<"Month (ex: for january write '1') :";
            cin>>month;
            cout<<"Year :";
            cin>>year;
            n=no_of_days_in_month(month,year);
        
    }
   date newDate;

   newDate.day=day;
   newDate.month=month;
   newDate.year=year;
   return newDate;
    
}

int getDurationOfStay(int startDay,int endDay,int startMonth,int endMonth, int startYear,int endYear){
      // Counting the difference between 2 dates in terms of no of days
    long long int diff = difference_of_days(startDay, startMonth, startYear, endDay, endMonth, endYear);
    return diff;
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////TEMPLATE FOR OUTPUT////////////////////////////////////////////////////
template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw(width) << setfill(separator) << t;
    cout<<"|";
}
//////////////////////////////////////////////////// MENU SELECTION - EDIT TO OUR NEEDS///////////////////////////////////////////////////////////
int getMenu(){
    int input;
    cout<<"=========================================GERRY HOTEL MANAGEMENT========================================="<<endl;
    cout<<"++MAIN MENU++\n\n";
    cout<<" 1.MANAGE ROOM\n 2.ADD RESERVATION\n 3.VIEW ROOM\n 4.VIEW RESERVATION \n 5.VIEW CUSTOMER \n 6.VIEW PAYMENT \n 7.SAVE CHANGES \n 0.EXIT"<<endl;

    cout<<"Please input the wanted operation code[1-6] otherwise  input '0' to exit: ";    cin>>input;
    //simple error checking- later add
    while(input<0 || input>6){
        cout<<"Wrong input!\n Please enter the correct operation code[0-6] : "; cin>>input;
    }
    
    return input;
}
/////////////////////////////////////////////////////////FIND FROM LIST////////////////////////////////////////////////////////////
//will return index 

int findRoom(int room_id ){
    
    //tranverse through every room and find the 
 bool found = false;
 
    for (int i = 0; i < arrRoom.size(); i++)
    {
        if (arrRoom[i].id == room_id)
        {
            
            found = true;
            return i;
            
        }
    }

    return -1;//not found
}

int findCustomer(char ic[] ){
    
    //tranverse through every room and find the 
 bool found = false;
 
    for (int i = 0; i < arrCustomer.size(); i++)
    {
        if (strcmp(arrCustomer[i].ic_number, ic))
        {
            
            found = true;
            return i;
            
        }
    }

    return -1;//not found
}

int findReservation(int id ){
    
    //tranverse through every room and find the 
 bool found = false;
 
    for (int i = 0; i < arrReservation.size(); i++)
    {
        if (arrReservation[i].id == id)
        {
            
            found = true;
            return i;
            
        }
    }

    return -1;//not found
}

//////////////////////////////////////////////////////////GET FROM TEXT FILE////////////////////////////////////////////////////////
//get all room in text file and add into the vector list
void get_arrRoom(){

    ifstream file;
    file.open("room.txt");

    while(!file.eof()){
        room currRoom;
        file>>currRoom.id>>currRoom.type>>currRoom.price>>currRoom.reserved;
        arrRoom.push_back(currRoom); //add the room to the list
    }
    file.close();
}
//get all customer in the text file and add into the vector list
void get_arrCustomer(){
    ifstream file;
    file.open("customer.txt");

    while(!file.eof()){
        customer currCust;
        file>>currCust.firstName>>currCust.lastName>>currCust.telephone>>currCust.ic_number;
        arrCustomer.push_back(currCust); //add the room to the list
    }
    file.close();
}
//get all reservation in the text file and add into the vector list
void get_arrReservation(){
    ifstream file;
    file.open("reservation.txt");
      while(!file.eof()){
       reservation currReservation;
       
       file>>currReservation.id>>currReservation.customer_ic>>currReservation.room_id;
       file>>currReservation.check_in>>currReservation.check_out>>currReservation.charged_price>>currReservation.deposit;
        cout<<currReservation.check_in;
        arrReservation.push_back(currReservation);
    }
    file.close();
}
///////////////////////////////////////////////////////SAVE TO TEXTFILE/////////////////////////////////////////////////////////////

void set_arrRoom(){
    ofstream file;
    file.open("room.txt");
    for(auto i=arrRoom.begin() ; i!= arrRoom.end(); ++i){
        file<<(*i).id<<" " <<(*i).type<<" "<<(*i).price<<" "<<(*i).reserved<<endl;
    }
    file.close();
}

void set_arrCustomer(){
    ofstream file;
    file.open("customer.txt");
    for(auto i=arrCustomer.begin() ; i!= arrCustomer.end(); ++i){
        file<<(*i).firstName<<" " <<(*i).lastName<<" "<<(*i).telephone<<" "<<(*i).ic_number<<endl;
    }
    file.close();
}

void set_arrReservation(){
    ofstream file;
    file.open("reservation.txt");
    for(auto i=arrReservation.begin() ; i!= arrReservation.end(); ++i){
        file<<(*i).id<<" " <<(*i).customer_ic<<" "<<(*i).room_id<<" "<<(*i).check_in<<" "<<(*i).check_out<<" "<< (*i).charged_price<<" "<<(*i).deposit<< endl;
    }
    file.close();
}
//////////////////////////////////////////////////////CUSTOMER MANAGEMENT//////////////////////////////////////////////////////////////////
void add_Customer(){
    customer newCustomer;
    cout<<"Enter the first name: "; cin>>newCustomer.firstName;
    cout<<"Enter the last name: "; cin>>newCustomer.lastName;
    cout<<"Enter the telephone number(without space): "; cin>>newCustomer.telephone;
    cout<<"Enter the ic number in the format(XXXXXX-XX-XXXX): ";cin>>newCustomer.ic_number;
    
    //find duplicate room in the vector list
    if(findCustomer(newCustomer.ic_number)!=-1){
       cout<< "The customer ic is already in the list, Please try again."<<endl;
        return; // end the function
    }

    /// add the room into the vector list
    arrCustomer.push_back(newCustomer);
    cout<<"OPERATION SUCCESS"<<endl;

}

//////////////////////////////////////////////////////RESERVATION MANAGEMENT -ALI//////////////////////////////////////////////////////////
void view_Reservation(){
    cout<<endl<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    printElement("ID",5);
    printElement("CUSTOMER IC", 15);
    printElement("CUSTOMER NAME", 30);
    printElement("ROOM ID",9);
    printElement("CHECK IN",12);
    printElement("CHECK OUT", 12);
    printElement("TOTAL CHARGED",20);
    printElement("DEPOSIT",20);
    printElement("OUTSTANDING FEE",20);
     cout<<endl<<"-------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

    for (int i = 0; i < arrReservation.size(); i++)
    {
        printElement(arrReservation[i].id,5);
        printElement(arrReservation[i].customer_ic,15);
        //find customer based on ic
        int custIndex=findCustomer(arrReservation[i].customer_ic);
        printElement(arrCustomer[custIndex].firstName +" " +arrCustomer[custIndex].lastName ,30);
        printElement(arrReservation[i].room_id,9);
        printElement(arrReservation[i].check_in,12);
        printElement(arrReservation[i].check_out,12);

        //format 2 decimal place money
        char str[20];
        sprintf(str,"RM %.2f",arrReservation[i].charged_price);
        printElement(str,20);
         sprintf(str,"RM %.2f",arrReservation[i].deposit);
         printElement(str,20);
         sprintf(str,"RM %.2f",arrReservation[i].charged_price - arrReservation[i].deposit);
         printElement(str,20);
        cout<<endl;
    }   
    
    cout<<endl<<endl;
    

}

void add_Reservation(){

    cout<<endl<<"--------------------------ADD RESERVATION----------------------"<<endl;
    reservation newReservation;
    cout<<"Enter the customer ic_number: "; cin>>newReservation.customer_ic;
    cout<<"Enter the room id: "; cin>>newReservation.room_id;
    cout<<"Enter the check in date :";
    date check_in =getDate();
    cout<<"Enter the check out date :";
    date check_out=getDate();
    //find for the price of the room and duration of stay
    double roomPrice=arrRoom[findRoom(newReservation.room_id)].price;
    int duration= getDurationOfStay(check_in.day,check_out.day,check_in.month,check_out.month,check_in.year,check_out.year);
    newReservation.charged_price=roomPrice*duration;
    cout<<"Total charges is RM "<<newReservation.charged_price<<endl;
    cout<<"Enter the deposited money: ";cin>>newReservation.deposit;
    //error checking 
    if ((findRoom(newReservation.room_id)== -1) || findCustomer(newReservation.customer_ic)==-1){
        //no record of room or customer in 
        cout<<"Error occur since the room id or customer id is not in the system. Please add the new room/customer if you still want to add the reservation."<<endl;
        return;//exit
    }

    else if(arrRoom[findRoom(newReservation.room_id)].reserved){
        cout<<"The room is already reserved.Please try again"<<endl;
        return;

    }
    
    newReservation.id=arrReservation.size()+1;

    arrReservation.push_back(newReservation);
    //CHANGE THE ROOM CONDITION FROM VACANT TO RESERVED
    arrRoom[findRoom(newReservation.room_id)].reserved=true;

    cout<<"operation successful"<<endl;


}

///////////////////////////////////////////////////////ROOM MANAGEMENT - SIA //////////////////////////////////////////////////////////////
void view_Room(){ 
    string status;
    cout<<endl<<"-------------------------------------------------------------"<<endl;
    printElement("ID",5);
    printElement("ROOM TYPE", 15);
    printElement("PRICE",20);
    printElement("RESERVATION STATUS",20);
    cout<<endl<<"-------------------------------------------------------------"<<endl;

    for (auto i = arrRoom.begin(); i != arrRoom.end(); i++)
    {
        printElement((*i).id,5);
        printElement((*i).type,15);
        //format 2 decimal place money
        char str[20];
        sprintf(str,"RM %.2f",(*i).price);
        printElement(str,20);
        if((*i).reserved==true){
             status="RESERVED";
        }
        else{
             status="VACANT";
        }
        printElement(status,20);
        cout<<endl;
    }   
    
    cout<<endl<<endl;
    
}
void add_Room(){
    cout<<endl<<"--------------------------ADD ROOM----------------------"<<endl;
    room newRoom;
    cout<<"Enter the room id: "; cin>>newRoom.id;
    cout<<"Enter the type of room: "; cin>>newRoom.type;
    cout<<"Enter the price of room (RM): "; cin>>newRoom.price;
    
    //find duplicate room in the vector list
    if(findRoom(newRoom.id)!=-1){
       cout<< "The room id is already in the list, Please try again with different id"<<endl;
        return; // end the function
    }

    /// add the room into the vector list
    arrRoom.push_back(newRoom);
    cout<<"OPERATION SUCCESS"<<endl;

}

void delete_Room(){
     cout<<endl<<"--------------------------DELETE ROOM----------------------"<<endl;
     int target_id;
     cout<<"Enter the room id that you wish to delete: "; cin>> target_id;
     int index=findRoom(target_id);
     if (index==-1){
        cout<<"The id is not in the list. Please try again"<<endl;

     }

     //proceed to delete the room
     arrRoom.erase(arrRoom.begin()+ index);
     cout<<"Successfully delete"<<endl;

}

///////////////////////////////////////////////////////MAIN FUNCTION////////////////////////////////////////////////////////////////
int main(){
    // must be at start to get the current data from file to the vector list
    ///
    get_arrCustomer();
    get_arrReservation();
    get_arrRoom();

    while(true){
        int selection=getMenu();
        if (selection==0)
        {
            break;
        }

        else if (selection==1){
            add_Room();

            set_arrRoom(); //to update the textfile
            cout<<"complete save";
        }

        else if (selection==3){
            view_Room();
        }

        else if (selection==4){
            view_Reservation();
        }
        else if (selection==5){
            add_Reservation();
        }

    //use all the set_arrXXXXX() to write back from the vector list to the textfile. Happy coding i guess. Please don't be ambitious for 5% project.Thenks
        
    }
    




   



    return 0;
}