#ifndef QIANWEIPARSE_H
#define QIANWEIPARSE_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QByteArray>

class QianWeiParse : public QObject
{
    Q_OBJECT
    QByteArray m_frameData;         // 获取接收的报文数据
    QByteArray m_frameHead;         // 获取报文头数据
    QByteArray m_frameBody;         // 获取报文体数据
    QByteArray m_frameTail;         // 获取报文尾数据


public:
    enum COMMAND_TYPE
    {
        QIANWEI_PROTOCOL_SET_COMMUICATION_PARAM             = 0x7011,   // 设置通讯参数
        QIANWEI_PROTOCOL_SET_REPORT_PERIOD                  = 0x7012,   // 设置上报周期
        QIANWEI_PROTOCOL_SET_BILLING_PLAN                   = 0x7013,   // 设置计费方案
        QIANWEI_PROTOCOL_SET_WARNING_THRESHOLD              = 0x7014,   // 设置事件阈值
        QIANWEI_PROTOCOL_REMOTE_WRITE_PARAM                 = 0x7015,   // 远程写参数
        QIANWEI_PROTOCOL_SET_VALVE_CLOSING_PARAM            = 0x7016,   // 设置关阀参数
        QIANWEI_PROTOCOL_SET_VALVE_OPENING_PARAM            = 0x7017,   // 设置开阀参数
        QIANWEI_PROTOCOL_SET_ALARM_FUNCTION_ENABLE_CONFIG   = 0x7018,   // 设置报警功能使能配置
        QIANWEI_PROTOCOL_SET_EVENT_UPLOAD_PARAM             = 0x7019,   // 设置事件上传参数
        QIANWEI_PROTOCOL_SET_METER_BASE_PARAM               = 0x701a,   // 设置表端基本参数
        QIANWEI_PROTOCOL_REPORT_SINGLE                      = 0x7021,   // 单条上报数据
        XINSHENG_PROTOCOL_REPORT_PACKAGED_DATA              = 0x7022,   // 打包上报数据
        QIANWEI_PROTOCOL_RECHARGE                           = 0x7023,   // 充值
        QIANWEI_PROTOCOL_REMORT_VALVE_CONTROL               = 0x7024,   // 远程阀控
        QIANWEI_PROTOCOL_MODIFY_PURCHASE_BALANCE            = 0x7025,   // 修改总购余额
        QIANWEI_PROTOCOL_GET_COMMUNICATION_PARAM            = 0x7041,   // 获取通讯参数
        QIANWEI_PROTOCOL_GET_REPORT_PERIOD                  = 0x7042,   // 获取上报周期设置
        QIANWEI_PROTOCOL_GET_PURCHASE_BALANCE               = 0x7043,   // 获取总购和余额
        QIANWEI_PROTOCOL_GET_BILLING_PLAM                   = 0x7044,   // 获取计费方案设置
        QIANWEI_PROTOCOL_GET_WARNING_THRESHOLD              = 0X7045,   // 获取报警阈值设置
        QIANWEI_PROTOCOL_GET_HARDSOFTWARE_VERSION_ICCID     = 0x7046,   // 获取软硬件版本和ICCID
        QIANWEI_PROTOCOL_GET_VALVE_CLOSING_PARAM            = 0x7047,   // 获取关阀参数
        QIANWEI_PROTOCOL_GET_VALVE_OPENING_PARAM            = 0x7048,   // 获取开阀参数
        QIANWEI_PROTOCOL_GET_ALARM_FUNCTION_ENABLE_CONFIG   = 0x7049,   // 获取报警功能使能配置
        QIANWEI_PROTOCOL_GET_EVENT_UPLOAD_PARAM             = 0x704a,   // 获取事件上传参数
        QIANWEI_PROTOCOL_GET_METER_BASE_PARAM               = 0x704b,   // 获取表端基本参数
        QIANWEI_PROTOCOL_GET_HOUR_FROZEN_DATA               = 0x7051,   // 获取小时冻结数据
        QIANWEI_PROTOCOL_GET_DAY_FROZEN_DATA                = 0x7052,   // 获取日冻结数据
        QIANWEI_PROTOCOL_GET_MONTH_FROZEN_DATA              = 0x7053,   // 获取月冻结数据

