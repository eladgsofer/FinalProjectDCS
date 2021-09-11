﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using System.IO;
using System.Threading;
using System.IO.Ports;
using System.Text.RegularExpressions;

namespace TerminalPC.Sources
{


    public class SerialPortConn : SerialPort
    {
        public static string LastMSG = "";

        // Message types

        public static class TYPE
        {
            // Messages
            public const string TELEMETRY = "tele";
            public const string SCAN = "scan";
            public const string SCRIPT_DONE = "fnsc";
            public const string FILE_ACK = "Fack";
            public const string CONN_ACK = "Cack";
            public const string GUI_CLEAR = "Gclr";
            public const string PARITY_ERR = "PErr";

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

        public void validateConn()
        {
            if (!this.IsOpen)
            {
                this.Open();
            }
        }

        public void sendMessage(string message)
        {
                this.validateConn();
                this.Write(message + "\n");
                LastMSG = message;
        }

        public void resendMessage()
        {
            this.validateConn();
            this.Write(LastMSG + "\n");
        }

        /*        public List<object> receiveData()
                {
                    List<object> Result = new List<object>(3);
                    return Result
                }*/
    }
}
