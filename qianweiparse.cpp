#include "qianweiparse.h"
#include "qianwei.h"


static const quint16 crc16Table[] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

template<typename T>
QString QianWeiParse::FormatOutput(const QString &str, const T &data, bool endline = true)
{
    if (str.toLocal8Bit().size() >= 12)
    {
        return QString().sprintf("%s\t：%0*x", str.toUtf8().data(), sizeof(data) * 2, data) + QString(endline ? "\n" : "");
    }
    else
    {
        return QString().sprintf("%s\t\t：%0*x", str.toUtf8().data(), sizeof(data) * 2, data) + QString(endline ? "\n" : "");
    }
}

QString FormatOutputTime(const QString &str, const uint8_t *time)
{
    if (str.toLocal8Bit().size()  >= 12)
    {
        return QString().sprintf("%s\t：%02x/%02x/%02x %02x:%02x:%02x\n", str.toUtf8().data(), time[0], time[1], time[2], time[3], time[4], time[5]);
    }
    else
    {
        return QString().sprintf("%s\t\t：%02x/%02x/%02x %02x:%02x:%02x\n", str.toUtf8().data(), time[0], time[1], time[2], time[3], time[4], time[5]);
    }

}

QString FormatOutputVersion(const QString &str, const uint8_t *version)
{
    if (str.toLocal8Bit().size() >= 12)
    {
        return QString().sprintf("%s\t：%d%d.%d%d\n", str.toUtf8().data(), version[0] - '0', version[1] - '0', version[2] - '0', version[3] - '0');
    }
    else
    {
        return QString().sprintf("%s\t\t：%d%d.%d%d\n", str.toUtf8().data(), version[0] - '0', version[1] - '0', version[2] - '0', version[3] - '0');
    }

}

QianWeiParse::QianWeiParse(QString &inputData, QObject *parent) : QObject(parent)
{
    this->m_frameData = QByteArray::fromHex(inputData.toLocal8Bit());

    this->m_frameHead = this->m_frameData.left(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER));
//    qDebug() << m_frameHead.data();
    this->m_frameTail = this->m_frameData.right(sizeof(QIANWEI_PROTOCOL_FRAME_TAIL));
//    qDebug() << m_frameTail.data();
}

