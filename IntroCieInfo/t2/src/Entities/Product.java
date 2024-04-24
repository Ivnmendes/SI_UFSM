package Entities;

public class Product {
    private int quantidade;
    private String descricao;
    private double precoUnitario;

    public Product(int quantidade, String descricao, double precoUnitario) {
        this.quantidade = quantidade;
        this.descricao = descricao;
        this.precoUnitario = precoUnitario;
    }

    public int getQuantidade() {
        return quantidade;
    }

    public void setQuantidade(int quantidade) {
        this.quantidade = quantidade;
    }

    public String getDescricao() {
        return descricao;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public double getPrecoUnitario() {
        return precoUnitario;
    }

    public void setPrecoUnitario(double precoUnitario) {
        this.precoUnitario = precoUnitario;
    }

    public double total() {
        return quantidade * precoUnitario;
    }

    @Override
    public String toString() {
        return quantidade + "*" + descricao + "*" + precoUnitario + "*" + total();
    }
}
