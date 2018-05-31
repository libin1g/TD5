public class ForTrain99 {
    public static void main(String[] args) {
        for (byte i = 1; i <= 9; ++i) {
            for (byte j = 1; j <= i; ++j) {
                //System.out.print(String.format("%d x %d = %d\t", j, i, j * i));
                System.out.print(j + " * " + i + " = " + j * i + "\t");
            }
            System.out.print('\n');
        }
    }
}
