using System;
using System.ComponentModel;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using TerminalPC.Sources;

namespace TerminalPC
{
    public partial class FormFileTransfer : Form
    {
        public static string file = "";
        public static bool waitingForFile = false;
        public static string fileName;
        public static int sendingMode=0;
        public System.Timers.Timer timer;
        public FormFileTransfer()
        {
            InitializeComponent();
            Home.port.DataReceived += new SerialDataReceivedEventHandler(port_File_DataReceived);
        }
        private void ButtonChoose_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void OpenFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            textBox1.Text = openFileDialog1.FileName;
        }

        private void ButtonSend_Click(object sender, EventArgs e)
        {
            sendingMode = 0;
            if (string.IsNullOrEmpty(textBox1.Text))
            {
                MessageBox.Show("File wasn't specified! Pick a file");
            }
            else
            {
                FileInfo f = new FileInfo(textBox1.Text);
                string fname = f.Name;              // file name: fileX.txt
                long s1 = f.Length;                 // file size in bytes
                StreamReader sr = new StreamReader(textBox1.Text);
                try
                {
                    file = sr.ReadToEnd();          //translate file to string
                    Home.port.sendMessage("RScript " + s1.ToString() + "," + fname);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }
        public void port_File_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string indata;
            string cmdVal;
            SerialPortConn spConn = (SerialPortConn)sender;
            System.Threading.Thread.Sleep(500);

            spConn.validateConn();
            indata = spConn.ReadLine().TrimStart('\0');

            //ProcessMessage(indata);

            string opCode = indata.Substring(0, 4);

            int cntDiff;
            // Check opc
            switch (opCode)
            {
                // File recieved ok 
                case SerialPortConn.TYPE.FILE_ACK:
                    try
                    {
                        Console.WriteLine("Sending file");
                        spConn.sendMessage(file);
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                    break;

                // Recieve Scanner info
                case SerialPortConn.TYPE.SCAN:
                    int deg = int.Parse(indata.Substring(4, 3));
                    cntDiff = int.Parse(indata.Substring(7, 4), System.Globalization.NumberStyles.HexNumber);
                    float dist = Home.calcDistsnce(cntDiff);
                    Console.WriteLine("scan: deg- " + deg + " dist- " + dist + " cm");

                    //this.Invoke((MethodInvoker)delegate
                    //{
                    //    DisplayRadar(deg, dist);
                    //    AngelLabel.Text = "Angle: " + deg;
                    //    DistanceLabel.Text = "Distance: " + dist.ToString("#.##");
                    //});
                    break;
                    //case default:
                    //Console.WriteLine("unkown response");
            }
        }

        private void FormFileTransfer_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                Home.port.sendMessage("SMExit");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            Home.port.DataReceived -= port_File_DataReceived;
        }

        private void ButtonFilesLCD_Click(object sender, EventArgs e)
        {
            try
            {
                Home.port.sendMessage("ScriptM");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void FormFileTransfer_Load(object sender, EventArgs e)
        {

        }
    }
}
