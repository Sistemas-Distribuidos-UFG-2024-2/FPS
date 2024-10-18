import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Baralho extends Remote {
    String obterNomeCarta(int valor, int naipe) throws RemoteException;
}
