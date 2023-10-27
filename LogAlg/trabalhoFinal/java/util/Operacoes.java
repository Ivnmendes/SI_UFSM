package util;

import entities.Carta;

import java.util.Arrays;
import java.util.Random;

public class Operacoes {

    Random gerador = new Random();
    public void distribuirMao (Carta[] baralho, Carta[] mao1, Carta[] mao2) {
        Carta cartaSort;
        for (int i = 0; i < 7; i++) {
            do {
                cartaSort = baralho[gerador.nextInt(54)];
            } while (cartaSort == null);
            mao1[i] = cartaSort;

            do {
                cartaSort = baralho[gerador.nextInt(54)];
            } while (cartaSort == null);
            mao2[i] = cartaSort;
        }
    }
    void fillArray(String[] array, int inicio, int fim, String valor) {
        for(int i = inicio; i <= fim; i++) {
            array[i] = valor;
        }
    }

    public Carta[] inicializarBaralho (Carta baralho[]) {
//        Carta[] baralho = new Carta[54];
        String nome[] = { "r1", "r1", "r2", "r2", "r3", "r3", "r4", "r5", "r6", "r7", "J", "Q", "K", "A",
                "1",  "1", "3", "3", "4","4", "5", "5", "7", "C", "J", "Q", "K", "A",
                "1",  "1", "2", "2", "3", "4", "5", "J", "Q", "K", "A",
                "2", "2", "2", "4", "4", "5","5","5", "J", "Q", "K", "A", "J", "J", "J"};
        String[] cores = new String[54];
        fillArray(cores, 0, 13, "p");
        fillArray(cores, 14, 27, "b");
        fillArray(cores, 28, 38, "r");
        fillArray(cores, 39, 50, "y");

        cores[51] = "p";
        cores[52] = "r";
        cores[53] = "y";

        int[] valores = new int[54];
        for (int i = 0; i < 54; i++) {
            switch (nome[i]) {
                case "r1":
                    valores[i] = 22;
                    break;
                case "r2":
                    valores[i] = 21;
                    break;
                case "r3":
                    valores[i] = 20;
                    break;
                case "r4":
                    valores[i] = 19;
                    break;
                case "r5":
                    valores[i] = 18;
                    break;
                case "r6":
                    valores[i] = 17;
                    break;
                case "r7":
                    valores[i] = 16;
                    break;
                case "C":
                    valores[i] = 15;
                    break;
                case "J":
                    valores[i] = 11;
                    break;
                case "Q":
                    valores[i] = 12;
                    break;
                case "K":
                    valores[i] = 13;
                    break;
                case "A":
                    valores[i] = 14;
                    break;
                default:
                    valores[i] = Integer.parseInt(nome[i]);
                    break;
            }
        }

        for (int i = 0; i < 54; i++) {
            baralho[i] = new Carta(nome[i], valores[i], cores[i]);
        }


        return baralho;
    }

}
