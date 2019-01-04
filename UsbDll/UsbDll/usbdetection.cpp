#include "usbdetection.h"
#include <devpkey.h>
#include <winioctl.h>
#include <mmeapi.h>


usbDetection::usbDetection(QWidget *parent)
	: QWidget(parent)
{
	GetRegeditMidiDeviceChanged();	///<初始化缓存，加入已插入MIDI输入设备
	timer_ = new QTimer();
	connect(timer_, SIGNAL(timeout()), this, SLOT(Slot_Usb_timeOut()));
#if 1
	static const GUID GUID_DEVINTERFACE_LIST[] =
	{
		// GUID_DEVINTERFACE_USB_DEVICE
		{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
		// GUID_DEVINTERFACE_DISK
		{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
		// GUID_DEVINTERFACE_HID,
		{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
		// GUID_NDIS_LAN_CLASS
		{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } },
		// GUID_DEVINTERFACE_COMPORT
		{ 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
		// GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
		{ 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },
		// GUID_DEVINTERFACE_PARALLEL
		{ 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },
		// GUID_DEVINTERFACE_PARCLASS
		{ 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
// 		//DEFINE_GUID(MediumChangerClassGuid
// 		{ 0x53f56310L, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } }
	};

	//注册插拔事件
	HDEVNOTIFY hDevNotify;
	DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
	ZeroMemory(&NotifacationFiler, sizeof(DEV_BROADCAST_DEVICEINTERFACE));
	NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

	for (int i = 0; i < sizeof(GUID_DEVINTERFACE_LIST) / sizeof(GUID); i++)
	{
		NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];//GetCurrentUSBGUID();//m_usb->GetDriverGUID();

		hDevNotify = RegisterDeviceNotification((HANDLE)this->winId(), &NotifacationFiler, DEVICE_NOTIFY_WINDOW_HANDLE);
		if (!hDevNotify)
		{
			int Err = GetLastError();
			qDebug() << "注册失败" << endl;
		}
		//else
	}
#endif
}

usbDetection::~usbDetection()
{

}
usbDetection* usbDetection::instance_ = NULL;
usbDetection * usbDetection::GetInstance()
{
	if (NULL == instance_)
	{
		return instance_ = new usbDetection();
	}
	return instance_;
}
bool usbDetection::nativeEvent(const QByteArray & eventType, void * message, long*result)
{
// 	qDebug() << "enter nativeEvent";
// 	typedef struct tagMSG {
// 		HWND        hwnd;
// 		UINT        message;
// 		WPARAM      wParam;
// 		LPARAM      lParam;
// 		DWORD       time;
// 		POINT       pt;
// 	} MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;

	MSG* msg = reinterpret_cast<MSG*>(message);
	int msgType = msg->message;
	if (msgType == WM_DEVICECHANGE)
	{
// 		qDebug() << "enter WM_DEVICECHANGE";

		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
		switch (msg->wParam) {
		case DBT_DEVICEARRIVAL:
			qDebug() << "enter DBT_DEVICEARRIVAL";

			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
			{
// 				qDebug() << "enter DBT_DEVTYP_VOLUME";

				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				if (lpdbv->dbcv_flags == 0)
				{
					//插入u盘
				}
			}
			if (lpdb->dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE)
			{
// 				qDebug() << "enter DBT_DEVTYP_DEVICEINTERFACE";

// 				typedef struct _DEV_BROADCAST_DEVICEINTERFACE_W {
// 					DWORD       dbcc_size;
// 					DWORD       dbcc_devicetype;
// 					DWORD       dbcc_reserved;
// 					GUID        dbcc_classguid;
// 					wchar_t     dbcc_name[1];
// 				} DEV_BROADCAST_DEVICEINTERFACE_W, *PDEV_BROADCAST_DEVICEINTERFACE_W;
// 				QString result_name = GetRegeditMidiDeviceChanged();
// 				if (result_name != "")
// 				{
// 					emit signal_InsertDevice(result_name);
// 				}
				timer_->start(2000);
// 				if (name_ != "")
// 				{
// 					emit signal_InsertDevice(name_);
// 				}
			}
			break;
		case DBT_DEVICEREMOVECOMPLETE:
// 			qDebug() << "enter DBT_DEVICEREMOVECOMPLETE";
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
			{
// 				struct _DEV_BROADCAST_VOLUME { /* */
// 					DWORD       dbcv_size;
// 					DWORD       dbcv_devicetype;
// 					DWORD       dbcv_reserved;
// 					DWORD       dbcv_unitmask;
// 					WORD        dbcv_flags;
// 				};
			}
			if (lpdb->dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE)
			{
// 				qDebug() << "enter DBT_DEVTYP_DEVICEINTERFACE";

// 				QString result_name = GetRegeditMidiDeviceChanged();
// 				if (result_name != "")
// 				{
// 					emit signal_RemoveDevice(result_name);
// 				}
				timer_->start(2000);
// 				if (name_ != "")
// 				{
// 					emit signal_RemoveDevice(name_);
// 				}
			}
			break;
		}
	}
// 	qDebug() << "quit nativeEvent";
	return false;
}
void usbDetection::Slot_Usb_timeOut()
{
	name_ = GetRegeditMidiDeviceChanged();
	timer_->stop();
}
QString usbDetection::GetRegeditMidiDeviceChanged()
{
	qDebug() << "enter GetRegeditMidiDeviceChanged";

	QString result_name = "";
	HKEY hKey;
	DWORD dwType = REG_DWORD;
	DWORD dwSize = MAX_PATH;
	// 	wchar_t data[MAX_PATH];
	DWORD data = 0;
	LONG result = RegOpenKey(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\services\\usbaudio\\Enum", &hKey);
	result = RegQueryValueEx(hKey, L"Count",
		NULL,
		&dwType,
		(LPBYTE)&data,
		&dwSize);
	int count_int = data;	///<插入设备数
	QVector<QString> vector_midiDevice_cache;
	for (int i = 0; i < count_int; i++)
	{
		HKEY hKey_device;
		DWORD dwType_device = REG_SZ;
		DWORD dwSize = MAX_PATH;
		wchar_t data_device[MAX_PATH];
		LONG result = RegOpenKey(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\services\\usbaudio\\Enum", &hKey_device);
		wchar_t i_convert[10];
		_itow_s(i, i_convert, 10, 10);
		result = RegQueryValueEx(hKey_device, i_convert,
			NULL,
			&dwType_device,
			(LPBYTE)data_device,
			&dwSize);
		QString device_name = QString::fromWCharArray(data_device);
		QString target_path = QString("%1%2").arg("SYSTEM\\CurrentControlSet\\Enum\\").arg(device_name);
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		HKEY hKey_target;
		DWORD dwType = REG_SZ;
		DWORD dwSize_value = MAX_PATH;
		wchar_t data[MAX_PATH];
		LONG result_value = RegOpenKey(HKEY_LOCAL_MACHINE, target_path.toStdWString().c_str(), &hKey_target);
		result_value = RegQueryValueEx(hKey_target, L"FriendlyName",
			NULL,
			&dwType,
			(LPBYTE)data,
			&dwSize_value);
		QString target_device_name = QString::fromWCharArray(data);
		vector_midiDevice_cache.append(target_device_name);	///<添加到缓存
	}

	result_name = GetWhichMidiDeviceChanged(vector_midiDevice_cache);
	return result_name;
}
QString usbDetection::GetWhichMidiDeviceChanged(QVector<QString> _vector_midiDevice)
{
	qDebug() << "enter GetWhichMidiDeviceChanged";

	QString result = "";
	int count_now = _vector_midiDevice.count();
	int count_previous = vector_midiDevice_cache_.count();
	qDebug() << "count_now====" << count_now;
	qDebug() << "count_previous====" << count_previous;
	if (count_previous <= 0 && count_now > 0)
	{
		vector_midiDevice_cache_ = _vector_midiDevice;		///<第一次插入midi设备返回该名称
		result = vector_midiDevice_cache_[0];
		if (result != "")
		{
			emit signal_InsertDevice(result);
		}
	}
	else
	{
		if (count_now >= count_previous)
		{
			for (int i = 0; i < count_now; i++)
			{
				QString name = _vector_midiDevice[i];
				bool is_contain = vector_midiDevice_cache_.contains(name);
				if (!is_contain)
				{
					result = name;	///<此项为插入设备
					qDebug() << "insert device=====" << result;
					if (result != "")
					{
						emit signal_InsertDevice(result);
					}
				}
			}
		}
		else if (count_now < count_previous)
		{
			for (int i = 0; i < count_previous; i++)
			{
				QString name = vector_midiDevice_cache_[i];
				bool is_contain = _vector_midiDevice.contains(name);
				if (!is_contain)
				{
					result = name;	///<此项为拔出设备
					qDebug() << "remove device=====" << result;
					if (result != "")
					{
						emit signal_RemoveDevice(result);
					}
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	vector_midiDevice_cache_ = _vector_midiDevice;		///<匹配完之后再更新缓存
	qDebug() << "quit GetWhichMidiDeviceChanged";
	qDebug() << "return result====" << result;

	return result;
}
