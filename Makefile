Flightprogram: Flygprogramplus.cpp 
	g++  Flygprogramplus.cpp -o Flightprogram

Run: Flightprogram 
	./Flightprogram -f flights.csv -b bookings.csv 
	ls -ltr
	cat ticket-1000.txt