void QianWeiParse::StartParse()
{
    // 校验协议头
    QIANWEI_PROTOCOL_FRAME_HEADER head;
    memcpy((uint8_t *)&head.StartChar, (uint8_t *)this->m_frameHead.data(), this->m_frameHead.size());
    // 判断起始符
    if (head.StartChar == QIANWEI_PROTOCOL_FRAME_STARTCHAR)
    {
        // 起始符正确
        qDebug() << "起始符正确!";
    }
    else
    {
        // 起始符错误
        qDebug() << "起始符错误!";
        this->m_ErrInfo += "起始符错误";
        return ;
    }

    FRAME_TYPE frameType;
    TRANS_DIRECTION transDirection;
    QianWeiParse::COMMAND_TYPE commandType = this->ParseHead(frameType, transDirection);

    // 校验协议尾
    QIANWEI_PROTOCOL_FRAME_TAIL tail;
    memcpy((uint8_t *)&tail.CRCCheck, (uint8_t *)this->m_frameTail.data(), this->m_frameTail.size());
    uint16_t crc = tail.CRCCheck;
    if (transDirection == QIANWEI_PROTOCOL_TRANS_DIRECTION_B2P)
    {
        crc = (tail.CRCCheck & 0xff) << 8;
        crc |= tail.CRCCheck >> 8;
    }


    // 需要校验的数据
    QByteArray needCRCData = this->m_frameData;
    needCRCData.chop(sizeof(QIANWEI_PROTOCOL_FRAME_TAIL));
    qDebug() << crc;
    qDebug() << crc16ForModbus(needCRCData);
    if (crc == crc16ForModbus(needCRCData))
    {
        // 校验码正确
        qDebug() << "校验码正确!";
    }
    else
    {
        // 校验码错误
        qDebug() << "校验码错误!";
        this->m_ErrInfo += "校验码错误";
        return ;
    }
    // 判断结束符
    if (tail.EndChar == QIANWEI_PROTOCOL_FRAME_ENDCHAR)
    {
        // 结束符正确
        qDebug() << "结束符正确!";
    }
    else
    {
        // 结束符错误
        qDebug() << "结束符错误!";
        this->m_ErrInfo += "结束符错误";
        return ;
    }

    switch(commandType)
        {
            case QIANWEI_PROTOCOL_SET_REPORT_PERIOD:
            if(transDirection == QIANWEI_PROTOCOL_TRANS_DIRECTION_P2B)
            {
                this->ComandTypePrint("7012——设置上报周期");
                qDebug() << "This is 7012 from PT";
                this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_SET_REPORT_PERIOD_DATA));
                this->ParseSetReportCycleData();
            }
            else
            {
                this->ComandTypePrint("7012——设置上报周期响应帧");
                qDebug() << "This is 7012 rsp from BD";
            }
            break;

            case QIANWEI_PROTOCOL_SET_BILLING_PLAN:
            if(transDirection == QIANWEI_PROTOCOL_TRANS_DIRECTION_P2B)
            {
                this->ComandTypePrint("7013——设置计费方案");
                qDebug() << "This is 7013 from PT";
                this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_SET_BILLING_PLAN_DATA));
                this->ParseSetBillingPlanData();
            }
            else
            {
                this->ComandTypePrint("7013——设置计费方案响应帧");
                qDebug() << "This is 7013 rsp from BD";
                this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_SET_BILLING_PLAN_RSP_DATA));
                this->ParseSetBillingPlanRspData();
            }
            break;

            case QIANWEI_PROTOCOL_REPORT_SINGLE:
            break;

            case QIANWEI_PROTOCOL_REMORT_VALVE_CONTROL:
            if(transDirection == QIANWEI_PROTOCOL_TRANS_DIRECTION_P2B)
            {
                this->ComandTypePrint("7024——远程阀控");
                qDebug() << "This is 7024 from PT";
                this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_REMOTE_VALVE_CONTROL_DATA));
                this->ParseSetRemoteValveData();
            }
            else
            {
                this->ComandTypePrint("7024——远程阀控响应帧");
                qDebug() << "This is 7024 rsp from BD";
                this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_REMOTE_VALVE_CONTROL_RSP_DATA));
                this->ParseSetRemoteValveRspData();
            }
            break;

            case QIANWEI_PROTOCOL_CORRECTOR_RECHARGE:
            {
                if (frameType == QIANWEI_PROTOCOL_REQUEST)
                {
                    this->ComandTypePrint("1013——修正仪充值");
                    qDebug() << "This is 1013 from PT";
                    this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_CORRECTOR_RECHARGE_DATA));
                    this->ParseCorrectorRechargeData();
                }
                else
                {
                    this->ComandTypePrint("1013——修正仪充值数据响应帧");
                    qDebug() << "This is 1013 rsp from BD";
                    this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_CORRECTOR_RECHARGE_RSP_DATA));
                    this->ParseCorrectorRechargeRspData();
                }
            }
            break;

            case QIANWEI_PROTOCOL_CORRECTOR_REPORT:
            {
                if (frameType == QIANWEI_PROTOCOL_REQUEST)
                {
                    this->ComandTypePrint("10e1——修正仪主动上报数据");
                    qDebug() << "This is 10E1 to PT";
                    this->m_frameBody = this->m_frameData.mid(sizeof(QIANWEI_PROTOCOL_FRAME_HEADER), sizeof(QIANWEI_PROTOCOL_CORRECTOR_REPORT_DATA));
//                    for(int i = 0; i < m_frameBody.size(); i++)
//                    {
//                        qDebug("%02x", m_frameBody.at(i));
//                    }
                    this->ParseCorrectorReportData();
                }
                else
                {
                    this->ComandTypePrint("10e1——修正仪主动上报数据响应帧");
                    qDebug() << "This is 10E1 rsp from PT";
                }

            }
            break;

            default:
                qDebug() << "未识别的命令码";
            break;
        }
}

