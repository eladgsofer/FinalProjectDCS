
C# terminal

The c# terminal is divided into 3 main winforms 
1. a connection menu 
2. FormChat - a form which is dedicaated to chat with the mcu
3. form file transfer - transofmring files..

The messages between the 2 sides are written via a protocol.

1. ConnectionParams: - a message to deliver the connection parameters
2. filer - a message to send a file
3  chat - followed by a "msg" message

The terminal is created using event handlers to receive serialport event, and sending via keyboard events

*PLEASE CREATE THE FOLLOWING DIRECTORY C:\Users\katri\Downloads\dcs