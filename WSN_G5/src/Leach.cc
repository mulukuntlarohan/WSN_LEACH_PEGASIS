#include "Leach.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/Protocol.h"

Define_Module(Leach);

Leach::~Leach() {
    cancelAndDelete(roundTimer);
}

void Leach::initialize() {
    p_desired = par("percentage");
    roundDuration = par("roundDuration");
    selfId = getParentModule()->getId();

    // Parameter reading with safety defaults
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

    roundTimer = new cMessage("roundTimer");
    scheduleAt(simTime() + 0.5, roundTimer);
}

// --- HELPER FUNCTION ---
void Leach::sendDown(inet::Packet *pkt) {
    // 1. MAC Address Tag (Broadcast)
    auto macReq = pkt->addTagIfAbsent<inet::MacAddressReq>();
    macReq->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);

    // 2. Protocol Tag (FIX: Use IPv4 so the 802.15.4 MAC accepts it)
    auto protocolReq = pkt->addTagIfAbsent<inet::PacketProtocolTag>();
    protocolReq->setProtocol(&inet::Protocol::ipv4);

    send(pkt, "radioOut");
}
// ----------------------

void Leach::handleMessage(cMessage *msg) {
    if (msg == roundTimer) {
        startNewRound();
        scheduleAt(simTime() + roundDuration, roundTimer);
    }
    else if (msg->arrivedOn("appIn")) {
        inet::Packet *pkt = check_and_cast<inet::Packet*>(msg);
        consumeEnergy(radioTx_mA);

        if (isClusterHead) sendDown(pkt);
        else if (myClusterHeadId != -1) sendDown(pkt);
        else delete pkt;
    }
    else if (msg->arrivedOn("radioIn")) {
        inet::Packet *pkt = check_and_cast<inet::Packet*>(msg);
        consumeEnergy(radioRx_mA);
        processPacket(pkt);
    }
    else {
        delete msg;
    }
}

void Leach::startNewRound() {
    currentRound++;
    myClusterHeadId = -1;
    isClusterHead = checkThreshold();

    if (isClusterHead) {
        advertiseCH();
    }
}

bool Leach::checkThreshold() {
    return dblrand() < p_desired;
}

void Leach::advertiseCH() {
    auto packet = new inet::Packet("CH_ADV");
    auto payload = inet::makeShared<NetworkPacket>();
    payload->setType(WsnPacketType::CH_ADV);
    payload->setSrcId(selfId);
    payload->setResidualEnergy(getResidualEnergy());
    packet->insertAtBack(payload);

    consumeEnergy(radioTx_mA);
    sendDown(packet);
}

void Leach::sendJoinRequest(int targetChId) {
    auto packet = new inet::Packet("JOIN_REQ");
    auto payload = inet::makeShared<NetworkPacket>();
    payload->setType(WsnPacketType::JOIN_REQ);
    payload->setSrcId(selfId);
    payload->setDestId(targetChId);
    packet->insertAtBack(payload);

    consumeEnergy(radioTx_mA);
    sendDown(packet);
}

void Leach::processPacket(inet::Packet *pkt) {
    auto chunk = pkt->peekAtFront<NetworkPacket>();
    int type = chunk->getType();
    int src = chunk->getSrcId();
    int dest = chunk->getDestId();

    if (type == WsnPacketType::CH_ADV && !isClusterHead && myClusterHeadId == -1) {
        myClusterHeadId = src;
        sendJoinRequest(src);
    }
    else if (type == WsnPacketType::DATA) {
        bool isBaseStation = (energyStorage->getNominalEnergyCapacity() == inet::J(0) ||
                              energyStorage->getNominalEnergyCapacity().get() > 1000000);

        if (isBaseStation) {
            emit(packetReceivedSignal, 1);
            emit(endToEndDelaySignal, simTime() - pkt->getCreationTime());
            delete pkt;
        }
        else if (isClusterHead) {
             auto fwd = pkt->dup();
             consumeEnergy(radioTx_mA);
             sendDown(fwd);
             delete pkt;
        }
    }
    else {
        delete pkt;
    }
}

void Leach::consumeEnergy(double current_mA) {}

double Leach::getResidualEnergy() {
    if (energyStorage) return energyStorage->getResidualEnergyCapacity().get();
    return 0.0;
}
