#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

// Forward declaration of classes
// Declaration of class representing a room
class Room;
// Declaration of base class representing a person 
class Person;
// Declaration of class representing a student 
class Student;
// Declaration of class representing an admin
class Admin;

// Base class representing a person
class Person
{
protected:
    // Name of the person
    string name;
    // Roll number of the person   
    string rollNumber;
    // Email of the person
    string email;
public:
    // Constructor to initialize person details
    Person(string n, string roll, string mail) : name(n), rollNumber(roll), email(mail) {}
    // Virtual destructor for polymorphism
    virtual ~Person() {}
    // Friend function to display person details                                                                 
    friend void displayPersonDetails(const Person& person);
};

// Function to display details of a person
void displayPersonDetails(const Person& person)
{
    // Displaying name
    cout << "Name: " << person.name << endl;
    // Displaying roll number
    cout << "Roll Number: " << person.rollNumber << endl;
    // Displaying email
    cout << "Email: " << person.email << endl;
}

// Class representing a Student
class Student : public Person
{
public:
    // Constructor to initialize student details
    Student(string n, string roll, string mail) : Person(n, roll, mail) {}
};

// Class representing a Room
class Room
{
private:
    // Room number
    int roomNumber;
    // Vector to store occupants (students)       
    vector<Student> occupants;

public:
    // Constructor to initialize room number
    Room(int number) : roomNumber(number) {}

    // Method to get room number
    int getRoomNumber() const
    {
        return roomNumber;
    }

    // Method to check if room is full
    bool isFull() const
    {
        return occupants.size() >= 4;
    }

    // Method to add occupant to the room
    void addOccupant(Student student)
    {
        // Check if room is not full
        if (!isFull())
        {
            // Add student to the room
            occupants.push_back(student);
        }
    }
};

// Class representing Hostel
class Hostel
{
private:
    // Vector to store rooms
    vector<Room> rooms;

public:
    Hostel()
    {
        // Initialize rooms
        for (int floor = 1; floor <= 3; ++floor)
        {
            for (int roomNumber = 10; roomNumber <= 14; ++roomNumber)
            {
                // Create rooms for each floor
                rooms.push_back(Room(floor * 100 + roomNumber));
            }
        }
    }

    // Display available rooms
    void displayAvailableRooms() const
    {
        cout << "Available Rooms:\n";
        for (vector<Room>::const_iterator it = rooms.begin(); it != rooms.end(); ++it)
        {
            const Room& room = *it;
            // Check if room is not full
            if (!room.isFull())
            {
                // Display room number
                cout << "Room " << room.getRoomNumber() << endl;
            }
        }
    }

    // Display all rooms
    void displayAllRooms() const
    {
        cout << "All Rooms:\n";
        for (vector<Room>::const_iterator it = rooms.begin(); it != rooms.end(); ++it)
        {
            const Room& room = *it;
            // Display room number
            cout << "Room " << room.getRoomNumber() << endl;
        }
    }

    // Display records
    void displayRecords() const
    {
        ifstream recordsFile("records.txt", ios::in);
        cout << "Displaying Records:\n";
        // Check if file is open
        if (recordsFile.is_open())
        {
            string line;
            while (getline(recordsFile, line))
            {
                // Display each line of records
                cout << line << endl;
            }
            // Close records file
            recordsFile.close();
        }
        else
        {
            // Display message if file cannot be opened
            cout << "No data found.\n";
        }
    }

    // Book a room
    Room* bookRoom(Student& student)
    {
        string name, roll, email;
        int payment;
        cout << "Enter your name: ";
        getline(cin >> ws, name);
        cout << "Enter your roll number: ";
        cin >> roll;
        cout << "Enter your email: ";
        cin >> email;
        displayAvailableRooms();
        int roomNumber;
        cout << "Enter room number you want to book: ";
        cin >> roomNumber;

        for (vector<Room>::iterator it = rooms.begin(); it != rooms.end(); ++it)
        {
            Room& room = *it;
            if (room.getRoomNumber() == roomNumber && !room.isFull())
            {
                while (true)
                {
                    cout << "Per Semester Booking Charges is: 36000\n";
                    cout << "Enter your payment here: \n";
                    cin >> payment;
                    if (payment != 36000)
                    {
                        cout << "Please make a full payment\n";
                    }
                    else
                    {
                        // Create student object
                        student = Student(name, roll, email);
                        // Add student to the room    
                        room.addOccupant(student);
                        // writing in append mode           
                        ofstream recordsFile("records.txt", ios::app);
                        // Check if file is open
                        if (recordsFile.is_open())
                        {
                            recordsFile << "Name: " << name << ", Roll Number: " << roll << ", Email: " << email << ", Room Number: " << roomNumber << endl; // Write record to file
                            recordsFile.close();                                                                                                             // Close records file
                        }
                        else
                        {
                            // Display message if file cannot be opened
                            cout << "Unkown Error\n";
                        }
                        // Return booked room
                        return &room;
                    }
                }
            }
        } // Display message if room cannot be booked
        cout << "Invalid room number or room is already full.\n";
        cout << "press any key to continue..." << "\n";
        _getch();
        system("cls");
        return nullptr;
    }

    // Add a room
    bool addRoom(int roomNumber)
    {
        for (vector<Room>::const_iterator it = rooms.begin(); it != rooms.end(); ++it)
        {
            const Room& room = *it;
            if (room.getRoomNumber() == roomNumber)
            {
                // Display message if room already exists
                cout << "Room " << roomNumber << " is already available.\n";
                // Return false indicating room addition failed
                return false;
            }
        }
        // Add room to the hostel
        rooms.push_back(roomNumber);
        // Display message indicating room addition successful                         
        cout << "Room " << roomNumber << " added successfully.\n";
        // Return true indicating room addition successful
        return true;
    }

