import inet.physicallayer.wireless.ieee802154.packetlevel.Ieee802154NarrowbandScalarRadioMedium;
import inet.visualizer.common.IntegratedVisualizer;

network WsnNetwork {
    parameters:
        int numNodes = default(18);
        string topologyType = default("clustered");

        // This parameter allows .ini to select the protocol
        string activeProtocol = default("Leach");

        // Unused params kept for compatibility
        string protocolA = default("leach");
        string protocolB = default("pegasis");
        bool compareAB = default(true);

        @display("bgb=600,600");

    submodules:
        radioMedium: Ieee802154NarrowbandScalarRadioMedium {
            @display("p=50,50");
        }
        visualizer: IntegratedVisualizer {
            @display("p=500,50");
        }
        baseStation: BaseStation {
            // FIX: Pass the protocol name correctly (Capitalized)
            routingProtocol = parent.activeProtocol == "Leach" ? "Leach" : "Pegasis";
            @display("p=300,300");
        }
        node[numNodes]: SensorNode {
            // FIX 1: Capital "L" in check to match .ini file
            routingProtocol = parent.activeProtocol == "Leach" ? "Leach" : "Pegasis";

            // FIX 2: Removed @display("p=100,100"); so nodes can appear at their real positions
        }
}