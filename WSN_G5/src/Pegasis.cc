#include "Pegasis.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/Protocol.h"
#include "NetworkPacket_m.h"

Define_Module(Pegasis);

void Pegasis::initialize() {
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

    scheduleAt(simTime() + 1.0, new cMessage("buildChain"));
}

void Pegasis::sendDown(inet::Packet *pkt) {
    auto req = pkt->addTagIfAbsent<inet::MacAddressReq>();
    req->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
    auto protocolReq = pkt->addTagIfAbsent<inet::PacketProtocolTag>();
    protocolReq->setProtocol(&inet::Protocol::ipv4);
    send(pkt, "radioOut");
}

void Pegasis::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage() && strcmp(msg->getName(), "buildChain") == 0) {
        buildChain();
        delete msg;
    }
    else if (msg->arrivedOn("appIn")) {
        inet::Packet *pkt = check_and_cast<inet::Packet*>(msg);
        consumeEnergy(radioTx_mA);
        if (isLeader || nextNodeId != -1) sendDown(pkt);
        else delete pkt;
    }
    else if (msg->arrivedOn("radioIn")) {
        inet::Packet *pkt = check_and_cast<inet::Packet*>(msg);
        consumeEnergy(radioRx_mA);

        // --- FIX: ROBUST BASE STATION CHECK ---
        bool isBaseStation = (strcmp(getParentModule()->getName(), "baseStation") == 0);

        if (isBaseStation) {
            // SINK LOGIC
            emit(packetReceivedSignal, 1); // Record PDR
            emit(endToEndDelaySignal, simTime() - pkt->getCreationTime()); // Record Delay
            delete pkt;
        }
        else {
            // FORWARDING
            auto fwdPacket = new inet::Packet("SensorData_Fwd");
            auto oldChunk = pkt->peekAtFront<NetworkPacket>();
            auto payload = inet::Ptr<NetworkPacket>(new NetworkPacket());
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
}

void Pegasis::buildChain() {
    if (!getParentModule()->isVector()) return;
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
