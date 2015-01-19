# RISC
"RFID Integrated Security Check"

RISC is my so called "Diplomarbeit".
Basically it´s a RFID security system which works through a Raspberry Pi B, an Arduino Nano and the RDM6300 (RFID Reader).

I´m 19 years old and currently attending the HTL Bulme Graz Goesting, a higher technical school in Graz - Austria.

The system itself is pretty easy; 
The RDM6300 reads data from the RFID Tag. This data is sent to the Arduino Nano.
To ensure a high level of security I also added a keypad for entering an (personal) passcode.
Both the Tag ID and the Passcode is sent to the Raspberry Pi.
On the Raspberry Pi there is an Apache Server and a MySQL Database which contains the Tag ID and the Passcode.
If the read data is stored on the database, you can enter the room, the building, ...
