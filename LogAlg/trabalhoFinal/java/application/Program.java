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
        nome = sc.next();
        while (nome.length() > 20) {
            System.out.print("Digite o nome do jogador 1: ");
            nome = sc.next();
        }

        Jogador j1 = new Jogador(nome, mao1);

        System.out.print("Digite o nome do jogador 2: ");
        nome = sc.next();
        while (nome.length() > 20 || nome.equalsIgnoreCase(j1.getNome())) {
            System.out.println("Nome muito grande (max 29 caracteres) ou igual ao primeiro jogador");
            System.out.print("Digite o nome do jogador 2: ");
            nome = sc.next();
        }

        Jogador j2 = new Jogador(nome, mao2);

        Carta ultimaCJogada2 = null;
        Carta ultimaCJogada1 = null;

        int op, op1, op2;
        int combater;
        int cartasCompradas;

        while (baralho.length - nulosBaralho >= 0) {
            limparTela();

            exibe.exibirJogo(baralho, j1, j2, nulosBaralho, ultimaCJogada1, ultimaCJogada2);

            if (j1.verificarContemCPreta()) {
                System.out.print("Voce possui uma ou mais carta(s) preta(s), deseja combater (digite 1 para sim ou 0 para nao)?");
                combater = sc.nextInt();
                while (combater != 0 && combater != 1) {
                    System.out.println("Opcao invalida!");
                    System.out.print("Voce possui uma ou mais carta(s) preta(s), deseja combater (digite 1 para sim ou 0 para nao)?");
                    combater = sc.nextInt();
                }

                if (combater == 1) {
                    System.out.print("Escolha uma carta preta para jogar (de 1 a 7): ");
                    op1 = sc.nextInt() - 1;
                    while (op1 < 0 || op1 > 6 || !j1.verificarCarta(op1)) {
                        System.out.println("Valor incorreto ou carta de cor incorreta");
                        System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
                        op1 = sc.nextInt() - 1;
                    }

                    limparTela();

                    ultimaCJogada1 = j1.getMao()[op1];
                    j1.setMao(null, op1);
                    ultimaCJogada2 = null;
                    exibe.exibirJogo(baralho, j2, j1, nulosBaralho, ultimaCJogada2, ultimaCJogada1);
                    System.out.printf("%s chamou uma batalha\n", j1.getNome());
                    System.out.print("Escolha uma carta preta para jogar (de 1 a 7): ");
                    op2 = sc.nextInt() - 1;
                    while (op2 < 0 || op2 > 6) {
                        System.out.println("Valor incorreto ou carta de cor incorreta");
                        System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
                        op2 = sc.nextInt() - 1;
                    }

                    limparTela();
                    ultimaCJogada2 = j2.getMao()[op2];
                    exibe.exibeBatalha(ultimaCJogada2, ultimaCJogada1, j2, j1);
                    int resultBatalha = operador.batalhar(ultimaCJogada1, ultimaCJogada2);
                    switch (resultBatalha) {
                        case 0:
                            System.out.println("A batalha empatou!");
                            break;
                        case 1:
                            System.out.printf("%s venceu!\n", j1.getNome());
                            j1.somarVitoria();
                            break;
                        case 2:
                            j2.somarVitoria();
                            System.out.printf("%s venceu!\n", j2.getNome());
                            break;
                    }
                    System.out.println("Digite qualquer valor para continuar");
                    ultimaCJogada1 = null;
                    ultimaCJogada2 = null;
                    j2.setMao(null, op2);
                    cartasCompradas = j1.comprarCarta(baralho);
                    nulosBaralho += cartasCompradas;
                    cartasCompradas = j2.comprarCarta(baralho);
                    nulosBaralho += cartasCompradas;
                    sc.next();
                    limparTela();
                }
            }

            exibe.exibirJogo(baralho, j1, j2, nulosBaralho, ultimaCJogada1, ultimaCJogada2);

            System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
            op = sc.nextInt() - 1;
            while (op < 0 || op > 6) {
                System.out.println("Valor incorreto");
                System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
                op = sc.nextInt() - 1;
            }
            ultimaCJogada1 = j1.jogarCarta(op);
            cartasCompradas = j1.comprarCarta(baralho);
            nulosBaralho += cartasCompradas;

            limparTela();

            exibe.exibirJogo(baralho, j2, j1, nulosBaralho, ultimaCJogada2, ultimaCJogada1);

            if (j2.verificarContemCPreta()) {
                System.out.print("Voce possui uma ou mais carta(s) preta(s), deseja combater (digite 1 para sim ou 0 para nao)?");
                combater = sc.nextInt();
                while (combater != 0 && combater != 1) {
                    System.out.println("Opcao invalida!");
                    System.out.print("Voce possui uma ou mais carta(s) preta(s), deseja combater (digite 1 para sim ou 0 para nao)?");
                    combater = sc.nextInt();
                }

                if (combater == 1) {
                    System.out.print("Escolha uma carta preta para jogar (de 1 a 7): ");
                    op2 = sc.nextInt() - 1;
                    while (op2 < 0 || op2 > 6 || !j2.verificarCarta(op2)) {
                        System.out.println("Valor incorreto ou carta de cor incorreta");
                        System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
                        op2 = sc.nextInt() - 1;
                    }

                    limparTela();

                    ultimaCJogada2 = j2.getMao()[op2];
                    j2.setMao(null, op2);
                    Carta aux = ultimaCJogada1;
                    ultimaCJogada1 = null;
                    exibe.exibirJogo(baralho, j1, j2, nulosBaralho, ultimaCJogada1, ultimaCJogada2);
                    System.out.printf("%s chamou uma batalha\n", j2.getNome());
                    System.out.print("Escolha uma carta preta para jogar (de 1 a 7): ");
                    op1 = sc.nextInt() - 1;
                    while (op1 < 0 || op1 > 6) {
                        System.out.println("Valor incorreto ou carta de cor incorreta");
                        System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
                        op1 = sc.nextInt() - 1;
                    }
                    ultimaCJogada1 = j1.getMao()[op1];
                    j1.setMao(null, op1);
                    limparTela();
                    exibe.exibeBatalha(ultimaCJogada1, ultimaCJogada2, j1, j2);
                    int resultBatalha = operador.batalhar(ultimaCJogada1, ultimaCJogada2);
                    switch (resultBatalha) {
                        case 0:
                            System.out.println("A batalha empatou!");
                            break;
                        case 1:
                            System.out.printf("%s venceu!\n", j1.getNome());
                            j1.somarVitoria();
                            break;
                        case 2:
                            j2.somarVitoria();
                            System.out.printf("%s venceu!\n", j2.getNome());
                            break;
                    }
                    System.out.println("Digite qualquer valor para continuar");
                    ultimaCJogada2 = null;
                    cartasCompradas = j1.comprarCarta(baralho);
                    nulosBaralho += cartasCompradas;
                    cartasCompradas = j2.comprarCarta(baralho);
                    nulosBaralho += cartasCompradas;
                    ultimaCJogada1 = aux;
                    sc.next();
                    limparTela();
                }
            }
            exibe.exibirJogo(baralho, j2, j1, nulosBaralho, ultimaCJogada2, ultimaCJogada1);

            System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
            op = sc.nextInt() - 1;
            while (op < 0 || op > 6) {
                System.out.println("Valor incorreto");
                System.out.print("\nEscolha uma carta para jogar (de 1 a 7): ");
                op = sc.nextInt() - 1;
            }
            ultimaCJogada2 = j2.jogarCarta(op);
            cartasCompradas = j2.comprarCarta(baralho);
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
