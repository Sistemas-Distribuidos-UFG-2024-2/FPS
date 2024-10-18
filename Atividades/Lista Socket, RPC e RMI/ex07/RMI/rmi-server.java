import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Aposentadoria extends Remote {
    boolean verificarAposentadoria(int idade, int tempoServico) throws RemoteException;
}