QianWeiParse::COMMAND_TYPE QianWeiParse::ParseHead(QianWeiParse::FRAME_TYPE &frameType, QianWeiParse::TRANS_DIRECTION &transDirection)
{
    QString temp = 0;

//    this->m_defaultKey = "QW";
//    qDebug() << "设置初始密钥";


    QIANWEI_PROTOCOL_FRAME_HEADER head;
    memcpy((uint8_t *)&head.StartChar, (uint8_t *)this->m_frameHead.data(), this->m_frameHead.size());

    temp += this->FormatOutput<uint8_t>(QString("帧头"), head.StartChar);
    temp += FormatOutput<uint16_t>("长度", head.FrameLength, false) + QString().sprintf("(%d)\n", head.FrameLength);
    qDebug("%02x", (uint16_t)head.FrameLength);
    temp += FormatOutput<uint8_t>("后续帧", head.HasMore, false) + QString().sprintf("(%s后续帧)\n", head.HasMore?"有":"没有");
    temp += FormatOutput<uint32_t>("报文ID", (uint32_t)head.FrameID);
    temp += FormatOutput<uint16_t>("协议版本号", head.ProtoclVersion);
    temp += FormatOutput<uint16_t>("命令码", head.CommodCode);

    temp += QString("表具编号\t\t：");
    for (int i = 0; i < 20; i++)
    {
        temp += QString().sprintf("%0*x", sizeof(head.MeterID[i]) * 2, head.MeterID[i]);
    }

    temp += QString("(");
    for (int i = 0; i < 20; i++)
    {
        temp += QString().sprintf("%x", head.MeterID[i] - '0');
    }
    temp += QString(")\n");

    // ICCID需要使用，平台下发的ICCID有问题
    if (head.TransferDirection)
    {
        transDirection = QIANWEI_PROTOCOL_TRANS_DIRECTION_B2P;
    }
    else
    {
        transDirection = QIANWEI_PROTOCOL_TRANS_DIRECTION_P2B;
    }

    temp += QString("ICCID号\t\t：");
    for (int i = 0; i < 20; i++)
    {
        temp += QString().sprintf("%0*x", sizeof(head.ICCID[i]) * 2, head.ICCID[i]);
    }
    temp += QString("(");
    if (transDirection == QIANWEI_PROTOCOL_TRANS_DIRECTION_B2P)
    {
        for (int i = 0; i < 20; i++)
        {
            temp += QString().sprintf("%x", head.ICCID[i] - '0');
        }
    }
    else if (transDirection == QIANWEI_PROTOCOL_TRANS_DIRECTION_P2B)
    {
        temp += QString("平台下发ICCID有问题");
    }

    temp += QString(")\n");

    temp += FormatOutput<uint8_t>("传输方向", head.TransferDirection, false) + QString().sprintf("(表具%s平台)\n", head.TransferDirection? "-->" : "<--");

    temp += FormatOutput<uint8_t>("请求响应标志位", head.RequestOrRespond, false) + QString().sprintf("(%s)\n", head.RequestOrRespond ? "响应" : "请求");
    if (head.RequestOrRespond)
    {
        frameType = QIANWEI_PROTOCOL_RESPONSE;
    }
    else
    {
        frameType = QIANWEI_PROTOCOL_REQUEST;
    }
    temp += FormatOutput<uint16_t>("数据保留位", head.Reserve);
    temp += FormatOutput<uint16_t>("加密保护", head.Encryption);
    temp += FormatOutput<uint16_t>("数据域长度", head.DataAreaLength, false) + QString().sprintf("(%d)\n", head.DataAreaLength);

    this->m_parsedHead = temp;
    return (QianWeiParse::COMMAND_TYPE)head.CommodCode;
}

