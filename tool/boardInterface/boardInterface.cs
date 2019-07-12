using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;
using System.IO;

namespace board
{
    public enum QSpyRxRecords {
        QS_RX_INFO,           /*!< query Target info (ver, config, tstamp) */
        QS_RX_COMMAND,        /*!< execute a user-defined command in the Target */
        QS_RX_RESET,          /*!< reset the Target */
        QS_RX_TICK,           /*!< call QF_TICK_X() in the Target */
        QS_RX_PEEK,           /*!< peek Target memory */
        QS_RX_POKE,           /*!< poke Target memory */
        QS_RX_FILL,           /*!< fill Target memory */
        QS_RX_TEST_SETUP,     /*!< test setup */
        QS_RX_TEST_TEARDOWN,  /*!< test teardown */
        QS_RX_TEST_PROBE,     /*!< set a Test-Probe in the Target */
        QS_RX_GLB_FILTER,     /*!< set global filters in the Target */
        QS_RX_LOC_FILTER,     /*!< set local  filters in the Target */
        QS_RX_AO_FILTER,      /*!< set local AO filter in the Target */
        QS_RX_CURR_OBJ,       /*!< set the "current-object" in the Target */
        QS_RX_TEST_CONTINUE,  /*!< continue a test after QS_TEST_PAUSE() */
        QS_RX_RESERVED1,      /*!< reserved for future use */
        QS_RX_EVENT           /*!< inject an event to the Target */
    }

    public enum QSPY {
        ATTACH = 128,
        DETACH = 129,
        SAVE_DICT = 130,
        SCREEN_OUT = 131,
        BIN_OUT = 132,
        MATLAB_OUT = 133,
        MSCGEN_OUT = 134,
        SEND_EVENT = 135,
        SEND_LOC_FILTER = 136,
        SEND_CURR_OBJ = 137,
        SEND_COMMAND = 138,
        SEND_TEST_PROBE = 139
    }
    public enum RecordId {
        RECORD_MOTOR = 70, // Should be aligned with QS_USER VALUE
        RECORD_STREAM,
    }
    public enum RecordType {
        STREAM_TAG = 0xFF,
        EVENT_TAG = 0xFE,
        RESPONSE_TAG = 0xFD
    }
    public enum CommandId {
        CMD_MOTOR_STOP = 0x10,
        CMD_MOTOR_RUN = 0x11,
        CMD_MOTOR_MOVE = 0x12,
        CMD_MOTOR_OPEN_LOOP = 0x13,
        CMD_MOTOR_GET_CTRL_PARAM = 0x14,
        CMD_MOTOR_SET_SPEED_COEFFA = 0x15,
        CMD_MOTOR_SET_SPEED_COEFFB = 0x16,
        CMD_MOTOR_SET_SPEED_COEFFC = 0x17,
        CMD_MOTOR_SET_POS_KP = 0x18,
        CMD_MOTOR_SET_DRV_CONV_FACTOR = 0x19,
        CMD_MOTOR_SET_POSITION_VALUE = 0x1A,

        CMD_DATA_STREAM_SET_FLAG = 0x30,
    }
    public enum ResponseStatus {
        RESPONSE_OK = 0x00,
        RESPONSE_INVALID
    }
    public enum MotorId {
        MOTOR_ONE = 0x00,
        MOTOR_TWO = 0x01,
        MOTOR_THREE = 0x02,
        MOTOR_FOUR = 0x03
    }
    public enum DataStreamItems {
        /* Motor One */
        STREAM_MOTOR_ONE_POSITION = 0,
        STREAM_MOTOR_ONE_SPEED,
        STREAM_MOTOR_ONE_CURRENT,
        /* Motor Two */
        STREAM_MOTOR_TWO_POSITION,
        STREAM_MOTOR_TWO_SPEED,
        STREAM_MOTOR_TWO_CURRENT,
        /* Motor Three */
        STREAM_MOTOR_THREE_POSITION,
        STREAM_MOTOR_THREE_SPEED,
        STREAM_MOTOR_THREE_CURRENT,
        /* Motor Four */
        STREAM_MOTOR_FOUR_POSITION,
        STREAM_MOTOR_FOUR_SPEED,
        STREAM_MOTOR_FOUR_CURRENT,
    }

