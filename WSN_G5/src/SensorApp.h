#ifndef __SENSORAPP_H_
#define __SENSORAPP_H_

#include <omnetpp.h>
#include "inet/common/packet/Packet.h"

using namespace omnetpp;

class SensorApp : public cSimpleModule {
  protected:
    simtime_t packetInterval;
    int payloadBytes;
    cMessage *timerMsg = nullptr;

    // Signals for Statistics
    simsignal_t packetSentSignal;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void generateTraffic();
    void setupClusteredTopology();

  public:
    virtual ~SensorApp();
};

#endif
