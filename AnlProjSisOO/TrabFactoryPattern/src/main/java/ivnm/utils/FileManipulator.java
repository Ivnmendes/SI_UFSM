package ivnm.utils;

import java.io.IOException;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public final class FileManipulator {

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

    public static void openArchive(String fileName, List<String> contentFile) {
        Path filePath = STORAGE_DIRECTORY.resolve(fileName);

        try {
            if (Files.notExists(filePath)) {
                Files.createFile(filePath);

                contentFile.clear();
                return;
            }

            contentFile.clear();
            contentFile.addAll(Files.readAllLines(filePath));
        } catch (IOException | RuntimeException ex) {
            System.out.printf("Erro ao ler o arquivo: {%s} \nErro: {%s}\n", fileName, ex.getMessage());
            return;
        }
    }

    public static void saveArchive(String fileName, List<String> contentFile) {
        Path filePath = STORAGE_DIRECTORY.resolve(fileName);


        try {
            Files.write(filePath, contentFile);
        } catch (IOException e) {
            System.err.println("Erro ao salvar as alterações no arquivo: " + e.getMessage());
        }
    }
}
