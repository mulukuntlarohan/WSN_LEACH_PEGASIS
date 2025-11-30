simple Leach like IRouting {
    parameters:
        double percentage = default(0.05);
        double roundDuration @unit(s) = default(20s);

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