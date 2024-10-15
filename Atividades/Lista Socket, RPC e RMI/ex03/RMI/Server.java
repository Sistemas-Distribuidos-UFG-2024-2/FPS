import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server {
    public static void main(String[] args) {
        try {
            Aprovacao aprovacao = new AprovacaoImpl();
            Registry registry = LocateRegistry.createRegistry(1099); // Porta padrão do RMI
            registry.bind("AprovacaoService", aprovacao);
            System.out.println("Servidor RMI está pronto.");
        } catch (Exception e) {
            System.err.println("Erro no servidor: " + e.toString());
            e.printStackTrace();
        }
    }
}