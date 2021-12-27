#ifndef QIANWEI_H
#define QIANWEI_H

#pragma pack(1)

#define QIANWEI_PROTOCOL_FRAME_STARTCHAR           0X68        // 前卫协议起始符
#define QIANWEI_PROTOCOL_FRAME_ENDCHAR             0X16        // 前卫协议结束符

/*----------------前卫协议报文头-----------------*/
typedef struct{
    uint8_t  	StartChar;                  //起始符
    uint16_t 	FrameLength;                //报文长度
    uint8_t	 	HasMore;                    //是否有后续帧
    int32_t  	FrameID;                    //报文ID
    uint16_t  	ProtoclVersion;             //协议版本号
    uint16_t 	CommodCode;                 //命令码
    uint8_t		MeterID[20];                //表具编号
    uint8_t		ICCID[20];                  //ICCID号
    uint8_t     TransferDirection;          //传输方向
    uint8_t     RequestOrRespond;           //请求响应标志位
    uint16_t    Reserve;                    //数据保留位 2字节
    uint16_t    Encryption;                 //加密保护
    uint16_t    DataAreaLength;             //数据与长度
}QIANWEI_PROTOCOL_FRAME_HEADER;

/*----------------前卫协议报文尾-----------------*/
typedef struct{
    uint16_t     CRCCheck;                  //CRC校验
    uint8_t      EndChar;                   //数据与长度
}QIANWEI_PROTOCOL_FRAME_TAIL;


/*-------------通讯参数设置7011---------------*/
typedef struct{
    uint8_t     IPAddress[3][4];            // IP地址1、2、3
    uint16_t    Port[3];                    // 端口号1、2、3
    uint8_t     Communicate_Protocol;       // 通信协议
    uint8_t     ResendTimes;                // 重发次数
    uint8_t     reserve[2];                 // 数据保留位 2字节
}QIANWEI_PROTOCOL_SET_COMMUNICATION_PARAM_DATA;  //设置通讯参数数据域(22字节)


/*----------------上报周期设置7012--------------*/
typedef struct{
    uint8_t     ReportyType;                // 上报周期类型
    uint8_t    	ReportTime[3];              // 上报时间
    uint16_t    CycleValue;                 // 上报周期值
    uint16_t    DataInvert;                 // 数据采集间隔
    uint16_t    reserve;                    // 数据保留位 2字节
}QIANWEI_PROTOCOL_SET_REPORT_PERIOD_DATA;  //设置上报周期数据域（10字节）


/*----------------计费方案设置7013--------------*/
typedef struct
{
    uint8_t     m_billingMode;              // 计费模式
    uint8_t     m_tieredBillingCycle;       // 阶梯计费周期
    uint8_t     m_tieredNumber;             // 阶梯阶数
    uint8_t     m_tieredBillingStartDate[6];// 阶梯计费开始日期
    uint8_t     m_tieredBillingEffectiveDate[6];    // 阶梯计费生效日期
    uint32_t    m_tieredGasCapacity[5];     // 阶梯气量
    uint32_t    m_tieredGasPrice[6];        // 阶梯气价
    uint16_t    m_reserve;                  // 数据保留位 2字节
}QIANWEI_PROTOCOL_SET_BILLING_PLAN_DATA;

typedef struct
{
    uint16_t    m_ResponseCode;             // 响应码
    uint16_t    m_reserve;                  // 数据保留位 2字节
}QIANWEI_PROTOCOL_SET_BILLING_PLAN_RSP_DATA;

/*----------------报警阈值设置7014-------------*/
typedef struct{
    uint32_t	MaskCode;       			//掩码
    uint32_t 	MaxSurplusMoney;			//最大剩余金额
    int32_t	    PriceSurplusValue;			//剩余金额一级限值
    int32_t	    PriceOverrunValue;			//剩余金额二级限值
    int16_t     SuperFlowTime;				//过载
    int16_t		LittleFlowTime;				//异常小
    int16_t		TempLowValue;				//温度低限值
    int16_t		TempHightValue;	   			//温度高限值
    int16_t     PressureLowValue;  			//压力下限
    int16_t     PressureHighValue; 			//压力上限
    int16_t     ContinuedFlowTime; 			//持续流量时间
    uint8_t     LongTimeUnused;    			//长时间未用
    int32_t     DirectGas;     	    		//直通气量
    int16_t     LiPower[2];  			    //锂电池报警限值
    int16_t     DryPower[2];        		//干电池报警限值
    uint8_t     Earthquake[2];        		//地震
    int16_t     LongTimeUnconnect; 			//长时间未连接通信
    uint8_t		Reserve[2];
}QIANWEI_PROTOCOL_SET_WARNING_THRESEHOLD_DATA;  //设置报警阈值数据域(49字节)

