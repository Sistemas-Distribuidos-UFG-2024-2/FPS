import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ClassificacaoNadador extends Remote {
    String classificarNadador(int idade) throws RemoteException;
}