#ifndef _BLE_H_
#define _BLE_H_

#include <QObject>
#include <QList>
#include <QString>
#include <QByteArray>
#include <QJSValue>

#include <QBluetoothDeviceInfo>

class QBluetoothDeviceDiscoveryAgent;
class QLowEnergyService;
class QLowEnergyCharacteristic;

class ServiceIdentifier : public QObject
{
	Q_OBJECT
public:
	ServiceIdentifier(const QString & s, const QString & r, const QString & t, QObject *parent = nullptr)
		:QObject(parent), serviceUuid(s), rxUuid(r), txUuid(t), service(nullptr), isValid(false) {}
	QString serviceUuid;
	QString rxUuid;
	QString txUuid;
	QString deviceName;
	QString deviceAddress;

	QLowEnergyService * service;

	bool isValid;

public Q_SLOTS:
	void write(const QByteArray & data);

Q_SIGNALS:
	void onMessage(const QByteArray & data);

private Q_SLOTS:
	void characteristicChanged(const QLowEnergyCharacteristic & characteristic, const QByteArray & newValue);
};

class Ble : public QObject
{
	Q_OBJECT
	Q_PROPERTY(bool scan READ scanning WRITE startScan NOTIFY scanningChanged)
	Q_PROPERTY(QList<QObject*> devices READ devices NOTIFY devicesChanged)
public:

	Ble(QObject* parent = nullptr);

	QList<QObject*> devices();
	QList<QObject*> devices(const QString & serviceUuid);
	QObject* device(const QString & address);

public Q_SLOTS:

	void addService(const QString & serviceUuid, const QString & rxUuid, const QString & txUuid);

	void startScan(bool scan);

	bool scanning();

Q_SIGNALS:
	void scanningChanged();
	void devicesChanged();

private Q_SLOTS:

	void deviceDiscovered(const QBluetoothDeviceInfo & device);

private:
	QList<ServiceIdentifier*> services;
	QBluetoothDeviceDiscoveryAgent* mDeviceDiscoveryAgent;
};


#endif
