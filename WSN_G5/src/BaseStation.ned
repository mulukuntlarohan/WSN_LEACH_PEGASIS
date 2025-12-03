import inet.linklayer.ieee802154.Ieee802154NarrowbandInterface;
import inet.mobility.static.StationaryMobility;
import inet.power.storage.IdealEpEnergyStorage;
import inet.networklayer.common.InterfaceTable;
import inet.common.lifecycle.NodeStatus;

module BaseStation {
    parameters:
        @networkNode;
        @display("i=device/antennatower;is=l");

        // --- FIX: Add this parameter so WsnNetwork can set it ---
        string routingProtocol;
        // -------------------------------------------------------

        double radioTx_mA = default(0);
        double radioRx_mA = default(0);
        double supplyVoltage @unit(V) = default(3.0V);

    submodules:
        status: NodeStatus {
            @display("p=25,50");
        }
        interfaceTable: InterfaceTable {
            @display("p=250,50");
        }
        mobility: StationaryMobility {
            @display("p=50,50");
        }
        energyStorage: IdealEpEnergyStorage {
            @display("p=50,150");
        }

        // --- FIX: Use the parameter to choose the protocol dynamically ---
        routing: <routingProtocol> like IRouting {
            @display("p=150,150");
        }
        // ---------------------------------------------------------------

        wlan: Ieee802154NarrowbandInterface {
            @display("p=150,250");
        }
    connections allowunconnected:
        routing.radioOut --> wlan.upperLayerIn;
        routing.radioIn <-- wlan.upperLayerOut;
}