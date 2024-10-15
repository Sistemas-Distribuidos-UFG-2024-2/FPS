import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Maioridade extends Remote {
    String verificarMaioridade(String nome, String sexo, int idade) throws RemoteException;
}