    // Delete a room
    void deleteRoom(int roomNumber)
    {
        for (vector<Room>::iterator it = rooms.begin(); it != rooms.end(); ++it)
        {
            Room& room = *it;
            if (room.getRoomNumber() == roomNumber)
            {
                // Erase room from the vector
                rooms.erase(it);
                // Display message indicating room deletion successful                                          
                cout << "Room " << roomNumber << " deleted successfully.\n";
                return;
            }
        }
        // Display message if room not found
        cout << "Room " << roomNumber << " not found.\n";
    }
};

// Class representing Admin
class Admin
{
private:
    // Admin username
    const string username = "admin";
    // Admin password
    const string password = "admin123";

public:
    // Method to authenticate admin
    bool authenticate(string inputUsername, string inputPassword) const
    {
        // Return true if username and password match
        return (inputUsername == username && inputPassword == password);
    }

    // Function to display admin menu
    void displayAdminMenu() const
    {
        cout << "\nAdmin Options:\n";
        cout << "1. Add Room\n";
        cout << "2. Delete Room\n";
        cout << "3. Display All Rooms\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
    }

    // Admin operations
    void adminOptions(Hostel& hostel)
    {
        string choice;
        do
        {
            displayAdminMenu();
            cin >> choice;
            if (choice == "1") {
                int roomNumber;
                cout << "Enter room number to add: ";
                cin >> roomNumber;
                //     // Add room
                hostel.addRoom(roomNumber);
            }
            else if (choice == "2") {
                int roomNumber;
                cout << "Enter room number to delete: ";
                cin >> roomNumber;
                //     // Delete room
                hostel.deleteRoom(roomNumber);
            }
            else if (choice == "3") {
                // Display all rooms
                hostel.displayAllRooms();
                cout << "press any key to continue..." << "\n";
                _getch();
                system("cls");
            }
            else if (choice == "4") {
                cout << "Exiting admin options...\n";
                system("cls");
            }
            else {
                cout << "Invalid choice. Please try again.\n";
                cout << "press any key to continue..." << "\n";
                _getch();
                system("cls");
            }
        } while (choice != "4");
    }
};

// Function to display menu
void displayMenu()
{
    cout << "\n\t***********************************************\n";
    cout << "\t*                 Menu                        *\n";
    cout << "\t*-------------------------------------------- *\n";
    cout << "\t*  1. Display Available Rooms                 *\n";
    cout << "\t*  2. Book a Room                             *\n";
    cout << "\t*  3. Display Records                         *\n";
    cout << "\t*  4. Admin Options                           *\n";
    cout << "\t*  5. Exit                                    *\n";
    cout << "\t***********************************************\n\n";
    cout << "Enter your choice: ";
}

int main()
{
    cout << "\n";
    cout << R"(
  ______       _____ _______   _    _  ____   _____ _______ ______ _      
|  ____/\    / ____|__   __| | |  | |/ __ \ / ____|__   __|  ____| |     
| |__ /  \  | (___    | |    | |__| | |  | | (___    | |  | |__  | |     
|  __/ /\ \  \___ \   | |    |  __  | |  | |\___ \   | |  |  __| | |     
| | / ____ \ ____) |  | |    | |  | | |__| |____) |  | |  | |____| |____ 
|_|/_/    \_\_____/   |_|    |_|  |_|\____/|_____/   |_|  |______|______|
                                                                         
)";

    cout << "\n\t\t*WElCOME TO FAST HOSTEL SYSTEM*\n\n";

    PlaySound(TEXT("Start.wav"), NULL, SND_FILENAME | SND_SYNC);

    // Create Hostel object
    Hostel hostel;

    string choice;
    do
    {
        displayMenu();
        cin >> choice;
        if (choice == "1") {
            hostel.displayAvailableRooms();
            cout << "press any key to continue..." << "\n";
            _getch();
            system("cls");
        }
        else if (choice == "2") {
            //  Implement booking a room
        //     // Initialize with empty values
            Student student("", "", "");
            //     // Book a room           
            Room* bookedRoom = hostel.bookRoom(student);
            if (bookedRoom)
            {
                //         // Display message if room booked successfully
                cout << "Room " << bookedRoom->getRoomNumber() << " booked successfully.\n";
                cout << "press any key to continue..." << "\n";
                _getch();
                system("cls");
            }
        }
        else if (choice == "3") {
            hostel.displayRecords(); // Display records
            cout << "press any key to continue..." << "\n";
            _getch();
            system("cls");
        }
        else if (choice == "4") {
            //     int a;
            while (true) {
                // Admin authentication
                string username, password;
                cout << "Enter admin username: ";
                cin >> username;
                cout << "Enter admin password: ";
                cin >> password;

                Admin admin;
                if (admin.authenticate(username, password))
                {
                    //         // Admin authenticated
                    //         // Perform admin options
                    admin.adminOptions(hostel);
                }
                else
                {
                    //         // Display message if authentication failed
                    cout << "Invalid Username Or Password!...\n";
                    cout << "press any key to continue..." << "\n";
                    _getch();
                    system("cls");
                    continue;
                }
            }
        }
        else if (choice == "5") {
            cout << "Thank you, See you next time...\n";
            PlaySound(TEXT("End.wav"), NULL, SND_FILENAME | SND_SYNC);
        }
        else {
            cout << "Invalid choice. Please try again.\n";
            cout << "press any key to continue..." << "\n";
            _getch();
            system("cls");
        }
    } while (choice != "5");

    return 0;
}