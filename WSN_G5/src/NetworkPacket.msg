import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;

// This block ensures the generated C++ code knows what FieldsChunk is
cplusplus {{
#include "inet/common/packet/chunk/FieldsChunk.h"
}}

enum WsnPacketType {
    DATA = 0;
    HELLO = 1;
    CH_ADV = 2;
    JOIN_REQ = 3;
    TDMA_SCH = 4;
}

// Inherit from inet::FieldsChunk so it works with the Radio
class NetworkPacket extends inet::FieldsChunk {
    int srcId;
    int destId;      // -1 for Broadcast
    int type @enum(WsnPacketType);
    int sequenceNumber;
    double residualEnergy;
    double xPos;
    double yPos;
}