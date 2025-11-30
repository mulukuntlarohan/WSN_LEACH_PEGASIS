import inet.applications.contract.IApp;

simple SensorApp like IApp {
    parameters:
        string traffic = default("constant");
        double packetInterval @unit(s) = default(1s);
        int payloadBytes @unit(B) = default(64B);

        // --- ADD STATISTICS ---
        @signal[packetSent];
        @statistic[packetSent](record=count,vector);
        // ----------------------

        @display("i=block/source");
    gates:
        input lowerLayerIn;
        output lowerLayerOut;
        input socketIn @loose;
        output socketOut @loose;
}