/* Read indata flights file and save it
Read indata booking file and save it
For each booking in the booking list
Find the flights list which match the booking
then allocate a seat (find a free seat), mark a seat booked
Then print the ticket to a ticket file */
/*-----------------------------------------------------------------------
Projectname:
Description:
Date: 15/11-2023
Name: Arwen Book
Contact: guardianbardess@gmail.com

-------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <cstdio>
#include <fstream>

using namespace std;

class Flight
{
private:
    int flightnr;       /* The flightnumber*/ 
    string departure;   /* Departure aiport*/
    string date;        /*Departure date*/
    string time;        /* Departure time*/
    string destination; /* Destination airport*/
    int nrfcseats;      /* Firstclass seats*/
    int *fcflags;       /* First class flags*/
    int nrbcseats;      /* Businessclass seats*/
    int *bcflags;       /* Businessclass flags*/
    int nrecseats;      /* Econonmy class seats*/
    int *ecflags;       /*Economyclass flags*/
    int nroseats;       /*Occupied seats on the flight */

public: /*Public acces specifier*/
    Flight(int flightnr, string departure, string destination, string date, string time, int nrfcseats, int nrbcseats, int nrecseats)
    {
        this->date.assign(date);
        this->time.assign(time);
        this->fcflags = new int[sizeof(int) * 7];
        this->nrbcseats = nrbcseats;
        this->bcflags = new int[sizeof(int) * 7];
        this->nrecseats = nrecseats;
        this->ecflags = new int[sizeof(int) * 7];
    }

    /*getters for the class flight*/

    int getfligthnr()
    {
        return flightnr;
    }
    string getDeparture()
    {
        return departure;
    }
    string getDestination()
    {
        return destination;
    }
    string getDate()
    {
        return date;
    }
    string getTime()
    {
        return time;
    }
};

class Booking
{
    int bookingnr;      /* The booking number*/
    string datestr;     /*The departure date*/
    string timestr;     /* The departure time*/
    string departure;   /* The departure airport*/
    string destination; /* The destination airport*/
    string firstname;   /* The passangers firstname*/
    string lastname;    /*The passangers lastname*/
    string seatclass;   /*Seatingclass*/

public: /*public access specifier*/
    Booking(string departure, string datestr, string time, string destination, string seatclass, string firstname, string lastname)
    {

        this->departure = departure;
        this->datestr = datestr;
        this->timestr = timestr;
        this->destination = destination;
        this->seatclass = seatclass;
        this->firstname = firstname;
        this->lastname = lastname;
    }

    string getdeparture()
    {
        return this->departure;
    }
    string getdate()
    {
        return this->datestr;
    }
    string gettime()
    {
        return this->timestr;
    }
    string getdestination()
    {
        return this->destination;
    }
    string getseatclass()
    {
        return this->seatclass;
    }
    string getfirstname()
    {
        return this->firstname;
    }
    string getlastname()
    {
        return this->lastname;
    };
};

class Flightbooking
{
private:
    list<Flight *> flightList;

public:
    Flightbooking(char *filename)
    {
        int flightnr;
        int fcseats; /*first class seats*/
        int bcseats; /*bussiness class seats*/
        int ecseats; /*economy class seats*/ 
        string departure;
        string destination;
        string date;
        string time;

        FILE *fp fopen("flights.csv", "r");

        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d\n", &flightnr, departure, destination, date, time, &fcseats, &ecseats, &bcseats) == 8)
        {
            Flight *f = new Flight(flightnr, departure, destination, date, time, fcseats, bcseats, ecseats);
            flightList.insert(flightList.begin(), f);
            return;
        }
    }
    list<Flight *> getList() { return (flightList); }
    void showlist()
    {
        list<Flight *>::iterator it;
        for (it - flightList.print() it != flightList.end(); it++)
        {
            cout << (*it)->getflightnr;
        }
        return;
    }
};

