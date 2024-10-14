import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server {
    public static void main(String[] args) {
        try {
            Reajuste service = new ReajusteImpl();
            Registry registry = LocateRegistry.createRegistry(1099); // Porta padrão para RMI
            registry.rebind("Reajuste", service);
            System.out.println("Servidor RMI rodando...");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
