package util;

import entities.Carta;
import entities.Jogador;

public class Interface {
    public void exibirJogo(Carta[] baralho, Jogador j1, Jogador j2, int nulosBaralho, Carta ultimaCJogada1, Carta ultimaCJogada2) {
        Carta[] maoj1 = j1.getMao();
        System.out.print("|");
        for (int i = 0; i < 99; i++) {
            System.out.print("-");
        }
        System.out.print("|\n");

        System.out.printf("|%100s\n", "|");
        System.out.print("|");
        System.out.printf("%4s----|", "|");
        System.out.printf("%20s", j2.getNome());
        for (int i = 0; i < 7; i++) {
            System.out.printf("%2s----|", "|");
        }
        System.out.printf("%22s", "|");
        for (int i = 0; i < 2; i++) {
            System.out.print("\n|");
            System.out.printf("%4s%5s", "|", "|");
            System.out.printf("%20s", " ");
            for (int j = 0; j < 7; j++) {
                System.out.printf("%2s%5s", "|", "|");
            }
            System.out.printf("%22s", "|");
        }
        System.out.print("\n|");
        System.out.printf("%4s----|", "|");
        System.out.printf("%20s", " ");
        for (int i = 0; i < 7; i++) {
            System.out.printf("%2s----|", "|");
        }
        System.out.printf("%22s", "|");
        System.out.print("\n|");
        System.out.printf("%9s: %2d", "baralho", 54 - nulosBaralho);
        System.out.printf("%87s\n", "|");

        for (int i = 0; i < 3; i++) {
            System.out.printf("|%100s\n", "|");
        }
        if (ultimaCJogada1 == null && ultimaCJogada2 == null) {
            for (int j = 0; j < 4; j++) {
                System.out.printf("|%100s\n", "|");
            }
        } else if (ultimaCJogada1 == null) {
            System.out.print("|");
            System.out.printf("%45s----|", "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s%3s%2s", "|", ultimaCJogada2.getCor(), "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s%3s%2s", "|", ultimaCJogada2.getTipo(), "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s----|", "|");
            System.out.printf("%50s", "|");
            System.out.print("\n");
            for (int j = 0; j < 4; j++) {
                System.out.printf("|%100s\n", "|");
            }
        } else {
            System.out.print("|");
            System.out.printf("%45s----|", "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s%3s%2s", "|", ultimaCJogada2.getCor(), "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s%3s%2s", "|", ultimaCJogada2.getTipo(), "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s----|", "|");
            System.out.printf("%50s", "|");
            System.out.printf("\n|%100s\n", "|");
            System.out.print("|");
            System.out.printf("%45s----|", "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s%3s%2s", "|", ultimaCJogada1.getCor(), "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s%3s%2s", "|", ultimaCJogada1.getTipo(), "|");
            System.out.printf("%50s", "|");
            System.out.print("\n|");
            System.out.printf("%45s----|", "|");
            System.out.printf("%50s", "|");
            System.out.print("\n");
        }
        for (int i = 0; i < 3; i++) {
            System.out.printf("|%100s\n", "|");
        }
        System.out.print("|");
        System.out.printf("%29s", j1.getNome());
        for (int i = 0; i < 7; i++) {
            System.out.printf("%2s----|", "|");
        }
        System.out.printf("%22s", "|");
        System.out.print("\n|");
        System.out.printf("%29s", " ");
        for (int i = 0; i < 7; i++) {
            System.out.printf("%2s%3s%2s", "|", maoj1[i].getCor(), "|");
        }
        System.out.printf("%22s", "|");
        System.out.print("\n|");
        System.out.printf("%29s", " ");
        for (int i = 0; i < 7; i++) {
            System.out.printf("%2s%3s%2s", "|", maoj1[i].getTipo(), "|");
        }
        System.out.printf("%22s", "|");
        System.out.print("\n|");
        System.out.printf("%29s", " ");
        for (int i = 0; i < 7; i++) {
            System.out.printf("%2s----|", "|");
        }
        System.out.printf("%22s", "|");
        System.out.printf("\n|%100s\n", "|");
        System.out.print("|");
        for (int i = 0; i < 99; i++) {
            System.out.print("-");
        }
        System.out.print("|\n");
    }

    public void exibeBatalha(Carta ultimaCarta1, Carta ultimaCarta2, Jogador j1, Jogador j2) {
        System.out.print("|");
        for (int i = 0; i < 99; i++) {
            System.out.print("-");
        }
        System.out.print("|\n");
        System.out.printf("|%100s", "|");
        System.out.printf("\n|%100s", "|");
        System.out.printf("\n|%20s", j2.getNome());
        System.out.printf("%28s----|", "|");
        System.out.printf("%48s", "|\n");
        System.out.printf("|%48s %2s |", "|", ultimaCarta2.getCor());
        System.out.printf("%48s", "|\n");
        System.out.printf("|%48s %2s |", "|", ultimaCarta2.getTipo());
        System.out.printf("%48s", "|\n");
        System.out.print("|");
        System.out.printf("%48s----|", "|");
        System.out.printf("%48s", "|\n");
        System.out.printf("|%100s\n", "|");
        System.out.printf("|%20s", j1.getNome());
        System.out.printf("%28s----|", "|");
        System.out.printf("%48s", "|\n");
        System.out.printf("|%48s %2s |", "|", ultimaCarta1.getCor());
        System.out.printf("%48s", "|\n");
        System.out.printf("|%48s %2s |", "|", ultimaCarta1.getTipo());
        System.out.printf("%48s", "|\n");
        System.out.printf("|%48s----|", "|");
        System.out.printf("%48s", "|\n");
        System.out.printf("|%100s", "|");
        System.out.printf("\n|%100s\n", "|");
        System.out.print("|");
        for (int i = 0; i < 99; i++) {
            System.out.print("-");
        }
        System.out.print("|\n");
    }
}