        // 以下为修正仪
        QIANWEI_PROTOCOL_CORRECTOR_RECHARGE                             = 0x1013,   // 修正仪充值
        QIANWEI_PROTOCOL_CORRECTOR_SET_WARNING_THRESHOLD                = 0x1015,   // 修正仪报警限值设置
        QIANWEI_PROTOCOL_CORRECTOR_SET_BASE_NUMBER                      = 0x1016,   // 修正仪远程写底数
        QIANWEI_PROTOCOL_CORRECTOR_SET_VALVE_CLOSING_PARAM              = 0x1017,   // 修正仪设置关阀参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_VALVE_OPENING_PARAM              = 0x1018,   // 修正仪设置开阀参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_ALARM_FUNCTION_ENABLE_CONFIG     = 0x1019,   // 修正仪设置报警功能使能配置
        QIANWEI_PROTOCOL_CORRECTOR_SET_EVENT_WARNING_OUTPUT_CONFIG      = 0x101a,   // 修正仪设置事件报警输出配置
        QIANWEI_PROTOCOL_CORRECTOR_SET_EVENT_UPLOAD_PARAM               = 0x101b,   // 修正仪设置事件上传参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_PERIOD_AMOUNT                    = 0x101e,   // 修正仪设置周期使用数
        QIANWEI_PROTOCOL_CORRECTOR_SET_PRESSURE_PARAM                   = 0x1020,   // 修正仪设置压力参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_TEMPERATURE_PARAM                = 0x1021,   // 修正仪设置温度参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_COMPRESSION_FACTOR_PARAM         = 0x1022,   // 修正仪设置压缩因子参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_INPUT_OUTPUT_PARAM               = 0x1023,   // 修正仪设置输入输出参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_LOCALE_COMMUNICATION_PARAM       = 0x1024,   // 修正仪设置本地通讯参数
        QIANWEI_PROTOCOL_CORRECTOR_SET_PURCHASE_BALANCE                 = 0x1025,   // 修正仪设置总购和余额
        QIANWEI_PROTOCOL_CORRECTOR_SET_CENTER_BILLING_BALANCE_PRICE_SYN = 0x1026,   // 修正仪设置中心计费余额和气价同步

        QIANWEI_PROTOCOL_CORRECTOR_GET_BALANCE                          = 0x1093,   // 修正仪查询余额
        QIANWEI_PROTOCOL_CORRECTOR_GET_WARNING_THRESHOLD                = 0x1095,   // 修正仪获取报警限值
        QIANWEI_PROTOCOL_CORRECTOR_GET_REMOTE_BASE_NUMBER               = 0x1096,   // 修正仪远程获取底数
        QIANWEI_PROTOCOL_CORRECTOR_GET_VALVE_CLOSING_PARAM              = 0x1097,   // 修正仪获取关阀参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_VALVE_OPENING_PARAM              = 0x1098,   // 修正仪获取开阀参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_ALARM_FUNCTION_ENABLE_CONFIG     = 0x1099,   // 修正仪获取报警功能使能配置
        QIANWEI_PROTOCOL_CORRECTOR_GET_EVENT_WARNING_OUTPUT_CONFIG      = 0x109a,   // 修正仪获取报警输出使能配置
        QIANWEI_PROTOCOL_CORRECTOR_GET_EVENT_UPLOAD_PARAM               = 0x109b,   // 修正仪获取事件上传参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_PERIOD_AMOUNT                    = 0x109e,   // 修正仪获取周期使用数
        QIANWEI_PROTOCOL_CORRECTOR_GET_PRESSURE_PARAM                   = 0x10a0,   // 修正仪获取压力参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_TEMPERATURE_PARAM                = 0x10a1,   // 修正仪获取温度参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_COMPRESSION_FACTOR_PARAM         = 0x10a2,   // 修正仪获取压缩因子参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_INPUT_OUTPUT_PARAM               = 0x10a3,   // 修正仪获取输入输出参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_LOCALE_COMMUNICATION_PARAM       = 0x10a4,   // 修正仪获取本地通信参数
        QIANWEI_PROTOCOL_CORRECTOR_GET_MIN_FROZEN_DATA                  = 0x10c1,   // 修正仪获取分钟冻结数据
        QIANWEI_PROTOCOL_CORRECTOR_GET_HOUR_FROZEN_DATA                 = 0x10c2,   // 修正仪获取小时冻结数据
        QIANWEI_PROTOCOL_CORRECTOR_GET_DAY_FROZEN_DATA                  = 0x10c3,   // 修正仪获取日冻结数据
        QIANWEI_PROTOCOL_CORRECTOR_GET_MONTH_FROZEN_DATA                = 0x10c4,   // 修正仪获取月冻结数据
        QIANWEI_RPOTOCOL_CORRECTOR_GET_EVENT_DATA                       = 0x10c5,   // 获取事件数据

        QIANWEI_PROTOCOL_CORRECTOR_REPORT                               = 0x10e1,   // 修正仪主动上报数据
        QIANWEI_PROTOCOL_CORRECTOR_INFRARED_READING_METER               = 0x10e2,   // 修正仪红外抄表

    };

    enum FRAME_TYPE
    {
        QIANWEI_PROTOCOL_REQUEST,                           // 请求报文
        QIANWEI_PROTOCOL_RESPONSE,                          // 响应报文
    };

    enum TRANS_DIRECTION
    {
        QIANWEI_PROTOCOL_TRANS_DIRECTION_B2P,               // 传输方向为表->平台
        QIANWEI_PROTOCOL_TRANS_DIRECTION_P2B,               // 传输方向为平台->表端
    };

    QString m_parsedHead;           // 解析后的报文头数据
    QString m_parsedBody;           // 解析后的报文体数据
    QString m_ErrInfo;              // 错误信息

public:
    QianWeiParse(QString &inputData, QObject *parent = 0);
    void StartParse(void);
    COMMAND_TYPE ParseHead(FRAME_TYPE &frameType, TRANS_DIRECTION &transDirection);

    void ParseCorrectorReportData(void);

private:
    uint16_t crc16ForModbus(const QByteArray &data);
    void ComandTypePrint(const char *printMsg);

signals:

public slots:
};

#endif // QIANWEIPARSE_H
