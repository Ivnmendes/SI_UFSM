package application;

import entities.Carta;
import entities.Jogador;
import util.Interface;
import util.Operacoes;

public class Program {
    public static void main(String[] args) {
        Operacoes operador = new Operacoes();

        Jogador j1 = new Jogador("ivan");
        Jogador j2 = new Jogador("outrocara");

        Carta[] baralho = new Carta[54];
        baralho = operador.inicializarBaralho(baralho);

        for (Carta c : baralho) {
            System.out.println(c);
        }
//        Interface exibe = new Interface();
//        exibe.exibirJogo();
    }
}
