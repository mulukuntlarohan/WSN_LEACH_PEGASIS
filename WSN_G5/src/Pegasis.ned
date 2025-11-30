import inet.applications.contract.IApp;

simple Pegasis like IRouting {
    parameters:
        // --- ADD STATISTICS ---
        @signal[packetReceived];
        @signal[endToEndDelay];
        @statistic[packetReceived](record=count,vector);
        @statistic[endToEndDelay](record=vector,mean);
        // ----------------------

        @display("i=block/routing");
    gates:
        input appIn;
        output appOut;
        input radioIn;
        output radioOut;
}