package BankingSystem;

public interface BankAccount extends A{

    int ID();

    double withdrawMoney(double amount) throws BankingSystem.e;

    double balance();

    double sub(org.omg.CORBA.DoubleHolder x, org.omg.CORBA.DoubleHolder y);

}

