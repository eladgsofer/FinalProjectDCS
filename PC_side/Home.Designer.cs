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
            this.comboBoxCOM = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.labelCOM = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.button1 = new System.Windows.Forms.Button();
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
            this.telemetriaOlLabel = new System.Windows.Forms.Label();
            this.telemetriaCmLabel = new System.Windows.Forms.Label();
            this.AngelLabel = new System.Windows.Forms.Label();
            this.DistanceLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.MaskedDistanceTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.radarPictureBox)).BeginInit();
            this.telemetriaPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxCOM
            // 
            this.comboBoxCOM.FormattingEnabled = true;
            this.comboBoxCOM.Items.AddRange(new object[] {
            "COM3",
            "COM4",
            "COM5",
            "COM6",
            "COM7"});
            this.comboBoxCOM.Location = new System.Drawing.Point(45, 412);
            this.comboBoxCOM.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.comboBoxCOM.Name = "comboBoxCOM";
            this.comboBoxCOM.Size = new System.Drawing.Size(315, 24);
            this.comboBoxCOM.TabIndex = 1;
            this.comboBoxCOM.SelectedIndexChanged += new System.EventHandler(this.ComboBoxCOM_SelectedIndexChanged);
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(45, 612);
            this.buttonConnect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(145, 44);
            this.buttonConnect.TabIndex = 5;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.ButtonConnect_Click);
            // 
            // labelCOM
            // 
            this.labelCOM.AutoSize = true;
            this.labelCOM.Location = new System.Drawing.Point(41, 393);
            this.labelCOM.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelCOM.Name = "labelCOM";
            this.labelCOM.Size = new System.Drawing.Size(133, 17);
            this.labelCOM.TabIndex = 8;
            this.labelCOM.Text = "Choose a COM Port";
            this.labelCOM.Click += new System.EventHandler(this.labelCOM_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "txt files (*.txt)|*.txt";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(45, 86);
            this.button1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(185, 81);
            this.button1.TabIndex = 16;
            this.button1.Text = "Send a script";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.ButtonFile_Click);
            // 
            // labelParity
            // 
            this.labelParity.AutoSize = true;
            this.labelParity.Location = new System.Drawing.Point(43, 545);
            this.labelParity.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelParity.Name = "labelParity";
            this.labelParity.Size = new System.Drawing.Size(48, 17);
            this.labelParity.TabIndex = 27;
            this.labelParity.Text = "Parity:";
            // 
            // labelSTPBIT
            // 
            this.labelSTPBIT.AutoSize = true;
            this.labelSTPBIT.Location = new System.Drawing.Point(41, 494);
            this.labelSTPBIT.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelSTPBIT.Name = "labelSTPBIT";
            this.labelSTPBIT.Size = new System.Drawing.Size(68, 17);
            this.labelSTPBIT.TabIndex = 26;
            this.labelSTPBIT.Text = "Stop Bits:";
            // 
            // labelBaud
            // 
            this.labelBaud.AutoSize = true;
            this.labelBaud.Location = new System.Drawing.Point(41, 444);
            this.labelBaud.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelBaud.Name = "labelBaud";
            this.labelBaud.Size = new System.Drawing.Size(79, 17);
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
            this.comboBoxParity.Location = new System.Drawing.Point(45, 569);
            this.comboBoxParity.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.comboBoxParity.Name = "comboBoxParity";
            this.comboBoxParity.Size = new System.Drawing.Size(315, 24);
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
            this.comboBoxBaud.Location = new System.Drawing.Point(45, 464);
            this.comboBoxBaud.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.comboBoxBaud.Name = "comboBoxBaud";
            this.comboBoxBaud.Size = new System.Drawing.Size(315, 24);
            this.comboBoxBaud.TabIndex = 23;
            // 
            // comboBoxSTPBIT
            // 
            this.comboBoxSTPBIT.FormattingEnabled = true;
            this.comboBoxSTPBIT.Items.AddRange(new object[] {
            "1",
            "2"});
            this.comboBoxSTPBIT.Location = new System.Drawing.Point(45, 516);
            this.comboBoxSTPBIT.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.comboBoxSTPBIT.Name = "comboBoxSTPBIT";
            this.comboBoxSTPBIT.Size = new System.Drawing.Size(315, 24);
            this.comboBoxSTPBIT.TabIndex = 22;
            // 
            // scanButton
            // 
            this.scanButton.Location = new System.Drawing.Point(45, 199);
            this.scanButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.scanButton.Name = "scanButton";
            this.scanButton.Size = new System.Drawing.Size(185, 81);
            this.scanButton.TabIndex = 28;
            this.scanButton.Text = "Start Scan";
            this.scanButton.UseVisualStyleBackColor = true;
            this.scanButton.Click += new System.EventHandler(this.scanButton_Click);
            // 
            // radarPictureBox
            // 
            this.radarPictureBox.Location = new System.Drawing.Point(499, 224);
            this.radarPictureBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radarPictureBox.Name = "radarPictureBox";
            this.radarPictureBox.Size = new System.Drawing.Size(1128, 478);
            this.radarPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.radarPictureBox.TabIndex = 29;
            this.radarPictureBox.TabStop = false;
            this.radarPictureBox.Click += new System.EventHandler(this.radarPictureBox_Click);
            // 
            // telemetriaEnterAngleLabel
            // 
            this.telemetriaEnterAngleLabel.AutoSize = true;
            this.telemetriaEnterAngleLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.telemetriaEnterAngleLabel.Location = new System.Drawing.Point(496, 58);
            this.telemetriaEnterAngleLabel.Name = "telemetriaEnterAngleLabel";
            this.telemetriaEnterAngleLabel.Size = new System.Drawing.Size(248, 20);
            this.telemetriaEnterAngleLabel.TabIndex = 32;
            this.telemetriaEnterAngleLabel.Text = "Enter Telemetry Angle (0°-180°)";
            // 
            // telemetriaDataTextBox
            // 
            this.telemetriaDataTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.telemetriaDataTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.telemetriaDataTextBox.Location = new System.Drawing.Point(497, 97);
            this.telemetriaDataTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.telemetriaDataTextBox.Name = "telemetriaDataTextBox";
            this.telemetriaDataTextBox.Size = new System.Drawing.Size(192, 30);
            this.telemetriaDataTextBox.TabIndex = 31;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(723, 95);
            this.button3.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(125, 30);
            this.button3.TabIndex = 33;
            this.button3.Text = "Send Telemetry";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // telemetriaPanel
            // 
            this.telemetriaPanel.Controls.Add(this.telemetriaOlLabel);
            this.telemetriaPanel.Controls.Add(this.telemetriaCmLabel);
            this.telemetriaPanel.Controls.Add(this.AngelLabel);
            this.telemetriaPanel.Controls.Add(this.DistanceLabel);
            this.telemetriaPanel.Location = new System.Drawing.Point(499, 149);
            this.telemetriaPanel.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.telemetriaPanel.Name = "telemetriaPanel";
            this.telemetriaPanel.Size = new System.Drawing.Size(611, 54);
            this.telemetriaPanel.TabIndex = 34;
            this.telemetriaPanel.Visible = false;
            // 
            // telemetriaOlLabel
            // 
            this.telemetriaOlLabel.AutoSize = true;
            this.telemetriaOlLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.telemetriaOlLabel.Location = new System.Drawing.Point(497, 9);
            this.telemetriaOlLabel.Name = "telemetriaOlLabel";
            this.telemetriaOlLabel.Size = new System.Drawing.Size(17, 20);
            this.telemetriaOlLabel.TabIndex = 7;
            this.telemetriaOlLabel.Text = "°";
            // 
            // telemetriaCmLabel
            // 
            this.telemetriaCmLabel.AutoSize = true;
            this.telemetriaCmLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.telemetriaCmLabel.Location = new System.Drawing.Point(287, 18);
            this.telemetriaCmLabel.Name = "telemetriaCmLabel";
            this.telemetriaCmLabel.Size = new System.Drawing.Size(34, 20);
            this.telemetriaCmLabel.TabIndex = 6;
            this.telemetriaCmLabel.Text = "cm";
            this.telemetriaCmLabel.Visible = false;
            // 
            // AngelLabel
            // 
            this.AngelLabel.AutoSize = true;
            this.AngelLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.AngelLabel.Location = new System.Drawing.Point(383, 16);
            this.AngelLabel.Name = "AngelLabel";
            this.AngelLabel.Size = new System.Drawing.Size(75, 25);
            this.AngelLabel.TabIndex = 5;
            this.AngelLabel.Text = "Angle:";
            // 
            // DistanceLabel
            // 
            this.DistanceLabel.AutoSize = true;
            this.DistanceLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.DistanceLabel.Location = new System.Drawing.Point(76, 17);
            this.DistanceLabel.Name = "DistanceLabel";
            this.DistanceLabel.Size = new System.Drawing.Size(103, 25);
            this.DistanceLabel.TabIndex = 4;
            this.DistanceLabel.Text = "Distance:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.label1.Location = new System.Drawing.Point(916, 58);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(184, 20);
            this.label1.TabIndex = 36;
            this.label1.Text = "Enter Masked Distance";
            this.label1.Click += new System.EventHandler(this.label1_Click_1);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(1140, 95);
            this.button4.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(125, 30);
            this.button4.TabIndex = 37;
            this.button4.Text = "Save";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // MaskedDistanceTextBox
            // 
            this.MaskedDistanceTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.MaskedDistanceTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(177)));
            this.MaskedDistanceTextBox.Location = new System.Drawing.Point(917, 97);
            this.MaskedDistanceTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MaskedDistanceTextBox.Name = "MaskedDistanceTextBox";
            this.MaskedDistanceTextBox.Size = new System.Drawing.Size(192, 30);
            this.MaskedDistanceTextBox.TabIndex = 38;
            this.MaskedDistanceTextBox.TextChanged += new System.EventHandler(this.MaskedDistanceTextBox_TextChanged);
            // 
            // Home
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Menu;
            this.BackgroundImage = global::TerminalPC.Properties.Resources.d4xmmg4_883c5c3d_2e64_445f_8dc4_a7c4eef8f41c;
            this.ClientSize = new System.Drawing.Size(1656, 720);
            this.Controls.Add(this.MaskedDistanceTextBox);
            this.Controls.Add(this.button4);
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
            this.Controls.Add(this.button1);
            this.Controls.Add(this.labelCOM);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.comboBoxCOM);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Home";
            this.Text = "Final Project By Katrin Nekhin and Elad Sofer";
            this.Load += new System.EventHandler(this.Home_Load);
            ((System.ComponentModel.ISupportInitialize)(this.radarPictureBox)).EndInit();
            this.telemetriaPanel.ResumeLayout(false);
            this.telemetriaPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox comboBoxCOM;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.Label labelCOM;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button button1;
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
        private System.Windows.Forms.Label telemetriaOlLabel;
        private System.Windows.Forms.Label telemetriaCmLabel;
        private System.Windows.Forms.Label AngelLabel;
        private System.Windows.Forms.Label DistanceLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.TextBox MaskedDistanceTextBox;
    }
}

