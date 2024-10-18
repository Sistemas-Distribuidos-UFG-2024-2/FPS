import java.rmi.registry.LocateRegistry

fun main() {
    val registry = LocateRegistry.getRegistry("localhost")
    val aposentadoria = registry.lookup("Aposentadoria") as Aposentadoria

    val idade = 62
    val tempoServico = 26

    val resultado = aposentadoria.verificarAposentadoria(idade, tempoServico)
    if (resultado) {
        println("Pode se aposentar")
    } else {
        println("Não pode se aposentar")
    }
}
