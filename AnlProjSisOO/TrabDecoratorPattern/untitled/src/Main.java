public class Main {
    public static void main(String[] args) {
        System.out.println("--- Teste do Padrão Decorator ---");

        System.out.println("\n1. Editor Simples:");
        TextEditor simpleEditor = new SimpleTextEditor();
        String text1 = simpleEditor.write("Olá, mundo!");
        System.out.println("Saída: " + text1);

        System.out.println("\n2. Editor com Negrito:");
        TextEditor boldEditor = new BoldDecorator(new SimpleTextEditor());
        String text2 = boldEditor.write("Este text está em negrito.");
        System.out.println("Saída: " + text2);

        System.out.println("\n3. Editor com Negrito e Itálico:");
        TextEditor boldItalicEditor = new ItalicDecorator(
                new BoldDecorator(
                        new SimpleTextEditor()
                )
        );
        String text3 = boldItalicEditor.write("Este text tem múltiplos formatos.");
        System.out.println("Saída: " + text3);

        System.out.println("\n4. Editor com todos os formatos (Sublinhado, Itálico e Negrito):");
        TextEditor completeEditor = new UnderlineDecorator(
                new ItalicDecorator(
                        new BoldDecorator(
                                new SimpleTextEditor()
                        )
                )
        );
        String text4 = completeEditor.write("Texto com formatação completa.");
        System.out.println("Saída: " + text4);
    }
}