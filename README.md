
This this program you use information from two files one flight.csv containing flightinformation and booking.csv that contains bookinginformation.
The program matches the flights with the bookings and allocates a seat and marks it booked.
The program creates files with a ticket for each file and will be printed out in .txt files. 




The flights.csv file contains:



flightnumber,departure,destination,date,time,f-rows,b-rows,e-rows

The bookings.csv file contains:


bookingnumber,date,time,departure,destination,seatclass,firstname,surname


All the printed tickets should contain the following information:



BOOKING:{bookingnumber} 
FLIGHT:{flight} DEPARTURE:{dep} DESTINATION: {dest} {date} {time}
PASSENGER {firstname} {surname}
CLASS: {seatclass}
ROW {row} SEAT {seatnumber}
