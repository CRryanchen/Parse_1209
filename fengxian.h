#ifndef FENGXIAN_H
#define FENGXIAN_H
#include "xinsheng.h"

#pragma pack(1)

#define  FX_METER_ID_LEN            7      //地址域长度7字节(14位)
#undef   ENCRYPTION_LEN
#undef   PADDING_LENGTH
#define  ENCRYPTION_LEN             8  //加密因子长度字节数
#define  PADDING_LENGTH(x)          (ENCRYPTION_LEN - (sizeof(x) % ENCRYPTION_LEN))

/*----------------奉贤协议报文头-----------------*/
typedef struct
{
    uint8_t             Start;                     //帧起始符  0x69
    uint16_t            RealDataLength;            //数据内容长度(整条数据帧长度)(帧起始符至结束符)
    uint16_t            ProtocolVer;               //协议版本（大端模式）
    uint8_t             VendoCode;                 //厂商代码  BCD码
    uint8_t             MeterAddr[FX_METER_ID_LEN];//表号地址位 地址A，7字节，14位，由BCD码A0A1A2A3A4A5A6组合而成，表示NB设备编号，如表号。在协议中为大端模式,高位A0在前,低位A6在后。
                                                                                         //示例：协议帧地址为“00 00 00 00 00 01”，表示地址编号000000000001。  //注意:为BCD码格式
    uint8_t             ContralArea;               //控制码
    uint16_t            DataIdent;                 //数据标识和安全模式 组成2字节 (大端模式)

}FENGXIAN_PROTOCOL_FRAME_HEADER;    //(16字节)


/*----------------奉贤协议报文尾-----------------*/
typedef struct
{
    uint8_t    cs;                         //校验和CS，是从第一个帧起始符开始到校验码之前,不含校验码，(即数据域的最后一个字节)若超出256，采用对256的取模值
    uint8_t    end;                        //帧结束符EOT采用0x16
}FENGXIAN_PROTOCOL_FRAME_TAIL;


/*----------------业务数据上报-----------------*/
//定时上报时间结构体
typedef union
{
    uint16_t m_time;
    struct
    {
        uint8_t hour;    //时(BCD码)
        uint8_t minute;  //分(BCD码)
    }detail;

}fxrq_timed_byte;

//安全功能结构体
typedef union
{
    uint16_t SafeCode;  //功能码值
    struct
    {
        uint16_t GasLeakage_Upload          :     1;  //泄漏上报  （0 不上报 1上报） bit0
        uint16_t GasLeakage_Offvalve        :     1;  //泄漏关阀  （0 不关阀 1关阀）
        uint16_t Magnetism_Upload           :     1;  //磁干扰上报
        uint16_t Magnetism_Offvalve         :     1;  //磁干扰关阀
        uint16_t GasUsrMax_Upload           :     1;  //大流上报
        uint16_t GasUsrMax_Offvalve         :     1;  //大流关阀
        uint16_t GasAbnormalLittl_Upload    :     1;  //小流上报
        uint16_t GasAbnormalLittl_Offvalve  :     1;  //小流关阀
        uint16_t Qinxie_Upload              :     1;  //倾斜上报 （重新开启该功能）
        uint16_t Qinxie_Offvalve            :     1;  //倾斜关阀
        uint16_t MoveMeter_Upload           :     1;  //拆表上报 （针对膜式燃气表，拆表为开盖报警）
        uint16_t MoveMeter_Offvalve         :     1;  //拆表关阀
        uint16_t Inverse_Upload             :     1;  //反向安装上报 （反向通气）
        uint16_t Inverse_Offvalve           :     1;  //反向安装关阀   bit13
        uint16_t reserve                    :     2;  //保留位
    }bit;

}Safety_Features;

//表具运行状态结构体
typedef union
{
    uint16_t Stat_Value;  //状态值
    struct
    {
        uint16_t Sampling_Fail          :       1;  //针对超声波的采样，膜式表采样根据具体的异常事件,需要确定
        uint16_t GasLeakage_Stat        :       1; // 0:无泄漏  1:有泄漏
        uint16_t Magnetism_Stat         :       1; //磁干扰状态
        uint16_t GasUsrMax_Stat         :       1; //大流
        uint16_t GasAbnormalLittl_Stat  :       1; //小流
        uint16_t Battery_Overdraft      :       1; //电量不足 （使用电量透支报警）
        uint16_t Battery_Low            :       1; //低电量（使用电量报警）
        uint16_t Qinxie_Stat            :       1; //倾斜（使用地震事件的晃动检测）(不需要)
        uint16_t MoveMeter_Stat         :       1; //拆表 （针对膜式燃气表，拆表事件即开盖报警）
        uint16_t Inverse_Stat           :       1; //反向安装 （反向通气）  bit9
        uint16_t reserve                :       6; //保留位
    }bit;

}Running_Stat;

