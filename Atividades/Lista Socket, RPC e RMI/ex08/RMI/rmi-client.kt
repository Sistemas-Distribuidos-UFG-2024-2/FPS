import java.rmi.registry.LocateRegistry

object ClienteBanco {
    @JvmStatic
    fun main(args: Array<String>) {
        val registry = LocateRegistry.getRegistry("localhost")
        val banco = registry.lookup("Banco") as Banco

        val saldoMedio = 450.0f
        val credito = banco.calcularCredito(saldoMedio)
        println("Saldo médio: $saldoMedio, Crédito concedido: $credito")
    }
}
