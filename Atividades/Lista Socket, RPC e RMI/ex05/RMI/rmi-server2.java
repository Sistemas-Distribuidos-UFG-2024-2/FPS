import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class ClassificacaoNadadorImpl extends UnicastRemoteObject implements ClassificacaoNadador {
    protected ClassificacaoNadadorImpl() throws RemoteException {
        super();
    }

    public String classificarNadador(int idade) throws RemoteException {
        if (idade >= 5 && idade <= 7) {
            return "Infantil A (5-7 anos)";
        } else if (idade >= 8 && idade <= 10) {
            return "Infantil B (8-10 anos)";
        } else if (idade >= 11 && idade <= 13) {
            return "Juvenil A (11-13 anos)";
        } else if (idade >= 14 && idade <= 17) {
            return "Juvenil B (14-17 anos)";
        } else if (idade >= 18) {
            return "Adulto (maiores de 18 anos)";
        } else {
            return "Sem categoria (menos de 5 anos)";
        }
    }

    public static void main(String[] args) {
        try {
            Naming.rebind("rmi://localhost/ClassificacaoNadadorService", new ClassificacaoNadadorImpl());
            System.out.println("Servidor RMI iniciado...");
        } catch (Exception e) {
            System.err.println("Erro no servidor: " + e);
        }
    }
}