/*----------------远传写参数7015-------------*/
typedef struct
{
    uint32_t    m_totalWorkingCondition;    // 工况总量
    uint32_t    m_standWorkingCondition;    // 标况总量
    uint32_t    m_reserve1;                 // 0xFFFFFFFF 无效
    uint32_t    m_reserve2;                 // 0xFFFFFFFF 无效
}QIANWEI_PROTOCOL_REMOTE_WRITE_PARAM;

/*----------------设置关阀参数7016-------------*/
typedef struct
{
    uint32_t    m_valveClosingParam;         // 关阀参数
    uint32_t    m_reserve;                  // 保留位
}QIANWEI_PROTOCOL_SET_VALVE_CLOSING_PARAM;

/*----------------设置开阀参数7017-------------*/
typedef struct
{
    uint32_t    m_valveOpeningParam;         // 开阀参数
    uint32_t    m_reserve;                  // 保留位
}QIANWEI_PROTOCOL_SET_VALVE_OPENING_PARAM;

/*----------------设置报警功能使能配置7018-------------*/
typedef struct
{
    uint32_t    m_alarmFunctionEnableConfig;    // 报警功能使能配置
    uint32_t    m_reserve;                  // 保留位
}QIANWEI_PROTOCOL_SET_ALARM_FUNCTION_ENABLE_CONFIG;

/*----------------设置事件上传参数7019-------------*/
typedef struct
{
    uint64_t    m_EventUploadParam;             // 事件上传参数
    uint64_t    m_reserve;                      // 保留位
}QIANWEI_PROTOCOL_SET_EVENT_UPLOAD_PARAM;


/*----------------设置表端基本参数701A-------------*/
typedef struct
{
    uint8_t		m_NewMeterID[20];                       // 表具编号
    uint32_t    m_PeriodStartReading;                   // 周期起始读数
    uint32_t    m_MinFlowrate;                          // 最小流量
    uint32_t    m_MaxFlowrate;                          // 最大流量
    uint32_t    m_OverloadFlowrate;                     // 过载流量
    uint32_t    m_TransitionalFlowrate;                 // 分界流量
    uint32_t    m_StartFlowrate;                        // 始动流量
    uint32_t    m_IsEnableRecordingFrozenData;          // 是否开启记录冻结数据
    uint32_t    m_ProductionOrExitFactoryMode;          // 生产模式/出厂模式
    uint8_t		Reserve[2];                             // 保留位
}QIANWEI_PROTOCOL_SET_METER_BASE_PARAM;



/*----------------单条数据上报7021-----------------*/
typedef struct{
    uint16_t	MeterType;                  //表具类型
    uint8_t		MeterReadYear;              //抄表时间
    uint8_t 	MeterReadMonth;
    uint8_t 	MeterReadDay;
    uint8_t		MeterReadHour;
    uint8_t		MeterReadMin;
    uint8_t		MeterReadSec;
    uint8_t		ReportType;                 //上报类型
    uint8_t		ValveStaus;                 //阀门状态
    uint32_t	Total_Working_Condition;    //工况总量,保留1位小数,传输时扩大10倍
    uint32_t	Stand_Working_Condition;    //标况总量,保留1位小数,传输时扩大10倍
    uint32_t	Standard_Instant_Flow;      //标况瞬时流量
    int16_t		Temperature;                //温度
    int16_t		Pressure;                   //压力
    int32_t		MoneySurplus;               //剩余金额,保留2位小数，传输时扩大100倍
    uint32_t	Latest_Settle_Reading;      //最新结算读数(表端预付费才上传)
    uint8_t		Latest_Settle_Timing[6];    //最新结算时间(表端预付费才上传)
    int32_t		WarmingStatus;              //告警状态
    int32_t		WarmingStatusReserveBit;    //告警状态保留位
    int16_t		DryPower;                   //干电池电量,保留2位小数,扩大100倍
    int16_t		LiPower;                    //锂电池电量,保留2位小数,扩大100倍
    int16_t		ModuleRSRP;                 //信号质量，保留1位小数，扩大10倍
    int16_t 	ModuleSNR;                  //信噪比，保留1位小数，扩大10倍
    int16_t		ModuleEARFCN;               //频点
    int8_t		ModuleCellId[6];            //基站小区标识
    int16_t		ModulePhysicalCellId;       //物理小区标识
    uint8_t		ModuleECL;                  //覆盖等级
    uint8_t		SoftWareVersion[4];         //固件版本号
    uint16_t	Reserve;                    //保留位
}QIANWEI_PROTOCOL_REPORT_SINGLE_DATA;      //单条数据上报数据域(73字节)


