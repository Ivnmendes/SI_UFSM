package application;

import entities.Carta;
import entities.Jogador;
import util.Interface;
import util.Operacoes;

import java.util.Scanner;

public class Program {
    public static void limparTela() {
        for (int i = 0; i < 100; i++) {
            System.out.println(" ");
        }
    }
    public static void main(String[] args) {
        Operacoes operador = new Operacoes();
        Carta[] baralho = new Carta[54];
        Scanner sc = new Scanner(System.in);
        Interface exibe = new Interface();

        baralho = operador.inicializarBaralho(baralho);

        Carta[] mao1 = new Carta[7];
        Carta[] mao2 = new Carta[7];
        operador.distribuirMao(baralho, mao1, mao2);

        int nulosBaralho = 14;

        String nome;
        System.out.print("Digite o nome do jogador 1: ");
        do {
            nome = sc.next();
        } while (nome.length() > 29);

        Jogador j1 = new Jogador(nome, mao1);

        System.out.print("Digite o nome do jogador 2: ");
        do {
            nome = sc.next();
        } while (nome.length() > 29 && nome.equalsIgnoreCase(j1.getNome()));

        Jogador j2 = new Jogador(nome, mao2);

        Carta ultimaCJogada2 = null;
        Carta ultimaCJogada1 = null;

        int op;
        int cartasCompradas;

        while (baralho.length - nulosBaralho >= 0) {
            limparTela();

            exibe.exibirJogo(baralho, j1, j2, nulosBaralho, ultimaCJogada1, ultimaCJogada2);
            System.out.print("\nEscolha uma carta para jogar (de 0 a 6): ");
            op = sc.nextInt();
            while (op < 0 || op > 6) {
                System.out.println("Valor incorreto");
                System.out.print("\nEscolha uma carta para jogar (de 0 a 6): ");
                op = sc.nextInt();
            }
            ultimaCJogada1 = j1.jogarCarta(op);
            cartasCompradas = j1.comprarCarta(baralho);
            nulosBaralho += cartasCompradas;

            limparTela();

            exibe.exibirJogo(baralho, j2, j1, nulosBaralho, ultimaCJogada2, ultimaCJogada1);
            System.out.print("\nEscolha uma carta para jogar (de 0 a 6): ");
            op = sc.nextInt();
            while (op < 0 || op > 6) {
                System.out.println("Valor incorreto");
                System.out.print("\nEscolha uma carta para jogar (de 0 a 6): ");
                op = sc.nextInt();
            }
            ultimaCJogada2 = j2.jogarCarta(op);
            j2.comprarCarta(baralho);
            nulosBaralho += cartasCompradas;
        }

        j1.calcPontFinal();
        j2.calcPontFinal();

        System.out.printf("Pontuacao jogador 1: %d\nPontuacao jogador 2: %d", j1.getPontFinal(), j2.getPontFinal());

        if (j1.getPontFinal() > j2.getPontFinal()) {
            System.out.println("Jogador 1 ganhou!");
        } else if (j2.getPontFinal() > j1.getPontFinal()) {
            System.out.println("Jogador 2 ganhou!");
        } else {
            System.out.println("Empate");
        }
    }
}
