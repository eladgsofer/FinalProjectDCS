using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using TerminalPC.Sources;
using System.IO;




using System.Threading;
using System.Runtime.InteropServices;


namespace TerminalPC
{
    public partial class Home : Form
    {
        // Console
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();

        // Serial Port connection
        public static SerialPortConn port;
        Boolean firstConnection = true;
        public static Parity parityTemp;
        public static StopBits stopbitsTemp;
        public static string comTemp;
        public static int baudTemp;

        public static string fileData = "";
        public static string fileName;



        private float maskedDistance = 100; // cm

        private int WIDTH, HEIGHT, HAND;
        private int handDegMain;
        private int handX, handY;
        private const int MAX_SERVO_ANGLE = 180;
        private int circleX, circleY;                                // center of the circle
        private List<Point> pointsArr;
        Point centerP;

        // Radar graphic objects
        private Bitmap bmp;
        private Graphics graphics;

        // border Pen
        private readonly  Pen borderGreenPen = new Pen(Color.Green, 2.5f);
        // Beam pens
        private readonly Pen greenPen = new Pen(Color.Red, 1f);
        private readonly Pen redPen = new Pen(Color.Red, 1f);
        private readonly Pen blackPen = new Pen(Color.Black, 1f);


        public Home()
        {
            InitializeComponent();

            string[] ports = SerialPort.GetPortNames().Length > 0 ? SerialPort.GetPortNames() : null;
            if (ports != null)
            {
                this.comboBoxCOM.Items.AddRange(ports);
                comboBoxCOM.SelectedIndex = 1;

            }

            comboBoxBaud.SelectedIndex = 1;
            
            comboBoxParity.SelectedIndex = 0;
            comboBoxSTPBIT.SelectedIndex = 0;
            WIDTH = radarPictureBox.Height * 2;
            HEIGHT = radarPictureBox.Height;
            HAND = radarPictureBox.Height;
            port = new SerialPortConn(comboBoxCOM.Text, 9600, Parity.None, 8, StopBits.One);

            //center
            circleX = radarPictureBox.Width / 2 ;
            circleY = radarPictureBox.Height;
            centerP = new Point(circleX, circleY);

            bmp = new Bitmap(WIDTH + 1, HEIGHT + 1);
            radarPictureBox.BackColor = Color.Black;
            pointsArr = new List<Point>();
            drawRadarPicture(true);

            // create a dataReceived handler function
            port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);

        }

        private void ComboBoxCOM_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        // Connect + update parameters
        private void ButtonConnect_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Connecting");
            
            try
            {
                parityTemp = (Parity)comboBoxParity.SelectedIndex;
                stopbitsTemp = (StopBits)(comboBoxSTPBIT.SelectedIndex+1);
                comTemp = comboBoxCOM.SelectedItem.ToString();
                baudTemp = int.Parse(comboBoxBaud.SelectedItem.ToString());

                port.sendMessage("ConnectionParams"+ " "+
                    comboBoxBaud.SelectedItem.ToString()+" "+
                    comboBoxParity.SelectedItem.ToString()+" "+
                    comboBoxSTPBIT.SelectedItem.ToString());
             }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public static float calcDistsnce(int cntrDiff)
        {
            // CounterClock period = 1 / (tpm clk/prescaler)  | tpm clk = 24MHz  , tpm prescaler = 32 
            // => CounterClock period = 32/24M = 1/750,000 sec
            // dist = (cntrDiff * CounterClock period) * 17,000 = cntrDiff * (17/750); 
            return (float)(cntrDiff * 17.0 / 750.0);
        }

        // Data recieved event
        public void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string indata;
            string cmdVal;
            SerialPortConn spConn = (SerialPortConn)sender;
            //System.Threading.Thread.Sleep(500);

            spConn.validateConn();
            indata = spConn.ReadLine().TrimStart('\0');

            //ProcessMessage(indata);

            string opCode = indata.Substring(0, 4);

