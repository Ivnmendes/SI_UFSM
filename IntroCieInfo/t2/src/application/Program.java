package application;

import Entities.Product;
import Entities.Client;

import java.util.ArrayList;
import java.util.Scanner;



public class Program {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Product> listaProdutos = new ArrayList<>();

        System.out.println("Bem vindo ao nosso sitema gerador de arquivos em formato EDI");

        int tipo;
        do {
            System.out.print("Insira o codigo tipo (5400 para venda | 5700 para compra: ");
            tipo = sc.nextInt();

            if (tipo != 5400 && tipo != 5700) {
                System.out.println("Opção inválida. Tente novamente.");
            }
        } while (tipo != 5400 && tipo != 5700);

        System.out.print("Insira o numero da nota fiscal: ");
        int numeroNotaFiscal = sc.nextInt();

        System.out.print("Insira a data da nota fiscal (dd/MM/yyyy): ");
        String dataNotaFiscal = sc.next();
        dataNotaFiscal = dataNotaFiscal.replace("/", "");

        System.out.println("Insira os dados do cliente: ");
        System.out.print("Nome: ");
        sc.nextLine();
        String nomeCliente = sc.nextLine();
        System.out.print("Endereco: ");
        String enderecoCliente = sc.nextLine();
        System.out.print("Cidade: ");
        String cidadeCliente = sc.nextLine();
        System.out.print("Telefone: ");
        String telefoneCliente = sc.next();
        String identificadorCliente;
        do {
            System.out.print("Insira o cpf ou cnpj do cliente (apenas numeros): ");
            identificadorCliente = sc.next();

            if (identificadorCliente.length() != 11 && identificadorCliente.length() != 14) {
                System.out.println("Identificador inválido. Tente novamente.");
            }
        } while (identificadorCliente.length() != 11 && identificadorCliente.length() != 14);

        Client cliente = new Client(nomeCliente, enderecoCliente, cidadeCliente, telefoneCliente, identificadorCliente);

        System.out.println("Insercao de produtos");
        int continuar = 0;
        do {
            System.out.print("Insira a quantidade: ");
            int quantidade = sc.nextInt();
            System.out.print("Insira a descrição do produto: ");
            sc.nextLine();
            String descricao = sc.nextLine();
            System.out.print("Insira o preco unitario: ");
            double precoUnitario = sc.nextDouble();

            listaProdutos.add(new Product(quantidade, descricao, precoUnitario));

            System.out.print("Insira qualquer valor para continuar inserindo produtos ou -1 para finalizar: ");
            continuar = sc.nextInt();
        } while (continuar != -1);


        if (CreateFile.criaArquivo(Integer.toString(tipo), Integer.toString(numeroNotaFiscal), dataNotaFiscal, cliente, listaProdutos)) {
            System.out.println("Nota gerada com sucesso!");
        } else {
            System.out.println("Erro ao gerar nota");
        }

        System.out.println("Obrigado por utilizar nosso sistema!");
        sc.close();
    }
}
