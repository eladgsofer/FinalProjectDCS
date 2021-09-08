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


        private float maskedDistance = 100; // cm

        private int WIDTH, HEIGHT, HAND;
        private int handDegMain;
        private int handX, handY;
        private const int MAX_SERVO_ANGLE = 180;
        private int circleX, circleY;                                // center of the circle
        private List<Point> pointsArr;
        Point centerP;

        // radar drawing
        private Bitmap bmp;
        private Pen greenPen = new Pen(Color.Green, 2.5f);
        private Pen redPen = new Pen(Color.Red, 2.5f);
        private Pen blackPen = new Pen(Color.Black, 2.5f);
        private Graphics graphics;



        public Home()
        {
            InitializeComponent();
            //Console.WriteLine("Main Form Init");
            comboBoxBaud.SelectedIndex = 1;
            comboBoxCOM.SelectedIndex = 3;
            comboBoxParity.SelectedIndex = 0;
            comboBoxSTPBIT.SelectedIndex = 0;
            WIDTH = radarPictureBox.Height * 2;
            HEIGHT = radarPictureBox.Height;
            HAND = radarPictureBox.Height;
            port = new SerialPortConn(comboBoxCOM.Text,
                                    9600,
                                    Parity.None,
                                    8,
                                    StopBits.One);



            //center
            circleX = radarPictureBox.Width / 2 - 50;
            circleY = radarPictureBox.Height;
            centerP = new Point(circleX, circleY);

            bmp = new Bitmap(WIDTH + 1, HEIGHT + 1);
            radarPictureBox.BackColor = Color.Black;
            pointsArr = new List<Point>(180);
            drawRadarPicture(true);

            // create a dataReceived handler function
            port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);

        }

        private void ComboBoxCOM_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        // Connect + update parameters
        private void ButtonConnect_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Connecting");
            

            try
            {
                if (!port.IsOpen)
                {
                    port.Open();
                }
                parityTemp = (Parity)comboBoxParity.SelectedIndex;
                stopbitsTemp = (StopBits)(comboBoxSTPBIT.SelectedIndex+1);
                comTemp = comboBoxCOM.SelectedItem.ToString();
                baudTemp = int.Parse(comboBoxBaud.SelectedItem.ToString());
               

                port.Write("ConnectionParams"+ " "+
                           comboBoxBaud.SelectedItem.ToString()+" "+
                           comboBoxParity.SelectedItem.ToString()+" "+
                           comboBoxSTPBIT.SelectedItem.ToString()+"\r\n");

             }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }


        }

        private float calcDistsnce(int tpmDiff)
        {
            // final clk: 1 / (tpm clk/prescaler)  | tpm clk = 24MHz  , tpm prescaler = 32 
            // => final clk = 24M/32 = 750,000 Hz
            // dist = tpmDiff * (17,150 / final clk); 
            // prescaler = 8 : 176.4705882352941
            // prescaler = 32 : 43.731778425655976676384839650146
            //return (float)(tpmDiff * 0.022866666666);
            return (float)tpmDiff / (float)43.731778425655976676384839650146;
        }

        // Data recieved event
        public void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string indata;
            SerialPortConn spConn = (SerialPortConn)sender;
            System.Threading.Thread.Sleep(500);
            
            if (!port.IsOpen)
            {
                port.Open();
            }

            indata = spConn.ReadExisting().TrimStart('\0');

            //ProcessMessage(indata);

            string opCode = indata.Substring(0, 3);
            string val = indata.Substring(3, 6);
            // Check opc
            switch (opCode)
            {
                // Baud rate change acknoledge


                // Recieve Scanner info
                case SerialPortConn.TYPE.SCAN:
                    int deg = int.Parse(indata.Substring(0, 3));
                    int tpmDiff = int.Parse(indata.Substring(3));
                    float dist = calcDistsnce(tpmDiff);
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
                    string distanceString = calcDistsnce(int.Parse(val)) > maskedDistance ?
                        "Out of Range" : calcDistsnce(int.Parse(val)).ToString("#.##") + " cm";
                    Console.WriteLine("Telemetria: Distance- " + distanceString);
                    this.Invoke((MethodInvoker)delegate
                    {
                        DistanceLabel.Text = "Distance: " + distanceString;
                        telemetriaPanel.Visible = true;
                    });
                    break;


                // File recieved ok 
                case SerialPortConn.TYPE.FILEEND:
                    Console.WriteLine("Finished executing file");
                    break;
                case SerialPortConn.TYPE.CONN_ACK:
                    refreshSerialPort();
                    break;

                // Unknown
                default:
                    Console.WriteLine("unreccognized type");
                    break;
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
                graphics.DrawEllipse(greenPen, circleX - radius, circleY - radius, radius * 2, radius * 2);
            }

            //draw perpendicular line
            graphics.DrawLine(greenPen, new Point(circleX, circleY), new Point(circleX, HEIGHT)); // UP-DOWN
            graphics.DrawLine(greenPen, new Point(0, circleY-3), new Point(WIDTH, circleY - 3)); // UP-DOWN

            // draw angled lines
            for (int ang = 30; ang < MAX_SERVO_ANGLE; ang += 30)
            {
                Point p_end = new Point(circleX - (int)(HAND * Math.Cos(ang * Math.PI / 180)), circleY - (int)(HAND * Math.Sin(ang * Math.PI / 180)));
                graphics.DrawLine(greenPen, new Point(circleX, circleY), p_end);
            }
            if (updatePicture)
            {
                graphics.Dispose();
                //load bitmap in picturebox1

                radarPictureBox.Image = bmp;
            }
        }
        private void eraseLines()
        {
            for (int i = 0; i < pointsArr.Count; i++)
            {
                graphics.DrawLine(blackPen, centerP, pointsArr[i]);
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

            // Draw radar hand
            Point startHand = new Point(circleX, circleY);
            Point endHand = new Point(handX, handY);

            if (adjustedDist == HAND) {
                graphics.DrawLine(greenPen, startHand, endHand);
            }
            else {
                graphics.DrawLine(redPen, startHand, endHand);
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

                port.Open();
                MessageBox.Show("Connected!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Connection Failed with response: " + ex.ToString());
            }

        }

        //Open file transfer window
        private void ButtonFile_Click(object sender, EventArgs e)
        {
            FormFileTransfer formFileTransfer = new FormFileTransfer();
            formFileTransfer.ShowDialog();
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
            port.Write("TELEMETRY_DEGREE");
        }
        private void scanButton_Click(object sender, EventArgs e)
        {
            port.Write("START_SCAN");
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