void QianWeiParse::ParseSetBillingPlanData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_SET_BILLING_PLAN_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());

    temp += this->FormatOutput<uint8_t>("计费模式", body.m_billingMode, false);
    switch (body.m_billingMode)
    {
    case 0x00:
        temp += QString("(中心计费)\n");
        break;

    case 0x01:
        temp += QString("(表端计费)\n");
        break;

    default:
        temp += QString("(未定义)\n");
        break;
    }

    temp += this->FormatOutput<uint8_t>("阶梯计费周期", body.m_tieredBillingCycle, false);
    switch (body.m_tieredBillingCycle)
    {
    case 0x00:
        temp += QString("(日阶梯)\n");
        break;

    case 0x01:
        temp += QString("(月阶梯)\n");
        break;

    case 0x02:
        temp += QString("(双月阶梯)\n");
        break;

    case 0x03:
        temp += QString("(季度阶梯)\n");
        break;

    case 0x04:
        temp += QString("(年阶梯)\n");
        break;

    default:
        temp += QString("(未定义)\n");
        break;
    }

    temp += this->FormatOutput<uint8_t>("阶梯阶数", body.m_tieredNumber, false);
    switch (body.m_tieredNumber)
    {
    case 0x00:
        temp += QString("(无阶梯)\n");
        break;

    case 0x02:
        temp += QString("(2阶梯)\n");
        break;

    case 0x03:
        temp += QString("(3阶梯)\n");
        break;

    case 0x04:
        temp += QString("(4阶梯)\n");
        break;

    case 0x05:
        temp += QString("(5阶梯)\n");
        break;

    case 0x06:
        temp += QString("(6阶梯)\n");
        break;

    default:
        temp += QString("(未定义)\n");
        break;
    }

    temp += FormatOutputTime("阶梯计费开始日期", body.m_tieredBillingStartDate);
    temp += FormatOutputTime("阶梯计费生效日期", body.m_tieredBillingEffectiveDate);

    for (int i = 0; i < 5; i++)
    {
        temp += this->FormatOutput<uint32_t>("阶梯气量i", body.m_tieredGasCapacity[i]);
    }

    for (int i = 0; i < 6; i++)
    {
        temp += this->FormatOutput<uint32_t>("阶梯气价i", body.m_tieredGasPrice[i]);
    }
    temp += this->FormatOutput<uint16_t>("保留位", body.m_reserve);

    this->m_parsedBody += temp;
}

void QianWeiParse::ParseSetBillingPlanRspData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_SET_BILLING_PLAN_RSP_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());

    temp += this->FormatOutput<uint16_t>("响应码", body.m_ResponseCode);
    temp += this->FormatOutput<uint16_t>("保留位", body.m_reserve);

    this->m_parsedBody += temp;
}

void QianWeiParse::ParseSetRemoteValveData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_REMOTE_VALVE_CONTROL_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());

    temp += this->FormatOutput<uint16_t>("开关阀命令", body.valveCommand, false);
    switch(body.valveCommand)
    {
        case 0X00:
            temp += "(强制关阀(用户无法打开))\n";
        break;

        case 0X01:
            temp += "(开阀)\n";
        break;

        case 0X02:
            temp += "(临时关阀(用户可以打开))\n";
        break;
    }

    this->m_parsedBody += temp;
}

void QianWeiParse::ParseSetRemoteValveRspData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_REMOTE_VALVE_CONTROL_RSP_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());

    temp += this->FormatOutput<uint16_t>("响应码", body.m_ResponseCode);
    temp += this->FormatOutput<uint16_t>("保留位", body.m_reserve);

    this->m_parsedBody += temp;
}

