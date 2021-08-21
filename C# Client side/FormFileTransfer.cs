using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;

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
                    if (!Home.port.IsOpen)
                    {
                        Home.port.Open();
                    }
                    
                    Home.port.Write("filer " + s1.ToString() + "," + fname + "\n");
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }
        public void port_File_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort spConn = (SerialPort)sender;
            string indata = "";
            if (waitingForFile)
            {
                waitingForFile = false;
                indata = ((char)Home.port.ReadChar()).ToString();//check
                while (!(indata.EndsWith("\0")))
                {
                    indata += ((char)Home.port.ReadChar()).ToString();
                }
                indata = indata.Substring(0, indata.Length - 1);
                File.WriteAllText(@"C:\Users\elads\Desktop\Terminal\Recived files\" + fileName, indata);
            }
            else
            {
                indata = spConn.ReadLine();
                if (indata.Equals("ack"))
                {
                    if (sendingMode == 0) { //normal sending
                        try
                        {
                            if (!Home.port.IsOpen)
                            {
                                Home.port.Open();
                            }
                            Home.port.Write(file);
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show(ex.ToString());
                        }
                    }
                }
                else
                {
                    if (indata.StartsWith("filename") || indata.StartsWith("ilename"))
                    {
                        fileName = indata.Substring(9, indata.Length - 9);
                        //string path = @"C:\Users\Elad\Desktop\Terminal\Recieved files\"+ fileName;
                        //File.Create(path);
                  
                        waitingForFile = true;
                        try
                        {
                            if (!Home.port.IsOpen)
                            {
                                Home.port.Open();
                            }
                            Home.port.Write("ackfile\n");
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show(ex.ToString());
                        }

                    }
                    else
                        MessageBox.Show("Ack Failed: " + indata);
                }
            }
        }

        private void FormFileTransfer_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                if (!Home.port.IsOpen)
                {
                    Home.port.Open();
                }
                Home.port.Write("FilesExit\r\n");
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
                if (!Home.port.IsOpen)
                {
                    Home.port.Open();
                }
                Home.port.Write("FilesLCD\r\n");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