    namespace Responses {
        namespace Motor {
            public class StopMotorRespArgs : EventArgs {
                public readonly board.MotorId motorId;
                public StopMotorRespArgs(board.MotorId id) {
                    this.motorId = id;
                }
            }
            public delegate void StopMotorRespHandler(object sender, board.Responses.Motor.StopMotorRespArgs e);
            public class RunMotorRespArgs : EventArgs {
                public readonly board.MotorId motorId;
                public RunMotorRespArgs(board.MotorId id) {
                    this.motorId = id;
                }
            }
            public delegate void RunMotorRespHandler(object sender, board.Responses.Motor.RunMotorRespArgs e);
            public class MoveMotorRespArgs : EventArgs {
                public readonly board.MotorId motorId;
                public MoveMotorRespArgs(board.MotorId id) {
                    this.motorId = id;
                }
            }
            public delegate void MoveMotorRespHandler(object sender, board.Responses.Motor.MoveMotorRespArgs e);
            public class RunOpenLoopArgs : EventArgs {
                public readonly board.MotorId motorId;
                public RunOpenLoopArgs(board.MotorId id) {
                    this.motorId = id;
                }
            }
            public delegate void RunOpenLoopRespHandler(object sender, board.Responses.Motor.RunMotorRespArgs e);
            public class GetMotorCtrlParamArgs : EventArgs {
                public readonly board.MotorId motorId;
                public readonly float PosKp;
                public readonly float SpdCoefA;
                public readonly float SpdCoefB;
                public readonly float SpdCoefC;
                public readonly float DriverConvFactor;
                public GetMotorCtrlParamArgs(
                        board.MotorId id,
                        float PosKp,
                        float SpdCoefA,
                        float SpdCoefB,
                        float SpdCoefC,
                        float DriverConvFactor) {
                    this.motorId = id;
                    this.PosKp = PosKp;
                    this.SpdCoefA = SpdCoefA;
                    this.SpdCoefB = SpdCoefB;
                    this.SpdCoefC = SpdCoefC;
                    this.DriverConvFactor = DriverConvFactor;
                }
            }
            public delegate void GetMotorCtrlParamRespHandler(object sender, board.Responses.Motor.GetMotorCtrlParamArgs e);
            public class SetMotorPositionArgs : EventArgs {
                public readonly board.MotorId motorId;
                public SetMotorPositionArgs(
                    board.MotorId id) {
                    this.motorId = id;
                }
            }
            public delegate void SetMotorPositionRespHandler(object sender, board.Responses.Motor.SetMotorPositionArgs e);
        }
        namespace Stream {
            public class SetStreamFlagRespArgs : EventArgs {
                public readonly ResponseStatus status;
                public SetStreamFlagRespArgs(ResponseStatus status) {
                    this.status = status;
                }
            }
            public delegate void SetStreamFlagRespHandler(object sender, board.Responses.Stream.SetStreamFlagRespArgs e);
        }
    }
    namespace Stream {
        public class PositionStreamEvtArgs : EventArgs {
            public readonly board.MotorId motorId;
            public readonly float position;
            public PositionStreamEvtArgs(
                board.MotorId id,
                float position) {
                this.motorId = id;
                this.position = position;
            }
        }
        public delegate void PositionStreamEvtHandler(object sender, board.Stream.PositionStreamEvtArgs e);
        public class SpeedStreamEvtArgs : EventArgs {
            public readonly board.MotorId motorId;
            public readonly float speed;
            public SpeedStreamEvtArgs(
                board.MotorId id,
                float speed) {
                this.motorId = id;
                this.speed = speed;
            }
        }
        public delegate void SpeedStreamEvtHandler(object sender, board.Stream.SpeedStreamEvtArgs e);
        public class CurrentStreamEvtArgs : EventArgs {
            public readonly board.MotorId motorId;
            public readonly float current;
            public CurrentStreamEvtArgs(
                board.MotorId id,
                float current) {
                this.motorId = id;
                this.current = current;
            }
        }
        public delegate void CurrentStreamEvtHandler(object sender, board.Stream.CurrentStreamEvtArgs e);
    }
    public class udpState {
        public UdpClient u;
        public IPEndPoint e;
        public udpState(UdpClient u, IPEndPoint e) {
            this.u = u;
            this.e = e;
        }
    }
    public class boardInterface {
        #region Response
        #region Response : Motor
        public event board.Responses.Motor.StopMotorRespHandler ResponseStopMotor;
        public event board.Responses.Motor.RunMotorRespHandler ResponseRunMotor;
        public event board.Responses.Motor.MoveMotorRespHandler ResponseMoveMotor;
        public event board.Responses.Motor.RunOpenLoopRespHandler ResponseRunOpenLoop;
        public event board.Responses.Motor.GetMotorCtrlParamRespHandler ResponseGetMotorCtrlParam;
        public event board.Responses.Motor.SetMotorPositionRespHandler ResponseSetMotorPosition;
        #endregion
        #region Response : Stream
        public event board.Responses.Stream.SetStreamFlagRespHandler ResponseSetStreamFlag;
        #endregion
        #endregion
        #region Streaming
        public event board.Stream.PositionStreamEvtHandler StreamPosition;
        public event board.Stream.SpeedStreamEvtHandler StreamSpeed;
        public event board.Stream.CurrentStreamEvtHandler StreamCurrent;
        #endregion
    
