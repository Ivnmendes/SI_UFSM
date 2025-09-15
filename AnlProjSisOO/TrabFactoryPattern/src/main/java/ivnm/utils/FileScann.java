package ivnm.utils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.stream.Stream;

public final class FileScann {

    private static final Path STORAGE_DIRECTORY;
    static {
        try {
            Path userHome = Paths.get(System.getProperty("user.home"));
            STORAGE_DIRECTORY = userHome.resolve(".TrabFactoryPatternData");
            if (Files.notExists(STORAGE_DIRECTORY)) {
                Files.createDirectories(STORAGE_DIRECTORY);
            }
        } catch (IOException e) {
            throw new RuntimeException("Falha ao criar o diretório de armazenamento externo.", e);
        }
    }

    public static void listFiles(List<String> textList, List<String> spreadSheetList, List<String> presentationList) {
        try (Stream<Path> stream = Files.list(STORAGE_DIRECTORY)) {
            stream.forEach(path -> {
                String fileName = path.getFileName().toString();
                int lastDotIndex = fileName.lastIndexOf('.');

                if (lastDotIndex > 0) {
                    String fileExtension = fileName.substring(lastDotIndex);

                    switch (fileExtension) {
                        case ".txt":
                            textList.add(fileName);
                            break;
                        case ".xls":
                            spreadSheetList.add(fileName);
                            break;
                        case ".pst":
                            presentationList.add(fileName);
                            break;
                        default:
                            break;
                    }
                }
            });
        } catch (IOException e) {
            System.err.println("Erro ao listar os arquivos do diretório: " + e.getMessage());
        }
    }
}
