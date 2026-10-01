using System;
using System.IO.Ports;
using System.Windows.Forms;

namespace advanced_Task3_3
{
    public partial class Form1 : Form
    {
        private System.IO.Ports.SerialPort serialPort; // 新增此行

        public Form1()
        {
            InitializeComponent();

            try
            {
                serialPort = new SerialPort("COM8", 9600);
                serialPort.Open();

                MessageBox.Show("已連線到 COM8");
            }
            catch (Exception ex)
            {
                MessageBox.Show("連線失敗：\n" + ex.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.Write("1");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.Write("0");
            }
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.Close();
            }

            base.OnFormClosing(e);
        }
    }
}
