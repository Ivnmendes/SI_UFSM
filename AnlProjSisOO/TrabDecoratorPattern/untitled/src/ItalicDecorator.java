public class ItalicDecorator extends TextEditorDecorator {

    public ItalicDecorator(TextEditor editor) {
        super(editor);
    }

    @Override
    public String write(String text) {
        String baseText = super.write(text);
        return "<i>" + baseText + "</i>";
    }
}
