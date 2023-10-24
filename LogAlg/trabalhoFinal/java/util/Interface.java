package util;

import entities.Carta;
import entities.Jogador;

public class Interface {
    public void exibirJogo(Carta baralho[], Jogador j1, Jogador j2) {
        System.out.print("|");
        for (int i = 0; i < 49; i++) {
            System.out.print("-");
        }
        System.out.print("|\n");
        System.out.printf("|%50s\n", "|");
        System.out.print("|");
        System.out.printf("%4s----", "|");
        System.out.printf("%10s", j2.getNome());
        for (int i = 0; i < 8; i++) {
            System.out.printf("%2s----|", "|");
        }

    }
}
