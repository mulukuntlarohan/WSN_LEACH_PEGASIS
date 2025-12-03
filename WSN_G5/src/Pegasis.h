#ifndef __PEGASIS_H_
#define __PEGASIS_H_

#include <omnetpp.h>
#include "inet/common/packet/Packet.h"
#include "inet/power/contract/IEpEnergyStorage.h"
#include "NetworkPacket_m.h"

using namespace omnetpp;

class Pegasis : public cSimpleModule {
  private:
    int selfId;
    int nextNodeId = -1;
    bool isLeader = false;
    double radioTx_mA;
    double radioRx_mA;

    inet::power::IEpEnergyStorage *energyStorage = nullptr;

    // Statistics
    simsignal_t packetReceivedSignal;
    simsignal_t endToEndDelaySignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    // Helper for MAC/Protocol Tagging
    void sendDown(inet::Packet *pkt);

    void buildChain();
    void consumeEnergy(double current_mA);
    double getResidualEnergy();

  public:
    virtual ~Pegasis() {}
};

#endif