            int cntDiff;
            // Check opc
            switch (opCode)
            {
                // Recieve Scanner info
                case SerialPortConn.TYPE.SCAN:
                    int deg = int.Parse(indata.Substring(4,3));
                    cntDiff = int.Parse(indata.Substring(7,4), System.Globalization.NumberStyles.HexNumber);
                    float dist = calcDistsnce(cntDiff);
                    Console.WriteLine("scan: deg- " + deg + " dist- " + dist + " cm");

                    this.Invoke((MethodInvoker)delegate
                    {
                        DisplayRadar(deg, dist);
                        AngelLabel.Text = "Angle: " + deg;
                        DistanceLabel.Text = "Distance: " + dist.ToString("#.##");
                    });
                    break;


                // Recieve Telemetry info
                case SerialPortConn.TYPE.TELEMETRY:
                    cmdVal = indata.Substring(4, 4);
                    cntDiff = int.Parse(cmdVal, System.Globalization.NumberStyles.HexNumber);
                    string distanceString = calcDistsnce(cntDiff) > maskedDistance ?
                        "Out of Range" : calcDistsnce(cntDiff).ToString("#.##") + " cm";
                    Console.WriteLine("Telemetria: Distance- " + distanceString);
                    this.Invoke((MethodInvoker)delegate
                    {
                        DistanceLabel.Text = "Distance: " + distanceString;
                        telemetriaPanel.Visible = true;
                    });
                    break;

                // File recieved ok 
                case SerialPortConn.TYPE.FILE_ACK:
                    Console.WriteLine("Sending file");
                    sendSerialMessage(spConn, fileData);
                    break;

                // Finish executing script
                case SerialPortConn.TYPE.SCRIPT_DONE:
                    Console.WriteLine("Finished executing command script " + fileName);
                    sendSerialMessage(spConn, "SMExit");
                    break;
                    
                // Change connection parameters ack
                case SerialPortConn.TYPE.CONN_ACK:
                    refreshSerialPort();
                    Console.WriteLine("SerialPort is connected");
                    break;

                // Unknown
                default:
                    Console.WriteLine("unreccognized type");
                    break;
            }

        }

        private void sendSerialMessage(SerialPortConn spConn, string serialCmd)
        {
            try
            {
                spConn.sendMessage(serialCmd);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        private void drawRadarPicture(bool updatePicture)
        {

            /////////////////////////////
            //      Draw Radar
            ////////////////////////////
            //graphics
            graphics = Graphics.FromImage(bmp);

            // draw circles
            for (int i = 50; i < HAND; i += 100)
            {
                int radius = HAND - i;
                graphics.DrawEllipse(borderGreenPen, circleX - radius, circleY - radius, radius * 2, radius * 2);
            }

            //draw perpendicular line
            graphics.DrawLine(borderGreenPen, new Point(circleX, circleY), new Point(circleX, HEIGHT)); // UP-DOWN
            graphics.DrawLine(borderGreenPen, new Point(0, circleY-3), new Point(WIDTH, circleY - 3)); // UP-DOWN

            // draw angled lines
            for (int ang = 30; ang < MAX_SERVO_ANGLE; ang += 30)
            {
                Point p_end = new Point(circleX - (int)(HAND * Math.Cos(ang * Math.PI / 180)), circleY - (int)(HAND * Math.Sin(ang * Math.PI / 180)));
                graphics.DrawLine(borderGreenPen, new Point(circleX, circleY), p_end);
            }
            if (updatePicture)
            {
                graphics.Dispose();
                radarPictureBox.Image = bmp;
            }
        }
        private void eraseLines()
        {
            for (int i = 0; i < pointsArr.Count; i++)
            {
                try
                {
                    graphics.DrawLine(blackPen, centerP, pointsArr[i]);
                }
                catch
                {
                    Console.WriteLine(blackPen +" " + centerP + " " + pointsArr[i]);
                }
            }
        }

        private void DisplayRadar(int deg, float dist)
        {
            drawRadarPicture(false);

            // Convert deg to range [-90,90]
            handDegMain = -(deg - 90);
            // Convert dist relative to HAND & maskedDistance
            float adjustedDist = dist > maskedDistance ? HAND : (dist / maskedDistance) * HAND;


            if (handDegMain >= 0 && handDegMain <= 90)
            {
                handX = circleX + (int)(adjustedDist * Math.Sin(Math.PI * handDegMain / 180));
                handY = circleY - (int)(adjustedDist * Math.Cos(Math.PI * handDegMain / 180));
            }
            else
            {
                handX = circleX - (int)(adjustedDist * -Math.Sin(Math.PI * handDegMain / 180));
                handY = circleY - (int)(adjustedDist * Math.Cos(Math.PI * handDegMain / 180));
            }

            
            Point endHand = new Point(handX, handY);

            if (adjustedDist == HAND) {
                graphics.DrawLine(greenPen, centerP, endHand);
            }
            else {
                graphics.DrawLine(redPen, centerP, endHand);
            }

            // for future deletion
            pointsArr.Add(endHand);
            if (handDegMain == 90)
            {
                eraseLines();
                pointsArr = new List<Point>(180);
            }

            graphics.Dispose();
            radarPictureBox.Image = bmp;
        }
        //public void ProcessMessage(){
        private void refreshSerialPort()
        {
            try
            {
                // refresh the connection
                port.Close();
                port = new SerialPortConn(comTemp,
                       baudTemp,
                       parityTemp,
                       8,
                       stopbitsTemp);

                port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);

                port.Open();
                MessageBox.Show("Connected!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Connection Failed with response: " + ex.ToString());
            }

        }

        // save masked distance
        private void button4_Click(object sender, EventArgs e)
        {
            this.maskedDistance = int.Parse(MaskedDistanceTextBox.Text);
            MaskedDistanceTextBox.Clear();
        }

        // telemetry button
        private void button3_Click_1(object sender, EventArgs e)
        {
            // \0? for ending a message? otherwise we could keep reading the next message?..
            int deg = int.Parse(telemetriaDataTextBox.Text);
            port.sendMessage("Tele" + deg.ToString("D3"));
        }
        private void scanButton_Click(object sender, EventArgs e)
        {
            port.sendMessage("RadDec");
        }
        private void stopButton_Click(object sender, EventArgs e)
        {
            port.sendMessage("Exit");
            eraseLines();
            pointsArr = new List<Point>();
        }
        private void label1_Click(object sender, EventArgs e)
        {

        }
        private void buttonFile_Paint(object sender, PaintEventArgs e)
        {

        }
        private void Home_Load(object sender, EventArgs e)
        {
            AllocConsole();
        }
        private void comboBoxBaud_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        private void labelSTPBIT_Click(object sender, EventArgs e)
        {

        }
        private void labelBaud_Click(object sender, EventArgs e)
        {

        }
        private void labelCOM_Click(object sender, EventArgs e)
        {

        }
        private void label1_Click_1(object sender, EventArgs e)
        {

        }
        private void MaskedDistanceTextBox_TextChanged(object sender, EventArgs e)
        {

        }
        private void radarPictureBox_Click(object sender, EventArgs e)
        {

        }

        private void telemetriaPanel_Paint(object sender, PaintEventArgs e)
        {

        }

        private void telemetriaDataTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
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
                    fileData = sr.ReadToEnd();          //translate file to string
                    Home.port.sendMessage("RScript " + s1.ToString() + "," + fname);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }

        private void buttonFilesLCD_Click(object sender, EventArgs e)
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

        private void buttonChoose_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }


        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void openFileDialog1_FileOk_1(object sender, CancelEventArgs e)
        {
            textBox1.Text = openFileDialog1.FileName;
        }

        private void comboBoxParity_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        private void labelParity_Click(object sender, EventArgs e)
        {

        }
        private void comboBoxSTPBIT_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        private void button3_Click(object sender, EventArgs e)
        {

        }


    }   
}
