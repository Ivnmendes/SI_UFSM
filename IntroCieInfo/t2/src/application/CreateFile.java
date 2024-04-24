package application;

import Entities.Client;
import Entities.Product;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;

public abstract class CreateFile {
    public static boolean criaArquivo(String tipoNota, String numeroNotaFiscal, String dataNotaFiscal, Client cliente, ArrayList<Product> listaProdutos) {
        String path = System.getProperty("user.dir") + "/src/arquivos/notaEDI.txt"; // Essa parte só roda no linux a principio, nao testei no windows

        Client fornecedor = new Client("Fornecedor", "Rua do Fornecedor", "Cidade do Fornecedor", "5533334444", "00101010000011");

        int totItens = 0;
        double totValor = 0;

        try (BufferedWriter bw = new BufferedWriter(new FileWriter(path))) {
            bw.write("ST*850*" + tipoNota);
            bw.newLine();

            bw.write("BG*" + numeroNotaFiscal + "*" + dataNotaFiscal);
            bw.newLine();

            bw.write("N1*" + fornecedor);
            bw.newLine();

            bw.write("N2*" + cliente);
            bw.newLine();

            for (Product produto : listaProdutos) {
                bw.write("POX*" + produto);
                bw.newLine();

                totItens += produto.getQuantidade();
                totValor += produto.total();
            }

            bw.write("CTT*" + totItens + "*" + totValor);
            bw.newLine();

            bw.write("SE*" + numeroNotaFiscal);
        }
        catch (Exception e) {
            throw new RuntimeException("Erro ao criar arquivo: " + e.getMessage());
            //return false;
        }

        return true;
    }
}
