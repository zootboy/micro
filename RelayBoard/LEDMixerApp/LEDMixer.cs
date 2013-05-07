using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LEDMixer
{
    public partial class LEDMixer : Form
    {
        public int checkboxStatus = 0x00;
        
        public LEDMixer()
        {
            InitializeComponent();
        }

        private void LEDMixer_Load(object sender, EventArgs e)
        {
            for (int i = 1; i <= 99; i++)
                cbPort.Items.Add("COM" + i.ToString());

            cbPort.SelectedIndex = 0;

        }
        
        private void NotifyLight()
        {
            byte[] buffer = new byte[1];
            buffer[0] = (byte)checkboxStatus;

            try
            {
                serSerialPort.PortName = cbPort.Text;
                serSerialPort.Open();
                serSerialPort.Write(buffer, 0, buffer.Length);
                serSerialPort.Close();
            }
            catch (Exception e)
            {

            }
        }

        private void cbPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            NotifyLight();
        }

        private void cb0_CheckedChanged(object sender, EventArgs e)
        {
            if (cb0.Checked) checkboxStatus |= (1 << 0);
            else checkboxStatus &= ~(1 << 0);
            NotifyLight();
        }

        private void cb1_CheckedChanged(object sender, EventArgs e)
        {
            if (cb1.Checked) checkboxStatus |= (1 << 1);
            else checkboxStatus &= ~(1 << 1);
            NotifyLight();
        }

        private void cb2_CheckedChanged(object sender, EventArgs e)
        {
            if (cb2.Checked) checkboxStatus |= (1 << 2);
            else checkboxStatus &= ~(1 << 2);
            NotifyLight();
        }

        private void cb3_CheckedChanged(object sender, EventArgs e)
        {
            if (cb3.Checked) checkboxStatus |= (1 << 3);
            else checkboxStatus &= ~(1 << 3);
            NotifyLight();
        }

        private void cb4_CheckedChanged(object sender, EventArgs e)
        {
            if (cb4.Checked) checkboxStatus |= (1 << 4);
            else checkboxStatus &= ~(1 << 4);
            NotifyLight();
        }

        private void cb5_CheckedChanged(object sender, EventArgs e)
        {
            if (cb5.Checked) checkboxStatus |= (1 << 5);
            else checkboxStatus &= ~(1 << 5);
            NotifyLight();
        }

        private void cb6_CheckedChanged(object sender, EventArgs e)
        {
            if (cb6.Checked) checkboxStatus |= (1 << 6);
            else checkboxStatus &= ~(1 << 6);
            NotifyLight();
        }

        private void cb7_CheckedChanged(object sender, EventArgs e)
        {
            if (cb7.Checked) checkboxStatus |= (1 << 7);
            else checkboxStatus &= ~(1 << 7);
            NotifyLight();
        }
        
    }
}
