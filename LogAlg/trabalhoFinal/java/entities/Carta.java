package entities;

public class Carta {
    private String tipo;
    private int valor;
    private String cor;

    public Carta(String tipo, int valor, String cor) {
        this.tipo = tipo;
        this.valor = valor;
        this.cor = cor;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public int getValor() {
        return valor;
    }

    public void setValor(int valor) {
        this.valor = valor;
    }

    public String getCor() {
        return cor;
    }

    public void setCor(String cor) {
        this.cor = cor;
    }

    @Override
    public String toString() {
        return tipo + " " + cor + " " + valor + "\n";
    }
}
