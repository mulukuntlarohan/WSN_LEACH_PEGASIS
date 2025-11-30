#ifndef __LEACH_H_
#define __LEACH_H_

#include <omnetpp.h>
#include <vector>
#include "inet/common/packet/Packet.h"
#include "inet/power/contract/IEpEnergyStorage.h"
#include "NetworkPacket_m.h"

using namespace omnetpp;

class Leach : public cSimpleModule {
  private:
    double p_desired;
    double roundDuration;
    int selfId;
    double radioTx_mA;
    double radioRx_mA;
    int currentRound = 0;
    bool isClusterHead = false;
    int myClusterHeadId = -1;
    cMessage *roundTimer = nullptr;
    inet::power::IEpEnergyStorage *energyStorage = nullptr;
    simsignal_t packetReceivedSignal;
    simsignal_t endToEndDelaySignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    // Helper for MAC Tagging
    void sendDown(inet::Packet *pkt);

    void startNewRound();
    bool checkThreshold();
    void advertiseCH();
    void sendJoinRequest(int targetChId);
    void processPacket(inet::Packet *pkt);
    void consumeEnergy(double current_mA);
    double getResidualEnergy();

  public:
    virtual ~Leach();
};

#endif
