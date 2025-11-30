#include "SensorApp.h"
#include "NetworkPacket_m.h"

Define_Module(SensorApp);

SensorApp::~SensorApp() {
    cancelAndDelete(timerMsg);
}

void SensorApp::initialize() {
    packetInterval = par("packetInterval");
    payloadBytes = par("payloadBytes");

    // Register Signal for Statistics
    packetSentSignal = registerSignal("packetSent");

    // REMOVED: setupClusteredTopology();
    // Logic moved to .ini file to avoid "Setting parameter not allowed" error.

    // 2. Start Traffic Timer
    timerMsg = new cMessage("sendTimer");
    scheduleAt(simTime() + uniform(0, 1), timerMsg);
}

// REMOVED: void SensorApp::setupClusteredTopology() { ... }

void SensorApp::handleMessage(cMessage *msg) {
    if (msg == timerMsg) {
        generateTraffic();
        scheduleAt(simTime() + packetInterval, timerMsg);
    } else {
        delete msg;
    }
}

void SensorApp::generateTraffic() {
    auto packet = new inet::Packet("SensorData");
    auto payload = inet::makeShared<NetworkPacket>();
    payload->setChunkLength(inet::B(payloadBytes));
    payload->setType(WsnPacketType::DATA);
    payload->setSrcId(getParentModule()->getId());
    payload->setDestId(0);

    packet->insertAtBack(payload);

    // Record Statistic
    emit(packetSentSignal, 1);

    send(packet, "lowerLayerOut");
}
