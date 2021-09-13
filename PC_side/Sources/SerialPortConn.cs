using System;
using System.IO.Ports;


namespace TerminalPC.Sources
{


    public class SerialPortConn : SerialPort
    {
        public static string LastMSG = "";

        // all available Message types which being received from the MCU.

        public static class MESSAGE_TYPE
        {

            public const string TELEMETRY = "tele"; // telemetry info message
            public const string SCAN = "scan"; // scan info message
            public const string SCRIPT_DONE = "fnsc"; // end of script execution message
            public const string FILE_ACK = "Fack"; // finish transfer a file
            public const string CONN_ACK = "Cack"; // connection created successfully 
            public const string GUI_CLEAR = "Gclr"; // GUI clear - command to reset the radar display
            public const string PARITY_ERR = "PErr"; // parity error occured
        }

        public SerialPortConn(string COM, int baudRate, Parity parity, int dataBits, StopBits stopBits)
        {
            this.BaudRate = baudRate;
            this.Parity = parity;
            this.DataBits = dataBits;
            this.StopBits = stopBits;
            this.PortName = COM;

        }

        /// <summary>
        /// validate the port is open
        /// </summary>
        public void validateConn()
        {
            if (!this.IsOpen)
            {
                this.Open();
            }
        }
        /// <summary>
        /// send a message with \n representing end of message
        /// </summary>
        /// <param name="message"></param>
        public void sendMessage(string message)
        {
            this.validateConn();
            this.Write(message + "\n");
            LastMSG = message;
        }
        // resend a message
        public void resendMessage()
        {
            this.validateConn();
            this.Write(LastMSG + "\n");
        }

        /// <summary>
        /// Read a message defined in the MESSAGE_TYPE above one byte by another in order to apply parity mechanism.
        /// a 7bit integer is supplied alongside parity
        /// </summary>
        /// <returns></returns>
        public string readMessage()
        {
            string inData = "";
            char ch = '\0'; ;
            int b, res;

            this.validateConn();

            while (ch != '\n')
            {
                while (this.BytesToRead == 0) ;
                b = this.ReadByte();
                res = b & (Convert.ToByte(127));
                ch = (char)res;
                inData += ch;
            }
            return inData.TrimStart('\0'); //spConn.ReadExisting(); //
        }

    }
}