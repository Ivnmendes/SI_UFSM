public class Bar {
    public static void main(String[] args) {
        Size small = new SmallSize();
        Size medium = new MediumSize();
        Size big = new BigSize();

        Soda smallCoke = new Coke(small);
        smallCoke.showDetails();

        Soda mediumCoke = new Coke(medium);
        mediumCoke.showDetails();

        Soda bigFanta = new Fanta(big);
        bigFanta.showDetails();

        Soda smallFanta = new Fanta(small);
        smallFanta.showDetails();
    }
}