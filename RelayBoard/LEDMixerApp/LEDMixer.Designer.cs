namespace LEDMixer
{
    partial class LEDMixer
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
            this.components = new System.ComponentModel.Container();
            this.serSerialPort = new System.IO.Ports.SerialPort(this.components);
            this.cbPort = new System.Windows.Forms.ComboBox();
            this.cb0 = new System.Windows.Forms.CheckBox();
            this.cb1 = new System.Windows.Forms.CheckBox();
            this.cb2 = new System.Windows.Forms.CheckBox();
            this.cb3 = new System.Windows.Forms.CheckBox();
            this.cb4 = new System.Windows.Forms.CheckBox();
            this.cb5 = new System.Windows.Forms.CheckBox();
            this.cb6 = new System.Windows.Forms.CheckBox();
            this.cb7 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // cbPort
            // 
            this.cbPort.FormattingEnabled = true;
            this.cbPort.Location = new System.Drawing.Point(97, 12);
            this.cbPort.Name = "cbPort";
            this.cbPort.Size = new System.Drawing.Size(99, 21);
            this.cbPort.TabIndex = 3;
            this.cbPort.SelectedIndexChanged += new System.EventHandler(this.cbPort_SelectedIndexChanged);
            // 
            // cb0
            // 
            this.cb0.AutoSize = true;
            this.cb0.Location = new System.Drawing.Point(12, 65);
            this.cb0.Name = "cb0";
            this.cb0.Size = new System.Drawing.Size(39, 17);
            this.cb0.TabIndex = 4;
            this.cb0.Text = "B0";
            this.cb0.UseVisualStyleBackColor = true;
            this.cb0.CheckedChanged += new System.EventHandler(this.cb0_CheckedChanged);
            // 
            // cb1
            // 
            this.cb1.AutoSize = true;
            this.cb1.Location = new System.Drawing.Point(12, 88);
            this.cb1.Name = "cb1";
            this.cb1.Size = new System.Drawing.Size(39, 17);
            this.cb1.TabIndex = 5;
            this.cb1.Text = "B1";
            this.cb1.UseVisualStyleBackColor = true;
            this.cb1.CheckedChanged += new System.EventHandler(this.cb1_CheckedChanged);
            // 
            // cb2
            // 
            this.cb2.AutoSize = true;
            this.cb2.Location = new System.Drawing.Point(12, 111);
            this.cb2.Name = "cb2";
            this.cb2.Size = new System.Drawing.Size(39, 17);
            this.cb2.TabIndex = 6;
            this.cb2.Text = "B2";
            this.cb2.UseVisualStyleBackColor = true;
            this.cb2.CheckedChanged += new System.EventHandler(this.cb2_CheckedChanged);
            // 
            // cb3
            // 
            this.cb3.AutoSize = true;
            this.cb3.Location = new System.Drawing.Point(12, 134);
            this.cb3.Name = "cb3";
            this.cb3.Size = new System.Drawing.Size(39, 17);
            this.cb3.TabIndex = 7;
            this.cb3.Text = "B3";
            this.cb3.UseVisualStyleBackColor = true;
            this.cb3.CheckedChanged += new System.EventHandler(this.cb3_CheckedChanged);
            // 
            // cb4
            // 
            this.cb4.AutoSize = true;
            this.cb4.Location = new System.Drawing.Point(57, 65);
            this.cb4.Name = "cb4";
            this.cb4.Size = new System.Drawing.Size(39, 17);
            this.cb4.TabIndex = 8;
            this.cb4.Text = "B4";
            this.cb4.UseVisualStyleBackColor = true;
            this.cb4.CheckedChanged += new System.EventHandler(this.cb4_CheckedChanged);
            // 
            // cb5
            // 
            this.cb5.AutoSize = true;
            this.cb5.Location = new System.Drawing.Point(57, 88);
            this.cb5.Name = "cb5";
            this.cb5.Size = new System.Drawing.Size(39, 17);
            this.cb5.TabIndex = 9;
            this.cb5.Text = "B5";
            this.cb5.UseVisualStyleBackColor = true;
            this.cb5.CheckedChanged += new System.EventHandler(this.cb5_CheckedChanged);
            // 
            // cb6
            // 
            this.cb6.AutoSize = true;
            this.cb6.Location = new System.Drawing.Point(57, 111);
            this.cb6.Name = "cb6";
            this.cb6.Size = new System.Drawing.Size(39, 17);
            this.cb6.TabIndex = 10;
            this.cb6.Text = "B6";
            this.cb6.UseVisualStyleBackColor = true;
            this.cb6.CheckedChanged += new System.EventHandler(this.cb6_CheckedChanged);
            // 
            // cb7
            // 
            this.cb7.AutoSize = true;
            this.cb7.Location = new System.Drawing.Point(57, 134);
            this.cb7.Name = "cb7";
            this.cb7.Size = new System.Drawing.Size(39, 17);
            this.cb7.TabIndex = 11;
            this.cb7.Text = "B7";
            this.cb7.UseVisualStyleBackColor = true;
            this.cb7.CheckedChanged += new System.EventHandler(this.cb7_CheckedChanged);
            // 
            // LEDMixer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 207);
            this.Controls.Add(this.cb7);
            this.Controls.Add(this.cb6);
            this.Controls.Add(this.cb5);
            this.Controls.Add(this.cb4);
            this.Controls.Add(this.cb3);
            this.Controls.Add(this.cb2);
            this.Controls.Add(this.cb1);
            this.Controls.Add(this.cb0);
            this.Controls.Add(this.cbPort);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LEDMixer";
            this.Text = "LED Mixer";
            this.Load += new System.EventHandler(this.LEDMixer_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serSerialPort;
        private System.Windows.Forms.ComboBox cbPort;
        private System.Windows.Forms.CheckBox cb0;
        private System.Windows.Forms.CheckBox cb1;
        private System.Windows.Forms.CheckBox cb2;
        private System.Windows.Forms.CheckBox cb3;
        private System.Windows.Forms.CheckBox cb4;
        private System.Windows.Forms.CheckBox cb5;
        private System.Windows.Forms.CheckBox cb6;
        private System.Windows.Forms.CheckBox cb7;
    }
}