        // Private members
        private UdpClient udpClient;
        private udpState state;
        private IPEndPoint endpoint;
        private byte seq;
        private byte rcvSeq;
        private int port;
        private bool isRecvRunning;
        private bool isAttached;
        private FileStream fileStreamWriter = null;
        private BinaryWriter StreamBinaryWriter = null;

        // Constructor
        public boardInterface(int udpPortNum) {
            this.udpClient = new UdpClient();
            this.udpClient.DontFragment = false;
            this.seq = 0;
            this.rcvSeq = 0;
            this.isRecvRunning = true;
            this.port = udpPortNum;
            this.isAttached = false;
            try {
                this.endpoint = new IPEndPoint(IPAddress.Any, this.port);
                this.udpClient.Connect("localhost", this.port);
                this.state = new udpState(this.udpClient, this.endpoint);
                this.SendAttach(1);
                this.udpClient.BeginReceive(new AsyncCallback(ReceiveCallback), this.state);
            } catch (Exception ex) {
                Console.WriteLine(ex.Message);
            }
        }
        ~boardInterface() {
            this.Close();
        }
        public void Close() {
            if (this.isAttached) {
                this.SendDetach();
            }
        }

        #region Motor 
        public void StopMotor(MotorId id) {
            SendCommand(CommandId.CMD_MOTOR_STOP,
                (UInt32)id, 0, 0);
        }
        public void RunMotor(MotorId id, float speed) {
            SendCommand(CommandId.CMD_MOTOR_RUN,
                (UInt32)id,
                (UInt32)(speed * 65536.0f),
                (UInt32)0);
        }
        public void MoveMotor(MotorId id, float position, float jogSpeed) {
            SendCommand(CommandId.CMD_MOTOR_MOVE,
                (UInt32)id,
                (UInt32)(position * 65536.0f),
                (UInt32)(jogSpeed * 65536.0f));
        }
        public void OpenLoopMotor(MotorId id, float open_loop_val) {
            SendCommand(CommandId.CMD_MOTOR_OPEN_LOOP,
                (UInt32)id,
                (UInt32)(open_loop_val * 65526.0f),
                0);
        }
        public void GetMotorCtrlParam(MotorId id) {
            SendCommand(CommandId.CMD_MOTOR_GET_CTRL_PARAM,
                (UInt32)id, 0, 0);
        }
        public void SetMotorCtrlSpdParam(MotorId id, float coefA, float coefB, float coefC) {
            this.SendCommand(CommandId.CMD_MOTOR_SET_SPEED_COEFFA,
                (UInt32)id,
                (UInt32)(coefA * 65536.0f),
                0);
            this.SendCommand(CommandId.CMD_MOTOR_SET_SPEED_COEFFB,
                (UInt32)id,
                (UInt32)(coefB * 65536.0f),
                0);
            this.SendCommand(CommandId.CMD_MOTOR_SET_SPEED_COEFFC,
                (UInt32)id,
                (UInt32)(coefC * 65536.0f),
                0);
        }
        public void SetMotorCtrlPosParam(MotorId id, float Kp) {
            this.SendCommand(CommandId.CMD_MOTOR_SET_POS_KP,
                (UInt32)id,
                (UInt32)(Kp * 65536.0f),
                0);
        }
        public void SetMotorCtrlDriveConv(MotorId id, float convFactor) {
            this.SendCommand(CommandId.CMD_MOTOR_SET_DRV_CONV_FACTOR,
                (UInt32)id,
                (UInt32)(convFactor * 65536.0f),
                0);
        }
        public void SetMotorPosition(MotorId id, float position) {
            this.SendCommand(CommandId.CMD_MOTOR_SET_POSITION_VALUE,
                (UInt32)id,
                (UInt32)((position * 65536.0f) + 0.5f),
                0);
        }
        #endregion
        #region Stream
        public void SetStreamConfig(UInt32 flag, bool enable) {
            UInt32 en = 0;
            if(enable) {
                en = 1;
            }
            this.SendCommand(CommandId.CMD_DATA_STREAM_SET_FLAG,
                flag, en, 0);
        }
        #endregion

