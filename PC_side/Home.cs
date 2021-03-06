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
        public static Parity parityTemp;
        public static StopBits stopbitsTemp;
        public static string comTemp;
        public static int baudTemp;
        public static int flag = 0;

        // file system props
        public static string fileData = "";
        // display arguments
        private bool displayOn = false;
        private int currTelDegree;

        // masked distance
        private float maskedDistance = 100; // cm

        // GUI Properties
        private int WIDTH, HEIGHT, HAND;
        private int handDegMain;
        private int handX, handY;
        private const int MAX_SERVO_ANGLE = 180;
        private int circleX, circleY;                                // center of the circle
        private List<Point> pointsArr; // pointsArr for future deletion
        Point centerP;

        // Radar graphic objects
        private Bitmap bmp;
        private Graphics graphics;

        // border Pen
        private readonly  Pen borderGreenPen = new Pen(Color.Green, 1f);
        // Beam pens
        private  Pen greenPen = new Pen(Color.Green, 1.2f);
        private  Pen redPen = new Pen(Color.Red, 1.2f);
        private  Pen blackPen = new Pen(Color.Black, 1.2f);


        public Home()
        {
            InitializeComponent();

            string[] availablePorts = SerialPort.GetPortNames().Length > 0 ? SerialPort.GetPortNames() : null;
            if (availablePorts != null)
            {
                this.comboBoxCOM.Items.AddRange(availablePorts);
                comboBoxCOM.SelectedIndex = 0;

            }
            // default values for GUI object
            comboBoxBaud.SelectedIndex = 1;
            comboBoxParity.SelectedIndex = 0;
            comboBoxSTPBIT.SelectedIndex = 0;
            WIDTH = radarPictureBox.Height * 2;
            HEIGHT = radarPictureBox.Height;
            HAND = radarPictureBox.Height;
            // Init default SerailPort
            port = new SerialPortConn(comboBoxCOM.Text, 9600, Parity.None, 8, StopBits.One);

            // Radar center calculation
            circleX = radarPictureBox.Width / 2 ;
            circleY = radarPictureBox.Height;
            centerP = new Point(circleX, circleY);

            // Radar Objects
            bmp = new Bitmap(WIDTH + 1, HEIGHT + 1);
            radarPictureBox.BackColor = Color.Black;
            pointsArr = new List<Point>();
            // draw the radar
            drawRadarPicture(true, false);

            // create a dataReceived handler function
            port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);

        }

        private void ComboBoxCOM_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        /// <summary>
        ///  Connect and update the parameters as specified in the GUI objects.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
                    comboBoxBaud.SelectedItem.ToString()[0]+
                    comboBoxParity.SelectedItem.ToString()[0]+
                    comboBoxSTPBIT.SelectedItem.ToString()[0]);
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

        /// <summary>
        /// Serial Port event handler - this function is the core in our app
        /// whenever the buffer has more then 1 byte received in the serialPort
        /// an interrupt occurs and we enter this function via new thread, the function
        /// handles and process the messages and performs the corresponded action
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int degree;
            float distance;
            string cmdVal, opCode, inData = "";
            
            SerialPortConn spConn = (SerialPortConn)sender;

            inData = spConn.readMessage();

            opCode = inData.Substring(0, 4);

            int tpmCntDelta;
            // each opcode performs different action
            switch (opCode)
            {
                // Recieve a scan info message
                case SerialPortConn.MESSAGE_TYPE.SCAN:
                    degree = int.Parse(inData.Substring(4,3));
                    tpmCntDelta = int.Parse(inData.Substring(7,4), System.Globalization.NumberStyles.HexNumber);
                    distance = calcDistsnce(tpmCntDelta);
                    Console.WriteLine("scan: deg- " + degree + " dist- " + distance + " cm");

                    this.Invoke((MethodInvoker)delegate
                    {
                        if (displayOn)
                        {
                            DisplayRadar(degree, distance);
                            AngelDataLabel.Text = degree + "°";
                            DistanceDataLabel.Text = distance.ToString("#.##") + " cm";
                        }
                    });
                    break;


                // Recieve Telemetry info
                case SerialPortConn.MESSAGE_TYPE.TELEMETRY:
                    cmdVal = inData.Substring(4, 4);
                    tpmCntDelta = int.Parse(cmdVal, System.Globalization.NumberStyles.HexNumber);
                    distance = calcDistsnce(tpmCntDelta);
                    string distanceString = distance > maskedDistance ? "Out of Range" : distance.ToString("#.##") + " cm";
                    Console.WriteLine("Telemetria: Distance- " + distanceString);
                    this.Invoke((MethodInvoker)delegate
                    {
                        if (displayOn)
                        {

                            DistanceDataLabel.Text = distanceString;
                            clearRadar();
                            DisplayRadar(currTelDegree, distance);
                        }
                    });
                    break;

                // File recieved successfully 
                case SerialPortConn.MESSAGE_TYPE.FILE_ACK:
                    Console.WriteLine("Sending file");
                    displayOn = true;
                    sendSerialMessage(spConn, fileData);
                    StatusDataLabel.Text = "Script mode is on";

                    break;

                // Script finished execution status message
                case SerialPortConn.MESSAGE_TYPE.SCRIPT_DONE:
                    Console.WriteLine("Finished script execution");
                    displayOn = false;
                    this.Invoke((MethodInvoker)delegate
                    {
                        StatusDataLabel.Text = "Script finished execution";
                        clearGUI();
                    });
                    
                    break;

                // SerialPort params update was finished successfully
                case SerialPortConn.MESSAGE_TYPE.CONN_ACK:
                    refreshSerialPort(comTemp, baudTemp, parityTemp, 8, stopbitsTemp);
                    Console.WriteLine("SerialPort is connected");
                    break;

                // Clear GUI request
                case SerialPortConn.MESSAGE_TYPE.GUI_CLEAR:
                    Console.WriteLine("Clearing GUI...");
                    this.Invoke((MethodInvoker)delegate
                    {
                        clearGUI();
                    });
                    break;

                // Parity Error occured, perform resend
                case SerialPortConn.MESSAGE_TYPE.PARITY_ERR:
                    port.resendMessage();
                    break;

                // Unknown
                default:
                    Console.WriteLine("Unknown command type" + opCode);
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
        /// <summary>
        /// Radar display - a function which draws a radar emptry picture
        /// </summary>
        /// <param name="updatePicture"></param>
        /// <param name="eraseLines"></param>
        private void drawRadarPicture(bool updatePicture, bool eraseLines)
        {

            //graphics
            graphics = Graphics.FromImage(bmp);

            if (eraseLines)
                this.eraseLines();

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
        /// <summary>
        ///  Erase the Radar display current lines
        /// </summary>
        private void eraseLines()
        {
            for (int i = 0; i < pointsArr.Count; i++)
            {
                try
                {
                    graphics.DrawLine(blackPen, centerP, pointsArr[i]);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(blackPen +" " + centerP + " " + pointsArr[i]);
                }
            }
            pointsArr.Clear();
        }

        /// <summary>
        /// Display the degree and distance as a line in the radar UI
        /// </summary>
        /// <param name="deg"></param>
        /// <param name="dist"></param>
        private void DisplayRadar(int deg, float dist)
        {
            if (!displayOn)
                return;

            drawRadarPicture(false, false);

            // Convert deg to range [-90,90]
            handDegMain = -(deg - 90);
            // Convert dist relative to HAND & maskedDistance
            float displayedDistance = dist > maskedDistance ? HAND : (dist / maskedDistance) * HAND;


            if (handDegMain >= 0 && handDegMain <= 90)
            {
                handX = circleX + (int)(displayedDistance * Math.Sin(Math.PI * handDegMain / 180));
                handY = circleY - (int)(displayedDistance * Math.Cos(Math.PI * handDegMain / 180));
            }
            else
            {
                handX = circleX - (int)(displayedDistance * -Math.Sin(Math.PI * handDegMain / 180));
                handY = circleY - (int)(displayedDistance * Math.Cos(Math.PI * handDegMain / 180));
            }

            
            Point endHand = new Point(handX, handY);

            if (displayedDistance == HAND) {
                graphics.DrawLine(greenPen, centerP, endHand);
            }
            else {
                graphics.DrawLine(redPen, centerP, endHand);
            }

            // for future deletion
            pointsArr.Add(endHand);
            if (handDegMain == 90)
            {
                drawRadarPicture(true, true);
            }
            else
            {
                graphics.Dispose();
                radarPictureBox.Image = bmp;
            }
        }
        /// <summary>
        /// Refresh the serialport connection parameters
        /// </summary>
        /// <param name="COM"></param>
        /// <param name="baudRate"></param>
        /// <param name="parity"></param>
        /// <param name="dataBits"></param>
        /// <param name="stopBits"></param>
        private void refreshSerialPort(string COM, int baudRate, Parity parity, int dataBits, StopBits stopBits)
        {
            try
            {
                // refresh the connection
                port.Close();
                port = new SerialPortConn(
                        COM,
                        baudRate,
                        parity,
                        dataBits,
                        stopBits
                    ); 

                port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);

                port.Open();
                this.Invoke((MethodInvoker)delegate
                {
                    ConnectionStatus.TextAlign = ContentAlignment.MiddleCenter;
                    ConnectionStatus.Text = "   Connected";
                    ConnectionStatus.ForeColor = Color.Green;
                    buttonSend.Enabled = true;
                    buttonChoose.Enabled = true;
                    buttonFilesLCD.Enabled = true;
                    scanButton.Enabled = true;
                    stopButton.Enabled = true;
                    button3.Enabled = true;
                    button4.Enabled = true;
                });

            }
            catch (Exception ex)
            {
                MessageBox.Show("Connection Failed with response: " + ex.ToString());
            }

        }

        private void clearGUI()
        {
            
            this.Invoke((MethodInvoker)delegate
            {
                drawRadarPicture(true, true);
                AngelDataLabel.Text = "";
                DistanceDataLabel.Text = "";
            });    
        }

        private void clearRadar()
        {
            this.Invoke((MethodInvoker)delegate
            {
                drawRadarPicture(true, true);
            });
        }
        // Masked distrance button - saving a new masked distance
        private void button4_Click(object sender, EventArgs e)
        {
            string maskedStr = MaskedDistanceTextBox.Text;
            MaskedDistanceTextBox.Clear();
            this.maskedDistance = int.Parse(maskedStr);
            MessageBox.Show("Masked distance new value " + maskedStr);
        }

        // Send Telemetry button
        private void button3_Click_1(object sender, EventArgs e)
        {
            this.displayOn = true;
            AngelDataLabel.Text = telemetriaDataTextBox.Text + "°";
            int deg = int.Parse(telemetriaDataTextBox.Text);
            currTelDegree = deg;
            telemetriaDataTextBox.Clear();
            // \0? for ending a message? otherwise we could keep reading the next message?..
            port.sendMessage("Tele" + deg.ToString("D3"));
            StatusDataLabel.Text = "Telemetry is on";
        }
        // perform a scan button
        private void scanButton_Click(object sender, EventArgs e)
        {
            this.displayOn = true;
            StatusDataLabel.Text = "Scan is on";
            port.sendMessage("RadDec");
        }
        // stop a telmetry/scan procedure button
        private void stopButton_Click(object sender, EventArgs e)
        {
            this.displayOn = false;
            port.sendMessage("Exit");
            StatusDataLabel.Text = "Opperation Stopped";
            clearGUI();


        }
        private void label1_Click(object sender, EventArgs e)
        {

        }
        private void buttonFile_Paint(object sender, PaintEventArgs e)
        {

        }
        private void Home_Load(object sender, EventArgs e)
        {
            // allocate a console log window
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
        /// <summary>
        /// Send a file to the MCU button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
                    StatusDataLabel.Text = "Script mode is on";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }

        /// <summary>
        /// send a show files command to the MCU button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
            displayOn = true;
        }
        // browse files button
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

        private void telemetriaOlLabel_Click(object sender, EventArgs e)
        {

        }

        private void AngelLabel_Click(object sender, EventArgs e)
        {

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
