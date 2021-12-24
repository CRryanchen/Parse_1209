#ifndef QIANWEI_H
#define QIANWEI_H

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
    uint8_t     Reserve[2];                 //数据保留位 2字节
    uint8_t		Encryption[2];              //加密保护
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
    uint8_t     reserve[2];                 // 数据保留位 2字节
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
    uint8_t     m_reserve[2];               // 数据保留位 2字节
}QIANWEI_PROTOCOL_SET_BILLING_PLAN;

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
}QIANWEI_REMOTE_WRITE_PARAM;

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
}QIANWEI_PROTOCOL_SET_ALARM_FUNCTION_ENABLE_CONFIG





#endif // QIANWEI_H
