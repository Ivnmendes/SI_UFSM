package application;

import entities.Product;
import entities.Client;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.regex.Pattern;

public class Program {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Product> listaProdutos = new ArrayList<>();

        Pattern padraoData = Pattern.compile("(0[1-9]|[1|2][0-9]|3[0|1])[./](0[1-9]|1[0-2])[./]([0-9]{4})");
        Pattern padraoNF = Pattern.compile("[0-9]{4}");
        Pattern padraoTelefone = Pattern.compile("[0-9]{10}");
        Pattern padraoIdentificador = Pattern.compile("([0-9]{11})|([0-9]{14})");
        
        System.out.println("Bem vindo ao nosso sitema gerador de arquivos em formato EDI");

        String tipo;
        do {
            System.out.print("Insira o codigo tipo (5400 para venda | 5700 para compra: ");
            tipo = sc.nextLine();

            if (!tipo.equals("5400") && !tipo.equals("5700")) {
                System.out.println("Opção inválida. Tente novamente.");
            }
        } while (!tipo.equals("5400") && !tipo.equals("5700"));

        String numeroNotaFiscal;
        do {
            System.out.print("Insira o numero da nota fiscal (4 digitos): ");
            numeroNotaFiscal = sc.nextLine();
            
            if (!padraoNF.matcher(numeroNotaFiscal).matches()) {
                System.out.println("A nota fiscal deve ter apenas 4 digitos!");
            }
        } while (!padraoNF.matcher(numeroNotaFiscal).matches());

        String dataNotaFiscal;
        do {
            System.out.print("Insira a data da nota fiscal (dd/MM/yyyy): ");
            dataNotaFiscal = sc.next();

            if (!padraoData.matcher(dataNotaFiscal).matches()) {
                System.out.println("Formato de data invalido!\n");
            }
        } while (!padraoData.matcher(dataNotaFiscal).matches());
        dataNotaFiscal = dataNotaFiscal.replace("/", "");

        System.out.println("Insira os dados do cliente: ");
        System.out.print("Nome: ");
        sc.nextLine();
        String nomeCliente = sc.nextLine();
        System.out.print("Endereco: ");
        String enderecoCliente = sc.nextLine();
        System.out.print("Cidade: ");
        String cidadeCliente = sc.nextLine();
        
        String telefoneCliente;
        do {
            System.out.print("Telefone: ");
            telefoneCliente = sc.next();

            if (!padraoTelefone.matcher(telefoneCliente).matches()) {
                System.out.println("Telefone invalido! O telefone deve conter 10 digitos\n");
            }
        } while (!padraoTelefone.matcher(telefoneCliente).matches());

        String identificadorCliente;
        do {
            System.out.print("Insira o cpf ou cnpj do cliente (apenas numeros): ");
            identificadorCliente = sc.next();

            if (!padraoIdentificador.matcher(identificadorCliente).matches()) {
                System.out.println("Identificador inválido. Tente novamente, use 11 digitos para o CPF e 14 para o CNPJ.\n");
            }
        } while (!padraoIdentificador.matcher(identificadorCliente).matches());

        Client cliente = new Client(nomeCliente, enderecoCliente, cidadeCliente, telefoneCliente, identificadorCliente);

        System.out.println("Insercao de produtos");
        int continuar = 0;
        do {
            try {
                System.out.print("Insira a quantidade: ");
                int quantidade = sc.nextInt();
                System.out.print("Insira a descrição do produto: ");
                sc.nextLine();
                String descricao = sc.nextLine();
                System.out.print("Insira o preco unitario: ");
                double precoUnitario = sc.nextDouble();

                listaProdutos.add(new Product(quantidade, descricao, precoUnitario));
            }
            catch (InputMismatchException e) {
                System.out.println("Valor invalido, insercao de produto reiniciada!\n");
                sc.nextLine();
                continue;
            }

            System.out.print("Insira qualquer valor para continuar inserindo produtos ou -1 para finalizar: ");
            continuar = sc.nextInt();
            System.out.println();
        } while (continuar != -1);


        if (CreateFile.criaArquivo(tipo, numeroNotaFiscal, dataNotaFiscal, cliente, listaProdutos)) {
            System.out.println("Nota gerada com sucesso!");
        } else {
            System.out.println("Erro ao gerar nota");
        }

        System.out.println("Obrigado por utilizar nosso sistema!");
        sc.close();
    }
}
