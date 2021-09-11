namespace TerminalPC
{
    partial class Home
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Home));
            this.comboBoxCOM = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.labelCOM = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.labelParity = new System.Windows.Forms.Label();
            this.labelSTPBIT = new System.Windows.Forms.Label();
            this.labelBaud = new System.Windows.Forms.Label();
            this.comboBoxParity = new System.Windows.Forms.ComboBox();
            this.comboBoxBaud = new System.Windows.Forms.ComboBox();
            this.comboBoxSTPBIT = new System.Windows.Forms.ComboBox();
            this.scanButton = new System.Windows.Forms.Button();
            this.radarPictureBox = new System.Windows.Forms.PictureBox();
            this.telemetriaEnterAngleLabel = new System.Windows.Forms.Label();
            this.telemetriaDataTextBox = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.telemetriaPanel = new System.Windows.Forms.Panel();
            this.AngelDataLabel = new System.Windows.Forms.Label();
            this.DistanceDataLabel = new System.Windows.Forms.Label();
            this.AngelLabel = new System.Windows.Forms.Label();
            this.DistanceLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.MaskedDistanceTextBox = new System.Windows.Forms.TextBox();
            this.stopButton = new System.Windows.Forms.Button();
            this.buttonSend = new System.Windows.Forms.Button();
            this.buttonFilesLCD = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonChoose = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.StatusDataLabel = new System.Windows.Forms.Label();
            this.Status = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.ConnectionStatus = new System.Windows.Forms.Label();
            this.panel4 = new System.Windows.Forms.Panel();
            this.label4 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.radarPictureBox)).BeginInit();
            this.telemetriaPanel.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxCOM
            // 
            this.comboBoxCOM.FormattingEnabled = true;
            this.comboBoxCOM.Location = new System.Drawing.Point(34, 335);
            this.comboBoxCOM.Name = "comboBoxCOM";
            this.comboBoxCOM.Size = new System.Drawing.Size(237, 21);
            this.comboBoxCOM.TabIndex = 1;
            this.comboBoxCOM.SelectedIndexChanged += new System.EventHandler(this.ComboBoxCOM_SelectedIndexChanged);
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(31, 497);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(109, 36);
            this.buttonConnect.TabIndex = 5;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.ButtonConnect_Click);
            // 
            // labelCOM
            // 
            this.labelCOM.AutoSize = true;
            this.labelCOM.Location = new System.Drawing.Point(31, 319);
            this.labelCOM.Name = "labelCOM";
            this.labelCOM.Size = new System.Drawing.Size(101, 13);
            this.labelCOM.TabIndex = 8;
            this.labelCOM.Text = "Choose a COM Port";
            this.labelCOM.Click += new System.EventHandler(this.labelCOM_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "txt files (*.txt)|*.txt";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk_1);
            // 
            // labelParity
            // 
            this.labelParity.AutoSize = true;
            this.labelParity.Location = new System.Drawing.Point(32, 443);
            this.labelParity.Name = "labelParity";
            this.labelParity.Size = new System.Drawing.Size(36, 13);
            this.labelParity.TabIndex = 27;
            this.labelParity.Text = "Parity:";
            // 
            // labelSTPBIT
            // 
            this.labelSTPBIT.AutoSize = true;
            this.labelSTPBIT.Location = new System.Drawing.Point(31, 401);
            this.labelSTPBIT.Name = "labelSTPBIT";
            this.labelSTPBIT.Size = new System.Drawing.Size(52, 13);
            this.labelSTPBIT.TabIndex = 26;
            this.labelSTPBIT.Text = "Stop Bits:";
            // 
            // labelBaud
            // 
            this.labelBaud.AutoSize = true;
            this.labelBaud.Location = new System.Drawing.Point(31, 361);
            this.labelBaud.Name = "labelBaud";
            this.labelBaud.Size = new System.Drawing.Size(61, 13);
            this.labelBaud.TabIndex = 25;
            this.labelBaud.Text = "Baud Rate:";
            // 
            // comboBoxParity
            // 
            this.comboBoxParity.FormattingEnabled = true;
            this.comboBoxParity.Items.AddRange(new object[] {
            "None",
            "Even",
            "Odd"});
            this.comboBoxParity.Location = new System.Drawing.Point(34, 462);
            this.comboBoxParity.Name = "comboBoxParity";
            this.comboBoxParity.Size = new System.Drawing.Size(237, 21);
            this.comboBoxParity.TabIndex = 24;
            // 
            // comboBoxBaud
            // 
            this.comboBoxBaud.FormattingEnabled = true;
            this.comboBoxBaud.Items.AddRange(new object[] {
            "2400",
            "9600",
            "19200",
            "38400"});
            this.comboBoxBaud.Location = new System.Drawing.Point(34, 377);
            this.comboBoxBaud.Name = "comboBoxBaud";
            this.comboBoxBaud.Size = new System.Drawing.Size(237, 21);
            this.comboBoxBaud.TabIndex = 23;
            // 
            // comboBoxSTPBIT
            // 
            this.comboBoxSTPBIT.FormattingEnabled = true;
            this.comboBoxSTPBIT.Items.AddRange(new object[] {
            "1",
            "2"});
            this.comboBoxSTPBIT.Location = new System.Drawing.Point(34, 419);
            this.comboBoxSTPBIT.Name = "comboBoxSTPBIT";
            this.comboBoxSTPBIT.Size = new System.Drawing.Size(237, 21);
            this.comboBoxSTPBIT.TabIndex = 22;
            // 
            // scanButton
            // 
            this.scanButton.Enabled = false;
            this.scanButton.Location = new System.Drawing.Point(23, 210);
            this.scanButton.Name = "scanButton";
            this.scanButton.Size = new System.Drawing.Size(139, 66);
            this.scanButton.TabIndex = 28;
            this.scanButton.Text = "Start Scan";
            this.scanButton.UseVisualStyleBackColor = true;
            this.scanButton.Click += new System.EventHandler(this.scanButton_Click);
            // 
            // radarPictureBox
            // 
            this.radarPictureBox.Location = new System.Drawing.Point(426, 186);
            this.radarPictureBox.Margin = new System.Windows.Forms.Padding(2);
            this.radarPictureBox.Name = "radarPictureBox";
            this.radarPictureBox.Size = new System.Drawing.Size(814, 388);
            this.radarPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.radarPictureBox.TabIndex = 29;
            this.radarPictureBox.TabStop = false;
            this.radarPictureBox.Click += new System.EventHandler(this.radarPictureBox_Click);
            // 
            // telemetriaEnterAngleLabel
            // 
            this.telemetriaEnterAngleLabel.AutoSize = true;
            this.telemetriaEnterAngleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.telemetriaEnterAngleLabel.Location = new System.Drawing.Point(423, 47);
            this.telemetriaEnterAngleLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.telemetriaEnterAngleLabel.Name = "telemetriaEnterAngleLabel";
            this.telemetriaEnterAngleLabel.Size = new System.Drawing.Size(212, 17);
            this.telemetriaEnterAngleLabel.TabIndex = 32;
            this.telemetriaEnterAngleLabel.Text = "Enter Telemetry Angle (0°-180°)";
            // 
            // telemetriaDataTextBox
            // 
            this.telemetriaDataTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.telemetriaDataTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.telemetriaDataTextBox.Location = new System.Drawing.Point(430, 84);
            this.telemetriaDataTextBox.Margin = new System.Windows.Forms.Padding(2);
            this.telemetriaDataTextBox.Name = "telemetriaDataTextBox";
            this.telemetriaDataTextBox.Size = new System.Drawing.Size(145, 26);
            this.telemetriaDataTextBox.TabIndex = 31;
            this.telemetriaDataTextBox.TextChanged += new System.EventHandler(this.telemetriaDataTextBox_TextChanged);
            // 
            // button3
            // 
            this.button3.Enabled = false;
            this.button3.Location = new System.Drawing.Point(590, 82);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(94, 28);
            this.button3.TabIndex = 33;
            this.button3.Text = "Send Telemetry";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // telemetriaPanel
            // 
            this.telemetriaPanel.Controls.Add(this.AngelDataLabel);
            this.telemetriaPanel.Controls.Add(this.DistanceDataLabel);
            this.telemetriaPanel.Controls.Add(this.AngelLabel);
            this.telemetriaPanel.Controls.Add(this.DistanceLabel);
            this.telemetriaPanel.Location = new System.Drawing.Point(426, 123);
            this.telemetriaPanel.Margin = new System.Windows.Forms.Padding(2);
            this.telemetriaPanel.Name = "telemetriaPanel";
            this.telemetriaPanel.Size = new System.Drawing.Size(506, 44);
            this.telemetriaPanel.TabIndex = 34;
            this.telemetriaPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.telemetriaPanel_Paint);
            // 
            // AngelDataLabel
            // 
            this.AngelDataLabel.AutoSize = true;
            this.AngelDataLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.AngelDataLabel.Location = new System.Drawing.Point(372, 15);
            this.AngelDataLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.AngelDataLabel.Name = "AngelDataLabel";
            this.AngelDataLabel.Size = new System.Drawing.Size(13, 17);
            this.AngelDataLabel.TabIndex = 7;
            this.AngelDataLabel.Text = " ";
            this.AngelDataLabel.Click += new System.EventHandler(this.telemetriaOlLabel_Click);
            // 
            // DistanceDataLabel
            // 
            this.DistanceDataLabel.AutoSize = true;
            this.DistanceDataLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.DistanceDataLabel.Location = new System.Drawing.Point(146, 15);
            this.DistanceDataLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.DistanceDataLabel.Name = "DistanceDataLabel";
            this.DistanceDataLabel.Size = new System.Drawing.Size(13, 17);
            this.DistanceDataLabel.TabIndex = 6;
            this.DistanceDataLabel.Text = " ";
            // 
            // AngelLabel
            // 
            this.AngelLabel.AutoSize = true;
            this.AngelLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.AngelLabel.Location = new System.Drawing.Point(308, 12);
            this.AngelLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.AngelLabel.Name = "AngelLabel";
            this.AngelLabel.Size = new System.Drawing.Size(60, 20);
            this.AngelLabel.TabIndex = 5;
            this.AngelLabel.Text = "Angle:";
            this.AngelLabel.Click += new System.EventHandler(this.AngelLabel_Click);
            // 
            // DistanceLabel
            // 
            this.DistanceLabel.AutoSize = true;
            this.DistanceLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.DistanceLabel.Location = new System.Drawing.Point(57, 14);
            this.DistanceLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.DistanceLabel.Name = "DistanceLabel";
            this.DistanceLabel.Size = new System.Drawing.Size(85, 20);
            this.DistanceLabel.TabIndex = 4;
            this.DistanceLabel.Text = "Distance:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label1.Location = new System.Drawing.Point(705, 47);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(154, 17);
            this.label1.TabIndex = 36;
            this.label1.Text = "Enter Masked Distance";
            this.label1.Click += new System.EventHandler(this.label1_Click_1);
            // 
            // button4
            // 
            this.button4.Enabled = false;
            this.button4.Location = new System.Drawing.Point(867, 82);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(94, 29);
            this.button4.TabIndex = 37;
            this.button4.Text = "Save";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // MaskedDistanceTextBox
            // 
            this.MaskedDistanceTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.MaskedDistanceTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.MaskedDistanceTextBox.Location = new System.Drawing.Point(708, 84);
            this.MaskedDistanceTextBox.Margin = new System.Windows.Forms.Padding(2);
            this.MaskedDistanceTextBox.Name = "MaskedDistanceTextBox";
            this.MaskedDistanceTextBox.Size = new System.Drawing.Size(145, 26);
            this.MaskedDistanceTextBox.TabIndex = 38;
            this.MaskedDistanceTextBox.TextChanged += new System.EventHandler(this.MaskedDistanceTextBox_TextChanged);
            // 
            // stopButton
            // 
            this.stopButton.Enabled = false;
            this.stopButton.Location = new System.Drawing.Point(180, 210);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(139, 66);
            this.stopButton.TabIndex = 37;
            this.stopButton.Text = "Stop";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // buttonSend
            // 
            this.buttonSend.Enabled = false;
            this.buttonSend.Location = new System.Drawing.Point(37, 137);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(75, 23);
            this.buttonSend.TabIndex = 43;
            this.buttonSend.Text = "Send";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // buttonFilesLCD
            // 
            this.buttonFilesLCD.Enabled = false;
            this.buttonFilesLCD.Location = new System.Drawing.Point(127, 137);
            this.buttonFilesLCD.Name = "buttonFilesLCD";
            this.buttonFilesLCD.Size = new System.Drawing.Size(129, 23);
            this.buttonFilesLCD.TabIndex = 42;
            this.buttonFilesLCD.Text = "Show Scripts via LCD";
            this.buttonFilesLCD.UseVisualStyleBackColor = true;
            this.buttonFilesLCD.Click += new System.EventHandler(this.buttonFilesLCD_Click);
            // 
            // textBox1
            // 
            this.textBox1.Enabled = false;
            this.textBox1.Location = new System.Drawing.Point(33, 83);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(272, 20);
            this.textBox1.TabIndex = 41;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // buttonChoose
            // 
            this.buttonChoose.Enabled = false;
            this.buttonChoose.Location = new System.Drawing.Point(311, 80);
            this.buttonChoose.Name = "buttonChoose";
            this.buttonChoose.Size = new System.Drawing.Size(75, 23);
            this.buttonChoose.TabIndex = 39;
            this.buttonChoose.Text = "Browse";
            this.buttonChoose.UseVisualStyleBackColor = true;
            this.buttonChoose.Click += new System.EventHandler(this.buttonChoose_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label3.Location = new System.Drawing.Point(34, 47);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(128, 17);
            this.label3.TabIndex = 44;
            this.label3.Text = "Choose a script file";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Controls.Add(this.StatusDataLabel);
            this.panel1.Controls.Add(this.Status);
            this.panel1.Location = new System.Drawing.Point(946, 123);
            this.panel1.Margin = new System.Windows.Forms.Padding(2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(294, 44);
            this.panel1.TabIndex = 35;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.label5);
            this.panel2.Location = new System.Drawing.Point(29, 63);
            this.panel2.Margin = new System.Windows.Forms.Padding(2);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(269, 44);
            this.panel2.TabIndex = 36;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label2.Location = new System.Drawing.Point(86, 18);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 17);
            this.label2.TabIndex = 6;
            this.label2.Text = " ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label5.Location = new System.Drawing.Point(14, 15);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 20);
            this.label5.TabIndex = 4;
            this.label5.Text = "Status:";
            // 
            // StatusDataLabel
            // 
            this.StatusDataLabel.AutoSize = true;
            this.StatusDataLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.StatusDataLabel.Location = new System.Drawing.Point(86, 18);
            this.StatusDataLabel.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.StatusDataLabel.Name = "StatusDataLabel";
            this.StatusDataLabel.Size = new System.Drawing.Size(13, 17);
            this.StatusDataLabel.TabIndex = 6;
            this.StatusDataLabel.Text = " ";
            // 
            // Status
            // 
            this.Status.AutoSize = true;
            this.Status.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.Status.Location = new System.Drawing.Point(14, 15);
            this.Status.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.Status.Name = "Status";
            this.Status.Size = new System.Drawing.Size(67, 20);
            this.Status.TabIndex = 4;
            this.Status.Text = "Status:";
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.ConnectionStatus);
            this.panel3.Controls.Add(this.panel4);
            this.panel3.Location = new System.Drawing.Point(146, 497);
            this.panel3.Margin = new System.Windows.Forms.Padding(2);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(125, 36);
            this.panel3.TabIndex = 45;
            // 
            // ConnectionStatus
            // 
            this.ConnectionStatus.AutoSize = true;
            this.ConnectionStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.ConnectionStatus.ForeColor = System.Drawing.Color.Red;
            this.ConnectionStatus.Location = new System.Drawing.Point(3, 10);
            this.ConnectionStatus.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.ConnectionStatus.Name = "ConnectionStatus";
            this.ConnectionStatus.Size = new System.Drawing.Size(111, 17);
            this.ConnectionStatus.TabIndex = 46;
            this.ConnectionStatus.Text = " Disconnected";
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.label4);
            this.panel4.Controls.Add(this.label6);
            this.panel4.Location = new System.Drawing.Point(29, 63);
            this.panel4.Margin = new System.Windows.Forms.Padding(2);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(269, 44);
            this.panel4.TabIndex = 36;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label4.Location = new System.Drawing.Point(86, 18);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(13, 17);
            this.label4.TabIndex = 6;
            this.label4.Text = " ";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label6.Location = new System.Drawing.Point(14, 15);
            this.label6.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 20);
            this.label6.TabIndex = 4;
            this.label6.Text = "Status:";
            // 
            // Home
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Menu;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(1275, 595);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.buttonSend);
            this.Controls.Add(this.buttonFilesLCD);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.buttonChoose);
            this.Controls.Add(this.MaskedDistanceTextBox);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.telemetriaPanel);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.telemetriaEnterAngleLabel);
            this.Controls.Add(this.telemetriaDataTextBox);
            this.Controls.Add(this.radarPictureBox);
            this.Controls.Add(this.scanButton);
            this.Controls.Add(this.labelParity);
            this.Controls.Add(this.labelSTPBIT);
            this.Controls.Add(this.labelBaud);
            this.Controls.Add(this.comboBoxParity);
            this.Controls.Add(this.comboBoxBaud);
            this.Controls.Add(this.comboBoxSTPBIT);
            this.Controls.Add(this.labelCOM);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.comboBoxCOM);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Home";
            this.Text = "Final Project By Katrin Nekhin and Elad Sofer";
            this.Load += new System.EventHandler(this.Home_Load);
            ((System.ComponentModel.ISupportInitialize)(this.radarPictureBox)).EndInit();
            this.telemetriaPanel.ResumeLayout(false);
            this.telemetriaPanel.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox comboBoxCOM;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Label labelCOM;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label labelParity;
        private System.Windows.Forms.Label labelSTPBIT;
        private System.Windows.Forms.Label labelBaud;
        private System.Windows.Forms.ComboBox comboBoxParity;
        private System.Windows.Forms.ComboBox comboBoxBaud;
        private System.Windows.Forms.ComboBox comboBoxSTPBIT;
        private System.Windows.Forms.Button scanButton;
        private System.Windows.Forms.PictureBox radarPictureBox;
        private System.Windows.Forms.Label telemetriaEnterAngleLabel;
        private System.Windows.Forms.TextBox telemetriaDataTextBox;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Panel telemetriaPanel;
        private System.Windows.Forms.Label AngelDataLabel;
        private System.Windows.Forms.Label AngelLabel;
        private System.Windows.Forms.Label DistanceLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.TextBox MaskedDistanceTextBox;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.Button buttonFilesLCD;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button buttonChoose;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label DistanceDataLabel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label StatusDataLabel;
        private System.Windows.Forms.Label Status;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label ConnectionStatus;
    }
}

