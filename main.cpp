#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void retrievecustomerinfo(string &customer, int &slotnum, char &slotlett); // the functions were passed around by parameter due to the majority of our code holding information in which distributes to another function
void markcustomerseat(int decision, int slotnum, char slotlett, char slots[7][27], string potentialcustomers[7][27]);
int rowLettertoNumber(char slotlett);
void customerinfo(string customer, int slotnum, char slotlett, string potentialcustomers[7][27]);

void roomChart(char s[7][27])
{
    for (int i = 0; i < 7; i++) //this for-loop determines the display of the airplay, the numbers going across, as well as the letters going downwards
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
        for (int j = 0; j < 27; j++)
        {
            cout << s[i][j];
        }
        cout << endl;
    }
}

void FlightChoices() // this is known as the display menu for the flight attender/customer who wants to partake in making a choice of what they would like to choose
{
    cout << "1.) Press this '1' button on your keyboard if you would like to make a reservation" << endl;
    cout << "2.) Press this '2' button on your keyboard if you would like to cancel a reservation" << endl;
    cout << "3.) Press this '3' button on your keyboard if you would like to print your reservation list" << endl;
    cout << "4.) Press this '4' button on your keyboard to print the total number of seats in which" << endl;
    cout << "have been reserved" << endl;
    cout << "5.) Press this '5' button on your keyboard to print the total number of seats in which" << endl;
    cout << "are still available" << endl
         << endl;
}

void ReadCustomerChoice(int &ch) // customer has to enter their choice in order to obtain more information of the specified flight in which they are going for
{
    cout << "Enter your preferred choice: " << endl;
    cin >> ch;
}

void main()
{
    int choice; //certain declarations for the flight attendant's options, such as choice, their name as well as the specific area of the seating
    string crewmember;
    int slotnum;
    char slotlett;
    int seatRow;
    string potentialcustomers[7][27];
    char slots[7][27] = {
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '\\'},
        {'A', char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), ' ', ' ', '\\'}, //the display of the airplane's seats had to be hardcoded in order for the customer to have a birdseye view of what is and isn't available
        {'B', char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), ' ', ' ', '\\'}, // in my case, I used ASCII keys in order to differentiate between what seats are and are not available
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'C', char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), ' ', ' ', '\\'},
        {'D', char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), char(179), ' ', ' ', '\\'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '/'}};

    while (1) // in order for the menu option to display over and over again, I used a while loop in order for the never ending option to contunue unless the user wishes to escape the program
    {
        FlightChoices();
        ReadCustomerChoice(choice);
        if (choice <= 2)
            retrievecustomerinfo(crewmember, slotnum, slotlett);
        customerinfo(crewmember, slotnum, slotlett, potentialcustomers);
        markcustomerseat(choice, slotnum, slotlett, slots, potentialcustomers);
        roomChart(slots);
        system("pause");
    }
}

void customerinfo(string customer, int slotnum, char slotlett, string potentialcustomers[7][27])
{
    potentialcustomers[rowLettertoNumber(slotlett)][slotnum] = customer;
    //cout << "'''''''" << potentialcustomers[rowLettertoNumber(_slotlett)][_slotnum] ;
}

void retrievecustomerinfo(string &customer, int &slotnum, char &slotlett) //the customer information is retrieved after the user enters their name, first or last, or both, and then the row letter as well as the seat number
{
    cout << "Please enter your name then the row letter as well as the seat number" << endl;
    cout << "in which you wish to reserve (FOR EXAMPLE: Michael C 5)" << endl;
    cout << endl;
    cin >> customer >> slotlett >> slotnum;
}

int rowLettertoNumber(char slotlett) // each row is determined by an if-else statment due to the variation of the option and the choice of the user of the program
{
    if (slotlett == 'A')
    {
        return 1;
    }
    else if (slotlett == 'B')
    {
        return 2;
    }
    else if (slotlett == 'C')
    {
        return 4;
    }
    else if (slotlett == 'D')
    {
        return 5;
    }
}

char rowNumbertoLetter(int pick) // these if-else statements are reverting back and forth between user options depending on picking a number or a letter
{
    if (pick == 1)
    {
        return 'A';
    }
    else if (pick == 2)
    {
        return 'B';
    }
    else if (pick == 4)
    {
        return 'C';
    }
    else if (pick == 5)
    {
        return 'D';
    }
}

void markcustomerseat(int decision, int slotnum, char slotlett, char slots[7][27], string potentialcustomers[7][27]) // in this function, it is moreso the most crucial due to the display marking of the seats each time the user books a seat, as well as the heads up notice it gives the user as far as what is left for them to book
{
    int counter = 0;
    if (decision == 1)
    {
        slots[rowLettertoNumber(slotlett)][slotnum] = char(219); // if the user picks the first option, then the program inherits what is entered
    }
    else if (decision == 2)
    {
        slots[rowLettertoNumber(slotlett)][slotnum] = char(219); // the second decision is depedent on whether or not the user wants to cancel a reservation or not
        potentialcustomers[rowLettertoNumber(slotlett)][slotnum] = "";
    }
    else if (decision == 3) // in this case, the reservation list of whoever books a flight is printed out and it can be filled up to however many the 2D array holds, in our case 7 rows, 27 columns
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 27; j++)
            {
                if (slots[i][j] == char(219))
                {
                    cout << potentialcustomers[i][j] << "  ";
                    cout << j << rowNumbertoLetter(i) << endl;
                }
            }
        }
    }
    else if (decision == 4) // if the user picks choice number four, then the total number of seats in which have been booked will show
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 27; j++)
            {
                if (slots[i][j] == char(219))
                {
                    counter++; // i displayed a counter in order for the program to actually be able to tell what slots are left
                }
            }
        }
        cout << "The amount of seats that have been booked: " << counter << endl;
    }
    else if (decision == 5) // in this case, the last choice is for the program to tell the user what seats are still left
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 27; j++)
            {
                if (slots[i][j] == char(219))
                {
                    counter++; //again, a counter has been distributed
                }
            }
        }
        cout << "There are still: " << 64 - counter << " available seats" << endl; //in this case the total number of seats are 64, so however many seats are booked(determined by the counter) will be subtracted from the total number of slots (64)
    }
}
