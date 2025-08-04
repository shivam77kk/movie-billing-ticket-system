// Movie Ticket Billing System :-
// Made by :
//   -> Shivam Tonpe
//   -> Sayum Dey
//   -> Tushar Poojari
//   -> Sahil Hode

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string Logged_in_user, user_full_name;
string movies[10] = {
    "Singham Again",
    "Bhool Bhulaiya 3",
    "Avengers",
    "Housefull 5",
    "Raid 2",
    "Demon Slayer Movie",
    "Stree 2",
    "Sitaare Zameen Par",
    "Marco",
    "MI vs CSK"};

string showTimes[4] = {"10:00 AM", "1:00 PM", "4:00 PM", "7:00 PM"};

int seatAvailable[10][4] = {
    {50, 60, 80, 55},
    {50, 75, 55, 50},
    {75, 20, 52, 124},
    {50, 55, 69, 90},
    {50, 50, 55, 60},
    {50, 60, 80, 55},
    {50, 75, 55, 50},
    {75, 20, 52, 124},
    {50, 55, 69, 90},
    {50, 50, 55, 60}};

int movieStats[10] = {0};

class MovieBillingSystem
{
private:
    int Movie_Index, Time_index, Ticket_count;
    string date, seat_type, Payment_method;
    double Price_per_ticket;

public:
    void selectMovie()
    {
        cout << "\n***********************************************************************************************************************\n";
        cout << "\n\t  Available Movies:\n";
        for (int i = 0; i < 10; i++)
        {
            cout << i + 1 << ". " << movies[i] << endl;
        }
        cout << "  Select a movie: ";
        cin >> Movie_Index;
        Movie_Index--;
    }

    void selectTime()
    {
        cout << "\n***********************************************************************************************************************\n";
        cout << "\n\t  Available Show Times:\n";
        for (int i = 0; i < 4; i++)
        {
            cout << i + 1 << ". " << showTimes[i] << " (" << seatAvailable[Movie_Index][i] << " seats left)\n";
        }
        cout << "  Select a time: ";
        cin >> Time_index;
        Time_index--;
    }

    void selectDate()
    {
        cout << "\n***********************************************************************************************************************\n";
        cout << "  \tDate for movie booking: \n";
        cout << "  Enter date (DD/MM/YYYY): ";
        cin >> date;
        cout << "  You have entered date: " << date;
    }

    void chooseSeat()
    {
        int choice;
        cout << "\n***********************************************************************************************************************\n";
        cout << "\n  Select Seat Types:\n";
        cout << "  1. VIP (3000)\n  2. Golden (1000)\n  3. Silver (400)\n  Choose seat type: ";
        cin >> choice;

        if (choice == 1)
        {
            seat_type = "VIP";
            Price_per_ticket = 3000;
        }
        else if (choice == 2)
        {
            seat_type = "Golden";
            Price_per_ticket = 1000;
        }
        else if (choice == 3)
        {
            seat_type = "Silver";
            Price_per_ticket = 400;
        }
        else
        {
            cout << "  Invalid choice ! ";
        }
    }

    void chooseTicket_count()
    {
        cout << "\n***********************************************************************************************************************\n";
        cout << "  \tTotal Tickets: \n";
        cout << "  Enter number of tickets: ";
        cin >> Ticket_count;

        if (Ticket_count > seatAvailable[Movie_Index][Time_index])
        {
            cout << "  Not enough seats available.\n";
            Ticket_count = 0;
        }
        else
        {
            seatAvailable[Movie_Index][Time_index] -= Ticket_count;
            movieStats[Movie_Index] += Ticket_count;
        }
    }

    void selectPayment()
    {
        cout << "\n***********************************************************************************************************************\n";
        int method;
        cout << "  Payment Methods:\n  1. Debit/Credit Card  \n  2. UPI Payment  \n  3. Cash at counter  \n  Choose method: ";
        cin >> method;

        if (method == 1)
        {
            Payment_method = "Card";
        } 
        else if (method == 2)
        {
            Payment_method = "UPI Payment";
        }
        else
        {
            Payment_method = "Cash at counter";
        }
    }