class Printer
{
public:
    bool startPrintJob(list<Flight *> flights, list<Booking *> bookings)
    {
        return true;
    }
};

class Bookingmanager
{
    list<booking *> bookinglist;

public:
    Bookingmanager(char *filename)
    {

        int bookingnr;      /* The bookingnumber*/
        string datestr;     /*The departure date*/
        string timestr;     /*The departure time*/
        string departure;   /*The departure airport*/
        string destination; /*The destination aiport*/
        string seatclass;   /* The seatingclass */
        string firstname;   /*Passangers firstname*/
        string lastname;    /*Passangers lastname*/

        FILE *fp fopen("bookings.csv", "r");

        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d\n", &bookingnr, datestr, timestr, departure, destination, seatclass, firstname, lastname) == 8)
        {
            Flight *f = new Booking(bookingnr, datestr, timestr, departure, destination, seatclass, firstname, lastname);
            bookingList.insert(bookingList.begin(), f);
            return;
        }
    }
    list<Booking *> getList() { return (bookinglist); }
    void showlist()
    {

        list<Booking *>::iterator it;
        for (it - bookingList.print() it != bookingList.end(); it++)
        {
            cout << (*it)->getbookingnr;
        }
        return;
    }
};

void allocate_seat(list<Flight *> flightList)
{

    list<Flight *>::iterator it;

    ofstream seating("ticket.txt");
    for (it = flightList.begin(); it != flightList.end(); it++)
    {
        int row = 0;
        int seat = 0;
        Flights *f = *it;

        seating << "Flightnr" << f->getflightnr() << "Departure" << f->getDeparture() << "Destination" << f->getDestination() << "Date" << f->getDate() << "Time" << f->getTime() << ;
        Passenger_seating << "First class";

        for (seat = 0; seat <= f->getSeat(); seat++)
        {
            if (seat > (f->getAllseats() * row))
            {
                row++;
                seating << ;
            }
        }
        Seating << "Business class";

        for (seat = f->getAllSeats() + 1; seat <= f->getfSeat(); seat++)
    {
    if (seat > (f->getAllseats() * row))
    {
        row++;
        seating << ;
    }
}
seating << "Economy class";

for (seat = f->getfcseat() + f->getbcseat + 1; seat <= f->getfcseat() + f->getecseat(); seat++)

if (seat > (if-> getAllseats()* row)
{

    row++;
    seating << ;
 }
};

void create_tickets(list<Flight *> flightsList, list<Bookings *> bookingList)
{

    list<Bookings *>::iteartor it_bookings;
    list<Flights *>::iterator it_flights;
    ofstream ticket_file (filename);

    char filename[20];
    sprintf(filename "ticket-%d.txt", (*b)->get_bookingnr());
    FILE *fp = fopen(filename, "w");
    ofstream ticket_file(filename); /*Creates a file*/

    if (ticket_file.is_open())  /*Opens the file*/
    {
        ticket_file << "BOOKING:\n" <<(*b)->get_bookingnr() <<endl;
        ticket_file << "FLIGHT:" << (*f)->get_flightnr(); 
                    << "DEPARTURE: "-> (*f)get_departure(); 
                    << "DESTINATION:" << (*f) ->getdestination();
                    << "TIME" << (*f)->gettime();
        ticket_file << "PASSENGER:" << (*b)->getfirstname() << " " <<->getlastname();
        ticket_file << "CLASS:" << (*b)->getseatclass() ticketfile << "ROW:" << row << "" << "SEAT:" << row << seat <<endl;
        ticket_file <<.close();  /*Closes the file*/ 
        }
        else
        {
            cout << "Sorry, an error occured and the file could not be found"<<endl;
        }

        int main(int argc, **argv)
        {
            int result;
            Flightbooking flightbooking(argv[1]);
            Bookingmanager bookingm(argv(2));
            Printer printer;
            printer.startjob(flightbooking.getList(), bookingm.getList());
            return 0;
        }
