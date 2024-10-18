import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CalculoSalario extends Remote {
    float calcularSalarioLiquido(String nome, char nivel, float salarioBruto, int dependentes) throws RemoteException;
}