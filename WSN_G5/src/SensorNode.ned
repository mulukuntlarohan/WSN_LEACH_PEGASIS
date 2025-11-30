import inet.linklayer.ieee802154.Ieee802154NarrowbandInterface;
import inet.power.storage.SimpleEpEnergyStorage;
import inet.mobility.static.StationaryMobility;
import inet.networklayer.common.InterfaceTable;
// ADD THIS IMPORT
import inet.common.lifecycle.NodeStatus;

module SensorNode {
    parameters:
        @networkNode;
        string routingProtocol;
        double initialJoules @unit(J);
        double radioTx_mA;
        double radioRx_mA;
        double sleep_mA;
        double supplyVoltage @unit(V);
        @display("i=misc/sensor2;r=,,#707070");

    gates:
        input radioIn @directIn;

    submodules:
        // ADD THIS SUBMODULE (Must be named 'status')
        status: NodeStatus {
            @display("p=25,50");
        }
        interfaceTable: InterfaceTable {
            @display("p=250,50");
        }
        mobility: StationaryMobility {
            @display("p=50,50");
        }
        energyStorage: SimpleEpEnergyStorage {
            nominalCapacity = parent.initialJoules;
            initialCapacity = parent.initialJoules;
            @display("p=50,150");
        }
        app: SensorApp {
            @display("p=150,50");
        }
        routing: <routingProtocol> like IRouting {
            @display("p=150,150");
        }
        wlan: Ieee802154NarrowbandInterface {
            @display("p=150,250");
        }

    connections allowunconnected:
        app.lowerLayerOut --> routing.appIn;
        app.lowerLayerIn <-- routing.appOut;
        routing.radioOut --> wlan.upperLayerIn;
        routing.radioIn <-- wlan.upperLayerOut;
}