void QianWeiParse::ParseCorrectorReportData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_CORRECTOR_REPORT_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());

    temp += FormatOutput<uint16_t>("有多少包需要发送", body.m_PackNumberToSend);
    temp += FormatOutput<uint16_t>("填充位", body.m_Padding1);
    temp += FormatOutput<uint16_t>("表具类型", body.m_MeterType, false);
    switch(body.m_MeterType)
    {
        case 0xCA:
        {
            temp += QString("(皮膜表)\n");
        }
        break;

        case 0xDA:
        {
            temp += QString("(家用超声波表)\n");
        }
        break;

        default:
        {
            temp += QString("(不存在的表具类型)\n");
        }
        break;
    }

    temp += FormatOutputTime("抄表时间", body.m_ReadMeterTime);
    temp += FormatOutput<uint8_t>("上一天冻结数据百年", body.LastDatFrozenData.m_Time[0]);
    temp += FormatOutput<uint8_t>("上一天冻结数据年", body.LastDatFrozenData.m_Time[1]);
    temp += FormatOutput<uint8_t>("上一天冻结数据月", body.LastDatFrozenData.m_Time[2]);
    temp += FormatOutput<uint8_t>("上一天冻结数据日", body.LastDatFrozenData.m_Time[3]);
    temp += FormatOutput<uint32_t>("上一天冻结数据最大压力", body.LastDatFrozenData.m_MaxPressure);
    temp += FormatOutput<uint32_t>("上一天冻结数据最小压力", body.LastDatFrozenData.m_MinPressure);
    temp += FormatOutput<uint16_t>("上一天冻结数据最大温度", body.LastDatFrozenData.m_MaxTemp);
    temp += FormatOutput<uint16_t>("上一天冻结数据最小温度", body.LastDatFrozenData.m_MinTemp);
    temp += FormatOutput<uint32_t>("上一天冻结数据工况总量整数", body.LastDatFrozenData.m_TotalWorkingConditionInteger);
    temp += FormatOutput<uint32_t>("上一天冻结数据工况总量小数", body.LastDatFrozenData.m_TotalWorkingConditionDecimal);
    temp += FormatOutput<uint32_t>("上一天冻结数据标况总量整数", body.LastDatFrozenData.m_TotalStandardConditionInteger);
    temp += FormatOutput<uint32_t>("上一天冻结数据标况总量小数", body.LastDatFrozenData.m_TotalStandardConditionDecimal);

    temp += FormatOutput<uint8_t>("上报类型", body.m_ReportType, false);
    switch(body.m_ReportType)
    {
        case 0x00:
        {
            temp += QString("(定时上报)\n");
        }
        break;

        case 0x01:
        {
            temp += QString("(手动上报)\n");
        }
        break;

        case 0x02:
        {
            temp += QString("(异常上报)\n");
        }
        break;

        default:
        {
            temp += QString("(不存在的上报类型)\n");
        }
        break;
    }

    temp += FormatOutput<uint8_t>("计费种类", body.m_BillingType, false);
    switch(body.m_BillingType)
    {
        case 0x00:
        {
            temp += QString("(金额计费)\n");
        }
        break;

        case 0x01:
        {
            temp += QString("(气量计费)\n");
        }
        break;

        default:
        {
            temp += QString("(不存在的计费种类)\n");
        }
        break;
    }

    temp += FormatOutput<uint8_t>("计费性质", body.m_BillingNature, false);
    switch(body.m_BillingNature)
    {
        case 0x00:
        {
            temp += QString("(预付费)\n");
        }
        break;

        case 0x01:
        {
            temp += QString("(后付费)\n");
        }
        break;

        default:
        {
            temp += QString("(不存在的计费性质)\n");
        }
        break;
    }

    temp += FormatOutput<uint8_t>("阀门状态", body.m_ValveStatus, false);
    switch(body.m_ValveStatus)
    {
        case 0x00:
        {
            temp += QString("(无阀门)\n");
        }
        break;

        case 0x01:
        {
            temp += QString("(阀门开)\n");
        }
        break;

        case 0x02:
        {
            temp += QString("(阀门临时关)\n");
        }
        break;

        case 0x03:
        {
            temp += QString("(阀门强制关)\n");
        }
        break;

        case 0x04:
        {
            temp += QString("(阀门状态未知)\n");
        }
        break;

        default:
        {
            temp += QString("(不存在的计费性质)\n");
        }
        break;
    }

    temp += FormatOutput<uint32_t>("工况总量整数", body.m_TotalWorkingConditionInteger);
    temp += FormatOutput<uint32_t>("工况总量小数", body.m_TotalWorkingConditionDecimal);
    temp += FormatOutput<uint32_t>("标况总量整数", body.m_TotalStandardConditionInteger);
    temp += FormatOutput<uint32_t>("标况总量小数", body.m_TotalStandardConditionDecimal);

    temp += FormatOutput<uint8_t>("修正算法", body.m_CorrectionAlgorithm, false);
    switch(body.m_CorrectionAlgorithm)
    {
        case 0x00:
        {
            temp += QString("(替代值)\n");
        }
        break;

        case 0x01:
        {
            temp += QString("(S-Gerg)\n");
        }
        break;

        case 0x02:
        {
            temp += QString("(AGA_8 DC92)\n");
        }
        break;

        case 0x03:
        {
            temp += QString("(AGA_NX19)\n");
        }
        break;

        default:
        {
            temp += QString("(未定义的修正算法)\n");
        }
        break;
    }

    temp += FormatOutput<uint8_t>("填充位", body.m_Padding2);
    temp += FormatOutput<uint16_t>("温度", body.m_Temperature);
    temp += FormatOutput<uint32_t>("压力", body.m_Pressure);
    temp += FormatOutput<uint32_t>("工况流速", body.m_WorkingConditionFlow);
    temp += FormatOutput<uint32_t>("标况流速", body.m_StandardConditionFlow);
    temp += FormatOutput<uint32_t>("工况压缩因子", body.m_WorkingConditionCompressionFactor);
    temp += FormatOutput<uint32_t>("标况压缩因子", body.m_StandardConditionCompressionFactor);
    temp += FormatOutput<uint32_t>("修正系数", body.m_CorrectionFactor);
    temp += FormatOutput<uint32_t>("剩余金额整数", body.m_BalanceInteger);
    temp += FormatOutput<uint32_t>("剩余金额小数", body.m_BalanceDecimal);
    temp += FormatOutput<uint32_t>("剩余气量整数", body.m_RemainingGasInteger);
    temp += FormatOutput<uint32_t>("剩余气量小数", body.m_RemainingGasDecimal);

    temp += FormatOutputVersion("硬件版本", body.m_HardwareVersion);
    temp += FormatOutputVersion("固件版本", body.m_SoftwareVersion);

    temp += FormatOutput<uint32_t>("工作状态集合1", body.m_WorkingStatusCol1);
    temp += FormatOutput<uint32_t>("工作状态集合2", body.m_WorkingStatusCol2);
    temp += FormatOutput<uint16_t>("内部锂电池电量", body.m_InnerLiBatteyPower);
    temp += FormatOutput<uint16_t>("阀门电池电量", body.m_ValveBatteryPower);
    temp += FormatOutput<uint16_t>("表具累计上报次数", body.m_CumulativeReportTimes);
    temp += FormatOutput<uint16_t>("信号质量", body.m_ModuleRSPR);
    temp += FormatOutput<uint16_t>("信噪比", body.m_ModuleSNR);
    temp += FormatOutput<uint16_t>("physical cell id", body.m_ModulePhysicalCellId);
    temp += FormatOutput<uint32_t>("主基站编号", body.m_MainBaseStationNumber);
    temp += FormatOutput<uint16_t>("频点", body.m_ModuleEARFCN);
    temp += FormatOutput<uint8_t>("网络传输失败原因", body.m_NerworkFailReason);
    temp += FormatOutput<uint8_t>("ecl", body.m_ModuleECL);

    temp += QString("基站小区标识\t\t：");
    for (int i = 0; i < 6; i++)
    {
        temp += QString().sprintf("%02x", (uint8_t)body.m_ModuleCellId[i]);
    }
    temp += FormatOutput<uint8_t>("\n填充位", body.m_Padding3);


    this->m_parsedBody += temp;
}