        private void SendCommand(CommandId id, UInt32 param1, UInt32 param2, UInt32 param3) {
            byte[] payload = new byte[] {
                this.seq++,
                (byte)QSpyRxRecords.QS_RX_COMMAND,
                (byte)id,
                (byte)(0x00FF & param1), (byte)(0x00FF & (param1 >> 8)), (byte)(0x00FF & (param1 >> 16)), (byte)(0x00FF & (param1 >> 24)),
                (byte)(0x00FF & param2), (byte)(0x00FF & (param2 >> 8)), (byte)(0x00FF & (param2 >> 16)), (byte)(0x00FF & (param2 >> 24)),
                (byte)(0x00FF & param3), (byte)(0x00FF & (param3 >> 8)), (byte)(0x00FF & (param3 >> 16)), (byte)(0x00FF & (param3 >> 24))
            };
            this.udpClient.Send(payload, payload.Length);
        }
        private void SendAttach(Byte channel) {
            byte[] payload = new byte[] {
                this.seq++,
                (byte)QSPY.ATTACH,
                channel
            };
            this.udpClient.Send(payload, payload.Length);
            this.isAttached = true;
        }
        private void SendDetach() {
            byte[] payload = new byte[] {
                this.seq++,
                (byte)QSPY.DETACH
            };
            this.udpClient.Send(payload, payload.Length);
            this.isAttached = false;
        }
        private void ReceiveCallback(IAsyncResult res) {
            UdpClient u = (UdpClient)((udpState)(res.AsyncState)).u;
            IPEndPoint e = (IPEndPoint)((udpState)(res.AsyncState)).e;
            byte[] received = u.EndReceive(res, ref e);

            UInt32 timestamp;
            RecordType recType;
            Byte motId = 0;
            UInt32 cmdSeq;
            Byte cmdId = 0;
            Byte sts = 0;
            ResponseStatus responseStatus;

            // Byte0: QSpy Seq num
            // Byte1: QSpy Record ID
            this.rcvSeq++;
            if(this.rcvSeq != received[0]) {
                Console.WriteLine("Discontinuity Detected! Expected " + this.rcvSeq + ", Received " + received[0]);
                this.rcvSeq = received[0];
            }
            // Record ID
            switch((RecordId)received[1]) {
                case RecordId.RECORD_MOTOR:
                    #region Record : Motor
                    // Byte2:5: Timestamp
                    // Byte6:7: Record Tag (note: byte6 is QSpy format)
                    timestamp = BitConverter.ToUInt32(received, 2);
                    recType = (RecordType)received[7];
                    switch(recType) {
                        case RecordType.RESPONSE_TAG:
                            #region Motor : Response
                            cmdSeq = BitConverter.ToUInt32(received, 9);
                            motId = received[14];
                            cmdId = received[16];
                            sts = received[18];
                            switch(cmdId) {
                                case (Byte)CommandId.CMD_MOTOR_STOP:
                                    if(ResponseStopMotor != null) {
                                        ResponseStopMotor(this, new board.Responses.Motor.StopMotorRespArgs((MotorId)motId));
                                    }
                                    break;
                                case (Byte)CommandId.CMD_MOTOR_RUN:
                                    if(ResponseRunMotor != null) {
                                        ResponseRunMotor(this, new board.Responses.Motor.RunMotorRespArgs((MotorId)motId));
                                    }
                                    break;
                                case (Byte)CommandId.CMD_MOTOR_MOVE:
                                    if(ResponseMoveMotor != null) {
                                        ResponseMoveMotor(this, new board.Responses.Motor.MoveMotorRespArgs((MotorId)motId));
                                    }
                                    break;
                                case (Byte)CommandId.CMD_MOTOR_OPEN_LOOP:
                                    if(ResponseRunOpenLoop != null) {
                                        ResponseRunOpenLoop(this, new board.Responses.Motor.RunMotorRespArgs((MotorId)motId));
                                    }
                                    break;
                                case (Byte)CommandId.CMD_MOTOR_GET_CTRL_PARAM: {
                                        float PosKp;
                                        float SpdCoefA;
                                        float SpdCoefB;
                                        float SpdCoefC;
                                        float driveConv;
                                        PosKp = (float)(BitConverter.ToInt32(received, 20)) / 65536.0f;
                                        SpdCoefA = (float)(BitConverter.ToInt32(received, 25)) / 65536.0f;
                                        SpdCoefB = (float)(BitConverter.ToInt32(received, 30)) / 65536.0f;
                                        SpdCoefC = (float)(BitConverter.ToInt32(received, 35)) / 65536.0f;
                                        driveConv = (float)(BitConverter.ToInt32(received, 40)) / 65536.0f;
                                        if(ResponseGetMotorCtrlParam != null) {
                                            ResponseGetMotorCtrlParam(this, new board.Responses.Motor.GetMotorCtrlParamArgs(
                                                                (MotorId)motId,
                                                                PosKp,
                                                                SpdCoefA,
                                                                SpdCoefB,
                                                                SpdCoefC,
                                                                driveConv));
                                        }
                                    }
                                    break;
                                case (Byte)CommandId.CMD_MOTOR_SET_POSITION_VALUE: {
                                        if(ResponseSetMotorPosition != null) {
                                            ResponseSetMotorPosition(this, new Responses.Motor.SetMotorPositionArgs((MotorId)motId));
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                            #endregion
                            break;                        
                        case RecordType.EVENT_TAG:
                            #region Motor : Event
                            Console.WriteLine("Event Received");
                            #endregion
                            break;
                        case RecordType.STREAM_TAG:
                            #region Motor : Stream
                            Console.WriteLine("Stream Received");
                            #endregion
                            break;
                        default:
                            break;
                    }
                    #endregion
                    break;
                case RecordId.RECORD_STREAM:
                    #region Record : Stream
                    // Byte2:5: Timestamp
                    // Byte6:7: Record Tag (note: byte6 is QSpy format)
                    timestamp = BitConverter.ToUInt32(received, 2);
                    recType = (RecordType)received[7];
                    switch(recType) {
                        case RecordType.RESPONSE_TAG:
                            #region Stream : Response
                            cmdSeq = BitConverter.ToUInt32(received, 9);
                            cmdId = received[14];
                            responseStatus = (ResponseStatus)received[16];
                            switch(cmdId) {
                                case (Byte)CommandId.CMD_DATA_STREAM_SET_FLAG:
                                    if(ResponseSetStreamFlag != null) {
                                        ResponseSetStreamFlag(this, new Responses.Stream.SetStreamFlagRespArgs(responseStatus));
                                    }
                                    break;
                                default:
                                    break;
                            }
                            #endregion
                            break;
                        case RecordType.EVENT_TAG:
                            #region Stream : Event
                            #endregion
                            break;
                        case RecordType.STREAM_TAG: {
                                #region Stream
                                int idx = 9;
                                String StreamString = "Stream Received:,";
                                StreamString += timestamp.ToString();
                                UInt32 streamFlag = BitConverter.ToUInt32(received, idx);
                                idx = idx + 5;
                                if((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_ONE_POSITION))) != 0) {
                                    Int32 qPos = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qPos / 65536.0f;
                                    if(StreamPosition != null) {
                                        StreamPosition(this, new Stream.PositionStreamEvtArgs(MotorId.MOTOR_ONE, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_ONE_SPEED))) != 0) {
                                    Int32 qSpd = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qSpd / 65536.0f;
                                    if (StreamSpeed != null) {
                                        StreamSpeed(this, new Stream.SpeedStreamEvtArgs(MotorId.MOTOR_ONE, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_ONE_CURRENT))) != 0) {
                                    Int32 qCur = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qCur / 65536.0f;
                                    if (StreamCurrent != null) {
                                        StreamCurrent(this, new Stream.CurrentStreamEvtArgs(MotorId.MOTOR_ONE, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_TWO_POSITION))) != 0) {
                                    Int32 qPos = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qPos / 65536.0f;
                                    if (StreamPosition != null) {
                                        StreamPosition(this, new Stream.PositionStreamEvtArgs(MotorId.MOTOR_TWO, (float)qPos / 65536.0f));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_TWO_SPEED))) != 0) {
                                    Int32 qSpd = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qSpd / 65536.0f;
                                    if (StreamSpeed != null) {
                                        StreamSpeed(this, new Stream.SpeedStreamEvtArgs(MotorId.MOTOR_TWO, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_TWO_CURRENT))) != 0) {
                                    Int32 qCur = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qCur / 65536.0f;
                                    if (StreamCurrent != null) {
                                        StreamCurrent(this, new Stream.CurrentStreamEvtArgs(MotorId.MOTOR_TWO, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_THREE_POSITION))) != 0) {
                                    Int32 qPos = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qPos / 65536.0f;
                                    if (StreamPosition != null) {
                                        StreamPosition(this, new Stream.PositionStreamEvtArgs(MotorId.MOTOR_THREE, (float)qPos / 65536.0f));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_THREE_SPEED))) != 0) {
                                    Int32 qSpd = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qSpd / 65536.0f;
                                    if (StreamSpeed != null) {
                                        StreamSpeed(this, new Stream.SpeedStreamEvtArgs(MotorId.MOTOR_THREE, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_THREE_CURRENT))) != 0) {
                                    Int32 qCur = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qCur / 65536.0f;
                                    if (StreamCurrent != null) {
                                        StreamCurrent(this, new Stream.CurrentStreamEvtArgs(MotorId.MOTOR_THREE, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_FOUR_POSITION))) != 0) {
                                    Int32 qPos = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qPos / 65536.0f;
                                    if (StreamPosition != null) {
                                        StreamPosition(this, new Stream.PositionStreamEvtArgs(MotorId.MOTOR_FOUR, (float)qPos / 65536.0f));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_FOUR_SPEED))) != 0) {
                                    Int32 qSpd = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qSpd / 65536.0f;
                                    if (StreamSpeed != null) {
                                        StreamSpeed(this, new Stream.SpeedStreamEvtArgs(MotorId.MOTOR_FOUR, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                if ((streamFlag & (1 << (int)(DataStreamItems.STREAM_MOTOR_FOUR_CURRENT))) != 0) {
                                    Int32 qCur = BitConverter.ToInt32(received, idx);
                                    idx = idx + 5;
                                    float val = (float)qCur / 65536.0f;
                                    if (StreamCurrent != null) {
                                        StreamCurrent(this, new Stream.CurrentStreamEvtArgs(MotorId.MOTOR_FOUR, val));
                                    }
                                    StreamString += "," + val.ToString();
                                }
                                StreamString += Environment.NewLine;
                                /* Store to file */
                                try {
                                    if (StreamBinaryWriter != null) {
                                        StreamBinaryWriter.Write(StreamString);
                                    }
                                } catch (Exception ex) {
                                    Console.WriteLine(ex.Message);
                                }
                                #endregion
                                break;
                            }
                        default:
                            break;
                    }
                    #endregion
                    break;
                default:
                    break;
            }

            if (this.isRecvRunning) {
                u.BeginReceive(new AsyncCallback(ReceiveCallback), (udpState)(res.AsyncState));
            }
        }

