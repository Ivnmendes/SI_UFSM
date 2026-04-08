public enum CoinSlot {
    PENNY(1),
    NICKEL(5),
    DIME(10),
    QUARTER(25),
    DOLLAR(100);

    private final int value;

    CoinSlot(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
