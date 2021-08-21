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
            this.comboBoxSTPBIT = new System.Windows.Forms.ComboBox();
            this.comboBoxBaud = new System.Windows.Forms.ComboBox();
            this.buttonConnect = new System.Windows.Forms.Button();
            this.comboBoxParity = new System.Windows.Forms.ComboBox();
            this.labelCOM = new System.Windows.Forms.Label();
            this.labelBaud = new System.Windows.Forms.Label();
            this.labelSTPBIT = new System.Windows.Forms.Label();
            this.labelParity = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBoxCOM
            // 
            this.comboBoxCOM.FormattingEnabled = true;
            this.comboBoxCOM.Items.AddRange(new object[] {
            "COM4",
            "COM6"});
            this.comboBoxCOM.Location = new System.Drawing.Point(277, 102);
            this.comboBoxCOM.Name = "comboBoxCOM";
            this.comboBoxCOM.Size = new System.Drawing.Size(237, 21);
            this.comboBoxCOM.TabIndex = 1;
            this.comboBoxCOM.SelectedIndexChanged += new System.EventHandler(this.ComboBoxCOM_SelectedIndexChanged);
            // 
            // comboBoxSTPBIT
            // 
            this.comboBoxSTPBIT.FormattingEnabled = true;
            this.comboBoxSTPBIT.Items.AddRange(new object[] {
            "1",
            "2"});
            this.comboBoxSTPBIT.Location = new System.Drawing.Point(277, 183);
            this.comboBoxSTPBIT.Name = "comboBoxSTPBIT";
            this.comboBoxSTPBIT.Size = new System.Drawing.Size(237, 21);
            this.comboBoxSTPBIT.TabIndex = 2;
            // 
            // comboBoxBaud
            // 
            this.comboBoxBaud.FormattingEnabled = true;
            this.comboBoxBaud.Items.AddRange(new object[] {
            "2400",
            "9600",
            "19200",
            "38400"});
            this.comboBoxBaud.Location = new System.Drawing.Point(277, 141);
            this.comboBoxBaud.Name = "comboBoxBaud";
            this.comboBoxBaud.Size = new System.Drawing.Size(237, 21);
            this.comboBoxBaud.TabIndex = 4;
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(277, 264);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(109, 36);
            this.buttonConnect.TabIndex = 5;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.ButtonConnect_Click);
            // 
            // comboBoxParity
            // 
            this.comboBoxParity.FormattingEnabled = true;
            this.comboBoxParity.Items.AddRange(new object[] {
            "None",
            "Even",
            "Odd"});
            this.comboBoxParity.Location = new System.Drawing.Point(277, 226);
            this.comboBoxParity.Name = "comboBoxParity";
            this.comboBoxParity.Size = new System.Drawing.Size(237, 21);
            this.comboBoxParity.TabIndex = 6;
            // 
            // labelCOM
            // 
            this.labelCOM.AutoSize = true;
            this.labelCOM.Location = new System.Drawing.Point(274, 86);
            this.labelCOM.Name = "labelCOM";
            this.labelCOM.Size = new System.Drawing.Size(101, 13);
            this.labelCOM.TabIndex = 8;
            this.labelCOM.Text = "Choose a COM Port";
            // 
            // labelBaud
            // 
            this.labelBaud.AutoSize = true;
            this.labelBaud.Location = new System.Drawing.Point(274, 125);
            this.labelBaud.Name = "labelBaud";
            this.labelBaud.Size = new System.Drawing.Size(61, 13);
            this.labelBaud.TabIndex = 9;
            this.labelBaud.Text = "Baud Rate:";
            // 
            // labelSTPBIT
            // 
            this.labelSTPBIT.AutoSize = true;
            this.labelSTPBIT.Location = new System.Drawing.Point(274, 167);
            this.labelSTPBIT.Name = "labelSTPBIT";
            this.labelSTPBIT.Size = new System.Drawing.Size(52, 13);
            this.labelSTPBIT.TabIndex = 11;
            this.labelSTPBIT.Text = "Stop Bits:";
            // 
            // labelParity
            // 
            this.labelParity.AutoSize = true;
            this.labelParity.Location = new System.Drawing.Point(274, 207);
            this.labelParity.Name = "labelParity";
            this.labelParity.Size = new System.Drawing.Size(36, 13);
            this.labelParity.TabIndex = 12;
            this.labelParity.Text = "Parity:";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "txt files (*.txt)|*.txt";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label1.Font = new System.Drawing.Font("Bahnschrift Light", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Black;
            this.label1.Location = new System.Drawing.Point(100, 28);
            this.label1.Name = "label1";
            this.label1.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.label1.Size = new System.Drawing.Size(482, 21);
            this.label1.TabIndex = 15;
            this.label1.Text = "Communication Terminal By Katrin Nekhin and Elad Sofer";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(100, 196);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(112, 51);
            this.button1.TabIndex = 16;
            this.button1.Text = "Files Exchange";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.ButtonFile_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(100, 102);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(112, 44);
            this.button2.TabIndex = 17;
            this.button2.Text = "LCD Chat";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.ButtonChat_Click);
            // 
            // Home
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Menu;
            this.BackgroundImage = global::TerminalPC.Properties.Resources.background;
            this.ClientSize = new System.Drawing.Size(705, 319);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.labelParity);
            this.Controls.Add(this.labelSTPBIT);
            this.Controls.Add(this.labelBaud);
            this.Controls.Add(this.labelCOM);
            this.Controls.Add(this.comboBoxParity);
            this.Controls.Add(this.buttonConnect);
            this.Controls.Add(this.comboBoxBaud);
            this.Controls.Add(this.comboBoxSTPBIT);
            this.Controls.Add(this.comboBoxCOM);
            this.Name = "Home";
            this.Text = "Terminal";
            this.Load += new System.EventHandler(this.Home_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ComboBox comboBoxCOM;
        private System.Windows.Forms.ComboBox comboBoxSTPBIT;
        private System.Windows.Forms.ComboBox comboBoxBaud;
        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.ComboBox comboBoxParity;
        private System.Windows.Forms.Label labelCOM;
        private System.Windows.Forms.Label labelBaud;
        private System.Windows.Forms.Label labelSTPBIT;
        private System.Windows.Forms.Label labelParity;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}