    void calculatePrice()
    {
        double total = Price_per_ticket * Ticket_count;
        double discount = total * 0.05;
        double finalTotal = total - discount;

        cout << "  Total after 5% discount: " << finalTotal << endl;
        saveReceipt(finalTotal);
    }

    void saveReceipt(double amount)
    {
        cout << "\n***********************************************************************************************************************\n";
        ofstream file("tickets_" + Logged_in_user + ".txt", ios::app);
        file << "\n  --- Ticket Receipt ---\n";
        file << "  User: " << user_full_name << endl;
        file << "  Movie: " << movies[Movie_Index] << endl;
        file << "  Time: " << showTimes[Time_index] << endl;
        file << "  Date: " << date << endl;
        file << "  Seat Type: " << seat_type << endl;
        file << "  Total Tickets: " << Ticket_count << endl;
        file << "  Payment: " << Payment_method << endl;
        file << "  Amount Paid: " << amount << endl;
        file << "-----------------------\n";
        file.close();
        cout << "  Receipt saved sucessfully!\n";
    }

    void viewReceipt()
    {
        ifstream file("tickets_" + Logged_in_user + ".txt");
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
    }

    void showStats()
    {
        cout << "\n  --- Booking Stats ---\n";
        for (int i = 0; i < 10; i++)
        {
            cout << movies[i] << ": " << movieStats[i] << " tickets booked\n";
        }
    }
};

bool login()
{
    string username, password, u, p, name;
    cout << "  Username: ";
    cin >> username;
    cout << "  Password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> u >> p)
    {
        file.ignore();
        getline(file, name);
        if (u == username && p == password)
        {
            Logged_in_user = u;
            user_full_name = name;
            return true;
        }
    }
    return false;
}

void registerUser()
{
    cout << "\n***********************************************************************************************************************\n";
    cout << "  \t========== Register now ==========\n";
    string username, password, confirm, name;
    cout << "  Full Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "  Choose Username: ";
    cin >> username;
    cout << "  Choose Password: ";
    cin >> password;
    cout << "  Confirm Password: ";
    cin >> confirm;

    if (password != confirm)
    {
        cout << "  Passwords do not match.\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << password << " " << name << "\n";
    cout << "  Registered saved successfully!\n";
}

void userMenu()
{
    MovieBillingSystem system;
    int choice;
    do
    {
        cout << "\n***********************************************************************************************************************\n";
        cout << "\n  ----------- Welcome, " << Logged_in_user << " -----------\n";
        cout << "  1. Book a new ticket\n  2. View My Tickets Reciept\n  3. View Stats\n  4. Logout\n  Choose option: ";
        cin >> choice;

        if (choice == 1)
        {
            system.selectMovie();
            system.selectTime();
            system.selectDate();
            system.chooseSeat();
            system.chooseTicket_count();
            system.selectPayment();
            system.calculatePrice();
        }
        else if (choice == 2)
        {
            system.viewReceipt();
        }
        else if (choice == 3)
        {
            system.showStats();
        }
    } while (choice != 4);
}

int main()
{
    int option;
    do
    {
        cout << "\n***********************************************************************************************************************\n";
        cout << "\n  ------------ Movie Ticket System ------------ \n";
        cout << "  1. Login\n  2. Register\n  3. Exit\n  Choose: ";
        cin >> option;

        if (option == 1)
        {
            if (login())
            {
                cout << "  Login successful!\n";
                userMenu();
            }
            else
            {
                cout << "  Invalid login.\n";
            }
        }
        else if (option == 2)
        {
            registerUser();
        }
    } while (option != 3);
    cout << "\n***********************************************************************************************************************\n";
    cout << "  \n\tExiting..... Goodbye!\n";
    return 0;
}
