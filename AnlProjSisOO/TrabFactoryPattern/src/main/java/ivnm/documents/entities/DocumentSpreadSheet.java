package ivnm.documents.entities;

import ivnm.enums.FileType;
import ivnm.utils.FileManipulator;
import org.jline.reader.EndOfFileException;
import org.jline.reader.LineReader;
import org.jline.reader.LineReaderBuilder;
import org.jline.reader.UserInterruptException;
import org.jline.terminal.Terminal;
import org.jline.terminal.TerminalBuilder;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class DocumentSpreadSheet extends AbstractDocument {

    public DocumentSpreadSheet(String fileName) {
        super(fileName, FileType.SPREADSHEET);
        open();
    }

    @Override
    public void open() {
        System.out.println("\nAbrindo planilha CSV...");
        FileManipulator.openArchive(this.fileName, this.content);
        System.out.println("Planilha aberta. Cada linha do arquivo é tratada individualmente.");
    }

    @Override
    public void edit() {
        List<String> newContent = new ArrayList<>();
        System.out.println("\nEditando planilha CSV... Pressione Ctrl+D para salvar e sair, ou Ctrl+C para cancelar.");
        System.out.println("Use vírgulas (,) para separar os valores das colunas em cada linha.");

        try (Terminal terminal = TerminalBuilder.builder().system(true).build()) {
            LineReader lineReader = LineReaderBuilder.builder().terminal(terminal).build();
            int lineIndex = 0;
            List<String> columns = null;
            while (true) {
                String currentLine;
                String prompt;

                if (lineIndex < this.getContent().size()) {
                    currentLine = this.getContent().get(lineIndex);
                    prompt = String.format("Linha %d/%d: ", lineIndex + 1, this.getContent().size());
                } else {
                    currentLine = "";
                    prompt = String.format("Nova Linha %d: ", lineIndex + 1);
                }

                String userInput = lineReader.readLine(prompt, null, currentLine);

                if (lineIndex == 0) {
                    columns = Arrays.asList(userInput.split(","));
                    newContent.add(userInput);
                    lineIndex++;
                    continue;
                }

                String[] userColumns = userInput.split(",");
                if (userColumns.length != columns.size()) {
                    if (userInput.trim().isEmpty() && currentLine.isEmpty()) {
                        System.out.println("\nLinha em branco detectada, finalizando a adição de novas linhas.");
                        throw new EndOfFileException();
                    }

                    System.out.println(String.format("ERRO: A linha deve ter %d colunas, mas você forneceu %d. Tente novamente.", columns.size(), userColumns.length));
                    continue;
                }

                newContent.add(userInput);

                lineIndex++;
            }
        } catch (EndOfFileException e) {
            this.setContent(newContent);
            System.out.println("\n\nEdição concluída e conteúdo salvo na memória.");
        } catch (UserInterruptException e) {
            System.out.println("\n\nEdição cancelada pelo usuário. Nenhuma alteração foi salva.");
        } catch (IOException e) {
            System.err.println("\n\nOcorreu um erro no terminal: " + e.getMessage());
        }
    }

    @Override
    public void save() {
        System.out.println("\nSalvando planilha CSV...");
        FileManipulator.saveArchive(this.fileName, this.content);
        System.out.println("Planilha salva com sucesso!");
    }
}