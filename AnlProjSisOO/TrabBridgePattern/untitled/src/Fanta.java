public class Fanta extends Soda{

    public Fanta(Size size) {
        super(size);
    }

    @Override
    public void showDetails() {
        System.out.println("Fanta " + size.getDescription());
    }
}