//阀门状态结构体
typedef union
{
    uint16_t Valve_Value;  //阀门状态值
    struct
    {
        uint16_t ContinueComm_Fail      :       1; //连续通讯失败 （0 无 1连续通讯失败）
        uint16_t GasLeakage_Stat        :       1; // 0:无泄漏  1:有泄漏
        uint16_t Magnetism_Stat         :       1; //磁干扰状态
        uint16_t GasUsrMax_Stat         :       1; //大流
        uint16_t GasAbnormalLittl_Stat  :       1; //小流
        uint16_t Battery_Overdraft      :       1; //电量不足 （使用电量透支报警）
        uint16_t Remote_OffValve        :       1; //无线关阀（需要协议确定具体代表什么） （0 无 1有无线关阀）
        uint16_t Qinxie_Stat            :       1; //倾斜（使用地震事件的晃动检测）(不需要)
        uint16_t MoveMeter_Stat         :       1; //拆表 （针对膜式燃气表，拆表事件即开盖报警）
        uint16_t Inverse_Stat           :       1; //反向安装 （反向通气）  bit9
        uint16_t reserve                :       6; //保留位
    }bit;

}Valve_Stat;

//上传原因结构体（上传方式）
typedef union
{
    uint16_t Upload_Way;   //上传方式
    struct
    {
        uint16_t Manual_Report      :       1;  //0:自动  1:按键
        uint16_t GasLeakage         :       1;  //0:无    1:泄漏
        uint16_t Magnetism          :       1;  //磁干扰
        uint16_t GasUsrMax          :       1;  //大流
        uint16_t GasAbnormalLittl   :       1;  //小流
        uint16_t TimeReport         :       1;  //定时上传
        uint16_t Qinxie             :       1;  //倾斜（暂时不需要）
        uint16_t Other              :       1;  //0:无  1:其他事件上报
        uint16_t MoveMeter          :       1;  //拆表（开盖报警事件）
        uint16_t Inverse            :       1;  //反向安装  bit9
        uint16_t reserve            :       6;  //保留位
    }bit;

}Upload_Reason;

//表具时间结构体 BCD码
typedef struct
{
    uint8_t              year;                                          //年
    uint8_t              month;                                         //月
    uint8_t              day;                                               //日
    uint8_t              hour;                                          //时
    uint8_t              minute;                                        //分
    uint8_t              second ;                                       //秒
}fxrq_rtc_time;

typedef struct
{
    uint16_t        CommFailDay;    //连续通讯失败关阀天数
    uint8_t         CommFailHour;   //连续通讯失败关阀时间 具体时间
    fxrq_timed_byte ReadStatTime;   //抄表冻结时间 （BCD码） 时分  2字节
    Safety_Features SafeFunCode;    //安全功能码 2字节

    int16_t         Temperature;    //温度
    uint16_t        Pressure;       //压力
    uint8_t         WorkTotalGas[5];    //工况累计量(扩大100倍,协议中确定为5字节)
    uint8_t         CurrentTotalGas[5]; //当前累计量(扩大100倍,协议中确定为5字节)

    uint32_t        LastThirtyDayGas[30]; //前30日冻结累积量
    Running_Stat    MeterState;    //表具运行状态 2字节
    Valve_Stat      ValveNum;      //阀门状态     2字节
    uint8_t         VoltageValue;  //电压值   1字节
    uint8_t         SupplyMode;    //供电方式 1字节
    uint8_t         Rssi;          //信号强度 1字节
    int16_t         Snr;           //信噪比   2字节
    int8_t          Cover_Level;   //覆盖等级 1字节
    uint8_t         Cell_id[6];    //基站编号 6字节 BCD码 超过12位取高位 不足12位高位补0

    fxrq_timed_byte TimeCommStart; //定时通讯开始时间  时 分 BCD码
    fxrq_timed_byte TimeCommEnd;   //定时通讯结束时间  时 分 BCD码
    uint16_t        TimeCommInterval; //定时通讯连接间隔  单位分钟 （相当于定时上报周期）
    uint8_t         CommTimeOut;   //通讯超时时间  单位分钟 (需要考虑与通用表的关联性)
    uint8_t         ReconnectNum;  //重连次数  单位次 （相当于重复上报的次数）
    uint8_t         ReconnectTime; //重连延迟时间 单位分钟
    uint8_t         SoftVer;       //程序版本号

    Upload_Reason   ReportWay;     //上报原因
    fxrq_rtc_time   MeterTime;     //表内时间  6字节 BCD码
    uint8_t         WorkMode;      //工作模式 1字节

}FENGXIAN_PROTOCOL_BUSINESS_REPORT_DATA;                                   //业务上报数据包(176字节)
;
typedef struct _BUSINESSUPLOADPACK
{
  FENGXIAN_PROTOCOL_FRAME_HEADER            head;
  FENGXIAN_PROTOCOL_BUSINESS_REPORT_DATA    body;
  uint8_t                                   complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_BUSINESS_REPORT_DATA)];
  FENGXIAN_PROTOCOL_FRAME_TAIL              tail;
}FENGXIAN_PROTOCOL_BUSINESS_REPORT_FRAME;                     //业务上报数据帧(表端发送)


