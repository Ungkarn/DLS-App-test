//---------------------------------------------------------------------------

#ifndef DeviceH
#define DeviceH
#include "ftd2xx_utils.h"
#include <windef.h>
//---------------------------------------------------------------------------

#define BLOCK_DATA_NUM 1024    //���������� ������ � �����
#define DATA_MIN_RATE 1500     //����������� ������� ������ ������ (������/���)

union Status    //��������� �������
{
	BYTE byte;
	struct
	{
	  unsigned data : 1;			  //���������� ����� ������ (0 - ������ �� ������)
	  unsigned prism : 1;
//      unsigned signal : 1;          //������� ������� ������������� (1 - � ������� 15� ������ �� ������)
	  unsigned goniometer : 1;      //��������� ������� ���������� (0 - ���� ���������)
	  unsigned polar : 1;
	  unsigned aperture : 1;
//	  unsigned photomultiplier : 1; //��������� ��� (0 - ��� ��������)
	  unsigned feed : 1;            //������� ������������� (0 - ������� ���������)
	  unsigned dummy : 2;
	} bits;
};

struct DeviceSettings
{
	WORD Amplification;
	WORD MinAmplification;
	WORD MaxAmplification;
	WORD deltaAmplification;

	double Temperature;
	double MinTemperature;
	double MaxTemperature;
	double deltaTemperature;

	double Angle;
	double MinAngle;
	double MaxAngle;
	double deltaAngle;

	BYTE Frequency;
	DeviceSettings();

	int ReadDataBlock;
	int MinReadDataBlock;
	int MaxReadDataBlock;
	int deltaReadDataBlock;
};

class Device
{
	public:
	  FTD2XX_Device ftd2xxDevice;
	  DeviceSettings deviceSettings;
	  bool Reset();  //�����
	  bool GetStatus(Status& value); //���������
	  bool Start(); //������ ����� ����� ������ �������������
	  WORD* GetData(DWORD& dwReadBlockNumData); //������ ����� ������
	  bool GetData(int dwReadBlockNumData, WORD *Data);
	  bool SetLength(BYTE value); //��������� ����� ����� ������, ������������ ������ � GetData
	  bool SetTemperature(double value);  //��������� ����������� ���������� (277.8� - 327.8�)
	  bool GetTemperature(double& value); //������ ����������� ���������� (277.8� - 327.8�)
	  bool SetPhotomultiplierAndPolarity(double value); //��������������� ���������� ��� (0-1250�) � ������������(0-416�)
	  bool PolarityInvert(); //���������� ������������ �������� �� ���������������
	  bool SetAngle(double value); //������� ���� �������� ����������
	  bool SetPhotomultiplierState(bool value); //����� �������������(true - �������� �������)
	  bool SetFrequency(int index);
	  bool WriteData(char index, int value);
	  bool ReadData(char index, int& value);
	  bool SetPolar(char value);
	  bool SetAperture(char value);
	  bool SetPrism(bool value);
	  bool PhotoOn(bool value);
	  bool SetAngle(char value);
	  bool GetIntensity(int& value);


};


#endif
