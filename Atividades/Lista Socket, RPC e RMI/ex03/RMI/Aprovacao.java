import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Aprovacao extends Remote {
    String calcularAprovacao(double n1, double n2, double n3) throws RemoteException;
}