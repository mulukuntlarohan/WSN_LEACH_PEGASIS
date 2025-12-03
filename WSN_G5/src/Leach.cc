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

    if (getParentModule()->hasPar("radioTx_mA"))
        radioTx_mA = getParentModule()->par("radioTx_mA").doubleValue();
    else radioTx_mA = 0.0;

    if (getParentModule()->hasPar("radioRx_mA"))
        radioRx_mA = getParentModule()->par("radioRx_mA").doubleValue();
    else radioRx_mA = 0.0;

    energyStorage = check_and_cast<inet::power::IEpEnergyStorage*>(getParentModule()->getSubmodule("energyStorage"));

    packetReceivedSignal = registerSignal("packetReceived");
    endToEndDelaySignal = registerSignal("endToEndDelay");

    roundTimer = new cMessage("roundTimer");
    scheduleAt(simTime() + 0.5 + uniform(0, 0.1), roundTimer);
}

void Leach::sendDown(inet::Packet *pkt) {
    auto macReq = pkt->addTagIfAbsent<inet::MacAddressReq>();
    macReq->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
    auto protocolReq = pkt->addTagIfAbsent<inet::PacketProtocolTag>();
    protocolReq->setProtocol(&inet::Protocol::ipv4);
    send(pkt, "radioOut");
}

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
    else delete msg;
}

void Leach::startNewRound() {
    currentRound++;
    myClusterHeadId = -1;
    clusterMembers.clear();
    isClusterHead = checkThreshold();
    if (isClusterHead) advertiseCH();
}

bool Leach::checkThreshold() { return dblrand() < p_desired; }

void Leach::advertiseCH() {
    auto packet = new inet::Packet("CH_ADV");
    auto payload = inet::makeShared<NetworkPacket>();
    payload->setChunkLength(inet::B(32));
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
    payload->setChunkLength(inet::B(32));
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

    if (type == WsnPacketType::CH_ADV) {
        if (!isClusterHead && myClusterHeadId == -1) {
            myClusterHeadId = src;
            sendJoinRequest(src);
        }
    }
    else if (type == WsnPacketType::JOIN_REQ) {
        if (isClusterHead && dest == selfId) clusterMembers.push_back(src);
    }
    else if (type == WsnPacketType::DATA) {
        // --- FIX: ROBUST BASE STATION CHECK ---
        // Check if the module name is "baseStation" (as defined in WsnNetwork.ned)
        bool isBaseStation = (strcmp(getParentModule()->getName(), "baseStation") == 0);

        if (isBaseStation) {
            // SINK LOGIC
            emit(packetReceivedSignal, 1); // Record PDR count
            emit(endToEndDelaySignal, simTime() - pkt->getCreationTime()); // Record Delay
            delete pkt;
        }
        else if (isClusterHead) {
             // FORWARDING LOGIC
             auto fwdPacket = new inet::Packet("SensorData_Fwd");
             auto oldChunk = pkt->peekAtFront<NetworkPacket>();
             auto payload = inet::makeShared<NetworkPacket>();
             payload->setChunkLength(inet::B(64));
             payload->setType(WsnPacketType::DATA);
             payload->setSrcId(oldChunk->getSrcId());
             payload->setDestId(0);
             fwdPacket->insertAtBack(payload);
             consumeEnergy(radioTx_mA);
             sendDown(fwdPacket);
             delete pkt;
        }
    }
    else delete pkt;
}

void Leach::consumeEnergy(double current_mA) {}
double Leach::getResidualEnergy() {
    if (energyStorage) return energyStorage->getResidualEnergyCapacity().get();
    return 0.0;
}