/*----------------心跳包-----------------*/
typedef struct
{
    fxrq_rtc_time  current_time;// 心跳包数据内容为当前时间
}FENGXIAN_PROTOCOL_HEARTBEAT_PACK_DATA;       // 心跳包数据内容

typedef struct
{
    FENGXIAN_PROTOCOL_FRAME_HEADER          head;
    FENGXIAN_PROTOCOL_HEARTBEAT_PACK_DATA   body;
    uint8_t                                 complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_HEARTBEAT_PACK_DATA)];
    FENGXIAN_PROTOCOL_FRAME_TAIL            tail;
}FENGXIAN_PROTOCOL_HEARTBEAT_PACK_FRAME;         // 心跳包数据帧结构


/*----------------通讯参数设置-----------------*/
//通讯参数设置功能码
typedef union
{
    uint8_t funcode;
    struct
    {
        uint8_t SetTimedCommInterval    :       1;  //设置定时通讯时段与连接间隔
        uint8_t SetCommTimeOut          :       1;  //设置通讯超时时间
        uint8_t SetReConnectNum         :       1;  //设置重连延迟时间与重连次数
        uint8_t QueryInfo               :       1;  //查询
        uint8_t reserve                 :       4;  //保留位

    }detail;

}Connect_FunCode;

typedef struct
{
    Connect_FunCode     ConnectCode;    //功能码  1字节
    fxrq_timed_byte     StartTime;      //定时通讯开始时间 2字节
    fxrq_timed_byte     EndTime;        //定时通讯结束时间 2字节
    uint16_t            CommInterval;   //定时通讯连接间隔 2字节 单位 分钟
    uint8_t             CommTimeOut;    //通讯超时时间 1字节
    uint8_t             ReCommNum;      //重连次数  1字节
    uint8_t             ReCommDelay;    //重连延迟时间 1字节

}FENGXIAN_PROTOCOL_SET_COMMUNICATION_PARAM_DATA,FENGXIAN_PROTOCOL_SET_COMMUNICATION_PARAM_RSP_DATA;  //通讯参数设置数据域(10字节)

typedef struct
{
  FENGXIAN_PROTOCOL_FRAME_HEADER                        head;
  FENGXIAN_PROTOCOL_SET_COMMUNICATION_PARAM_DATA        body;        //加密时:数据内容长度后面紧接着为数据内容
  uint8_t                                               complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_SET_COMMUNICATION_PARAM_DATA)];
  FENGXIAN_PROTOCOL_FRAME_TAIL                          tail;
}FENGXIAN_PROTOCOL_SET_COMMUNICATION_PARAM_FRAME,           //通讯参数设置数据帧(表端接收)
FENGXIAN_PROTOCOL_SET_COMMUNICATION_PARAM_RSP_FRAME;        //通讯参数设置应答数据帧(表端发送)


/*----------------功能设置-----------------*/
//功能设置功能码结构体
typedef union
{
    uint8_t funcode;
    struct
    {
        uint8_t SetSecureMode       :       1; //设置安全模式
        uint8_t SetWorkMode         :       1; //设置工作模式
        uint8_t SetConnectFailed    :       1; //设置连续通讯失败关阀天数与时间
        uint8_t SetReadStaTime      :       1; //设置抄表冻结时间
        uint8_t SetFunMode          :       1; //设置安全功能
        uint8_t SetOverLittle       :       1; //设置大小流参数
        uint8_t reserve             :       2; //保留位
    }detail;

}FXRQ_FuncCode;

