/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file     battery.h
  * @author   ZMtangyuan
  * @version  v1.0
  * @brief    BMS Battery information reader for the UNNC Formular 
  *           Student 
  * 
  ******************************************************************************
  * @attention
  *
  * There is nothing here now :)
  *
  ******************************************************************************
  */

#ifndef BCU_HCU_INFO
#define BCU_HCU_INFO
struct BCU_HCU_INFO{
	uint8_t BatVoltage_MSB;
	uint8_t BatVoltage_LSB;
	uint16_t BatVoltage; //动力电池总电压
	uint8_t BatCurrent_MSB;
	uint8_t BatCurrent_LSB;
	uint16_t BatCurrent; //动力电池总电流
	uint8_t BatSoc; //动力电池SOC
	uint8_t BatSoh; //动力电池COH
	uint8_t BatState; /*动力电池状态
						1:Sleep (休眠)
						2:Power Up (自检状态)
						3:Standby (待机状态)
						4:Pre-charge (预充状态)
						5:Run (正常运行状态)
						6:Shutdown (关机状态)
						7:Error (故障状态)*/
	uint8_t BatAlmLv; /*0:无告警
						1:一级告警 (最严重)
						2:二级告警
						3:三级告警
						4:四级告警*/
	uint8_t BatLife; //通信生命信息 循环递增 (0 - 255)
};
#endif
#ifndef BMS_HCU_MAXV
#define BMS_HCU_MAXV
struct BMS_HCU_MAXV{
	uint8_t MaxCellVolt_MSB;
	uint8_t MaxCellVolt_LSB;
	uint16_t MaxCellVolt; //最高单体电压
	uint8_t MinCellVolt_MSB;
	uint8_t MinCellVolt_LSB;
	uint16_t MinCellVolt; //最低单体电压
	uint8_t MaxCellVoltNo; //最高单体电压序号
	uint8_t MinCellVoltNo; //最低单体电压序号
};
#endif
#ifndef BMS_HCU_MAXT
#define BMS_HCU_MAXT
struct BMS_HCU_MAXT{
	uint8_t MaxTemp; //最高温度
	uint8_t MinTemp; //最低温度
	uint8_t MaxTempNo; //最高温度序号
	uint8_t MinTempNo; //最低温度序号
	uint8_t CoolingCtl; //冷却控制, 0 停止, 1 启动
	uint8_t HeatingCtl; //发热控制, 0 停止, 1 启动
};
#endif
#ifndef BMS_HCU_RELAY
#define BMS_HCU_RELAY
struct BMS_HCU_RELAY{
	uint8_t PosRlyStr; /*	总正继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t NegRlyStr; /*	总负继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t PreRlyStr; /*	预充继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t OnChrRlyStr; /*	车载充电（慢充）继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t OffChrRlyStr; /*非车载充电（快充）继电器状态
							0:Open
							1:Close
							2:Error */
	uint8_t ChrState; /*	充电状态
							0:停止充电
							1:进入充电
							2:恒流充电
							3:涓充充电
							4:充电完成 */
	uint8_t ChrCommunication; /*	充电机是否在线
									0：通信超时
									1：在线 */
	uint8_t ChrOFFCC2; /*	非车载充电机连接确认
							0：未连接
							1：已连接 */
	uint8_t ChrONCC; /*	车载充电机连接确认
						0: 未连接
						1: 220Ω
						2: 680Ω
						3: 未知 */
	uint8_t ChrReqVolt_MSB; //
	uint8_t ChrReqVolt_LSB; //
	uint16_t ChrReqVolt; //	充电请求电压
	uint8_t ChrReqCurr_MSB;
	uint8_t ChrReqCurr_LSB;
	uint16_t ChrReqCurr; // 充电请求电流
};
#endif
#ifndef BMS_HCU_POWER
#define BMS_HCU_POWER
struct BMS_HCU_POWER{
	uint8_t MaxChrCurtLimit_MSB;
	uint8_t MaxChrCurtLimit_LSB;
	uint16_t MaxChrCurtLimit; //当前最大允许充电电流
	uint8_t MaxDisCurtLimit_MSB;
	uint8_t MaxDisCurtLimit_LSB;
	uint16_t MaxDisCurtLimit; //当前最大允许放电电流
	uint8_t MaxChrPowerLimit_MSB;
	uint8_t MaxChrPowerLimit_LSB;
	uint16_t MaxChrPowerLimit; //当前最大允许充电功率
	uint8_t MaxDisPowerLimit_MSB;
	uint8_t MaxDisPowerLimit_LSB;
	uint16_t MaxDisPowerLimit; //当前最大允许放电功率
};
#endif
#ifndef BMS_HCU_ALARM
#define BMS_HCU_ALARM
struct BMS_HCU_ALARM{
	uint8_t ALM_CELL_OV; /*	单体过压
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_UV; /*	单体欠压
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_OT; /*	电池高温
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_UT; /*	电池低温
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_CELL_LBK; /*单体电压断线
							0:无告警
							1:1级告警 */
	uint8_t ALM_CELL_TBK; /*单体温度断线
							0:无告警
							1:1级告警 */
	uint8_t ALM_BATT_DV; /*	单体压差过大
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_BATT_DT; /*	电池温差过大
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_BATT_OV; //	整组过压
	uint8_t ALM_BATT_UV; //	整组欠压
	uint8_t ALM_BATT_OC; //	电池组SOC过高
	uint8_t ALM_BATT_UC; //	电池组SOC过低
	uint8_t ALM_CHRG_OCS; //稳态充电过流
	uint8_t ALM_DSCH_OCS; //稳态放电过流
	uint8_t ALM_CHRG_OCT; //瞬态充电过流
	uint8_t ALM_DSCH_OCT; //瞬态放电过流
	uint8_t ALM_BSU_OFFLINE; //	BSU离线
	uint8_t ALM_BSU_FAULT; /*	BSU均衡故障
								0:无告警
								1:1级告警 */
	uint8_t ALM_LEAK_OC; /*	漏电流超限
							0:无告警
							1:1级告警（最严重）
							2:2级告警
							3:3级告警
							4:4级告警 */
	uint8_t ALM_PRECHRG_FAIL; /*预充失败
								0:无告警
								1:1级告警 */
	uint8_t ALM_AUX_FAIL; /*	继电器故障
								0:无告警
								1:1级告警 */
	uint8_t ALM_BMU_FAIL; /*	BMU故障
								0:无告警
								1:1级告警 */
	uint8_t ALM_VCU_OFFLINE; /*	HCU通信超时
								0:无告警
								1:1级告警（最严重）
								2:2级告警
								3:3级告警
								4:4级告警 */
	uint8_t ALM_HVREL_FAIL; /*	电池高压异常
								0:无告警
								1:1级告警 */
	uint8_t ALM_HALL_BREAK;/*	霍尔断线
								0:无告警
								1:1级告警 */
};
#endif