/*----------------打包数据上报7022-----------------*/
//表端->平台
//typedef struct{
//    uint16_t	MeterType;                  //表具类型
//    uint8_t		MeterReadYear;              //抄表时间
//    uint8_t 	MeterReadMonth;
//    uint8_t 	MeterReadDay;
//    uint8_t		MeterReadHour;
//    uint8_t		MeterReadMin;
//    uint8_t		MeterReadSec;
//    uint8_t     ReportYear;                 //上报时间
//    uint8_t     ReportMonth;
//    uint8_t     ReportDay;
//    uint8_t     ReportHour;
//    uint8_t     ReportMin;
//    uint8_t     ReportSec;
//    uint8_t		ValveStaus;                 //阀门状态
//    uint32_t	Total_Working_Condition;    //工况总量,保留1位小数,传输时扩大10倍
//    uint32_t	Stand_Working_Condition;    //标况总量,保留1位小数,传输时扩大10倍
//    uint32_t	Standard_Instant_Flow;      //标况瞬时流量
//    int16_t		Temperature;                //温度
//    int16_t		Pressure;                   //压力
//    int32_t		MoneySurplus;               //剩余金额,保留2位小数，传输时扩大100倍
//    uint32_t	Latest_Settle_Reading;      //最新结算读数(表端预付费才上传)
//    uint8_t		Latest_Settle_Timing[6];    //最新结算时间(表端预付费才上传)
//    int32_t		WarmingStatus;              //告警状态
//    int32_t		WarmingStatusReserveBit;    //告警状态保留位
//    int16_t		DryPower;                   //干电池电量,保留2位小数,扩大100倍
//    int16_t		LiPower;                    //锂电池电量,保留2位小数,扩大100倍
//    int16_t		ModuleRSRP;                 //信号质量，保留1位小数，扩大10倍
//    int16_t 	ModuleSNR;                  //信噪比，保留1位小数，扩大10倍
//    int16_t		ModuleEARFCN;               //频点
//    int8_t		ModuleCellId[6];            //基站小区标识
//    int16_t		ModulePhysicalCellId;       //物理小区标识
//    uint8_t		ModuleECL;                  //覆盖等级
//    uint8_t		SoftWareVersion[4];         //固件版本号
//    uint16_t	Reserve;                    //保留位
//}XINSHENG_PROTOCOL_REPORT_PACKAGED_DATA;    // 打包数据上报


/*----------------充值7023-----------------*/
typedef struct
{
    uint32_t    m_RechargeTotalPurchaseBalance;     // 充值总购余额
    uint16_t	Reserve;                            // 保留位
}QIANWEI_PROTOCOL_RECHARGE;


/*---------------远程阀控7024-----------------*/
typedef struct{
    uint16_t     valveCommand;				//开关阀命令
}QIANWEI_PROTOCOL_REMOTE_VALVE_CONTROL_DATA; //远程阀控数据域(2字节)

typedef struct
{
    uint16_t    m_ResponseCode;             // 响应码
    uint16_t    m_reserve;                  // 数据保留位 2字节
}QIANWEI_PROTOCOL_REMOTE_VALVE_CONTROL_RSP_DATA;

/*--------------设置总购和余额7025------------*/
typedef struct{
    uint32_t	TotoalMoney;	//充值总购金额
    int32_t		LeftMoney;		//剩余金额
    uint32_t	CurrentPrice;	//当前单价
    uint8_t		reserve[2];
}QIANWEI_PROTOCOL_MODIFY_PURCHASE_BALANCE_DATA;		//修改总购余额数据域(14字节)


///*--------------获取通讯参数7041------------*/
//typedef struct
//{

//}QIANWEI_PROTOCOL_GET_COMMUNICATION_PARAM;



/*--------------修正仪充值1013------------*/
typedef struct
{
    uint8_t     m_BillingType;                      // 计费种类
    uint8_t     m_reserve[3];                       // 保留位
    uint32_t    m_RechargeTotalPurchaseAmountInt;   // 充值总购金额整数
    uint32_t    m_RechargeTotalPurchaseAmountDec;   // 充值总购金额小数
    uint32_t    m_RechargeTotalGasPurchaseInt;      // 充值总购气量整数
    uint32_t    m_RechargeTotalGasPurchaseDec;      // 充值总购气量小数
}QIANWEI_PROTOCOL_CORRECTOR_RECHARGE_DATA;

