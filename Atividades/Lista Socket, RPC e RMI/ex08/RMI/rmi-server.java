import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Banco extends Remote {
    float calcularCredito(float saldoMedio) throws RemoteException;
}
