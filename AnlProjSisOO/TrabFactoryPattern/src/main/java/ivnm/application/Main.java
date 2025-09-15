package ivnm.application;

import ivnm.documents.entities.AbstractDocument;
import ivnm.documents.factory.DocumentPresentationFactory;
import ivnm.documents.factory.DocumentSpreadSheetFactory;
import ivnm.documents.factory.DocumentTextFactory;
import ivnm.utils.FileScann;
import org.jline.reader.LineReader;
import org.jline.reader.LineReaderBuilder;
import org.jline.terminal.Terminal;
import org.jline.terminal.TerminalBuilder;
import org.jline.utils.InfoCmp;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    private static AbstractDocument currentDocument = null;
    private static final DocumentTextFactory documentTextFactory = new DocumentTextFactory();
    private static final DocumentSpreadSheetFactory documentSpreadSheetFactory = new DocumentSpreadSheetFactory();
    private static final DocumentPresentationFactory documentPresentationFactory = new DocumentPresentationFactory();
    private static final Scanner scanner = new Scanner(System.in);
    private static Terminal terminal;
    private static LineReader lineReader;

    static {
        try {
            terminal = TerminalBuilder.builder().system(true).build();
            lineReader = LineReaderBuilder.builder().terminal(terminal).build();
        } catch (IOException e) {
            throw new RuntimeException("Não foi possível inicializar o terminal.", e);
        }
    }

    public static void main(String[] args) {
        while (true) {
            displayMenu();
            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    handleCreateDocument();
                    break;
                case "2":
                    handleOpenDocument();
                    break;
                case "3":
                    handleSaveDocument();
                    break;
                case "4":
                    System.out.println("Saindo do editor. Até logo!");
                    return;
                default:
                    System.out.println("Opção inválida! Tente novamente.");
                    break;
            }
        }
    }

    private static void displayMenu() {
        terminal.puts(InfoCmp.Capability.clear_screen);
        terminal.flush();

        List<String> textFiles = new ArrayList<>();
        List<String> spreadSheetFiles = new ArrayList<>();
        List<String> presentationFiles = new ArrayList<>();

        FileScann.listFiles(textFiles, spreadSheetFiles, presentationFiles);

        System.out.println("\n╔══════════════════════════════════╗");
        System.out.println("║         EDITOR DE ARQUIVOS       ║");
        System.out.println("╚══════════════════════════════════╝");

        System.out.println("\n--- Arquivos de Texto (.txt) ---");
        textFiles.forEach(System.out::println);
        if (textFiles.isEmpty()) System.out.println("(Nenhum arquivo)");

        System.out.println("\n--- Planilhas (.xls) ---");
        spreadSheetFiles.forEach(System.out::println);
        if (spreadSheetFiles.isEmpty()) System.out.println("(Nenhum arquivo)");

        System.out.println("\n--- Apresentações (.pst) ---");
        presentationFiles.forEach(System.out::println);
        if (presentationFiles.isEmpty()) System.out.println("(Nenhum arquivo)");

        if (currentDocument != null) {
            System.out.println("\nDocumento Aberto: " + currentDocument.getFileName());
        }

        System.out.println("\n--- OPÇÕES ---");
        System.out.println("1. Criar Novo Documento");
        System.out.println("2. Abrir e Editar Documento");
        System.out.println("3. Salvar Documento Aberto");
        System.out.println("4. Sair");
        System.out.print("Escolha uma opção: ");
    }

    private static void handleCreateDocument() {
        System.out.print("Digite o nome do novo arquivo (ex: 'meu_arquivo.txt'): ");
        String fileName = scanner.nextLine();

        if (!isValidFilename(fileName)) {
            System.out.println("Nome de arquivo inválido. Deve conter uma extensão suportada (.txt, .xls, .pst).");
            return;
        }

        try {
            currentDocument = createDocumentByFileName(fileName);

            System.out.println("Arquivo '" + fileName + "' criado e aberto!");
        } catch (IllegalArgumentException e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }

    private static void handleOpenDocument() {
        System.out.print("Digite o nome do arquivo para abrir e editar: ");
        String fileName = scanner.nextLine();

        try {
            currentDocument = createDocumentByFileName(fileName);

            System.out.println("Documento '" + fileName + "' aberto. Iniciando edição...");
            currentDocument.edit();
        } catch (IllegalArgumentException e) {
            System.out.println("Erro ao abrir o arquivo: " + e.getMessage());
        }
    }

    private static AbstractDocument createDocumentByFileName(String fileName) {
        String extension = fileName.substring(fileName.lastIndexOf('.'));

        return switch (extension) {
            case ".txt" -> documentTextFactory.createDocument(fileName);
            case ".xls" -> documentSpreadSheetFactory.createDocument(fileName);
            case ".pst" -> documentPresentationFactory.createDocument(fileName);
            default -> throw new IllegalArgumentException("Tipo de arquivo não suportado");
        };
    }

    private static void handleSaveDocument() {
        if (currentDocument == null) {
            System.out.println("Nenhum documento aberto para salvar.");
            return;
        }
        currentDocument.save();
    }

    private static boolean isValidFilename(String fileName) {
        if (fileName == null || fileName.trim().isEmpty()) {
            return false;
        }
        return fileName.endsWith(".txt") || fileName.endsWith(".xls") || fileName.endsWith(".pst");
    }
}