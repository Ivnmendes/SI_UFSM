package ivnm.documents.factory;

import ivnm.documents.entities.AbstractDocument;
import ivnm.documents.entities.Document;
import ivnm.documents.entities.DocumentPresentation;
import ivnm.documents.entities.DocumentSpreadSheet;

public class DocumentSpreadSheetFactory implements DocumentFactory {

    @Override
    public AbstractDocument createDocument(String fileName) {
        if (fileName == null || !fileName.contains(".")) {
            throw new IllegalArgumentException("Nome de arquivo inválido ou sem extensão.");
        }

        String extension = fileName.substring(fileName.lastIndexOf('.'));

        if (extension.equals(".xls")) {
            return new DocumentSpreadSheet(fileName);
        }

        throw new IllegalArgumentException("Tipo de arquivo incorreto: " + extension);
    }
}
