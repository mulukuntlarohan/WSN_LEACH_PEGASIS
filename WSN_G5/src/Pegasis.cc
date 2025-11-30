#include "Pegasis.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/Protocol.h"

Define_Module(Pegasis);

void Pegasis::initialize() {
    selfId = getParentModule()->getId();

    if (getParentModule()->hasPar("radioTx_mA"))
        radioTx_mA = getParentModule()->par("radioTx_mA").doubleValue();
    else
        radioTx_mA = 0.0;

    if (getParentModule()->hasPar("radioRx_mA"))
        radioRx_mA = getParentModule()->par("radioRx_mA").doubleValue();
    else
        radioRx_mA = 0.0;

    energyStorage = check_and_cast<inet::power::IEpEnergyStorage*>(getParentModule()->getSubmodule("energyStorage"));
    packetReceivedSignal = registerSignal("packetReceived");
    endToEndDelaySignal = registerSignal("endToEndDelay");

    scheduleAt(simTime() + 1.0, new cMessage("buildChain"));
}

// --- HELPER FUNCTION ---
void Pegasis::sendDown(inet::Packet *pkt) {
    // 1. MAC Address Tag (Broadcast)
    auto macReq = pkt->addTagIfAbsent<inet::MacAddressReq>();
    macReq->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);

    // 2. Protocol Tag (FIX: Use IPv4 so the 802.15.4 MAC accepts it)
    auto protocolReq = pkt->addTagIfAbsent<inet::PacketProtocolTag>();
    protocolReq->setProtocol(&inet::Protocol::ipv4);

    send(pkt, "radioOut");
}
// ----------------------

void Pegasis::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage() && strcmp(msg->getName(), "buildChain") == 0) {
        buildChain();
        delete msg;
    }
    else if (msg->arrivedOn("appIn")) {
        inet::Packet *pkt = check_and_cast<inet::Packet*>(msg);
        consumeEnergy(radioTx_mA);
        if (isLeader || nextNodeId != -1) {
            sendDown(pkt);
        } else {
            delete pkt;
        }
    }
    else if (msg->arrivedOn("radioIn")) {
        inet::Packet *pkt = check_and_cast<inet::Packet*>(msg);
        consumeEnergy(radioRx_mA);

        bool isBaseStation = (energyStorage->getNominalEnergyCapacity() == inet::J(0) ||
                              energyStorage->getNominalEnergyCapacity().get() > 1000000);

        if (isBaseStation) {
            emit(packetReceivedSignal, 1);
            emit(endToEndDelaySignal, simTime() - pkt->getCreationTime());
            delete pkt;
        }
        else {
            consumeEnergy(radioTx_mA);
            sendDown(pkt->dup());
            delete pkt;
        }
    }
}

void Pegasis::buildChain() {
    int numNodes = getParentModule()->getParentModule()->par("numNodes");
    int index = getParentModule()->getIndex();
    if (index < numNodes - 1) nextNodeId = index + 1;
    else isLeader = true;
}

void Pegasis::consumeEnergy(double current_mA) {}

double Pegasis::getResidualEnergy() {
    if (energyStorage) return energyStorage->getResidualEnergyCapacity().get();
    return 0.0;
}