typedef struct
{
    uint16_t    m_ResponseCode;                     // 响应码
    uint8_t     m_BillingType;                      // 计费种类
    uint8_t     m_reserve;                          // 保留位
    uint32_t    m_RechargeTotalPurchaseAmountInt;   // 充值总购金额整数
    uint32_t    m_RechargeTotalPurchaseAmountDec;   // 充值总购金额小数
    uint32_t    m_RechargeTotalGasPurchaseInt;      // 充值总购气量整数
    uint32_t    m_RechargeTotalGasPurchaseDec;      // 充值总购气量小数
}QIANWEI_PROTOCOL_CORRECTOR_RECHARGE_RSP_DATA;


/*--------------修正仪主动上报数据10e1------------*/
// 上一天冻结数据结构体
typedef struct
{
    uint8_t         m_Time[4];                      // 上一天冻结数据时间 百年——年——月——日
    uint32_t        m_MaxPressure;                  // 上一天冻结数据最大压力
    uint32_t        m_MinPressure;                  // 上一天冻结数据最小压力
    uint16_t        m_MaxTemp;                      // 上一天冻结数据最大温度
    uint16_t        m_MinTemp;                      // 上一天冻结数据最小温度
    uint32_t        m_TotalWorkingConditionInteger; // 上一天冻结数据工况总量整数
    uint32_t        m_TotalWorkingConditionDecimal; // 上一天冻结数据工况总量小数
    uint32_t        m_TotalStandardConditionInteger; // 上一天冻结数据标况总量整数
    uint32_t        m_TotalStandardConditionDecimal; // 上一天冻结数据标况总量小数

}_LastDatFrozenData;

typedef struct
{
    uint16_t        m_PackNumberToSend;             // 有多少包需要发送
    uint16_t        m_Padding1;                      // 填充位
    uint16_t        m_MeterType;                    // 表具类型
    uint8_t         m_ReadMeterTime[6];             // 抄表时间
    _LastDatFrozenData LastDatFrozenData;           // 上一天冻结数据
    uint8_t         m_ReportType;                   // 上报类型
    uint8_t         m_BillingType;                  // 计费种类
    uint8_t         m_BillingNature;                // 计费性质
    uint8_t         m_ValveStatus;                  // 阀门状态
    uint32_t        m_TotalWorkingConditionInteger; // 工况总量整数
    uint32_t        m_TotalWorkingConditionDecimal; // 工况总量小数
    uint32_t        m_TotalStandardConditionInteger;// 标况总量整数
    uint32_t        m_TotalStandardConditionDecimal;// 标况总量小数
    uint8_t         m_CorrectionAlgorithm;          // 修正算法
    uint8_t         m_Padding2;                     // 填充位
    uint16_t        m_Temperature;                  // 温度
    uint32_t        m_Pressure;                     // 压力
    uint32_t        m_WorkingConditionFlow;         // 工况流速
    uint32_t        m_StandardConditionFlow;        // 标况流速
    uint32_t        m_WorkingConditionCompressionFactor;// 工况压缩因子
    uint32_t        m_StandardConditionCompressionFactor;// 标况压缩因子
    uint32_t        m_CorrectionFactor;             // 修正系数
    uint32_t        m_BalanceInteger;               // 剩余金额整数
    uint32_t        m_BalanceDecimal;               // 剩余金额小数
    uint32_t        m_RemainingGasInteger;          // 剩余气量整数
    uint32_t        m_RemainingGasDecimal;          // 剩余气量小数
    uint8_t         m_HardwareVersion[4];           // 硬件版本号
    uint8_t         m_SoftwareVersion[4];           // 固件版本号
    uint32_t        m_WorkingStatusCol1;            // 工作状态集合1
    uint32_t        m_WorkingStatusCol2;            // 工作状态集合2
    uint16_t        m_InnerLiBatteyPower;           // 内部锂电池电量
    uint16_t        m_ValveBatteryPower;            // 阀门电池电量
    uint16_t        m_CumulativeReportTimes;        // 表具累计上报次数
    uint16_t        m_ModuleRSPR;                   // 信号质量
    uint16_t        m_ModuleSNR;                    // 信噪比
    uint16_t        m_ModulePhysicalCellId;         // 物理小区标识
    uint32_t        m_MainBaseStationNumber;        // 主基站编号
    uint16_t        m_ModuleEARFCN;                 // 频点
    uint8_t         m_NerworkFailReason;            // 网络传输失败原因
    uint8_t         m_ModuleECL;                    // 覆盖等级
    uint8_t         m_ModuleCellId[6];              // 基站小区标识
    uint16_t        m_Padding3;                     // 填充位
}QIANWEI_PROTOCOL_CORRECTOR_REPORT_DATA;


#pragma pack()

#endif // QIANWEI_H
