import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Reajuste extends Remote {
    float calcularReajuste(String nome, String cargo, float salario) throws RemoteException;
}
