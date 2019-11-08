/*
 * IPersistentDataMemory.h
 *
 *  Created on: 23.01.2014
 *      Author: niklausd
 */

#ifndef IPERSISTENDATAMEMORY_H_
#define IPERSISTENDATAMEMORY_H_

class IPersistentDataMemory
{
public:
  typedef enum
  {
    KT_devId   = 0,
    KT_devAddr = 1,
    KT_nwkSKey = 2,
    KT_appSKey = 3,
    KT_NumKeys
  } KeyType;

  static const unsigned int s_numMaxChars = 32;

protected:
  /**
   * Constructor, protected since this is an Interface.
   */
  IPersistentDataMemory() { };
public:
  virtual ~IPersistentDataMemory() { };
  virtual void write(unsigned int address, unsigned char data) = 0;
  virtual char read(unsigned int address) = 0;
  virtual void setDeviceSerialNr(unsigned long int deviceSerialNr) { }

private: // forbidden default functions
  IPersistentDataMemory& operator = (const IPersistentDataMemory& );  // assignment operator
  IPersistentDataMemory(const IPersistentDataMemory& src);            // copy constructor
};

#endif /* IPERSISTENDATAMEMORY_H_ */
