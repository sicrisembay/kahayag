using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using board;
using ZedGraph;

namespace MotorTuner {
    public partial class MotorTuner : Form {
        private class motorRecord {
            public float Position;
            public float Speed;
            public float Current;
            public float PosKp;
            public float SpdCoefA;
            public float SpdCoefB;
            public float SpdCoefC;
            public float DriveConvFactor;
        }

        private board.boardInterface board;
        private motorRecord[] motRec;
        private bool updateMotRec;
        private bool updateGraph;
        private MotorId selectedMotor;

        public MotorTuner() {
            InitializeComponent();
            motRec = new motorRecord[4];
            for(int idx = 0; idx < 4; idx++) {
                motRec[idx] = new motorRecord();
            }
            this.updateMotRec = false;
            this.updateGraph = false;
            cboMotor.Items.Add(MotorId.MOTOR_ONE);
            cboMotor.Items.Add(MotorId.MOTOR_TWO);
            cboMotor.Items.Add(MotorId.MOTOR_THREE);
            cboMotor.Items.Add(MotorId.MOTOR_FOUR);
            cboMotor.Text = "MOTOR_ONE";
            this.selectedMotor = (MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text);

            this.initGraph();
        }

        private void btnConnect_Click(object sender, EventArgs e) {
            if (btnConnect.Text == "Connect") {
                try {
                    this.board = new board.boardInterface(7701);
                    this.registerEvents();
                    mainTab.SelectedIndex = 0;
                    this.board.GetMotorCtrlParam((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text));
                    this.configStream(true);
                    btnConnect.Text = "Disconnect";
                } catch (Exception ex) {
                    MessageBox.Show(ex.Message);
                }
            } else {
                if (this.board != null) {
                    this.configStream(false);
                    this.board.Close();
                    this.unregisterEvents();
                    this.board = null;
                }
                btnConnect.Text = "Connect";
            }
        }

        private void registerEvents() {
            if(this.board != null) {
                this.board.ResponseGetMotorCtrlParam += evtCtrlParam;
                this.board.StreamPosition += evtPosition;
                this.board.StreamSpeed += evtSpeed;
                this.board.StreamCurrent += evtCurrent;
            }
        }
        private void configStream(bool enable) {
            UInt32 flag = 0b111_111_111_111;
            if(this.board == null) {
                return;
            }
            this.board.SetStreamConfig(flag, enable);
        }
        private void unregisterEvents() {
            if(this.board != null) {
                this.board.ResponseGetMotorCtrlParam -= evtCtrlParam;
                this.board.StreamPosition -= evtPosition;
                this.board.StreamSpeed -= evtSpeed;
                this.board.StreamCurrent -= evtCurrent;
            }
        }

        private void evtCtrlParam(object sender, board.Responses.Motor.GetMotorCtrlParamArgs e) {
            try {
                Byte idx = (Byte)(e.motorId);
                motRec[idx].PosKp = e.PosKp;
                motRec[idx].SpdCoefA = e.SpdCoefA;
                motRec[idx].SpdCoefB = e.SpdCoefB;
                motRec[idx].SpdCoefC = e.SpdCoefC;
                motRec[idx].DriveConvFactor = e.DriverConvFactor;
                this.updateMotRec = true;
            } catch (Exception ex) {
                Console.WriteLine(ex.Message);
            }
        }

        private void evtPosition(object sender, board.Stream.PositionStreamEvtArgs e) {
            int idx = (int)(e.motorId);
            this.motRec[idx].Position = e.position;
            if (e.motorId == this.selectedMotor) {
                DateTime now = DateTime.Now;
                double timestamp = (now.Minute * 60.0) + now.Second + (now.Millisecond / 1000.0);
                if (MotorPositionPairList != null) {
                    MotorPositionPairList.Add(timestamp, this.motRec[idx].Position);
                    this.updateGraph = true;
                }
            }
        }
        private void evtSpeed(object sender, board.Stream.SpeedStreamEvtArgs e) {
            int idx = (int)(e.motorId);
            this.motRec[idx].Speed = e.speed;
            if (e.motorId == this.selectedMotor) {
                DateTime now = DateTime.Now;
                double timestamp = (now.Minute * 60.0) + now.Second + (now.Millisecond / 1000.0);
                if (MotorSpeedPairList != null) {
                    MotorSpeedPairList.Add(timestamp, this.motRec[idx].Speed);
                    this.updateGraph = true;
                }
            }
        }
        private void evtCurrent(object sender, board.Stream.CurrentStreamEvtArgs e) {
            int idx = (int)(e.motorId);
            this.motRec[idx].Current = e.current;
            if (e.motorId == this.selectedMotor) {
                DateTime now = DateTime.Now;
                double timestamp = (now.Minute * 60.0) + now.Second + (now.Millisecond / 1000.0);
                if (MotorCurrentPairList != null) {
                    MotorCurrentPairList.Add(timestamp, this.motRec[idx].Current);
                    this.updateGraph = true;
                }
            }
        }
        private void mainTab_Selected(object sender, TabControlEventArgs e) {
            if(this.board == null) {
                return;
            }
            switch(e.TabPageIndex) {
                case 0:
                    this.board.GetMotorCtrlParam((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text));
                    break;
                default:
                    break;
            }
        }

        LineItem MotorPositionCurve, MotorSpeedCurve, MotorCurrentCurve;
        PointPairList MotorPositionPairList, MotorSpeedPairList, MotorCurrentPairList;

