package entities;

import util.Operacoes;

import java.util.Random;

public class Jogador {
    Random gerador = new Random();
    Operacoes operador = new Operacoes();
    private String nome;
    private Carta[] mao;
    private int numCartasVermelhas;
    private int somaMonte;
    private int numVitorias;
    private int pontFinal;

    public Jogador(String nome, Carta[] mao) {
        this.nome = nome;
        this.mao = mao;
        this.numCartasVermelhas = 0;
        this.somaMonte = 0;
        this.numVitorias = 0;
        this.pontFinal = 0;
    }

    public Jogador(String nome) {
        this.nome = nome;
        this.mao = new Carta[]{null, null, null, null, null, null, null};
        this.numCartasVermelhas = 0;
        this.somaMonte = 0;
        this.numVitorias = 0;
        this.pontFinal = 0;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Carta[] getMao() {
        return mao;
    }

    public void setMao(Carta[] mao) {
        this.mao = mao;
    }

    public int getNumCartasVermelhas() {
        return numCartasVermelhas;
    }

    public void setNumCartasVermelhas(int numCartasVermelhas) {
        this.numCartasVermelhas = numCartasVermelhas;
    }

    public int getSomaMonte() {
        return somaMonte;
    }

    public void setSomaMonte(int somaMonte) {
        this.somaMonte = somaMonte;
    }

    public int getNumVitorias() {
        return numVitorias;
    }

    public void setNumVitorias(int numVitorias) {
        this.numVitorias = numVitorias;
    }

    public int getPontFinal() {
        return pontFinal;
    }

    public void setPontFinal(int pontFinal) {
        this.pontFinal = pontFinal;
    }

    public int numCartasMao () {
        int cont = 0;
        for (Carta carta : mao) {
            if (carta != null) {
                cont++;
            }
        }
        return cont;
    }

    public void ordenarMao() {
        int cartas = numCartasMao();
        int numNulos = mao.length - cartas;
        for (int i = 0; i < mao.length - numNulos; i++) {
            for (int j = 0; j < mao.length - 1 - i; j++) {
                if (mao[j] == null && mao[j+1] != null) {
                    Carta aux = mao[j];
                    mao[j] = mao[j+1];
                    mao[j+1] = aux;
                }
            }
        }

        for (int i = 0; i < cartas - 1; i++) {
            for (int j = 0; j < cartas - i - 1; j++) {
                if (mao[j].getValor() > mao[j+1].getValor()) {
                    Carta aux = mao[j];
                    mao[j] = mao[j + 1];
                    mao[j + 1] = aux;
                }
            }
        }
    }

    public void comprarCarta(Carta baralho[]) {
        int numCartasMao = numCartasMao();
        int cartasVermelhasMesa = numCartasVermelhas;
        do  {
            Carta cartaComprada = null;
            int posCarta;
            do {
                posCarta = gerador.nextInt(54);
                cartaComprada = baralho[posCarta];
            } while (cartaComprada == null);

            mao[numCartasMao] = cartaComprada;
            baralho[posCarta] = null;

            numCartasMao++;
            cartasVermelhasMesa--;
        } while (mao.length < 7 && cartasVermelhasMesa > 0);
    }

    public Carta jogarCarta(int posCartaEsc) {
        Carta cartaJogada = mao[posCartaEsc];
        mao[posCartaEsc] = null;
        somaMonte += cartaJogada.getValor();
        if (cartaJogada.getCor().equalsIgnoreCase("vermelho")) {
            numCartasVermelhas++;
        }

        return cartaJogada;
    }

    public void calcPontFinal() {
        pontFinal += somaMonte;
    }
}
