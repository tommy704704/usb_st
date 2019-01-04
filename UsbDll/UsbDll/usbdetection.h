/*!
* @file usbdetection.h
* @date 2017/12/14 20:06
*
* @author 宋涛
* Contact:
*
* @brief
*	MIDI设备热插拔消息通知上层应用
* TODO: long description
*
* @note
首先GetInstance()获取usbDetection实例，然后接受插入和拔出设备信号就可以接受操作的设备名
*/
#ifndef USBDETECTION_H
#define USBDETECTION_H

#include <QtWidgets/QWidget>
#include <winuser.rh>
#include <afxwin.h>
#include <minwinbase.h>
#include <QtDebug>
#include <dbt.h>
#include <Setupapi.h>
#include <devpropdef.h>
#include <QTimer>
#ifdef USBDETECTION_LIB
# define USBDETECTION_EXPORT Q_DECL_EXPORT
#else
# define USBDETECTION_EXPORT Q_DECL_IMPORT
#endif
class USBDETECTION_EXPORT usbDetection : public QWidget
{
	Q_OBJECT

public:
	static usbDetection * GetInstance();

signals:
	/************************************
	* @Method:    signal_InsertDevice
	* @FullName:  usbDetection::signal_InsertDevice
	* @Access:    public 
	* @Returns:   void
	* @Qualifier:
	* @Parameter: const QString _device_name			插入midi设备的名称
	* @comment: midi设备插入信号
	************************************/
	void signal_InsertDevice(const QString _device_name);	///<插入设备信号
	/************************************
	* @Method:    signal_RemoveDevice
	* @FullName:  usbDetection::signal_RemoveDevice
	* @Access:    public 
	* @Returns:   void
	* @Qualifier:
	* @Parameter: const QString _device_name			拔出midi设备的名称
	* @comment: midi设备拔出信号
	************************************/
	void signal_RemoveDevice(const QString _device_name);	///<拔出设备信号
	private slots:
	void Slot_Usb_timeOut();
protected:
	bool nativeEvent(const QByteArray & eventType, void * message, long * result);
private:
	usbDetection(QWidget *parent = 0);
	~usbDetection();

	QString GetRegeditMidiDeviceChanged();
	QString GetWhichMidiDeviceChanged(QVector<QString> _vector_midiDevice);
private:
	static usbDetection *instance_;
	QVector<QString> vector_midiDevice_;
	QVector<QString> vector_midiDevice_cache_;
	QTimer *timer_;
	QString name_;
};

#endif // USBDETECTION_H
