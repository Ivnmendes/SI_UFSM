public class UnderlineDecorator extends TextEditorDecorator{

    public UnderlineDecorator(TextEditor textEditor) {
        super(textEditor);
    }

    @Override
    public String write(String text) {
        String baseText = super.write(text);
        return "<u>" + baseText + "</u>";
    }
}
