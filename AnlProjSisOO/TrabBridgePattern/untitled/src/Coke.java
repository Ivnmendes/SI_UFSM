public class Coke extends Soda{

    public Coke(Size size) {
        super(size);
    }

    @Override
    public void showDetails() {
        System.out.println("Coca-Cola " + size.getDescription());
    }
}
