package ivnm.documents.entities;

import ivnm.enums.FileType;

import java.util.List;

public class DocumentSpreadSheet extends AbstractDocument {

    public DocumentSpreadSheet(String fileName) {
        super(fileName, FileType.SPREADSHEET);
    }

    @Override
    public void open() {

    }

    @Override
    public void edit() {

    }

    @Override
    public void save() {

    }
}
