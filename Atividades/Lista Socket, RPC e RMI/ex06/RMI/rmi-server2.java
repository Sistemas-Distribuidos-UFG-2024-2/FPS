import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class CalculoSalarioImpl extends UnicastRemoteObject implements CalculoSalario {
    protected CalculoSalarioImpl() throws RemoteException {
        super();
    }

    public float calcularSalarioLiquido(String nome, char nivel, float salarioBruto, int dependentes) throws RemoteException {
        float desconto;
        switch (nivel) {
            case 'A':
                desconto = dependentes > 0 ? 0.08f : 0.03f;
                break;
            case 'B':
                desconto = dependentes > 0 ? 0.10f : 0.05f;
                break;
            case 'C':
                desconto = dependentes > 0 ? 0.15f : 0.08f;
                break;
            case 'D':
                desconto = dependentes > 0 ? 0.17f : 0.10f;
                break;
            default:
                return -1; // Nível inválido
        }
        return salarioBruto - (salarioBruto * desconto);
    }

    public static void main(String[] args) {
        try {
            Naming.rebind("rmi://localhost/CalculoSalarioService", new CalculoSalarioImpl());
            System.out.println("Servidor RMI rodando...");
        } catch (Exception e) {
            System.err.println("Erro no servidor: " + e);
        }
    }
}