        public void Streaming(bool enable) {
            if(enable) {
                this.OpenDataStream();
            } else {
                this.CloseDataStream();
            }
        }

        private void OpenDataStream() {
            // Filename: DataStream_YYYYMMDD_hhmmss.bin
            string streamFileName = Path.Combine(Environment.CurrentDirectory, "DataStream_" +
                System.DateTime.Now.Year.ToString("D4") + System.DateTime.Now.Month.ToString("D2") + System.DateTime.Now.Day.ToString("D2") + "_" +
                System.DateTime.Now.Hour.ToString("D2") + System.DateTime.Now.Minute.ToString("D2") + System.DateTime.Now.Second.ToString("D2") + ".csv");

            // Close and Create new Stream
            CloseDataStream();
            fileStreamWriter = new FileStream(streamFileName, FileMode.Append, FileAccess.Write, FileShare.Read);
            StreamBinaryWriter = new BinaryWriter(fileStreamWriter);

        }

        private void CloseDataStream() {
            // Close stream
            if (null != StreamBinaryWriter) {
                StreamBinaryWriter.Flush();
                StreamBinaryWriter.Close();
                StreamBinaryWriter = null;
            }

            if (null != fileStreamWriter) {
                fileStreamWriter.Close();
                fileStreamWriter = null;
            }
        }
    }
}
