# Case A: Parking Management and Billing System
A shopping mall needs a program to manage its parking spaces and calculate parking fees for
different vehicle types. The system can store information such as vehicle plate number, vehicle
type, entry time, exit time, parking duration, and parking fee. The maximum of vehicle that can
be stored is 20.

Minimum requirements:
- The system can perform vehicle registration by recording the vehicle plate number,
vehicle type, and entry time. If no parking slot is available, the system will reject the new
registration.
- The system can automatically assign an available parking slot to each registered
vehicle.
- The system can calculate parking duration based on the entry and exit times, including
vehicles that park overnight. Any partial hour will be rounded up to the next full hour.
- The system can calculate parking fees based on the following rules:
- Motorcycle: Rp3,000 for the first 2 hours and Rp2,000 for each additional hour.
- Car: Rp5,000 for the first 2 hours and Rp3,000 for each additional hour.
- Vehicles parked for more than 8 hours receive a 10% discount.
- The system can mark each parking slot as either occupied or available.
- The system can process vehicle checkout by calculating the parking fee and marking the
parking slot as available again.
- The system can prevent a vehicle from being assigned to an already occupied parking
slot.
- The system can display a daily parking report containing the number of occupied
spaces, available spaces, completed parking transactions, and total collected revenue.