namespace MotorTuner {
    partial class MotorTuner {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            this.btnConnect = new System.Windows.Forms.Button();
            this.btnRun = new System.Windows.Forms.Button();
            this.mainTab = new System.Windows.Forms.TabControl();
            this.tabMotor = new System.Windows.Forms.TabPage();
            this.gb_PositionTest = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.tbx_JogRef = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_Move = new System.Windows.Forms.Button();
            this.tbx_PosRef = new System.Windows.Forms.TextBox();
            this.gb_SpeedTest = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tbx_SpdRef = new System.Windows.Forms.TextBox();
            this.gb_CurrentLoop = new System.Windows.Forms.GroupBox();
            this.btn_CurrentLoopTest = new System.Windows.Forms.Button();
            this.lbl_CurrRef = new System.Windows.Forms.Label();
            this.tbx_CurrRef = new System.Windows.Forms.TextBox();
            this.cb_ShowCurrent = new System.Windows.Forms.CheckBox();
            this.cb_ShowSpeed = new System.Windows.Forms.CheckBox();
            this.cb_ShowPosition = new System.Windows.Forms.CheckBox();
            this.zedGraphControl_motor = new ZedGraph.ZedGraphControl();
            this.gb_CtrlParam = new System.Windows.Forms.GroupBox();
            this.btnUpdateCtrl = new System.Windows.Forms.Button();
            this.tbx_mot1_PosKp = new System.Windows.Forms.TextBox();
            this.lbl_mot1_PosKp = new System.Windows.Forms.Label();
            this.tbx_mot1_SpdCoefA = new System.Windows.Forms.TextBox();
            this.lbl_mot1_DriveConvFactor = new System.Windows.Forms.Label();
            this.tbx_mot1_SpdCoefB = new System.Windows.Forms.TextBox();
            this.lbl_mot1_SpdCoefC = new System.Windows.Forms.Label();
            this.tbx_mot1_SpdCoefC = new System.Windows.Forms.TextBox();
            this.lbl_mot1_SpdCoefB = new System.Windows.Forms.Label();
            this.tbx_mot1_DriveConvFactor = new System.Windows.Forms.TextBox();
            this.lbl_mot1_SpdCoefA = new System.Windows.Forms.Label();
            this.lbl_Motor = new System.Windows.Forms.Label();
            this.cboMotor = new System.Windows.Forms.ComboBox();
            this.tabIMS = new System.Windows.Forms.TabPage();
            this.tmrUpdateUI = new System.Windows.Forms.Timer(this.components);
            this.btn_ResetPos = new System.Windows.Forms.Button();
            this.mainTab.SuspendLayout();
            this.tabMotor.SuspendLayout();
            this.gb_PositionTest.SuspendLayout();
            this.gb_SpeedTest.SuspendLayout();
            this.gb_CurrentLoop.SuspendLayout();
            this.gb_CtrlParam.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(12, 48);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(124, 41);
            this.btnConnect.TabIndex = 0;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // btnRun
            // 
            this.btnRun.Location = new System.Drawing.Point(16, 78);
            this.btnRun.Name = "btnRun";
            this.btnRun.Size = new System.Drawing.Size(191, 44);
            this.btnRun.TabIndex = 1;
            this.btnRun.Text = "Run";
            this.btnRun.UseVisualStyleBackColor = true;
            this.btnRun.Click += new System.EventHandler(this.btnRun_Click);
            // 
            // mainTab
            // 
            this.mainTab.Controls.Add(this.tabMotor);
            this.mainTab.Controls.Add(this.tabIMS);
            this.mainTab.Location = new System.Drawing.Point(142, 12);
            this.mainTab.Name = "mainTab";
            this.mainTab.SelectedIndex = 0;
            this.mainTab.Size = new System.Drawing.Size(1014, 764);
            this.mainTab.TabIndex = 2;
            this.mainTab.Selected += new System.Windows.Forms.TabControlEventHandler(this.mainTab_Selected);
            // 
            // tabMotor
            // 
            this.tabMotor.Controls.Add(this.gb_PositionTest);
            this.tabMotor.Controls.Add(this.gb_SpeedTest);
            this.tabMotor.Controls.Add(this.gb_CurrentLoop);
            this.tabMotor.Controls.Add(this.cb_ShowCurrent);
            this.tabMotor.Controls.Add(this.cb_ShowSpeed);
            this.tabMotor.Controls.Add(this.cb_ShowPosition);
            this.tabMotor.Controls.Add(this.zedGraphControl_motor);
            this.tabMotor.Controls.Add(this.gb_CtrlParam);
            this.tabMotor.Controls.Add(this.lbl_Motor);
            this.tabMotor.Controls.Add(this.cboMotor);
            this.tabMotor.Location = new System.Drawing.Point(4, 22);
            this.tabMotor.Name = "tabMotor";
            this.tabMotor.Padding = new System.Windows.Forms.Padding(3);
            this.tabMotor.Size = new System.Drawing.Size(1006, 738);
            this.tabMotor.TabIndex = 0;
            this.tabMotor.Text = "Motor";
            this.tabMotor.UseVisualStyleBackColor = true;
            // 
            // gb_PositionTest
            // 
            this.gb_PositionTest.Controls.Add(this.btn_ResetPos);
            this.gb_PositionTest.Controls.Add(this.label3);
            this.gb_PositionTest.Controls.Add(this.tbx_JogRef);
            this.gb_PositionTest.Controls.Add(this.label2);
            this.gb_PositionTest.Controls.Add(this.btn_Move);
            this.gb_PositionTest.Controls.Add(this.tbx_PosRef);
            this.gb_PositionTest.Location = new System.Drawing.Point(19, 554);
            this.gb_PositionTest.Name = "gb_PositionTest";
            this.gb_PositionTest.Size = new System.Drawing.Size(352, 168);
            this.gb_PositionTest.TabIndex = 13;
            this.gb_PositionTest.TabStop = false;
            this.gb_PositionTest.Text = "Position Test";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(42, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Jog Speed";
            // 
            // tbx_JogRef
            // 
            this.tbx_JogRef.Location = new System.Drawing.Point(106, 52);
            this.tbx_JogRef.Name = "tbx_JogRef";
            this.tbx_JogRef.Size = new System.Drawing.Size(100, 20);
            this.tbx_JogRef.TabIndex = 6;
            this.tbx_JogRef.Text = "100";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(57, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Position";
            // 
            // btn_Move
            // 
            this.btn_Move.Location = new System.Drawing.Point(16, 90);
            this.btn_Move.Name = "btn_Move";
            this.btn_Move.Size = new System.Drawing.Size(191, 44);
            this.btn_Move.TabIndex = 3;
            this.btn_Move.Text = "Move";
            this.btn_Move.UseVisualStyleBackColor = true;
            this.btn_Move.Click += new System.EventHandler(this.btn_Move_Click);
            // 
            // tbx_PosRef
            // 
            this.tbx_PosRef.Location = new System.Drawing.Point(106, 22);
            this.tbx_PosRef.Name = "tbx_PosRef";
            this.tbx_PosRef.Size = new System.Drawing.Size(100, 20);
            this.tbx_PosRef.TabIndex = 4;
            this.tbx_PosRef.Text = "300";
            // 
            // gb_SpeedTest
            // 
            this.gb_SpeedTest.Controls.Add(this.label1);
            this.gb_SpeedTest.Controls.Add(this.btnRun);
            this.gb_SpeedTest.Controls.Add(this.tbx_SpdRef);
            this.gb_SpeedTest.Location = new System.Drawing.Point(19, 405);
            this.gb_SpeedTest.Name = "gb_SpeedTest";
            this.gb_SpeedTest.Size = new System.Drawing.Size(220, 143);
            this.gb_SpeedTest.TabIndex = 12;
            this.gb_SpeedTest.TabStop = false;
            this.gb_SpeedTest.Text = "Speed Test";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(44, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Reference";
            // 
            // tbx_SpdRef
            // 
            this.tbx_SpdRef.Location = new System.Drawing.Point(107, 38);
            this.tbx_SpdRef.Name = "tbx_SpdRef";
            this.tbx_SpdRef.Size = new System.Drawing.Size(100, 20);
            this.tbx_SpdRef.TabIndex = 1;
            this.tbx_SpdRef.Text = "100.0";
            // 
            // gb_CurrentLoop
            // 
            this.gb_CurrentLoop.Controls.Add(this.btn_CurrentLoopTest);
            this.gb_CurrentLoop.Controls.Add(this.lbl_CurrRef);
            this.gb_CurrentLoop.Controls.Add(this.tbx_CurrRef);
            this.gb_CurrentLoop.Location = new System.Drawing.Point(19, 276);
            this.gb_CurrentLoop.Name = "gb_CurrentLoop";
            this.gb_CurrentLoop.Size = new System.Drawing.Size(219, 123);
            this.gb_CurrentLoop.TabIndex = 11;
            this.gb_CurrentLoop.TabStop = false;
            this.gb_CurrentLoop.Text = "Current Test";
            // 
            // btn_CurrentLoopTest
            // 
            this.btn_CurrentLoopTest.Location = new System.Drawing.Point(16, 67);
            this.btn_CurrentLoopTest.Name = "btn_CurrentLoopTest";
            this.btn_CurrentLoopTest.Size = new System.Drawing.Size(191, 44);
            this.btn_CurrentLoopTest.TabIndex = 2;
            this.btn_CurrentLoopTest.Text = "Enable";
            this.btn_CurrentLoopTest.UseVisualStyleBackColor = true;
            this.btn_CurrentLoopTest.Click += new System.EventHandler(this.btn_CurrentLoopTest_Click);
            // 
            // lbl_CurrRef
            // 
            this.lbl_CurrRef.AutoSize = true;
            this.lbl_CurrRef.Location = new System.Drawing.Point(44, 33);
            this.lbl_CurrRef.Name = "lbl_CurrRef";
            this.lbl_CurrRef.Size = new System.Drawing.Size(57, 13);
            this.lbl_CurrRef.TabIndex = 1;
            this.lbl_CurrRef.Text = "Reference";
            // 
            // tbx_CurrRef
            // 
            this.tbx_CurrRef.Location = new System.Drawing.Point(107, 30);
            this.tbx_CurrRef.Name = "tbx_CurrRef";
            this.tbx_CurrRef.Size = new System.Drawing.Size(100, 20);
            this.tbx_CurrRef.TabIndex = 0;
            this.tbx_CurrRef.Text = "1.0";
            // 
            // cb_ShowCurrent
            // 
            this.cb_ShowCurrent.AutoSize = true;
            this.cb_ShowCurrent.Location = new System.Drawing.Point(399, 27);
            this.cb_ShowCurrent.Name = "cb_ShowCurrent";
            this.cb_ShowCurrent.Size = new System.Drawing.Size(59, 17);
            this.cb_ShowCurrent.TabIndex = 10;
            this.cb_ShowCurrent.Text = "current";
            this.cb_ShowCurrent.UseVisualStyleBackColor = true;
            // 
            // cb_ShowSpeed
            // 
            this.cb_ShowSpeed.AutoSize = true;
            this.cb_ShowSpeed.Checked = true;
            this.cb_ShowSpeed.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cb_ShowSpeed.Location = new System.Drawing.Point(338, 27);
            this.cb_ShowSpeed.Name = "cb_ShowSpeed";
            this.cb_ShowSpeed.Size = new System.Drawing.Size(55, 17);
            this.cb_ShowSpeed.TabIndex = 10;
            this.cb_ShowSpeed.Text = "speed";
            this.cb_ShowSpeed.UseVisualStyleBackColor = true;
            // 
            // cb_ShowPosition
            // 
            this.cb_ShowPosition.AutoSize = true;
            this.cb_ShowPosition.Location = new System.Drawing.Point(270, 27);
            this.cb_ShowPosition.Name = "cb_ShowPosition";
            this.cb_ShowPosition.Size = new System.Drawing.Size(62, 17);
            this.cb_ShowPosition.TabIndex = 10;
            this.cb_ShowPosition.Text = "position";
            this.cb_ShowPosition.UseVisualStyleBackColor = true;
            // 
            // zedGraphControl_motor
            // 
            this.zedGraphControl_motor.Location = new System.Drawing.Point(245, 14);
            this.zedGraphControl_motor.Name = "zedGraphControl_motor";
            this.zedGraphControl_motor.ScrollGrace = 0D;
            this.zedGraphControl_motor.ScrollMaxX = 0D;
            this.zedGraphControl_motor.ScrollMaxY = 0D;
            this.zedGraphControl_motor.ScrollMaxY2 = 0D;
            this.zedGraphControl_motor.ScrollMinX = 0D;
            this.zedGraphControl_motor.ScrollMinY = 0D;
            this.zedGraphControl_motor.ScrollMinY2 = 0D;
            this.zedGraphControl_motor.Size = new System.Drawing.Size(755, 513);
            this.zedGraphControl_motor.TabIndex = 9;
            this.zedGraphControl_motor.DoubleClick += new System.EventHandler(this.zedGraphControl_motor_DoubleClick);
            // 
            // gb_CtrlParam
            // 
            this.gb_CtrlParam.Controls.Add(this.btnUpdateCtrl);
            this.gb_CtrlParam.Controls.Add(this.tbx_mot1_PosKp);
            this.gb_CtrlParam.Controls.Add(this.lbl_mot1_PosKp);
            this.gb_CtrlParam.Controls.Add(this.tbx_mot1_SpdCoefA);
            this.gb_CtrlParam.Controls.Add(this.lbl_mot1_DriveConvFactor);
            this.gb_CtrlParam.Controls.Add(this.tbx_mot1_SpdCoefB);
            this.gb_CtrlParam.Controls.Add(this.lbl_mot1_SpdCoefC);
            this.gb_CtrlParam.Controls.Add(this.tbx_mot1_SpdCoefC);
            this.gb_CtrlParam.Controls.Add(this.lbl_mot1_SpdCoefB);
            this.gb_CtrlParam.Controls.Add(this.tbx_mot1_DriveConvFactor);
            this.gb_CtrlParam.Controls.Add(this.lbl_mot1_SpdCoefA);
            this.gb_CtrlParam.Location = new System.Drawing.Point(19, 58);
            this.gb_CtrlParam.Name = "gb_CtrlParam";
            this.gb_CtrlParam.Size = new System.Drawing.Size(220, 212);
            this.gb_CtrlParam.TabIndex = 8;
            this.gb_CtrlParam.TabStop = false;
            this.gb_CtrlParam.Text = "Control Parameter";
            // 
            // btnUpdateCtrl
            // 
            this.btnUpdateCtrl.Location = new System.Drawing.Point(16, 161);
            this.btnUpdateCtrl.Name = "btnUpdateCtrl";
            this.btnUpdateCtrl.Size = new System.Drawing.Size(191, 37);
            this.btnUpdateCtrl.TabIndex = 6;
            this.btnUpdateCtrl.Text = "Update";
            this.btnUpdateCtrl.UseVisualStyleBackColor = true;
            this.btnUpdateCtrl.Click += new System.EventHandler(this.btnUpdateCtrl_Click);
            // 
            // tbx_mot1_PosKp
            // 
            this.tbx_mot1_PosKp.Location = new System.Drawing.Point(107, 19);
            this.tbx_mot1_PosKp.Name = "tbx_mot1_PosKp";
            this.tbx_mot1_PosKp.Size = new System.Drawing.Size(100, 20);
            this.tbx_mot1_PosKp.TabIndex = 1;
            this.tbx_mot1_PosKp.Text = "--";
            // 
            // lbl_mot1_PosKp
            // 
            this.lbl_mot1_PosKp.AutoSize = true;
            this.lbl_mot1_PosKp.Location = new System.Drawing.Point(41, 26);
            this.lbl_mot1_PosKp.Name = "lbl_mot1_PosKp";
            this.lbl_mot1_PosKp.Size = new System.Drawing.Size(60, 13);
            this.lbl_mot1_PosKp.TabIndex = 0;
            this.lbl_mot1_PosKp.Text = "Position Kp";
            // 
            // tbx_mot1_SpdCoefA
            // 
            this.tbx_mot1_SpdCoefA.Location = new System.Drawing.Point(107, 45);
            this.tbx_mot1_SpdCoefA.Name = "tbx_mot1_SpdCoefA";
            this.tbx_mot1_SpdCoefA.Size = new System.Drawing.Size(100, 20);
            this.tbx_mot1_SpdCoefA.TabIndex = 1;
            this.tbx_mot1_SpdCoefA.Text = "--";
            // 
            // lbl_mot1_DriveConvFactor
            // 
            this.lbl_mot1_DriveConvFactor.AutoSize = true;
            this.lbl_mot1_DriveConvFactor.Location = new System.Drawing.Point(13, 125);
            this.lbl_mot1_DriveConvFactor.Name = "lbl_mot1_DriveConvFactor";
            this.lbl_mot1_DriveConvFactor.Size = new System.Drawing.Size(88, 13);
            this.lbl_mot1_DriveConvFactor.TabIndex = 5;
            this.lbl_mot1_DriveConvFactor.Text = "Drive Conversion";
            // 
            // tbx_mot1_SpdCoefB
            // 
            this.tbx_mot1_SpdCoefB.Location = new System.Drawing.Point(107, 71);
            this.tbx_mot1_SpdCoefB.Name = "tbx_mot1_SpdCoefB";
            this.tbx_mot1_SpdCoefB.Size = new System.Drawing.Size(100, 20);
            this.tbx_mot1_SpdCoefB.TabIndex = 1;
            this.tbx_mot1_SpdCoefB.Text = "--";
            // 
            // lbl_mot1_SpdCoefC
            // 
            this.lbl_mot1_SpdCoefC.AutoSize = true;
            this.lbl_mot1_SpdCoefC.Location = new System.Drawing.Point(28, 105);
            this.lbl_mot1_SpdCoefC.Name = "lbl_mot1_SpdCoefC";
            this.lbl_mot1_SpdCoefC.Size = new System.Drawing.Size(73, 13);
            this.lbl_mot1_SpdCoefC.TabIndex = 4;
            this.lbl_mot1_SpdCoefC.Text = "Speed CoeffC";
            // 
            // tbx_mot1_SpdCoefC
            // 
            this.tbx_mot1_SpdCoefC.Location = new System.Drawing.Point(107, 97);
            this.tbx_mot1_SpdCoefC.Name = "tbx_mot1_SpdCoefC";
            this.tbx_mot1_SpdCoefC.Size = new System.Drawing.Size(100, 20);
            this.tbx_mot1_SpdCoefC.TabIndex = 1;
            this.tbx_mot1_SpdCoefC.Text = "--";
            // 
            // lbl_mot1_SpdCoefB
            // 
            this.lbl_mot1_SpdCoefB.AutoSize = true;
            this.lbl_mot1_SpdCoefB.Location = new System.Drawing.Point(28, 79);
            this.lbl_mot1_SpdCoefB.Name = "lbl_mot1_SpdCoefB";
            this.lbl_mot1_SpdCoefB.Size = new System.Drawing.Size(73, 13);
            this.lbl_mot1_SpdCoefB.TabIndex = 3;
            this.lbl_mot1_SpdCoefB.Text = "Speed CoeffB";
            // 
            // tbx_mot1_DriveConvFactor
            // 
            this.tbx_mot1_DriveConvFactor.Location = new System.Drawing.Point(107, 125);
            this.tbx_mot1_DriveConvFactor.Name = "tbx_mot1_DriveConvFactor";
            this.tbx_mot1_DriveConvFactor.Size = new System.Drawing.Size(100, 20);
            this.tbx_mot1_DriveConvFactor.TabIndex = 1;
            this.tbx_mot1_DriveConvFactor.Text = "--";
            // 
            // lbl_mot1_SpdCoefA
            // 
            this.lbl_mot1_SpdCoefA.AutoSize = true;
            this.lbl_mot1_SpdCoefA.Location = new System.Drawing.Point(28, 51);
            this.lbl_mot1_SpdCoefA.Name = "lbl_mot1_SpdCoefA";
            this.lbl_mot1_SpdCoefA.Size = new System.Drawing.Size(73, 13);
            this.lbl_mot1_SpdCoefA.TabIndex = 2;
            this.lbl_mot1_SpdCoefA.Text = "Speed CoeffA";
            // 
            // lbl_Motor
            // 
            this.lbl_Motor.AutoSize = true;
            this.lbl_Motor.Location = new System.Drawing.Point(59, 22);
            this.lbl_Motor.Name = "lbl_Motor";
            this.lbl_Motor.Size = new System.Drawing.Size(48, 13);
            this.lbl_Motor.TabIndex = 7;
            this.lbl_Motor.Text = "Motor ID";
            // 
            // cboMotor
            // 
            this.cboMotor.FormattingEnabled = true;
            this.cboMotor.Location = new System.Drawing.Point(113, 19);
            this.cboMotor.Name = "cboMotor";
            this.cboMotor.Size = new System.Drawing.Size(100, 21);
            this.cboMotor.TabIndex = 6;
            this.cboMotor.Text = "MOTOR_ONE";
            this.cboMotor.SelectedIndexChanged += new System.EventHandler(this.cboMotor_SelectedIndexChanged);
            // 
            // tabIMS
            // 
            this.tabIMS.Location = new System.Drawing.Point(4, 22);
            this.tabIMS.Name = "tabIMS";
            this.tabIMS.Size = new System.Drawing.Size(1006, 738);
            this.tabIMS.TabIndex = 4;
            this.tabIMS.Text = "IMS";
            this.tabIMS.UseVisualStyleBackColor = true;
            // 
            // tmrUpdateUI
            // 
            this.tmrUpdateUI.Enabled = true;
            this.tmrUpdateUI.Interval = 10;
            this.tmrUpdateUI.Tick += new System.EventHandler(this.tmrUpdateUI_Tick);
            // 
            // btn_ResetPos
            // 
            this.btn_ResetPos.Location = new System.Drawing.Point(213, 90);
            this.btn_ResetPos.Name = "btn_ResetPos";
            this.btn_ResetPos.Size = new System.Drawing.Size(120, 44);
            this.btn_ResetPos.TabIndex = 8;
            this.btn_ResetPos.Text = "Reset";
            this.btn_ResetPos.UseVisualStyleBackColor = true;
            this.btn_ResetPos.Click += new System.EventHandler(this.btn_ResetPos_Click);
            // 
            // MotorTuner
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1168, 788);
            this.Controls.Add(this.mainTab);
            this.Controls.Add(this.btnConnect);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MotorTuner";
            this.Text = "Tuner";
            this.mainTab.ResumeLayout(false);
            this.tabMotor.ResumeLayout(false);
            this.tabMotor.PerformLayout();
            this.gb_PositionTest.ResumeLayout(false);
            this.gb_PositionTest.PerformLayout();
            this.gb_SpeedTest.ResumeLayout(false);
            this.gb_SpeedTest.PerformLayout();
            this.gb_CurrentLoop.ResumeLayout(false);
            this.gb_CurrentLoop.PerformLayout();
            this.gb_CtrlParam.ResumeLayout(false);
            this.gb_CtrlParam.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Button btnRun;
        private System.Windows.Forms.TabControl mainTab;
        private System.Windows.Forms.TabPage tabMotor;
        private System.Windows.Forms.TabPage tabIMS;
        private System.Windows.Forms.TextBox tbx_mot1_PosKp;
        private System.Windows.Forms.Label lbl_mot1_PosKp;
        private System.Windows.Forms.Timer tmrUpdateUI;
        private System.Windows.Forms.Label lbl_mot1_DriveConvFactor;
        private System.Windows.Forms.Label lbl_mot1_SpdCoefC;
        private System.Windows.Forms.Label lbl_mot1_SpdCoefB;
        private System.Windows.Forms.Label lbl_mot1_SpdCoefA;
        private System.Windows.Forms.TextBox tbx_mot1_DriveConvFactor;
        private System.Windows.Forms.TextBox tbx_mot1_SpdCoefC;
        private System.Windows.Forms.TextBox tbx_mot1_SpdCoefB;
        private System.Windows.Forms.TextBox tbx_mot1_SpdCoefA;
        private System.Windows.Forms.ComboBox cboMotor;
        private System.Windows.Forms.Label lbl_Motor;
        private System.Windows.Forms.GroupBox gb_CtrlParam;
        private System.Windows.Forms.Button btnUpdateCtrl;
        private ZedGraph.ZedGraphControl zedGraphControl_motor;
        private System.Windows.Forms.CheckBox cb_ShowCurrent;
        private System.Windows.Forms.CheckBox cb_ShowSpeed;
        private System.Windows.Forms.CheckBox cb_ShowPosition;
        private System.Windows.Forms.GroupBox gb_CurrentLoop;
        private System.Windows.Forms.TextBox tbx_CurrRef;
        private System.Windows.Forms.Button btn_CurrentLoopTest;
        private System.Windows.Forms.Label lbl_CurrRef;
        private System.Windows.Forms.GroupBox gb_SpeedTest;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbx_SpdRef;
        private System.Windows.Forms.GroupBox gb_PositionTest;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_Move;
        private System.Windows.Forms.TextBox tbx_PosRef;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbx_JogRef;
        private System.Windows.Forms.Button btn_ResetPos;
    }
}

