#include <iostream>
using namespace std;

int WhoIsOlder(int month1, int day1, int year1, int month2, int day2, int year2){
    int result ;
    if(year1 > year2){
        result = 2 ;
    }
    else if(year2 > year1){
        result = 1 ;
    }
    else if(year1 == year2){
            if(month1 > month2){
            result = 2 ;
        }
        else if(month2 > month1){
            result = 1 ;
        }
        else if(month1 == month2){
                if(day1 > day2){
                result = 2 ;
            }
            else if(day1 > day2){
                result = 1 ;
            }
            else if(day1 == day2){
                result = 3 ;
            }
        }
    }
    else{
        result = 0 ;
    }
return result ;
}

bool validDate(string input){
    if(input.length() != 10){
        return false ;
    }
    if(input.at(2) != '/' || input.at(5) != '/'){ //make sure the slashes are in the right place
        return false;
    }
    if(!isdigit(input.at(0)) ||!isdigit(input.at(1)) ||!isdigit(input.at(3)) ||!isdigit(input.at(4))){
        //check the month and days are digits
        return false;
    }
    if(!isdigit(input.at(6)) ||!isdigit(input.at(7)) ||!isdigit(input.at(8)) ||!isdigit(input.at(9))){
        //check the year is made of digits
        return false;
    }

    if (0 >= stoi(input.substr(0,2)) || 12 < stoi(input.substr(0,2))){ //make sure month is between 1&12
        return false;
    }
    if (0 >= stoi(input.substr(3,2)) || 31 < stoi(input.substr(3,2))){ //make sure day is between 01&31
        return false;
    }
    else{
    return true;
    }
}



int main(){
    // int result ;
    int year1, year2, month1, month2, day1, day2 ;
    string birthday1, birthday2 ;

    cout << "Please enter the first person's birthday (MM/DD/YYYY)" << endl;
    cin >> birthday1 ;

    cout << "Please enter the second person's birthday (MM/DD/YYYY)" << endl;
    cin >> birthday2 ;

    if(validDate(birthday1) == true && validDate(birthday2) == true){
        day1 = stoi(birthday1.substr(0,2)) ;
        month1 = stoi(birthday1.substr(3,2)) ;
        year1 = stoi(birthday1.substr(6,4)) ;

        day2 = stoi(birthday2.substr(0,2)) ;
        month2 = stoi(birthday2.substr(3,2)) ;
        year2 = stoi(birthday2.substr(6,4)) ;
        
        WhoIsOlder(month1, day1, year1, month2, day2, year2) ;

        switch(WhoIsOlder(month1, day1, year1, month2, day2, year2)){
            case 1:
                cout << "Person 1 is older." << endl;
                return 0;
                break;
            case 2:
                cout << "Person 2 is older." << endl;
                return 0;
                break;
            case 3:
                cout << "Both people are the same age." << endl;
                return 0;
                break;
            case 0:
                cout << "Please enter a valid input." << endl;
                return 0;
                break;

        }

    }
return 0;
}