void QianWeiParse::ParseCorrectorRechargeData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_CORRECTOR_RECHARGE_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());

    temp += this->FormatOutput<uint8_t>("计费种类", body.m_BillingType, false);
    switch (body.m_BillingType)
    {
    case 0x00:
        temp += QString("(金额计费)\n");
        break;
    case 0x01:
        temp += QString("(气量计费)\n");
        break;
    default:
        temp += QString("(未定义的类型)");
        break;
    }

//    temp += QString.sprintf("保留位\t：%02x%02x%02x\n", body.m_reserve[0], body.m_reserve[1], body.m_reserve[2]);
    temp += FormatOutput<uint32_t>("充值总购金额整数", body.m_RechargeTotalPurchaseAmountInt);
    temp += FormatOutput<uint32_t>("充值总购金额小数", body.m_RechargeTotalPurchaseAmountDec);
    temp += FormatOutput<uint32_t>("充值总购气量整数", body.m_RechargeTotalGasPurchaseInt);
    temp += FormatOutput<uint32_t>("充值总购气量小数", body.m_RechargeTotalGasPurchaseDec);

    this->m_parsedBody += temp;
}

void QianWeiParse::ParseCorrectorRechargeRspData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_CORRECTOR_RECHARGE_RSP_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());

    temp += this->FormatOutput<uint16_t>("响应码", body.m_ResponseCode);
    temp += this->FormatOutput<uint8_t>("计费种类", body.m_BillingType, false);
    switch (body.m_BillingType)
    {
    case 0x00:
        temp += QString("(金额计费)\n");
        break;
    case 0x01:
        temp += QString("(气量计费)\n");
        break;
    default:
        temp += QString("(未定义的类型)");
        break;
    }

