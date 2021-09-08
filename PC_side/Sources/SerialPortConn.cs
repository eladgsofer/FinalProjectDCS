using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Threading;
using System.IO.Ports;
using System.Text.RegularExpressions;

namespace TerminalPC.Sources
{

    // Message types


    public class SerialPortConn : SerialPort
    {
        public static class TYPE
        {
            // Messages
            public const string TELEMETRY = "TL";
            public const string SCAN = "SC";
            public const string FILEEND = "FE";
            public const string CONN_ACK = "ackconn";
        }

        List<object> Result;
        public SerialPortConn(string COM, int baudRate, Parity parity, int dataBits, StopBits stopBits)
        {
            this.BaudRate = baudRate;
            this.Parity = parity;
            this.DataBits = dataBits;
            this.StopBits = stopBits;
            this.PortName = COM;
        }

/*        public List<object> receiveData()
        {
            List<object> Result = new List<object>(3);
            return Result
        }*/
    }
}
