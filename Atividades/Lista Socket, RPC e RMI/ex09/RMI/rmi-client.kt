import java.rmi.registry.LocateRegistry

object ClienteBaralho {
    @JvmStatic
    fun main(args: Array<String>) {
        val registry = LocateRegistry.getRegistry("localhost")
        val baralho = registry.lookup("Baralho") as Baralho

        val valor = 10
        val naipe = 3

        val nomeCarta = baralho.obterNomeCarta(valor, naipe)
        println("A carta é: $nomeCarta")
    }
}
