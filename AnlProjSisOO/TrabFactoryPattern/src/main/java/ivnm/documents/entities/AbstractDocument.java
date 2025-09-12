package ivnm.documents.entities;

import ivnm.enums.FileType;

import java.util.ArrayList;
import java.util.List;

public abstract class AbstractDocument implements Document {

    protected String fileName;
    protected FileType fileType;
    protected List<String> content;

    public AbstractDocument(String fileName,  FileType fileType) {
        this.fileName = fileName;
        this.fileType = fileType;
        this.content = new ArrayList<String>();
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public FileType getFileType() {
        return fileType;
    }

    public void setFileType(FileType fileType) {
        this.fileType = fileType;
    }

    public List<String> getContent() {
        return content;
    }

    public void setContent(List<String> content) {
        this.content = content;
    }
}
