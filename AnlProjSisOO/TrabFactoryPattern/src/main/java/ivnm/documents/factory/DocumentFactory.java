package ivnm.documents.factory;

import ivnm.documents.entities.AbstractDocument;
import ivnm.documents.entities.Document;

public interface DocumentFactory {

    public AbstractDocument createDocument(String fileName);
}
