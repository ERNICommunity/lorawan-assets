 /*
  * Assets.h
  *
  *  Created on: 25.08.2018
  *      Author: kath
  */

#include<string.h>
//#include "Adafruit_FRAM_I2C.h" // PIO Lib: 658 -> https://platformio.org/lib/show/658/Adafruit%20FRAM%20I2C
#include <IAssetsDeviceSerialNrAdapter.h>
#include <IPersistentDataMemory.h>
#include <DbgCliTopic.h>
#include <DbgTracePort.h>
#include <DbgTraceLevel.h>
#include <AssetsDbgCmd.h>
#include <Assets.h>

Assets::Assets(IAssetsDeviceSerialNrAdapter* deviceSerialNrAdapter /*= 0*/, IPersistentDataMemory* persistentDataMemory /*= 0*/)
: m_trPort(new DbgTrace_Port("assets", DbgTrace_Level::info))
, m_dbgCliTopicAssets(new DbgCli_Topic(DbgCli_Node::RootNode(), "assets", "Assets."))
, m_dbgCliTopicAssetsDeviceSerial(new DbgCli_Topic(m_dbgCliTopicAssets, "dvcser", "Device Serial Number."))
, m_dbgCliTopicAssetsLoRaKeys(new DbgCli_Topic(m_dbgCliTopicAssets, "lorakeys", "LoRa Keys."))
, m_dbgCliSetDeviceSerialCmd(new AssetsDbgCmd_SetDeviceSerial(this))
, m_dbgCliGetDeviceSerialCmd(new AssetsDbgCmd_GetDeviceSerial(this))
, m_dbgCliGetLoRaKeysCmd(new AssetsDbgCmd_GetLoRaKeys(this))
, m_deviceSerialNr(0)
, m_deviceSerialNrAdapter(0)
, m_persistentDataMemory(0)
{
  setDeviceSerialNrAdapter(deviceSerialNrAdapter);
  setPersistentDataMemory(persistentDataMemory);
}

Assets::~Assets()
{ }

void Assets::setDeviceSerialNrAdapter(IAssetsDeviceSerialNrAdapter* deviceSerialNrAdapter)
{
  m_deviceSerialNrAdapter = deviceSerialNrAdapter;
  if (0 != m_deviceSerialNrAdapter)
  {
    m_deviceSerialNr = m_deviceSerialNrAdapter->getDeviceSerialNr();
  }
  else
  {
    TR_PRINTF(m_trPort, DbgTrace_Level::error, "ERROR IN Assets: no deviceSerialNrAdapter set! Assume deviceSerialNr = 0");
    m_deviceSerialNr = 0;
  }
  TR_PRINTF(m_trPort, DbgTrace_Level::info, "Assets: deviceSerialNr = %u", m_deviceSerialNr);
}

IAssetsDeviceSerialNrAdapter* Assets::getDeviceSerialNrAdapter()
{
  return m_deviceSerialNrAdapter;
}

void Assets::setPersistentDataMemory(IPersistentDataMemory* persistentDataMemory)
{
  m_persistentDataMemory = persistentDataMemory;
}

IPersistentDataMemory* Assets::getPersistentDataMemory()
{
  return m_persistentDataMemory;
}

DbgTrace_Port* Assets::trPort()
{
  return m_trPort;
}


unsigned long int Assets::getDeviceSerialNr()
{
  return m_deviceSerialNr;
}

void Assets::setDeviceSerialNr(unsigned long int deviceSerialNr)
{
  m_deviceSerialNr = deviceSerialNr;
  if (0 != m_persistentDataMemory)
  {
    m_persistentDataMemory->setDeviceSerialNr(m_deviceSerialNr);
  }
}

unsigned int Assets::getDeviceId( char* deviceId, unsigned int len)
{
  unsigned int count = 0;
  const unsigned int addr = IPersistentDataMemory::KT_devId * IPersistentDataMemory::s_numMaxChars;
  while ((0 != m_persistentDataMemory) && (count < len) && (count < IPersistentDataMemory::s_numMaxChars))
  {
    deviceId[count] = m_persistentDataMemory->read(addr + count);
    count++;
  }
  deviceId[count] = '\0';
  return count;
}

unsigned int Assets::getDevAddr(char* devAddr,  unsigned int len)
{
  unsigned int count = 0;
  const unsigned int addr = IPersistentDataMemory::KT_devAddr * IPersistentDataMemory::s_numMaxChars;
  while ((0 != m_persistentDataMemory) && (count < len) && (count < IPersistentDataMemory::s_numMaxChars))
  {
    devAddr[count] = m_persistentDataMemory->read(addr + count);
    count++;
  }
  devAddr[count] = '\0';
  return count;
}

unsigned int Assets::getNwkSKey(char* nwkSKey,  unsigned int len)
{
  unsigned int count = 0;
  const unsigned int addr = IPersistentDataMemory::KT_nwkSKey * IPersistentDataMemory::s_numMaxChars;
  while ((0 != m_persistentDataMemory) && (count < len) && (count < IPersistentDataMemory::s_numMaxChars))
  {
    nwkSKey[count] = m_persistentDataMemory->read(addr + count);
    count++;
  }
  nwkSKey[count] = '\0';
  return count;
}

unsigned int Assets::getAppSKey(char* appSKey,  unsigned int len)
{
  unsigned int count = 0;
  const unsigned int addr = IPersistentDataMemory::KT_appSKey * IPersistentDataMemory::s_numMaxChars;
  while ((0 != m_persistentDataMemory) && (count < len) && (count < IPersistentDataMemory::s_numMaxChars))
  {
    appSKey[count] = m_persistentDataMemory->read(addr + count);
    count++;
  }
  appSKey[count] = '\0';
  return count;
}
