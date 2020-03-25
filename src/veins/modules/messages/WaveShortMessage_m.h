//
// Generated file, do not edit! Created by nedtool 5.1 from veins/modules/messages/WaveShortMessage.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __WAVESHORTMESSAGE_M_H
#define __WAVESHORTMESSAGE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "veins/base/utils/Coord.h"
// }}

/**
 * Class generated from <tt>veins/modules/messages/WaveShortMessage.msg:26</tt> by nedtool.
 * <pre>
 * packet WaveShortMessage
 * {
 *     //Version of the Wave Short Message
 *     int wsmVersion = 0;
 *     //Determine which security mechanism was used
 *     int securityType = 0;
 *     //Channel Number on which this packet was sent
 *     int channelNumber;
 *     //Data rate with which this packet was sent
 *     int dataRate = 1;
 *     //User priority with which this packet was sent (note the AC mapping rules in Mac1609_4::mapUserPriority)
 *     int userPriority = 7;
 *     //Unique number to identify the service
 *     int psid = 0;
 *     //Provider Service Context
 *     string psc = "Service with some Data";
 *     //Length of Wave Short Message
 *     int wsmLength;
 *     //Data of Wave Short Message
 *     string wsmData = "Some Data";
 *     //Emergency message
 *     int em = 0;
 * 
 *     int senderAddress = 0;
 *     int recipientAddress = -1;
 *     int serial = 0;
 *     simtime_t timestamp = 0;
 * 
 *     Coord senderPos;
 *     Coord senderSpeed;
 * 
 *     double angleRad = -1;
 *     int priorityList[]; // Orden calculado por el nodo fuente para TrAD
 *     int Oirigin_ID = -1;
 *     Coord Origin_pos;
 *     int ID = -1;
 *     double cw; // contention window for DSP
 *     int Parts; // Partitions for DSP
 *     double PartitionArray[]; //Partition Disntance for DPS
 * }
 * </pre>
 */
class WaveShortMessage : public ::omnetpp::cPacket
{
  protected:
    int wsmVersion;
    int securityType;
    int channelNumber;
    int dataRate;
    int userPriority;
    int psid;
    ::omnetpp::opp_string psc;
    int wsmLength;
    ::omnetpp::opp_string wsmData;
    int em;
    int senderAddress;
    int recipientAddress;
    int serial;
    ::omnetpp::simtime_t timestamp;
    Coord senderPos;
    Coord senderSpeed;
    double angleRad;
    int *priorityList; // array ptr
    unsigned int priorityList_arraysize;
    int Oirigin_ID;
    Coord Origin_pos;
    int ID;
    double cw;
    int Parts;
    double *PartitionArray; // array ptr
    unsigned int PartitionArray_arraysize;

  private:
    void copy(const WaveShortMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const WaveShortMessage&);

  public:
    WaveShortMessage(const char *name=nullptr, short kind=0);
    WaveShortMessage(const WaveShortMessage& other);
    virtual ~WaveShortMessage();
    WaveShortMessage& operator=(const WaveShortMessage& other);
    virtual WaveShortMessage *dup() const override {return new WaveShortMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getWsmVersion() const;
    virtual void setWsmVersion(int wsmVersion);
    virtual int getSecurityType() const;
    virtual void setSecurityType(int securityType);
    virtual int getChannelNumber() const;
    virtual void setChannelNumber(int channelNumber);
    virtual int getDataRate() const;
    virtual void setDataRate(int dataRate);
    virtual int getUserPriority() const;
    virtual void setUserPriority(int userPriority);
    virtual int getPsid() const;
    virtual void setPsid(int psid);
    virtual const char * getPsc() const;
    virtual void setPsc(const char * psc);
    virtual int getWsmLength() const;
    virtual void setWsmLength(int wsmLength);
    virtual const char * getWsmData() const;
    virtual void setWsmData(const char * wsmData);
    virtual int getEm() const;
    virtual void setEm(int em);
    virtual int getSenderAddress() const;
    virtual void setSenderAddress(int senderAddress);
    virtual int getRecipientAddress() const;
    virtual void setRecipientAddress(int recipientAddress);
    virtual int getSerial() const;
    virtual void setSerial(int serial);
    virtual ::omnetpp::simtime_t getTimestamp() const;
    virtual void setTimestamp(::omnetpp::simtime_t timestamp);
    virtual Coord& getSenderPos();
    virtual const Coord& getSenderPos() const {return const_cast<WaveShortMessage*>(this)->getSenderPos();}
    virtual void setSenderPos(const Coord& senderPos);
    virtual Coord& getSenderSpeed();
    virtual const Coord& getSenderSpeed() const {return const_cast<WaveShortMessage*>(this)->getSenderSpeed();}
    virtual void setSenderSpeed(const Coord& senderSpeed);
    virtual double getAngleRad() const;
    virtual void setAngleRad(double angleRad);
    virtual void setPriorityListArraySize(unsigned int size);
    virtual unsigned int getPriorityListArraySize() const;
    virtual int getPriorityList(unsigned int k) const;
    virtual void setPriorityList(unsigned int k, int priorityList);
    virtual int getOirigin_ID() const;
    virtual void setOirigin_ID(int Oirigin_ID);
    virtual Coord& getOrigin_pos();
    virtual const Coord& getOrigin_pos() const {return const_cast<WaveShortMessage*>(this)->getOrigin_pos();}
    virtual void setOrigin_pos(const Coord& Origin_pos);
    virtual int getID() const;
    virtual void setID(int ID);
    virtual double getCw() const;
    virtual void setCw(double cw);
    virtual int getParts() const;
    virtual void setParts(int Parts);
    virtual void setPartitionArrayArraySize(unsigned int size);
    virtual unsigned int getPartitionArrayArraySize() const;
    virtual double getPartitionArray(unsigned int k) const;
    virtual void setPartitionArray(unsigned int k, double PartitionArray);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const WaveShortMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, WaveShortMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef __WAVESHORTMESSAGE_M_H

