import inet.physicallayer.wireless.ieee802154.packetlevel.Ieee802154NarrowbandScalarRadioMedium;
import inet.visualizer.common.IntegratedVisualizer;

network WsnNetwork {
    parameters:
        int numNodes = default(18);
        string topologyType = default("clustered");
        string activeProtocol = default("Leach");
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
            @display("p=300,300");
        }
        node[numNodes]: SensorNode {
            routingProtocol = parent.activeProtocol == "leach" ? "Leach" : "Pegasis";
            @display("p=100,100");
        }
}