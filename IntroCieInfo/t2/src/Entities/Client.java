package Entities;

import javax.swing.text.MaskFormatter;

public class Client {
    private String nome;
    private String endereco;
    private String cidade;
    private String telefone;
    private String identificador;

    public Client(String nome, String endereco, String cidade, String telefone, String identificador) {

        this.nome = nome;
        this.endereco = endereco;
        this.cidade = cidade;
        this.telefone = telefone;

        try {
            MaskFormatter mascara;
            String fmt = (identificador.length() == 11) ? "###.###.###-##" : "##.###.###/####-##";
            mascara = new MaskFormatter(fmt);

            mascara.setMask(identificador);
            this.identificador = identificador;
        }
        catch (Exception e) {
            throw new RuntimeException("Erro ao formatar identificador: " + e.getMessage());
        }
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public String getCidade() {
        return cidade;
    }

    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    public String getTelefone() {
        return telefone;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }

    public String getIdentificador() {
        return identificador;
    }

    public void setIdentificador(String identificador) {
        this.identificador = identificador;
    }

    @Override
    public String toString() {
        return nome+"*"+endereco+"*"+cidade+"*"+telefone+"*"+identificador;
    }
}
