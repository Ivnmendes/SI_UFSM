public class TextEditorDecorator extends TextEditor {

    protected TextEditor decoratedEditor;

    public TextEditorDecorator(TextEditor decoratedEditor) {
        this.decoratedEditor = decoratedEditor;
    }

    @Override
    public String write(String text) {
        return decoratedEditor.write(text);
    }
}
