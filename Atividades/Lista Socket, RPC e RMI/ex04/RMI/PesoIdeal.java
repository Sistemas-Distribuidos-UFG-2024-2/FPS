import java.rmi.Remote;
import java.rmi.RemoteException;

public interface PesoIdeal extends Remote {
    float calcularPesoIdeal(float altura, char sexo) throws RemoteException;
}