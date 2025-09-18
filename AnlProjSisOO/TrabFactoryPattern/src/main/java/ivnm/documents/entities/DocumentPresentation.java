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
import java.util.List;

public class DocumentPresentation extends AbstractDocument {

    private static final String SLIDE_SEPARATOR = "---";

    public DocumentPresentation(String fileName) {
        super(fileName, FileType.PRESENTATION);
        open();
    }

    @Override
    public void open() {
        System.out.println("\nAbrindo apresentação...");
        FileManipulator.openArchive(this.fileName, this.content);
        System.out.println("Apresentação aberta, você está livre para manipulá-la!");
    }

    @Override
    public void edit() {
        List<String> newContent = new ArrayList<>();
        List<List<String>> slides = new ArrayList<>();
        List<String> currentSlide = new ArrayList<>();
        for (String line : this.getContent()) {
            if (line.equals(SLIDE_SEPARATOR)) {
                if (!currentSlide.isEmpty()) {
                    slides.add(new ArrayList<>(currentSlide));
                    currentSlide.clear();
                }
            } else {
                currentSlide.add(line);
            }
        }
        if (!currentSlide.isEmpty()) {
            slides.add(currentSlide);
        }

        System.out.println("\nEditando apresentação... Pressione Ctrl+D para salvar e sair, ou Ctrl+C para cancelar.");
        System.out.println("Cada slide tem um título e conteúdo. Deixe uma linha de conteúdo em branco para finalizar um slide.");
        System.out.println("Para parar de adicionar novos slides, deixe o título do novo slide em branco.");

        try (Terminal terminal = TerminalBuilder.builder().system(true).build()) {
            LineReader lineReader = LineReaderBuilder.builder().terminal(terminal).build();
            int slideIndex = 0;

            while (true) {
                System.out.println("\n" + SLIDE_SEPARATOR);
                List<String> slideContent;
                String slideHeader;

                if (slideIndex < slides.size()) {
                    slideHeader = String.format("Editando Slide %d/%d", slideIndex + 1, slides.size());
                    slideContent = slides.get(slideIndex);
                } else {
                    slideHeader = String.format("Novo Slide %d", slideIndex + 1);
                    slideContent = new ArrayList<>();
                }
                System.out.println(slideHeader);

                String currentTitle = slideContent.isEmpty() ? "" : slideContent.get(0);
                String title = lineReader.readLine("Título: ", null, currentTitle);

                if (slideIndex >= slides.size() && (title == null || title.trim().isEmpty())) {
                    System.out.println("\nCriação de novos slides finalizada.");
                    throw new EndOfFileException();
                }
                newContent.add(title);

                int lineIndex = 1;
                while (true) {
                    String currentLine = (lineIndex < slideContent.size()) ? slideContent.get(lineIndex) : "";
                    String prompt = String.format("Conteúdo (linha %d): ", lineIndex);
                    String line = lineReader.readLine(prompt, null, currentLine);

                    if (line == null || line.trim().isEmpty() && currentLine.isEmpty()) {
                        break;
                    }
                    newContent.add(line);
                    lineIndex++;
                }
                newContent.add(SLIDE_SEPARATOR);
                slideIndex++;
            }
        } catch (EndOfFileException e) {
            if (!newContent.isEmpty() && newContent.get(newContent.size() - 1).equals(SLIDE_SEPARATOR)) {
                newContent.remove(newContent.size() - 1);
            }
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
        System.out.println("\nSalvando apresentação...");
        FileManipulator.saveArchive(this.fileName, this.content);
        System.out.println("Apresentação salva!");
    }
}