//    temp += QString.sprintf("保留位\t：%02x%02x%02x\n", body.m_reserve[0], body.m_reserve[1], body.m_reserve[2]);
    temp += FormatOutput<uint32_t>("充值总购金额整数", body.m_RechargeTotalPurchaseAmountInt);
    temp += FormatOutput<uint32_t>("充值总购金额小数", body.m_RechargeTotalPurchaseAmountDec);
    temp += FormatOutput<uint32_t>("充值总购气量整数", body.m_RechargeTotalGasPurchaseInt);
    temp += FormatOutput<uint32_t>("充值总购气量小数", body.m_RechargeTotalGasPurchaseDec);

    this->m_parsedBody += temp;
}

void QianWeiParse::ParseSetReportCycleData()
{
    QString temp = 0;
    uint8_t *pArray = NULL;
    QIANWEI_PROTOCOL_SET_REPORT_PERIOD_DATA body;

    pArray = (uint8_t *)this->m_frameBody.data();
    memcpy((uint8_t *)&body, pArray, this->m_frameBody.size());


    temp += FormatOutput<uint8_t>("上报周期类型", body.ReportyType, false);
    switch(body.ReportyType)
    {
        case 0x01:
            temp += "(每N分钟上报(单条上报))\n";
        break;

        case 0x02:
            temp += "(每N小时上报(单条上报))\n";
        break;

        case 0x03:
            temp += "(每N天上报(单条上报))\n";
        break;

        case 0x04:
            temp += "(每N小时上报(打包上报))\n";
        break;

        case 0x05:
            temp += "(每N天上报(打包上报))\n";
        break;
    }

    temp += QString().sprintf("上报时间\t\t：%02d:%02d:%02d(只适用于每N天上报)\n", body.ReportTime[0], body.ReportTime[1], body.ReportTime[2]);
    temp += FormatOutput<uint16_t>("上报周期", body.CycleValue, false) +  QString().sprintf("(%hd)\n", body.CycleValue);
    temp += FormatOutput<uint16_t>("数据采集间隔", body.DataInvert);
    temp += FormatOutput<uint16_t>("保留位", body.reserve);

    this->m_parsedBody += temp;
}

uint16_t QianWeiParse::crc16ForModbus(const QByteArray &data)
{
    quint8 buf;
    quint16 crc16 = 0xFFFF;

    for ( auto i = 0; i < data.size(); ++i )
    {
        buf = data.at( i ) ^ crc16;
        crc16 >>= 8;
        crc16 ^= crc16Table[buf];
    }
    return  crc16;
}

void QianWeiParse::ComandTypePrint(const char *printMsg)
{
    this->m_parsedBody += QString().sprintf("---------------%s-----------------\n", printMsg);
}