typedef struct
{
    FXRQ_FuncCode   FunCode;   //功能码 1字节
    uint8_t         SecureMode;  //安全模式
    uint8_t         WorkMode;    //工作模式
    uint16_t        CommFailedDay; //连续通讯失败关阀天数  2字节
    uint8_t         CommFailedTime;//连续通讯失败关阀时间  1字节
    fxrq_timed_byte ReadMeterTime; //抄表冻结时间 2字节 BCD码
    Safety_Features Safe_Func;     //安全功能 2字节
    uint8_t         OverLoadTime;  //大流时间 1字节 单位秒
    uint16_t        OverLoadFlow;  //大流流量上限  单位 0.1立方
    uint8_t         LittleTime;    //小流时间 1字节 单位秒
    uint8_t         LittleFlow;     //小流流量上限  单位 0.001立方

}FENGXIAN_PROTOCOL_SET_FUNCTION_DATA,FENGXIAN_PROTOCOL_SET_FUNCTION_RSP_DATA;   //功能设置数据域(15字节)

typedef struct
{
  FENGXIAN_PROTOCOL_FRAME_HEADER                        head;
  FENGXIAN_PROTOCOL_SET_FUNCTION_DATA                   body;        //加密时:数据内容长度后面紧接着为数据内容
  uint8_t                                               complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_SET_FUNCTION_DATA)];
  FENGXIAN_PROTOCOL_FRAME_TAIL                          tail;
}FENGXIAN_PROTOCOL_SET_FUNCTION_FRAME,                  //功能设置数据帧(表端接收)
FENGXIAN_PROTOCOL_SET_FUNCTION_RSP_FRAME;               //功能设置应答数据帧(表端发送)


/*----------------业务下发-----------------*/
//功能码结构体(业务下发)
typedef union
{
    uint8_t funcode;
    struct
    {
        uint8_t SetAccountBalance   :       1; //设置账户余额
        uint8_t SetBalanceStat      :       1; //设置余额状态
        uint8_t SetMeterTime        :       1; //设置表内时间
        uint8_t reserve             :       5; //保留位
    }detail;

}Fun_Code;

typedef struct
{
    Fun_Code        FunValue;     //功能码 1字节
    int32_t         SurplusMoney;  //账户余额 4字节 单位 精确到分
    uint8_t         SurplusStat;   //余额状态 00 正常 01 低余额  02 余额不足
    fxrq_rtc_time   MeterTime;     //表内时间 6字节 BCD码

}FENGXIAN_PROTOCOL_BUSINESS_DISTRIBUTE_DATA,FENGXIAN_PROTOCOL_BUSINESS_DISTRIBUTE_RSP_DATA;   //业务下发数据域(12字节)

typedef struct
{
    FENGXIAN_PROTOCOL_FRAME_HEADER                      head;   //帧头
    FENGXIAN_PROTOCOL_BUSINESS_DISTRIBUTE_DATA          body;   //帧体
    uint8_t                                             complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_BUSINESS_DISTRIBUTE_DATA)]; //补码
    FENGXIAN_PROTOCOL_FRAME_TAIL                        tail;
}FENGXIAN_PROTOCOL_BUSINESS_DISTRIBUTE_FRAME,       //业务下发数据帧(表端接收)
FENGXIAN_PROTOCOL_BUSINESS_DISTRIBUTE_RSP_FRAME;    //业务下发数据帧应答(表端发送)


/*----------------累积量设置-----------------*/
typedef struct
{
    uint8_t     TotalGas[5];     //5字节，最后一字节代表最后两位小数值

}FENGXIAN_PROTOCOL_SET_TOTAL_GAS_DATA,FENGXIAN_PROTOCOL_SET_TOTAL_GAS_RSP_DATA;   //累计量设置数据域(5字节)

typedef struct
{
    FENGXIAN_PROTOCOL_FRAME_HEADER                      head;   //帧头
    FENGXIAN_PROTOCOL_SET_TOTAL_GAS_DATA                body;   //帧体
    uint8_t                                             complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_SET_TOTAL_GAS_DATA)]; //补码
    FENGXIAN_PROTOCOL_FRAME_TAIL                        tail;
}FENGXIAN_PROTOCOL_SET_TOTAL_GAS_FRAME,       //累计量设置数据帧(表端接收)
FENGXIAN_PROTOCOL_SET_TOTAL_GAS_RSP_FRAME;    //累计量设置数据帧(表端发送)

