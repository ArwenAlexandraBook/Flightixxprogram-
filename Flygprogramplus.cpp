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
#include <cstring>

using namespace std;

class Flight /* class that implemets the flight info*/
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

public: /*Public access specifier*/
    Flight(int flightnr, string departure, string destination, string date, string time, int nrfcrows, int nrbcrows, int nrecrows)
    {
        this->flightnr = flightnr;
        this->departure = departure;
        this->destination = destination;
        this->date = date;
        this->time = time;
        this->nrfcseats = nrfcrows;
        this->fcflags = new int[nrfcrows *sizeof(int) * 7];
        memset(this->fcflags, 0, nrfcrows *sizeof(int) * 7);
        this->nrbcseats = nrbcrows;
        this->bcflags = new int[nrbcrows *sizeof(int) * 7];
        memset(this->bcflags, 0, nrbcrows *sizeof(int) * 7);
        this->nrecseats = nrecrows;
        this->ecflags = new int[nrecrows * sizeof(int) * 7];
        memset(this->ecflags, 0, nrecrows * sizeof(int) * 7);
    }

    /*getters for the class flight*/

    int getflightnr()
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
    int getnrfcseats() { return (this->nrfcseats); }
    int getfcseats(int p) { return (this->fcflags[p]); }
    void bookfseat(int p) { this->fcflags[p] = 1; }
};

class Booking /* Class implementing booking information*/
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
    Booking(int bookingnr, char *datestr, char *timestr, char *departure, char *destination, char *seatclass, char *firstname, char *lastname)
    {
        this->bookingnr = bookingnr;
        this->departure = departure;
        this->datestr = datestr;
        this->timestr = timestr;
        this->destination = destination;
        this->seatclass = seatclass;
        this->firstname = firstname;
        this->lastname = lastname;
    }

    int getbookingnr()
    {
        return this->bookingnr;
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
        char departure[10];
        char destination[10];
        char date[15];
        char time[10];

        FILE *fp fopen("flights.csv", "r");

        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n", &flightnr, departure, destination, date, time, &fcseats, &ecseats, &bcseats) == 8)
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
        for (it = flightList.begin(); it != flightList.end(); it++)
        {
            cout << (*it)->getflightnr();
        }
        return;
    }
};

class Printer
{
public:
    bool startPrintJob(list<Flight *> flights, list<Booking *> bookings)
    {
        list<Flight *>::iterator fit;
        list<Booking *> iterator bit;
        for (bit = bookings.begin(); bit != bookings.end(); bit++)
        {
            /*Searches after flight for booking*/
            for (fit = flights.begin(); fit != flights.end(); fit++)
            {

                if (
                    (*bit)->getdeparture() == (*fit)->getDeparture() &&
                    (*bit)->getdestination() == (*fit)->getDestination() &&
                    (*bit)->getdate() == (*fit)->getDate() &&
                    (*bit)->gettime() == (*fit)->getTime())
                {
                    int row = 0;
                    int seat = 0;

                    if (this->allocate_seat(*fit, (*bit)->getseatclass(), &row, &seat))
                    {
                        print_ticket(*fit, *bit, row, seat);
                    }
                }
            }
        }

        return true;
    }
    /* This function allocates seats to the bookings*/
    bool allocate_seat(Flight *f, string inclass, int *row, int *seat)
    {

        if (inclass == "first")
        {
            for (int p = 0; p < f->getnrfcseats(); p++)
            {
                if (f->gefseat(p) == 0)
                {
                    f->bookfseat(p); /* Marking a seat taken*/
                    *row = p / 7 + 1;
                    *seat = p % 7 + 1;
                    return (true); /*Found a seat*/
                }
            }
        }
        if (inclass == "bussiness")
        {
            for (int p = 0; p < f->getnrbcseats(); p++)
            {
                if (f->getfseats(p) == 0)
                {
                    f->bookfseat(p);
                    *row = p / 7 + 1;
                    *seat = p % 7 + 1;
                    return (true);
                }
            }
        }
        if (inclass == "economy")
        {
            for (int p = 0; p < f->getnrecseats(); p++)
            {
                if (f->getfseat(p) == 0)
                {
                    f->bookfseat(p);
                    *row = p / 7 + 1;
                    *seat p % 7 + 1;
                    return (true);
                }
            }
        }
        return (false); /* Did not find a seat*/
    }

    void print_ticket(Flight *f, Booking *b, int row, int seat)
    {

        char filename[20];
        sprintf(filename "ticket-%d.txt", b->getbookingnr());
        ofstream ticket_file(filename); /*Creates a file*/

        if (ticket_file.is_open()) /*Opens the file*/
        {
            ticket_file << "BOOKING:\n"
                        << b->getbookingnr() << endl;
            ticket_file << "FLIGHT:" << f->getflightnr();
            ticket_file << "DEPARTURE:" << f->getDeparture();
            ticket_file << "DESTINATION:" << f->getDestination();
            ticket_file << "TIME" << f->getTime();
            ticket_file << "PASSENGER:" << b->getfirstname() << " " << b->getlastname();
            ticket_file << "CLASS:" << b->getseatclass();
            ticket_file << "ROW:" << row << ""
                        << "SEAT:" << seat << endl; /*prints information to the ticket file*/
            ticket_file.close();                    /*Closes the file*/
        }
        else
        {
            cout << "Sorry, an error occured and the file could not be found" << endl;
        }
    }
};
class Bookingmanager
{
    list<Booking *> bookinglist;

public:
    Bookingmanager(char *filename)
    {

        int bookingnr;        /* The bookingnumber*/
        char datestr[15];     /*The departure date*/
        char timestr[15];     /*The departure time*/
        char departure[15];   /*The departure airport*/
        char destination[15]; /*The destination aiport*/
        char seatclass[15];   /* The seatingclass */
        char firstname[50];   /*Passangers firstname*/
        string lastname[50];  /*Passangers lastname*/

        FILE *fp = fopen("bookings.csv", "r");

        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", &bookingnr, datestr, timestr, departure, destination, seatclass, firstname, lastname) == 8)
        {
            Booking *b = new Booking(bookingnr, datestr, timestr, departure, destination, seatclass, firstname, lastname);
            bookingList.insert(bookingList.begin(), b);
        }
    }
} list<Booking *> getList() { return (bookingList); }

void showlist()
{

    list<Booking *>::iterator it;
    for (it = bookingList.begin(); it != bookingList.end(); it++)
    {
        cout << (*it)->getbookingnr();
    }
    return;
}
};

int main(int argc, **argv)
{
    int result;
    Flightbooking flightbooking(argv[1]);
    Bookingmanager bookingm(argv(2));
    Printer printer;
    printer.startPrintJob(flightbooking.getList(), bookingm.getList());
    return 0;
}
