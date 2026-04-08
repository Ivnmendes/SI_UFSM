public class Main {
    public static void main(String[] args) {
        Product chips = new Product("Chips", 250);

        VendingMachine machine = new VendingMachine(chips);
        machine.displayProductInfo();

        machine.insertCoin(Coin.DOLLAR);
        machine.insertCoin(Coin.QUARTER);
        machine.insertCoin(Coin.QUARTER);
        machine.insertCoin(Coin.DIME);
        machine.insertCoin(Coin.PENNY);
        machine.insertCoin(Coin.DOLLAR);

        System.out.println("\n--- Começando uma nova compra de refrigerante ($1.00) ---");

        Product soda = new Product("Refrigerante", 100);
        VendingMachine machine2 = new VendingMachine(soda);
        machine2.displayProductInfo();

        machine2.insertCoin(Coin.QUARTER);
        machine2.insertCoin(Coin.QUARTER);
        machine2.insertCoin(Coin.QUARTER);
        machine2.insertCoin(Coin.QUARTER);
    }
}