/*----------------施工开阀-----------------*/
typedef struct
{
    uint8_t     valve_control;   //阀门控制(00 开阀)

}FENGXIAN_PROTOCOL_CONSTRUCTION_VALVE_CONTROL_DATA,FENGXIAN_PROTOCOL_CONSTRUCTION_VALVE_CONTROL_RSP_DATA;    //施工开阀数据域(1字节)

typedef struct
{
    FENGXIAN_PROTOCOL_FRAME_HEADER                      head;   //帧头
    FENGXIAN_PROTOCOL_CONSTRUCTION_VALVE_CONTROL_DATA   body;   //帧体
    uint8_t                                             complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_CONSTRUCTION_VALVE_CONTROL_DATA)]; //补码
    FENGXIAN_PROTOCOL_FRAME_TAIL                        tail;
}FENGXIAN_PROTOCOL_CONSTRUCTION_VALVE_CONTROL_FRAME,     //施工开阀数据帧(表端接收)
FENGXIAN_PROTOCOL_CONSTRUCTION_VALVE_CONTROL_RSP_FRAME;      //施工开阀应答数据帧(表端发送)


/*----------------通信结束帧-----------------*/
typedef struct
{
    fxrq_rtc_time       Server_Time;  //时间
    uint32_t            LadderSurplusGas;  //年累计量 该功能为：计算年累计用量(每年9月1号-次年8月31号),累计用量为整数（m3）
    uint16_t            CurGasPrice;  //当前气价(12字节)

}FENGXIAN_PROTOCOL_COMMUNICATION_END_DATA;    //通讯结束数据帧

typedef struct
{
    FENGXIAN_PROTOCOL_FRAME_HEADER                      head;   //帧头
    FENGXIAN_PROTOCOL_COMMUNICATION_END_DATA            body;   //帧体
    uint8_t                                             complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_COMMUNICATION_END_DATA)]; //补码
    FENGXIAN_PROTOCOL_FRAME_TAIL                        tail;
}FENGXIAN_PROTOCOL_COMMUNICATION_END_FRAME;   //通讯结束帧(表端接收)


/*----------------更新密钥-----------------*/
typedef struct
{
    uint8_t     KeyLength;      //密钥长度  1~32
    uint8_t     KeyVersion;     //密钥版本  1~255
    uint8_t     Key[32];        //密钥

}FENGXIAN_PROTOCOL_SET_KEY_DATA,FENGXIAN_PROTOCOL_SET_KEY_RSP_DATA;   //秘钥更新命令数据域(34字节)

typedef struct
{
    FENGXIAN_PROTOCOL_FRAME_HEADER                      head;   //帧头
    FENGXIAN_PROTOCOL_SET_KEY_DATA                      body;   //帧体
    uint8_t                                             complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_SET_KEY_DATA)]; //补码
    FENGXIAN_PROTOCOL_FRAME_TAIL                        tail;
}FENGXIAN_PROTOCOL_SET_KEY_FRAME,      //秘钥更新命令数据帧(表端接收)
FENGXIAN_PROTOCOL_SET_KEY_RSP_FRAME;       //秘钥更新命令应答数据帧(表端发送)

/*----------------开关阀命令-----------------*/
typedef struct
{
    uint8_t     valve_cmd;      //阀门控制命令

}FENGXIAN_PROTOCOL_REMOTE_VALVE_CONTROL_DATA,FENGXIAN_PROTOCOL_REMOTE_VALVE_CONTROL_RSP_DATA;   //开关阀命令数据域(1字节)

typedef struct
{
    FENGXIAN_PROTOCOL_FRAME_HEADER                      head;   //帧头
    FENGXIAN_PROTOCOL_REMOTE_VALVE_CONTROL_DATA         body;   //帧体
    uint8_t                                             complement[PADDING_LENGTH(FENGXIAN_PROTOCOL_REMOTE_VALVE_CONTROL_DATA)]; //补码
    FENGXIAN_PROTOCOL_FRAME_TAIL                        tail;

}FENGXIAN_PROTOCOL_REMOTE_VALVE_CONTROL_FRAME,      //开关阀命令（表端接收）
FENGXIAN_PROTOCOL_REMOTE_VALVE_CONTROL_RSP_FRAME;    //开关阀命令应答结果（表端发送）

#pragma pack()
#endif // FENGXIAN_H
