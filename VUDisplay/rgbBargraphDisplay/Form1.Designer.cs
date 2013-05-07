namespace rgbBargraphDisplay
    {
    partial class Form1
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
                this.statusStrip1 = new System.Windows.Forms.StatusStrip();
                this.usbToolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
                this.displayUpdateTimer = new System.Windows.Forms.Timer(this.components);
                this.leftVolumeStaticLabel = new System.Windows.Forms.Label();
                this.rightVolumeStaticLabel = new System.Windows.Forms.Label();
                this.leftVolumeLabel = new System.Windows.Forms.Label();
                this.rightVolumeLabel = new System.Windows.Forms.Label();
                this.bargraphOutputGroupBox = new System.Windows.Forms.GroupBox();
                this.led16Label = new System.Windows.Forms.Label();
                this.led15Label = new System.Windows.Forms.Label();
                this.led14Label = new System.Windows.Forms.Label();
                this.led13Label = new System.Windows.Forms.Label();
                this.led12Label = new System.Windows.Forms.Label();
                this.led11Label = new System.Windows.Forms.Label();
                this.led10Label = new System.Windows.Forms.Label();
                this.led9Label = new System.Windows.Forms.Label();
                this.led8Label = new System.Windows.Forms.Label();
                this.led7Label = new System.Windows.Forms.Label();
                this.led6Label = new System.Windows.Forms.Label();
                this.led5Label = new System.Windows.Forms.Label();
                this.led4Label = new System.Windows.Forms.Label();
                this.led3Label = new System.Windows.Forms.Label();
                this.led2Label = new System.Windows.Forms.Label();
                this.led1Label = new System.Windows.Forms.Label();
                this.groupBox1 = new System.Windows.Forms.GroupBox();
                this.label2 = new System.Windows.Forms.Label();
                this.label1 = new System.Windows.Forms.Label();
                this.rightDecibelLabel = new System.Windows.Forms.Label();
                this.leftDecibelLabel = new System.Windows.Forms.Label();
                this.groupBox2 = new System.Windows.Forms.GroupBox();
                this.ledFadeOffSpeedLabel = new System.Windows.Forms.Label();
                this.ledFadeOffSpeedStaticLabel = new System.Windows.Forms.Label();
                this.ledFadeOffSpeedTrackBar = new System.Windows.Forms.TrackBar();
                this.displayDampingRateLabel = new System.Windows.Forms.Label();
                this.displayDampingRateStaticLabel = new System.Windows.Forms.Label();
                this.displayDamperTrackBar = new System.Windows.Forms.TrackBar();
                this.groupBox3 = new System.Windows.Forms.GroupBox();
                this.peakColourLengthLabel = new System.Windows.Forms.Label();
                this.peakColourLengthStaticLabel = new System.Windows.Forms.Label();
                this.PeakColourLengthTrackBar = new System.Windows.Forms.TrackBar();
                this.endColourButton = new System.Windows.Forms.Button();
                this.startColourButton = new System.Windows.Forms.Button();
                this.startColourDialog = new System.Windows.Forms.ColorDialog();
                this.endColourDialog = new System.Windows.Forms.ColorDialog();
                this.groupBox4 = new System.Windows.Forms.GroupBox();
                this.displayTypeRadioButton3 = new System.Windows.Forms.RadioButton();
                this.displayTypeRadioButton2 = new System.Windows.Forms.RadioButton();
                this.displayTypeRadioButton1 = new System.Windows.Forms.RadioButton();
                this.serSerialPort = new System.IO.Ports.SerialPort(this.components);
                this.statusStrip1.SuspendLayout();
                this.bargraphOutputGroupBox.SuspendLayout();
                this.groupBox1.SuspendLayout();
                this.groupBox2.SuspendLayout();
                ((System.ComponentModel.ISupportInitialize)(this.ledFadeOffSpeedTrackBar)).BeginInit();
                ((System.ComponentModel.ISupportInitialize)(this.displayDamperTrackBar)).BeginInit();
                this.groupBox3.SuspendLayout();
                ((System.ComponentModel.ISupportInitialize)(this.PeakColourLengthTrackBar)).BeginInit();
                this.groupBox4.SuspendLayout();
                this.SuspendLayout();
                // 
                // statusStrip1
                // 
                this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.usbToolStripStatusLabel});
                this.statusStrip1.Location = new System.Drawing.Point(0, 491);
                this.statusStrip1.Name = "statusStrip1";
                this.statusStrip1.Size = new System.Drawing.Size(341, 22);
                this.statusStrip1.TabIndex = 0;
                this.statusStrip1.Text = "statusStrip1";
                // 
                // usbToolStripStatusLabel
                // 
                this.usbToolStripStatusLabel.Name = "usbToolStripStatusLabel";
                this.usbToolStripStatusLabel.Size = new System.Drawing.Size(58, 17);
                this.usbToolStripStatusLabel.Text = "Unknown";
                // 
                // displayUpdateTimer
                // 
                this.displayUpdateTimer.Enabled = true;
                this.displayUpdateTimer.Interval = 10;
                this.displayUpdateTimer.Tick += new System.EventHandler(this.displayUpdateTimer_Tick);
                // 
                // leftVolumeStaticLabel
                // 
                this.leftVolumeStaticLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
                this.leftVolumeStaticLabel.AutoSize = true;
                this.leftVolumeStaticLabel.Location = new System.Drawing.Point(11, 25);
                this.leftVolumeStaticLabel.Name = "leftVolumeStaticLabel";
                this.leftVolumeStaticLabel.Size = new System.Drawing.Size(66, 13);
                this.leftVolumeStaticLabel.TabIndex = 5;
                this.leftVolumeStaticLabel.Text = "Left Volume:";
                // 
                // rightVolumeStaticLabel
                // 
                this.rightVolumeStaticLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
                this.rightVolumeStaticLabel.AutoSize = true;
                this.rightVolumeStaticLabel.Location = new System.Drawing.Point(4, 38);
                this.rightVolumeStaticLabel.Name = "rightVolumeStaticLabel";
                this.rightVolumeStaticLabel.Size = new System.Drawing.Size(73, 13);
                this.rightVolumeStaticLabel.TabIndex = 6;
                this.rightVolumeStaticLabel.Text = "Right Volume:";
                // 
                // leftVolumeLabel
                // 
                this.leftVolumeLabel.AutoSize = true;
                this.leftVolumeLabel.Location = new System.Drawing.Point(78, 25);
                this.leftVolumeLabel.Name = "leftVolumeLabel";
                this.leftVolumeLabel.Size = new System.Drawing.Size(19, 13);
                this.leftVolumeLabel.TabIndex = 7;
                this.leftVolumeLabel.Text = "99";
                // 
                // rightVolumeLabel
                // 
                this.rightVolumeLabel.AutoSize = true;
                this.rightVolumeLabel.Location = new System.Drawing.Point(78, 38);
                this.rightVolumeLabel.Name = "rightVolumeLabel";
                this.rightVolumeLabel.Size = new System.Drawing.Size(19, 13);
                this.rightVolumeLabel.TabIndex = 8;
                this.rightVolumeLabel.Text = "99";
                // 
                // bargraphOutputGroupBox
                // 
                this.bargraphOutputGroupBox.Controls.Add(this.led16Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led15Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led14Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led13Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led12Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led11Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led10Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led9Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led8Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led7Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led6Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led5Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led4Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led3Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led2Label);
                this.bargraphOutputGroupBox.Controls.Add(this.led1Label);
                this.bargraphOutputGroupBox.Location = new System.Drawing.Point(13, 13);
                this.bargraphOutputGroupBox.Name = "bargraphOutputGroupBox";
                this.bargraphOutputGroupBox.Size = new System.Drawing.Size(313, 42);
                this.bargraphOutputGroupBox.TabIndex = 9;
                this.bargraphOutputGroupBox.TabStop = false;
                this.bargraphOutputGroupBox.Text = "Bargraph Status";
                // 
                // led16Label
                // 
                this.led16Label.AutoSize = true;
                this.led16Label.BackColor = System.Drawing.Color.Black;
                this.led16Label.Location = new System.Drawing.Point(292, 20);
                this.led16Label.Name = "led16Label";
                this.led16Label.Size = new System.Drawing.Size(13, 13);
                this.led16Label.TabIndex = 15;
                this.led16Label.Text = "  ";
                // 
                // led15Label
                // 
                this.led15Label.AutoSize = true;
                this.led15Label.BackColor = System.Drawing.Color.Black;
                this.led15Label.Location = new System.Drawing.Point(273, 20);
                this.led15Label.Name = "led15Label";
                this.led15Label.Size = new System.Drawing.Size(13, 13);
                this.led15Label.TabIndex = 14;
                this.led15Label.Text = "  ";
                // 
                // led14Label
                // 
                this.led14Label.AutoSize = true;
                this.led14Label.BackColor = System.Drawing.Color.Black;
                this.led14Label.Location = new System.Drawing.Point(254, 20);
                this.led14Label.Name = "led14Label";
                this.led14Label.Size = new System.Drawing.Size(13, 13);
                this.led14Label.TabIndex = 13;
                this.led14Label.Text = "  ";
                // 
                // led13Label
                // 
                this.led13Label.AutoSize = true;
                this.led13Label.BackColor = System.Drawing.Color.Black;
                this.led13Label.Location = new System.Drawing.Point(235, 20);
                this.led13Label.Name = "led13Label";
                this.led13Label.Size = new System.Drawing.Size(13, 13);
                this.led13Label.TabIndex = 12;
                this.led13Label.Text = "  ";
                // 
                // led12Label
                // 
                this.led12Label.AutoSize = true;
                this.led12Label.BackColor = System.Drawing.Color.Black;
                this.led12Label.Location = new System.Drawing.Point(216, 20);
                this.led12Label.Name = "led12Label";
                this.led12Label.Size = new System.Drawing.Size(13, 13);
                this.led12Label.TabIndex = 11;
                this.led12Label.Text = "  ";
                // 
                // led11Label
                // 
                this.led11Label.AutoSize = true;
                this.led11Label.BackColor = System.Drawing.Color.Black;
                this.led11Label.Location = new System.Drawing.Point(197, 20);
                this.led11Label.Name = "led11Label";
                this.led11Label.Size = new System.Drawing.Size(13, 13);
                this.led11Label.TabIndex = 10;
                this.led11Label.Text = "  ";
                // 
                // led10Label
                // 
                this.led10Label.AutoSize = true;
                this.led10Label.BackColor = System.Drawing.Color.Black;
                this.led10Label.Location = new System.Drawing.Point(178, 20);
                this.led10Label.Name = "led10Label";
                this.led10Label.Size = new System.Drawing.Size(13, 13);
                this.led10Label.TabIndex = 9;
                this.led10Label.Text = "  ";
                // 
                // led9Label
                // 
                this.led9Label.AutoSize = true;
                this.led9Label.BackColor = System.Drawing.Color.Black;
                this.led9Label.Location = new System.Drawing.Point(159, 20);
                this.led9Label.Name = "led9Label";
                this.led9Label.Size = new System.Drawing.Size(13, 13);
                this.led9Label.TabIndex = 8;
                this.led9Label.Text = "  ";
                // 
                // led8Label
                // 
                this.led8Label.AutoSize = true;
                this.led8Label.BackColor = System.Drawing.Color.Black;
                this.led8Label.Location = new System.Drawing.Point(140, 20);
                this.led8Label.Name = "led8Label";
                this.led8Label.Size = new System.Drawing.Size(13, 13);
                this.led8Label.TabIndex = 7;
                this.led8Label.Text = "  ";
                // 
                // led7Label
                // 
                this.led7Label.AutoSize = true;
                this.led7Label.BackColor = System.Drawing.Color.Black;
                this.led7Label.Location = new System.Drawing.Point(121, 20);
                this.led7Label.Name = "led7Label";
                this.led7Label.Size = new System.Drawing.Size(13, 13);
                this.led7Label.TabIndex = 6;
                this.led7Label.Text = "  ";
                // 
                // led6Label
                // 
                this.led6Label.AutoSize = true;
                this.led6Label.BackColor = System.Drawing.Color.Black;
                this.led6Label.Location = new System.Drawing.Point(102, 20);
                this.led6Label.Name = "led6Label";
                this.led6Label.Size = new System.Drawing.Size(13, 13);
                this.led6Label.TabIndex = 5;
                this.led6Label.Text = "  ";
                // 
                // led5Label
                // 
                this.led5Label.AutoSize = true;
                this.led5Label.BackColor = System.Drawing.Color.Black;
                this.led5Label.Location = new System.Drawing.Point(83, 20);
                this.led5Label.Name = "led5Label";
                this.led5Label.Size = new System.Drawing.Size(13, 13);
                this.led5Label.TabIndex = 4;
                this.led5Label.Text = "  ";
                // 
                // led4Label
                // 
                this.led4Label.AutoSize = true;
                this.led4Label.BackColor = System.Drawing.Color.Black;
                this.led4Label.Location = new System.Drawing.Point(64, 20);
                this.led4Label.Name = "led4Label";
                this.led4Label.Size = new System.Drawing.Size(13, 13);
                this.led4Label.TabIndex = 3;
                this.led4Label.Text = "  ";
                // 
                // led3Label
                // 
                this.led3Label.AutoSize = true;
                this.led3Label.BackColor = System.Drawing.Color.Black;
                this.led3Label.Location = new System.Drawing.Point(45, 20);
                this.led3Label.Name = "led3Label";
                this.led3Label.Size = new System.Drawing.Size(13, 13);
                this.led3Label.TabIndex = 2;
                this.led3Label.Text = "  ";
                // 
                // led2Label
                // 
                this.led2Label.AutoSize = true;
                this.led2Label.BackColor = System.Drawing.Color.Black;
                this.led2Label.Location = new System.Drawing.Point(26, 20);
                this.led2Label.Name = "led2Label";
                this.led2Label.Size = new System.Drawing.Size(13, 13);
                this.led2Label.TabIndex = 1;
                this.led2Label.Text = "  ";
                // 
                // led1Label
                // 
                this.led1Label.AutoSize = true;
                this.led1Label.BackColor = System.Drawing.Color.Black;
                this.led1Label.Location = new System.Drawing.Point(7, 20);
                this.led1Label.Name = "led1Label";
                this.led1Label.Size = new System.Drawing.Size(13, 13);
                this.led1Label.TabIndex = 0;
                this.led1Label.Text = "  ";
                // 
                // groupBox1
                // 
                this.groupBox1.Controls.Add(this.label2);
                this.groupBox1.Controls.Add(this.label1);
                this.groupBox1.Controls.Add(this.rightDecibelLabel);
                this.groupBox1.Controls.Add(this.leftDecibelLabel);
                this.groupBox1.Controls.Add(this.leftVolumeStaticLabel);
                this.groupBox1.Controls.Add(this.rightVolumeStaticLabel);
                this.groupBox1.Controls.Add(this.rightVolumeLabel);
                this.groupBox1.Controls.Add(this.leftVolumeLabel);
                this.groupBox1.Location = new System.Drawing.Point(13, 62);
                this.groupBox1.Name = "groupBox1";
                this.groupBox1.Size = new System.Drawing.Size(313, 62);
                this.groupBox1.TabIndex = 10;
                this.groupBox1.TabStop = false;
                this.groupBox1.Text = "Volume Output Levels";
                // 
                // label2
                // 
                this.label2.AutoSize = true;
                this.label2.Location = new System.Drawing.Point(131, 38);
                this.label2.Name = "label2";
                this.label2.Size = new System.Drawing.Size(25, 13);
                this.label2.TabIndex = 12;
                this.label2.Text = "dBs";
                // 
                // label1
                // 
                this.label1.AutoSize = true;
                this.label1.Location = new System.Drawing.Point(131, 25);
                this.label1.Name = "label1";
                this.label1.Size = new System.Drawing.Size(25, 13);
                this.label1.TabIndex = 11;
                this.label1.Text = "dBs";
                // 
                // rightDecibelLabel
                // 
                this.rightDecibelLabel.AutoSize = true;
                this.rightDecibelLabel.Location = new System.Drawing.Point(103, 38);
                this.rightDecibelLabel.Name = "rightDecibelLabel";
                this.rightDecibelLabel.Size = new System.Drawing.Size(22, 13);
                this.rightDecibelLabel.TabIndex = 10;
                this.rightDecibelLabel.Text = "-40";
                // 
                // leftDecibelLabel
                // 
                this.leftDecibelLabel.AutoSize = true;
                this.leftDecibelLabel.Location = new System.Drawing.Point(103, 25);
                this.leftDecibelLabel.Name = "leftDecibelLabel";
                this.leftDecibelLabel.Size = new System.Drawing.Size(22, 13);
                this.leftDecibelLabel.TabIndex = 9;
                this.leftDecibelLabel.Text = "-40";
                // 
                // groupBox2
                // 
                this.groupBox2.Controls.Add(this.ledFadeOffSpeedLabel);
                this.groupBox2.Controls.Add(this.ledFadeOffSpeedStaticLabel);
                this.groupBox2.Controls.Add(this.ledFadeOffSpeedTrackBar);
                this.groupBox2.Controls.Add(this.displayDampingRateLabel);
                this.groupBox2.Controls.Add(this.displayDampingRateStaticLabel);
                this.groupBox2.Controls.Add(this.displayDamperTrackBar);
                this.groupBox2.Location = new System.Drawing.Point(13, 131);
                this.groupBox2.Name = "groupBox2";
                this.groupBox2.Size = new System.Drawing.Size(313, 127);
                this.groupBox2.TabIndex = 11;
                this.groupBox2.TabStop = false;
                this.groupBox2.Text = "Display controls";
                // 
                // ledFadeOffSpeedLabel
                // 
                this.ledFadeOffSpeedLabel.AutoSize = true;
                this.ledFadeOffSpeedLabel.Location = new System.Drawing.Point(197, 104);
                this.ledFadeOffSpeedLabel.Name = "ledFadeOffSpeedLabel";
                this.ledFadeOffSpeedLabel.Size = new System.Drawing.Size(13, 13);
                this.ledFadeOffSpeedLabel.TabIndex = 5;
                this.ledFadeOffSpeedLabel.Text = "1";
                // 
                // ledFadeOffSpeedStaticLabel
                // 
                this.ledFadeOffSpeedStaticLabel.AutoSize = true;
                this.ledFadeOffSpeedStaticLabel.Location = new System.Drawing.Point(83, 104);
                this.ledFadeOffSpeedStaticLabel.Name = "ledFadeOffSpeedStaticLabel";
                this.ledFadeOffSpeedStaticLabel.Size = new System.Drawing.Size(105, 13);
                this.ledFadeOffSpeedStaticLabel.TabIndex = 4;
                this.ledFadeOffSpeedStaticLabel.Text = "LED Fade off speed:";
                // 
                // ledFadeOffSpeedTrackBar
                // 
                this.ledFadeOffSpeedTrackBar.Location = new System.Drawing.Point(7, 72);
                this.ledFadeOffSpeedTrackBar.Name = "ledFadeOffSpeedTrackBar";
                this.ledFadeOffSpeedTrackBar.Size = new System.Drawing.Size(298, 45);
                this.ledFadeOffSpeedTrackBar.TabIndex = 3;
                this.ledFadeOffSpeedTrackBar.Value = 1;
                this.ledFadeOffSpeedTrackBar.Scroll += new System.EventHandler(this.ledFadeOffSpeedTrackBar_Scroll);
                // 
                // displayDampingRateLabel
                // 
                this.displayDampingRateLabel.AutoSize = true;
                this.displayDampingRateLabel.Location = new System.Drawing.Point(197, 52);
                this.displayDampingRateLabel.Name = "displayDampingRateLabel";
                this.displayDampingRateLabel.Size = new System.Drawing.Size(13, 13);
                this.displayDampingRateLabel.TabIndex = 2;
                this.displayDampingRateLabel.Text = "1";
                // 
                // displayDampingRateStaticLabel
                // 
                this.displayDampingRateStaticLabel.AutoSize = true;
                this.displayDampingRateStaticLabel.Location = new System.Drawing.Point(68, 52);
                this.displayDampingRateStaticLabel.Name = "displayDampingRateStaticLabel";
                this.displayDampingRateStaticLabel.Size = new System.Drawing.Size(123, 13);
                this.displayDampingRateStaticLabel.TabIndex = 1;
                this.displayDampingRateStaticLabel.Text = "Display Damping Speed:";
                this.displayDampingRateStaticLabel.Click += new System.EventHandler(this.displayDampingRateStaticLabel_Click);
                // 
                // displayDamperTrackBar
                // 
                this.displayDamperTrackBar.Location = new System.Drawing.Point(7, 20);
                this.displayDamperTrackBar.Name = "displayDamperTrackBar";
                this.displayDamperTrackBar.Size = new System.Drawing.Size(298, 45);
                this.displayDamperTrackBar.TabIndex = 0;
                this.displayDamperTrackBar.Value = 1;
                this.displayDamperTrackBar.Scroll += new System.EventHandler(this.displayDamperTrackBar_Scroll);
                // 
                // groupBox3
                // 
                this.groupBox3.Controls.Add(this.peakColourLengthLabel);
                this.groupBox3.Controls.Add(this.peakColourLengthStaticLabel);
                this.groupBox3.Controls.Add(this.PeakColourLengthTrackBar);
                this.groupBox3.Controls.Add(this.endColourButton);
                this.groupBox3.Controls.Add(this.startColourButton);
                this.groupBox3.Location = new System.Drawing.Point(13, 265);
                this.groupBox3.Name = "groupBox3";
                this.groupBox3.Size = new System.Drawing.Size(313, 110);
                this.groupBox3.TabIndex = 12;
                this.groupBox3.TabStop = false;
                this.groupBox3.Text = "Display Colours";
                // 
                // peakColourLengthLabel
                // 
                this.peakColourLengthLabel.AutoSize = true;
                this.peakColourLengthLabel.Location = new System.Drawing.Point(197, 82);
                this.peakColourLengthLabel.Name = "peakColourLengthLabel";
                this.peakColourLengthLabel.Size = new System.Drawing.Size(13, 13);
                this.peakColourLengthLabel.TabIndex = 4;
                this.peakColourLengthLabel.Text = "3";
                // 
                // peakColourLengthStaticLabel
                // 
                this.peakColourLengthStaticLabel.AutoSize = true;
                this.peakColourLengthStaticLabel.Location = new System.Drawing.Point(84, 82);
                this.peakColourLengthStaticLabel.Name = "peakColourLengthStaticLabel";
                this.peakColourLengthStaticLabel.Size = new System.Drawing.Size(104, 13);
                this.peakColourLengthStaticLabel.TabIndex = 3;
                this.peakColourLengthStaticLabel.Text = "Peak Colour Length:";
                // 
                // PeakColourLengthTrackBar
                // 
                this.PeakColourLengthTrackBar.Location = new System.Drawing.Point(10, 50);
                this.PeakColourLengthTrackBar.Maximum = 8;
                this.PeakColourLengthTrackBar.Minimum = 1;
                this.PeakColourLengthTrackBar.Name = "PeakColourLengthTrackBar";
                this.PeakColourLengthTrackBar.Size = new System.Drawing.Size(295, 45);
                this.PeakColourLengthTrackBar.TabIndex = 2;
                this.PeakColourLengthTrackBar.Value = 3;
                this.PeakColourLengthTrackBar.Scroll += new System.EventHandler(this.PeakColourLengthTrackBar_Scroll);
                // 
                // endColourButton
                // 
                this.endColourButton.BackColor = System.Drawing.Color.Red;
                this.endColourButton.Location = new System.Drawing.Point(86, 19);
                this.endColourButton.Name = "endColourButton";
                this.endColourButton.Size = new System.Drawing.Size(75, 23);
                this.endColourButton.TabIndex = 1;
                this.endColourButton.Text = "End Colour";
                this.endColourButton.UseVisualStyleBackColor = false;
                this.endColourButton.Click += new System.EventHandler(this.endColourButton_Click);
                // 
                // startColourButton
                // 
                this.startColourButton.BackColor = System.Drawing.Color.Lime;
                this.startColourButton.Location = new System.Drawing.Point(7, 20);
                this.startColourButton.Name = "startColourButton";
                this.startColourButton.Size = new System.Drawing.Size(75, 23);
                this.startColourButton.TabIndex = 0;
                this.startColourButton.Text = "Start Colour";
                this.startColourButton.UseVisualStyleBackColor = false;
                this.startColourButton.Click += new System.EventHandler(this.startColourButton_Click);
                // 
                // startColourDialog
                // 
                this.startColourDialog.Color = System.Drawing.Color.Lime;
                // 
                // endColourDialog
                // 
                this.endColourDialog.Color = System.Drawing.Color.Red;
                // 
                // groupBox4
                // 
                this.groupBox4.Controls.Add(this.displayTypeRadioButton3);
                this.groupBox4.Controls.Add(this.displayTypeRadioButton2);
                this.groupBox4.Controls.Add(this.displayTypeRadioButton1);
                this.groupBox4.Location = new System.Drawing.Point(13, 382);
                this.groupBox4.Name = "groupBox4";
                this.groupBox4.Size = new System.Drawing.Size(313, 92);
                this.groupBox4.TabIndex = 13;
                this.groupBox4.TabStop = false;
                this.groupBox4.Text = "Display Type";
                // 
                // displayTypeRadioButton3
                // 
                this.displayTypeRadioButton3.AutoSize = true;
                this.displayTypeRadioButton3.Location = new System.Drawing.Point(7, 68);
                this.displayTypeRadioButton3.Name = "displayTypeRadioButton3";
                this.displayTypeRadioButton3.Size = new System.Drawing.Size(116, 17);
                this.displayTypeRadioButton3.TabIndex = 2;
                this.displayTypeRadioButton3.TabStop = true;
                this.displayTypeRadioButton3.Text = "Dual bar (to centre)";
                this.displayTypeRadioButton3.UseVisualStyleBackColor = true;
                // 
                // displayTypeRadioButton2
                // 
                this.displayTypeRadioButton2.AutoSize = true;
                this.displayTypeRadioButton2.Location = new System.Drawing.Point(7, 44);
                this.displayTypeRadioButton2.Name = "displayTypeRadioButton2";
                this.displayTypeRadioButton2.Size = new System.Drawing.Size(127, 17);
                this.displayTypeRadioButton2.TabIndex = 1;
                this.displayTypeRadioButton2.Text = "Dual bar (from centre)";
                this.displayTypeRadioButton2.UseVisualStyleBackColor = true;
                // 
                // displayTypeRadioButton1
                // 
                this.displayTypeRadioButton1.AutoSize = true;
                this.displayTypeRadioButton1.Checked = true;
                this.displayTypeRadioButton1.Location = new System.Drawing.Point(7, 20);
                this.displayTypeRadioButton1.Name = "displayTypeRadioButton1";
                this.displayTypeRadioButton1.Size = new System.Drawing.Size(72, 17);
                this.displayTypeRadioButton1.TabIndex = 0;
                this.displayTypeRadioButton1.TabStop = true;
                this.displayTypeRadioButton1.Text = "Single bar";
                this.displayTypeRadioButton1.UseVisualStyleBackColor = true;
                this.displayTypeRadioButton1.CheckedChanged += new System.EventHandler(this.displayTypeRadioButton1_CheckedChanged);
                // 
                // serSerialPort
                // 
                this.serSerialPort.PortName = "COM10";
                // 
                // Form1
                // 
                this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
                this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
                this.ClientSize = new System.Drawing.Size(341, 513);
                this.Controls.Add(this.groupBox4);
                this.Controls.Add(this.groupBox3);
                this.Controls.Add(this.groupBox2);
                this.Controls.Add(this.groupBox1);
                this.Controls.Add(this.bargraphOutputGroupBox);
                this.Controls.Add(this.statusStrip1);
                this.Name = "Form1";
                this.Text = "USB RGB VU Display";
                this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
                this.statusStrip1.ResumeLayout(false);
                this.statusStrip1.PerformLayout();
                this.bargraphOutputGroupBox.ResumeLayout(false);
                this.bargraphOutputGroupBox.PerformLayout();
                this.groupBox1.ResumeLayout(false);
                this.groupBox1.PerformLayout();
                this.groupBox2.ResumeLayout(false);
                this.groupBox2.PerformLayout();
                ((System.ComponentModel.ISupportInitialize)(this.ledFadeOffSpeedTrackBar)).EndInit();
                ((System.ComponentModel.ISupportInitialize)(this.displayDamperTrackBar)).EndInit();
                this.groupBox3.ResumeLayout(false);
                this.groupBox3.PerformLayout();
                ((System.ComponentModel.ISupportInitialize)(this.PeakColourLengthTrackBar)).EndInit();
                this.groupBox4.ResumeLayout(false);
                this.groupBox4.PerformLayout();
                this.ResumeLayout(false);
                this.PerformLayout();

            }

        #endregion

        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel usbToolStripStatusLabel;
        private System.Windows.Forms.Timer displayUpdateTimer;
        private System.Windows.Forms.Label leftVolumeStaticLabel;
        private System.Windows.Forms.Label rightVolumeStaticLabel;
        private System.Windows.Forms.Label leftVolumeLabel;
        private System.Windows.Forms.Label rightVolumeLabel;
        private System.Windows.Forms.GroupBox bargraphOutputGroupBox;
        private System.Windows.Forms.Label led16Label;
        private System.Windows.Forms.Label led15Label;
        private System.Windows.Forms.Label led14Label;
        private System.Windows.Forms.Label led13Label;
        private System.Windows.Forms.Label led12Label;
        private System.Windows.Forms.Label led11Label;
        private System.Windows.Forms.Label led10Label;
        private System.Windows.Forms.Label led9Label;
        private System.Windows.Forms.Label led8Label;
        private System.Windows.Forms.Label led7Label;
        private System.Windows.Forms.Label led6Label;
        private System.Windows.Forms.Label led5Label;
        private System.Windows.Forms.Label led4Label;
        private System.Windows.Forms.Label led3Label;
        private System.Windows.Forms.Label led2Label;
        private System.Windows.Forms.Label led1Label;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label rightDecibelLabel;
        private System.Windows.Forms.Label leftDecibelLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label displayDampingRateLabel;
        private System.Windows.Forms.Label displayDampingRateStaticLabel;
        private System.Windows.Forms.TrackBar displayDamperTrackBar;
        private System.Windows.Forms.Label ledFadeOffSpeedLabel;
        private System.Windows.Forms.Label ledFadeOffSpeedStaticLabel;
        private System.Windows.Forms.TrackBar ledFadeOffSpeedTrackBar;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button endColourButton;
        private System.Windows.Forms.Button startColourButton;
        private System.Windows.Forms.ColorDialog startColourDialog;
        private System.Windows.Forms.ColorDialog endColourDialog;
        private System.Windows.Forms.Label peakColourLengthLabel;
        private System.Windows.Forms.Label peakColourLengthStaticLabel;
        private System.Windows.Forms.TrackBar PeakColourLengthTrackBar;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.RadioButton displayTypeRadioButton2;
        private System.Windows.Forms.RadioButton displayTypeRadioButton1;
        private System.Windows.Forms.RadioButton displayTypeRadioButton3;
        private System.IO.Ports.SerialPort serSerialPort;
        }
    }

