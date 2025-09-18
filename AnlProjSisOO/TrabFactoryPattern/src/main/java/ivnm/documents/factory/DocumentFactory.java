package ivnm.documents.factory;

import ivnm.documents.entities.AbstractDocument;

public interface DocumentFactory {

    AbstractDocument createDocument(String fileName);
}