        private void initGraph() {
            zedGraphControl_motor.GraphPane.CurveList.Clear();

            MotorPositionPairList = new PointPairList();
            MotorSpeedPairList = new PointPairList();
            MotorCurrentPairList = new PointPairList();

            MotorPositionCurve = zedGraphControl_motor.GraphPane.AddCurve("Position", MotorPositionPairList, Color.DarkBlue, SymbolType.None);
            MotorPositionCurve.Line.Width = 2.0f;
            MotorSpeedCurve = zedGraphControl_motor.GraphPane.AddCurve("Speed", MotorSpeedPairList, Color.DarkGreen, SymbolType.None);
            MotorSpeedCurve.Line.Width = 2.0f;
            MotorCurrentCurve = zedGraphControl_motor.GraphPane.AddCurve("Current", MotorCurrentPairList, Color.DarkOrange, SymbolType.None);
            MotorCurrentCurve.Line.Width = 2.0f;

            zedGraphControl_motor.GraphPane.Title.Text = "Motor Data";
            zedGraphControl_motor.GraphPane.XAxis.Title.Text = "Time";
            zedGraphControl_motor.GraphPane.XAxis.Title.FontSpec.Size = 10.0f;
            zedGraphControl_motor.GraphPane.YAxis.Title.Text = " ";
            zedGraphControl_motor.GraphPane.YAxis.Title.FontSpec.Size = 10.0f;
        }

        private void btnRun_Click(object sender, EventArgs e) {
            try {
                if (this.board == null) {
                    return;
                }
                if (btnRun.Text == "Run") {
                    this.board.RunMotor((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text), 
                        Convert.ToSingle(tbx_SpdRef.Text));
                    btnRun.Text = "Stop";
                } else {
                    this.board.StopMotor((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text));
                    btnRun.Text = "Run";
                }
            } catch (Exception ex) {
                MessageBox.Show(ex.Message);
            }
        }

        private void btn_CurrentLoopTest_Click(object sender, EventArgs e) {
            if(this.board == null) {
                return;
            }
            if (btn_CurrentLoopTest.Text == "Enable") {
                this.board.OpenLoopMotor((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text), Convert.ToSingle(tbx_CurrRef.Text));
                btn_CurrentLoopTest.Text = "Disable";
            } else {
                this.board.StopMotor((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text));
                btn_CurrentLoopTest.Text = "Enable";
            }
        }

        private void btn_Move_Click(object sender, EventArgs e) {
            try {
                if(this.board == null) {
                    return;
                }
                this.board.MoveMotor((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text),
                    Convert.ToSingle(tbx_PosRef.Text),
                    Convert.ToSingle(tbx_JogRef.Text));
                this.board.Streaming(true);
            } catch (Exception ex) {
                MessageBox.Show(ex.Message);
            }
        }

        private void zedGraphControl_motor_DoubleClick(object sender, EventArgs e) {
            MotorPositionPairList.Clear();
            MotorSpeedPairList.Clear();
            MotorCurrentPairList.Clear();
        }

        private void tmrUpdateUI_Tick(object sender, EventArgs e) {
            switch(mainTab.SelectedIndex) {
                case 0: {
                        MotorId id = (MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text);
                        if (this.updateMotRec) {
                            tbx_mot1_PosKp.Text = this.motRec[(int)id].PosKp.ToString("0.000000");
                            tbx_mot1_SpdCoefA.Text = this.motRec[(int)id].SpdCoefA.ToString("0.000000");
                            tbx_mot1_SpdCoefB.Text = this.motRec[(int)id].SpdCoefB.ToString("0.000000");
                            tbx_mot1_SpdCoefC.Text = this.motRec[(int)id].SpdCoefC.ToString("0.000000");
                            tbx_mot1_DriveConvFactor.Text = this.motRec[(int)id].DriveConvFactor.ToString("0.000000");
                            this.updateMotRec = false;
                        }

                        if (this.updateGraph) {
                            zedGraphControl_motor.AxisChange();
                            zedGraphControl_motor.Invalidate();
                            zedGraphControl_motor.Refresh();
                            this.updateGraph = false;
                        }

                        MotorPositionCurve.IsVisible = cb_ShowPosition.Checked;
                        MotorSpeedCurve.IsVisible = cb_ShowSpeed.Checked;
                        MotorCurrentCurve.IsVisible = cb_ShowCurrent.Checked;
                    break;
                    }
                default:
                    break;
            }            
        }

        private void btn_ResetPos_Click(object sender, EventArgs e) {
            if(this.board == null) {
                return;
            }
            this.board.SetMotorPosition((MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text), 0.0f);
            this.board.Streaming(false);
        }

        private void cboMotor_SelectedIndexChanged(object sender, EventArgs e) {
            if(this.board == null) {
                return;
            }
            MotorId id = (MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text);
            this.selectedMotor = id;
            this.board.GetMotorCtrlParam(id);
        }

        private void btnUpdateCtrl_Click(object sender, EventArgs e) {
            if(this.board == null) {
                MessageBox.Show("Not Connected to board!");
                return;
            }
            MotorId id = (MotorId)Enum.Parse(typeof(MotorId), cboMotor.Text);
            this.board.SetMotorCtrlSpdParam(id,
                Convert.ToSingle(tbx_mot1_SpdCoefA.Text),
                Convert.ToSingle(tbx_mot1_SpdCoefB.Text),
                Convert.ToSingle(tbx_mot1_SpdCoefC.Text));
            this.board.SetMotorCtrlPosParam(id,
                Convert.ToSingle(tbx_mot1_PosKp.Text));
            this.board.SetMotorCtrlDriveConv(id,
                Convert.ToSingle(tbx_mot1_DriveConvFactor.Text));
            this.board.GetMotorCtrlParam(id);
        }

    }
}
