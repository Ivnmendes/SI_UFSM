public class BoldDecorator extends TextEditorDecorator {

    public BoldDecorator(TextEditor editor) {
        super(editor);
    }

    @Override
    public String write(String text) {
        String baseText = super.write(text);
        return "<b>" + baseText + "</b>";
    }
}
