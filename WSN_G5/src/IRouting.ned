moduleinterface IRouting {
    parameters:
        @display("i=block/network");
    gates:
        input appIn;
        output appOut;
        input radioIn;
        output radioOut;
}