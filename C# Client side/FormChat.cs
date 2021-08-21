using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TerminalPC
{
    public partial class FormChat : Form
    {
        public FormChat()
        {
            InitializeComponent();
            this.richTextBox1.Text = "Hello User\n You can send up to 32 chars.\n Press Enter to send, look at the LCD (:\n ";
        }

        private void TextBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Enter)
            {
                richTextBox1.Text += "\n"+"["+ DateTime.Now+"]: " + textBox1.Text;
                try
                {
                    if (!Home.port.IsOpen)
                    {
                        Home.port.Open();
                    }

                    if(textBox1.Text.StartsWith("\r\n"))
                        // emit the \r\n
                        Home.port.Write("msg " + textBox1.Text.Substring(2) + "\r\n");
                    else
                        Home.port.Write("msg " + textBox1.Text + "\r\n");
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }

                Home.port.Close();
                textBox1.Text = "";
            } 
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
