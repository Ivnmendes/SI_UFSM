package ivnm.application;

import ivnm.documents.entities.DocumentText;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("insira o nome do arquivo: ");
        String fileName = sc.next();

        DocumentText doc = new DocumentText(fileName);
        doc.edit();
        doc.save();
        sc.close();
    }
}
