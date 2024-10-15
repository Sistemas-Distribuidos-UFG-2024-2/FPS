import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ServidorMaioridade {
    public static void main(String[] args) {
        try {
            Maioridade maioridade = new MaioridadeImpl();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("Maioridade", maioridade);
            System.out.println("Servidor RMI de Maioridade pronto.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
