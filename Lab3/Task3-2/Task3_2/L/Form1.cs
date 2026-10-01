using System;
using System.IO.Ports;
using System.Windows.Forms;


namespace L
{
    public partial class Form1 : Form
    {
        SerialPort serialPort = new SerialPort("COM5", 9600);
        public Form1()
        {
            InitializeComponent();
            serialPort.Open();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort.Write("1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort.Write("0");
        }
    }
}
